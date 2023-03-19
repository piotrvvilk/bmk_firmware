//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

#include <zephyr/kernel.h>
#include <zephyr/kernel_structs.h>
#include <zephyr/device.h>
#include <zephyr/types.h>
#include <zephyr/devicetree.h>
#include <zephyr/sys/byteorder.h>
#include <soc.h>
#include <assert.h>
#include <zephyr/spinlock.h>
#include <zephyr/settings/settings.h>

#include <zephyr/drivers/gpio.h>

#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>

#include <zephyr/bluetooth/services/bas.h>
#include <bluetooth/services/hids.h>
#include <zephyr/bluetooth/services/dis.h>

#include <zephyr/sys/printk.h>
#include <zephyr/logging/log.h>

#include "config_app.h"
#include "main.h"
#include "board.h"
#include "version.h"
#include "led.h"
#include "matrix_keyboard.h"
#include "display.h"
#include "i2c_devices.h"
#include "lis2dh/lis2dh.h"
#include "charger.h"

/*---------------------------------------------------------------------------*/
/* Definitions */
/*---------------------------------------------------------------------------*/
#define DEVICE_NAME     					CONFIG_BT_DEVICE_NAME
#define DEVICE_NAME_LEN 					(sizeof(DEVICE_NAME) - 1)

#define BASE_USB_HID_SPEC_VERSION   		0x0101

#define OUTPUT_REPORT_MAX_LEN            	1
#define OUTPUT_REPORT_BIT_MASK_CAPS_LOCK 	0x02
#define INPUT_REP_KEYS_REF_ID            	1
#define OUTPUT_REP_KEYS_REF_ID           	1
#define MODIFIER_KEY_POS                 	0
#define SHIFT_KEY_CODE                   	0x02
#define SCAN_CODE_POS                    	2
#define KEYS_MAX_LEN                    	(INPUT_REPORT_KEYS_MAX_LEN - SCAN_CODE_POS)

#define ADV_LED_BLINK_INTERVAL  			1000

/* Key used to accept or reject passkey value */
#define KEY_PAIRING_ACCEPT DK_BTN1_MSK
#define KEY_PAIRING_REJECT DK_BTN2_MSK

/* HIDs queue elements. */
#define HIDS_QUEUE_SIZE 10

/* ********************* */
/* Buttons configuration */

/* Note: The configuration below is the same as BOOT mode configuration
 * This simplifies the code as the BOOT mode is the same as REPORT mode.
 * Changing this configuration would require separate implementation of
 * BOOT mode report generation.
 */
#define KEY_CTRL_CODE_MIN 224 /* Control key codes - required 8 of them */
#define KEY_CTRL_CODE_MAX 231 /* Control key codes - required 8 of them */
#define KEY_CODE_MIN      0   /* Normal key codes */
#define KEY_CODE_MAX      101 /* Normal key codes */
#define KEY_PRESS_MAX     6   /* Maximum number of non-control keys
			       * pressed simultaneously
			       */

/* Number of bytes in key report
 *
 * 1B - control keys
 * 1B - reserved
 * rest - non-control keys
 */
#define INPUT_REPORT_KEYS_MAX_LEN (1 + 1 + KEY_PRESS_MAX)

/* Current report map construction requires exactly 8 buttons */
BUILD_ASSERT((KEY_CTRL_CODE_MAX - KEY_CTRL_CODE_MIN) + 1 == 8);

/* OUT report internal indexes.
 *
 * This is a position in internal report table and is not related to
 * report ID.
 */
enum {
	OUTPUT_REP_KEYS_IDX = 0
};

/* INPUT report internal indexes.
 *
 * This is a position in internal report table and is not related to
 * report ID.
 */
enum {
	INPUT_REP_KEYS_IDX = 0
};

LOG_MODULE_REGISTER(my_bmk_main,LOG_LEVEL_DBG);

/* HIDS instance. */
BT_HIDS_DEF(hids_obj, OUTPUT_REPORT_MAX_LEN, INPUT_REPORT_KEYS_MAX_LEN);


//---------------------------------------------------------------------------
// Local objects 
//---------------------------------------------------------------------------
static volatile bool is_adv;

static const struct bt_data ad[] = {
	BT_DATA_BYTES(BT_DATA_GAP_APPEARANCE,
		      (CONFIG_BT_DEVICE_APPEARANCE >> 0) & 0xff,
		      (CONFIG_BT_DEVICE_APPEARANCE >> 8) & 0xff),
	BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
	BT_DATA_BYTES(BT_DATA_UUID16_ALL, BT_UUID_16_ENCODE(BT_UUID_HIDS_VAL),
					  BT_UUID_16_ENCODE(BT_UUID_BAS_VAL)),
};

static const struct bt_data sd[] = {
	BT_DATA(BT_DATA_NAME_COMPLETE, DEVICE_NAME, DEVICE_NAME_LEN),
};

static struct conn_mode {
	struct bt_conn *conn;
	bool in_boot_mode;
} conn_mode[CONFIG_BT_HIDS_MAX_CLIENT_COUNT];

 static const uint8_t hello_world_str[] = {
 	0x0b,	/* Key h */
 	0x08,	/* Key e */
 	0x0f,	/* Key l */
 	0x0f,	/* Key l */
 	0x12,	/* Key o */
 	0x28,	/* Key Return */
 };

static const uint8_t shift_key[] = { 225 };

/* Current report status
 */
static struct keyboard_state {
	uint8_t ctrl_keys_state; /* Current keys state */
	uint8_t keys_state[KEY_PRESS_MAX];
} hid_keyboard_state;

static struct k_work pairing_work;
struct pairing_data_mitm {
	struct bt_conn *conn;
	unsigned int passkey;
};

K_MSGQ_DEFINE(mitm_queue, sizeof(struct pairing_data_mitm), CONFIG_BT_HIDS_MAX_CLIENT_COUNT, 4);

//---------------------------------------------------------------------------
// Global objects
//---------------------------------------------------------------------------
volatile uint32_t     	device_active_counter;		  
volatile uint32_t     	display_default_counter;		  
volatile uint32_t     	device_state;
volatile uint32_t 		lcd_pairing_state;
volatile uint32_t 		led_pairing_state;
uint32_t				bas_counter;

//---------------------------------------------------------------------------
// Implementation 
//---------------------------------------------------------------------------
//===============================================================================================================
static void advertising_start(void)
{
	int err;
	struct bt_le_adv_param *adv_param = BT_LE_ADV_PARAM(
						BT_LE_ADV_OPT_CONNECTABLE |
						BT_LE_ADV_OPT_ONE_TIME,
						BT_GAP_ADV_FAST_INT_MIN_2,
						BT_GAP_ADV_FAST_INT_MAX_2,
						NULL);

	err = bt_le_adv_start(adv_param, ad, ARRAY_SIZE(ad), sd, ARRAY_SIZE(sd));
	if (err) {
		if (err == -EALREADY) 
		{
			LOG_INF("Advertising continued\n");
		} 
		else 
		{
			LOG_INF("Advertising failed to start (err %d)\n", err);
		}

		return;
	}

	is_adv = true;
	#ifdef DEBUG_LOG_HID
		LOG_INF("Advertising successfully started\n");
	#endif
}

//===============================================================================================================
static void pairing_process(struct k_work *work)
{
	int err;
	struct pairing_data_mitm pairing_data;

	char addr[BT_ADDR_LE_STR_LEN];

	err = k_msgq_peek(&mitm_queue, &pairing_data);
	if (err) 
	{
		return;
	}

	bt_addr_le_to_str(bt_conn_get_dst(pairing_data.conn), addr, sizeof(addr));

	lcd_pairing_state = PAIRING;
	led_pairing_state = PAIRING;

	#ifdef DEBUG_LOG_HID
		LOG_INF("Passkey for %s: %06u\n", addr, pairing_data.passkey);
		LOG_INF("Press Button 1 to confirm, Button 2 to reject.\n");
	#endif
}

//===============================================================================================================
static void connected(struct bt_conn *conn, uint8_t err)
{
	char addr[BT_ADDR_LE_STR_LEN];

	bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));

	if (err) 
	{
		lcd_pairing_state = DISCONNECTED;
		led_pairing_state = DISCONNECTED;
		LOG_INF("Failed to connect to %s (%u)\n", addr, err);
		return;
	}

	LOG_INF("Connected %s\n", addr);
	
	lcd_pairing_state = CONNECTED;
	led_pairing_state = CONNECTED;

	err = bt_hids_connected(&hids_obj, conn);

	if (err) 
	{
		lcd_pairing_state = DISCONNECTED;
		led_pairing_state = DISCONNECTED;
		LOG_INF("Failed to notify HID service about connection\n");
		return;
	}

	for (size_t i = 0; i < CONFIG_BT_HIDS_MAX_CLIENT_COUNT; i++) 
	{
		if (!conn_mode[i].conn) 
		{
			conn_mode[i].conn = conn;
			conn_mode[i].in_boot_mode = false;
			break;
		}
	}

	for (size_t i = 0; i < CONFIG_BT_HIDS_MAX_CLIENT_COUNT; i++) 
	{
		if (!conn_mode[i].conn) 
		{
			advertising_start();
			return;
		}
	}

	is_adv = false;
}

//===============================================================================================================
static void disconnected(struct bt_conn *conn, uint8_t reason)
{
	int err;
	bool is_any_dev_connected = false;
	char addr[BT_ADDR_LE_STR_LEN];

	bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));
	
	#ifdef DEBUG_LOG_HID
		LOG_INF("Disconnected from %s (reason %u)\n", addr, reason);
	#endif

	err = bt_hids_disconnected(&hids_obj, conn);

	if (err) 
	{
		#ifdef DEBUG_LOG_HID
			LOG_INF("Failed to notify HID service about disconnection\n");
		#endif
	}

	for (size_t i = 0; i < CONFIG_BT_HIDS_MAX_CLIENT_COUNT; i++) 
	{
		if (conn_mode[i].conn == conn) 
		{
			conn_mode[i].conn = NULL;
		} 
		else 
		{
			if (conn_mode[i].conn) 
			{
				is_any_dev_connected = true;
			}
		}
	}

	if (!is_any_dev_connected) 
	{
		//dk_set_led_off(CON_STATUS_LED);
	}

	advertising_start();
}

//===============================================================================================================
static void security_changed(struct bt_conn *conn, bt_security_t level, enum bt_security_err err)
{
	char addr[BT_ADDR_LE_STR_LEN];

	bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));

	if (!err) 
	{
		#ifdef DEBUG_LOG_HID
			LOG_INF("Security changed: %s level %u\n", addr, level);
		#endif
	} 
	else 
	{
		#ifdef DEBUG_LOG_HID
			LOG_INF("Security failed: %s level %u err %d\n", addr, level,err);
		#endif
	}
}

//===============================================================================================================
BT_CONN_CB_DEFINE(conn_callbacks) = {
	.connected = connected,
	.disconnected = disconnected,
	.security_changed = security_changed,
};

//===============================================================================================================
static void caps_lock_handler(const struct bt_hids_rep *rep)
{
	uint8_t report_val = ((*rep->data) & OUTPUT_REPORT_BIT_MASK_CAPS_LOCK) ? 1 : 0;
	//dk_set_led(LED_CAPS_LOCK, report_val);
}

//===============================================================================================================
static void hids_outp_rep_handler(struct bt_hids_rep *rep, struct bt_conn *conn, bool write)
{
	char addr[BT_ADDR_LE_STR_LEN];

	if (!write) 
	{
		#ifdef DEBUG_LOG_HID
			LOG_INF("Output report read\n");
		#endif
		return;
	};

	bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));
	#ifdef DEBUG_LOG_HID
		LOG_INF("Output report has been received %s\n", addr);
	#endif
	caps_lock_handler(rep);
}

//===============================================================================================================
static void hids_boot_kb_outp_rep_handler(struct bt_hids_rep *rep, struct bt_conn *conn, bool write)
{
	char addr[BT_ADDR_LE_STR_LEN];

	if (!write)
	{
		#ifdef DEBUG_LOG_HID
			LOG_INF("Output report read\n");
		#endif
		return;
	};

	bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));
	#ifdef DEBUG_LOG_HID
		LOG_INF("Boot Keyboard Output report has been received %s\n", addr);
	#endif
	caps_lock_handler(rep);
}

//===============================================================================================================
static void hids_pm_evt_handler(enum bt_hids_pm_evt evt, struct bt_conn *conn)
{
	char addr[BT_ADDR_LE_STR_LEN];
	size_t i;

	for(i = 0; i < CONFIG_BT_HIDS_MAX_CLIENT_COUNT; i++) 
	{
		if (conn_mode[i].conn == conn) 
		{
			break;
		}
	}

	if(i >= CONFIG_BT_HIDS_MAX_CLIENT_COUNT) 
	{
		LOG_INF("Cannot find connection handle when processing PM");
		return;
	}

	bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));

	switch (evt) 
	{
		case BT_HIDS_PM_EVT_BOOT_MODE_ENTERED:
			LOG_INF("Boot mode entered %s\n", addr);
			conn_mode[i].in_boot_mode = true;
			break;

		case BT_HIDS_PM_EVT_REPORT_MODE_ENTERED:
			LOG_INF("Report mode entered %s\n", addr);
			conn_mode[i].in_boot_mode = false;
			break;

		default:
			break;
	}
}

//===============================================================================================================
static void hid_init(void)
{
	int err;
	struct bt_hids_init_param    hids_init_obj = { 0 };
	struct bt_hids_inp_rep       *hids_inp_rep;
	struct bt_hids_outp_feat_rep *hids_outp_rep;

	static const uint8_t report_map[] = {
		0x05, 0x01,       /* Usage Page (Generic Desktop) */
		0x09, 0x06,       /* Usage (Keyboard) */
		0xA1, 0x01,       /* Collection (Application) */

		/* Keys */
#if INPUT_REP_KEYS_REF_ID
		0x85, INPUT_REP_KEYS_REF_ID,
#endif
		0x05, 0x07,       /* Usage Page (Key Codes) */
		0x19, 0xe0,       /* Usage Minimum (224) */
		0x29, 0xe7,       /* Usage Maximum (231) */
		0x15, 0x00,       /* Logical Minimum (0) */
		0x25, 0x01,       /* Logical Maximum (1) */
		0x75, 0x01,       /* Report Size (1) */
		0x95, 0x08,       /* Report Count (8) */
		0x81, 0x02,       /* Input (Data, Variable, Absolute) */

		0x95, 0x01,       /* Report Count (1) */
		0x75, 0x08,       /* Report Size (8) */
		0x81, 0x01,       /* Input (Constant) reserved byte(1) */

		0x95, 0x06,       /* Report Count (6) */
		0x75, 0x08,       /* Report Size (8) */
		0x15, 0x00,       /* Logical Minimum (0) */
		0x25, 0x65,       /* Logical Maximum (101) */
		0x05, 0x07,       /* Usage Page (Key codes) */
		0x19, 0x00,       /* Usage Minimum (0) */
		0x29, 0x65,       /* Usage Maximum (101) */
		0x81, 0x00,       /* Input (Data, Array) Key array(6 bytes) */

		/* LED */
#if OUTPUT_REP_KEYS_REF_ID
		0x85, OUTPUT_REP_KEYS_REF_ID,
#endif
		0x95, 0x05,       /* Report Count (5) */
		0x75, 0x01,       /* Report Size (1) */
		0x05, 0x08,       /* Usage Page (Page# for LEDs) */
		0x19, 0x01,       /* Usage Minimum (1) */
		0x29, 0x05,       /* Usage Maximum (5) */
		0x91, 0x02,       /* Output (Data, Variable, Absolute), */
				  /* Led report */
		0x95, 0x01,       /* Report Count (1) */
		0x75, 0x03,       /* Report Size (3) */
		0x91, 0x01,       /* Output (Data, Variable, Absolute), */
				  /* Led report padding */

		0xC0              /* End Collection (Application) */
	};

	hids_init_obj.rep_map.data = report_map;
	hids_init_obj.rep_map.size = sizeof(report_map);

	hids_init_obj.info.bcd_hid = BASE_USB_HID_SPEC_VERSION;
	hids_init_obj.info.b_country_code = 0x00;
	hids_init_obj.info.flags = (BT_HIDS_REMOTE_WAKE |
				    BT_HIDS_NORMALLY_CONNECTABLE);

	hids_inp_rep =
		&hids_init_obj.inp_rep_group_init.reports[INPUT_REP_KEYS_IDX];
	hids_inp_rep->size = INPUT_REPORT_KEYS_MAX_LEN;
	hids_inp_rep->id = INPUT_REP_KEYS_REF_ID;
	hids_init_obj.inp_rep_group_init.cnt++;

	hids_outp_rep =
		&hids_init_obj.outp_rep_group_init.reports[OUTPUT_REP_KEYS_IDX];
	hids_outp_rep->size = OUTPUT_REPORT_MAX_LEN;
	hids_outp_rep->id = OUTPUT_REP_KEYS_REF_ID;
	hids_outp_rep->handler = hids_outp_rep_handler;
	hids_init_obj.outp_rep_group_init.cnt++;

	hids_init_obj.is_kb = true;
	hids_init_obj.boot_kb_outp_rep_handler = hids_boot_kb_outp_rep_handler;
	hids_init_obj.pm_evt_handler = hids_pm_evt_handler;

	err = bt_hids_init(&hids_obj, &hids_init_obj);
	__ASSERT(err == 0, "HIDS initialization failed\n");
}

//===============================================================================================================
static void auth_passkey_display(struct bt_conn *conn, unsigned int passkey)
{
	char addr[BT_ADDR_LE_STR_LEN];

	bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));

	LOG_INF("Passkey for %s: %06u\n", addr, passkey);
}

//===============================================================================================================
static void auth_passkey_confirm(struct bt_conn *conn, unsigned int passkey)
{
	int err;

	struct pairing_data_mitm pairing_data;

	pairing_data.conn    = bt_conn_ref(conn);
	pairing_data.passkey = passkey;

	err = k_msgq_put(&mitm_queue, &pairing_data, K_NO_WAIT);
	if (err) 
	{
		//printk("Pairing queue is full. Purge previous data.\n");
	}

	/* In the case of multiple pairing requests, trigger
	 * pairing confirmation which needed user interaction only
	 * once to avoid display information about all devices at
	 * the same time. Passkey confirmation for next devices will
	 * be proccess from queue after handling the earlier ones.
	 */
	if (k_msgq_num_used_get(&mitm_queue) == 1) 
	{
		k_work_submit(&pairing_work);
	}
}

//===============================================================================================================
static void auth_cancel(struct bt_conn *conn)
{
	char addr[BT_ADDR_LE_STR_LEN];

	bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));

	lcd_pairing_state = NO_ACTION;
	led_pairing_state = NO_ACTION; 
	device_theme=THEME_INFO;
	device_state=BMK_ACTIVE;
	
	#ifdef DEBUG_LOG_HID
		LOG_INF("Pairing cancelled: %s\n", addr);
	#endif
}

//===============================================================================================================
static void pairing_complete(struct bt_conn *conn, bool bonded)
{
	char addr[BT_ADDR_LE_STR_LEN];

	bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));

	lcd_pairing_state = PAIRED;
	led_pairing_state = PAIRED; 
	display_default_time_reset();
	
	#ifdef DEBUG_LOG_HID
		LOG_INF("Pairing completed: %s, bonded: %d\n", addr, bonded);
	#endif
}

//===============================================================================================================
static void pairing_failed(struct bt_conn *conn, enum bt_security_err reason)
{
	char addr[BT_ADDR_LE_STR_LEN];
	struct pairing_data_mitm pairing_data;

	if (k_msgq_peek(&mitm_queue, &pairing_data) != 0) 
	{
		return;
	}

	if (pairing_data.conn == conn) 
	{
		bt_conn_unref(pairing_data.conn);
		k_msgq_get(&mitm_queue, &pairing_data, K_NO_WAIT);
	}

	bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));

	lcd_pairing_state = NO_ACTION;
	led_pairing_state = NO_ACTION; 
	device_theme=THEME_INFO;
	device_state=BMK_ACTIVE;
	#ifdef DEBUG_LOG_HID
		LOG_INF("Pairing failed conn: %s, reason %d\n", addr, reason);
	#endif
}

//===============================================================================================================
static struct bt_conn_auth_cb conn_auth_callbacks = {
	.passkey_display = auth_passkey_display,
	.passkey_confirm = auth_passkey_confirm,
	.cancel = auth_cancel,
};

//===============================================================================================================
static struct bt_conn_auth_info_cb conn_auth_info_callbacks = {
	.pairing_complete = pairing_complete,
	.pairing_failed = pairing_failed
};

//===============================================================================================================
/** @brief Function process keyboard state and sends it
 *
 *  @param pstate     The state to be sent
 *  @param boot_mode  Information if boot mode protocol is selected.
 *  @param conn       Connection handler
 *
 *  @return 0 on success or negative error code.
 */
static int key_report_con_send(const struct keyboard_state *state, bool boot_mode, struct bt_conn *conn)
{
	int err = 0;
	uint8_t  data[INPUT_REPORT_KEYS_MAX_LEN];
	uint8_t *key_data;
	const uint8_t *key_state;
	size_t n;

	data[0] = state->ctrl_keys_state;
	data[1] = 0;
	key_data = &data[2];
	key_state = state->keys_state;

	for (n = 0; n < KEY_PRESS_MAX; ++n) 
	{
		*key_data++ = *key_state++;
	}

	if(boot_mode) 
	{
		err = bt_hids_boot_kb_inp_rep_send(&hids_obj, conn, data, sizeof(data), NULL);
	} 
	else 
	{
		err = bt_hids_inp_rep_send(&hids_obj, conn,	INPUT_REP_KEYS_IDX, data, sizeof(data), NULL);
	}

	return err;
}

//===============================================================================================================
/** @brief Function process and send keyboard state to all active connections
 *
 * Function process global keyboard state and send it to all connected
 * clients.
 *
 * @return 0 on success or negative error code.
 */
static int key_report_send(void)
{
	for (size_t i = 0; i < CONFIG_BT_HIDS_MAX_CLIENT_COUNT; i++) 
	{
		if(conn_mode[i].conn) 
		{
			int err;

			err = key_report_con_send(&hid_keyboard_state, conn_mode[i].in_boot_mode, conn_mode[i].conn);
			if (err) 
			{
				LOG_INF("Key report send error: %d\n", err);
				return err;
			}
		}
	}
	return 0;
}

//===============================================================================================================
/** @brief Change key code to ctrl code mask
 *
 *  Function changes the key code to the mask in the control code
 *  field inside the raport.
 *  Returns 0 if key code is not a control key.
 *
 *  @param key Key code
 *
 *  @return Mask of the control key or 0.
 */
static uint8_t button_ctrl_code(uint8_t key)
{
	if (KEY_CTRL_CODE_MIN <= key && key <= KEY_CTRL_CODE_MAX) 
	{
		return (uint8_t)(1U << (key - KEY_CTRL_CODE_MIN));
	}
	return 0;
}

//===============================================================================================================
static int hid_kbd_state_key_set(uint8_t key)
{
	uint8_t ctrl_mask = button_ctrl_code(key);

	if (ctrl_mask) 
	{
		hid_keyboard_state.ctrl_keys_state |= ctrl_mask;
		return 0;
	}

	for (size_t i = 0; i < KEY_CTRL_CODE_MAX; ++i) 
	{
		if (hid_keyboard_state.keys_state[i] == 0) 
		{
			hid_keyboard_state.keys_state[i] = key;
			return 0;
		}
	}
	/* All slots busy */
	return -EBUSY;
}

//===============================================================================================================
static int hid_kbd_state_key_clear(uint8_t key)
{
	uint8_t ctrl_mask = button_ctrl_code(key);

	if (ctrl_mask) 
	{
		hid_keyboard_state.ctrl_keys_state &= ~ctrl_mask;
		return 0;
	}

	for (size_t i = 0; i < KEY_CTRL_CODE_MAX; ++i) 
	{
		if (hid_keyboard_state.keys_state[i] == key) 
		{
			hid_keyboard_state.keys_state[i] = 0;
			return 0;
		}
	}
	/* Key not found */
	return -EINVAL;
}

//===============================================================================================================
// static void button_text_changed(bool down)
// {
// 	static const uint8_t *chr = hello_world_str;

// 	if (down) {
// 		hid_buttons_press(chr, 1);
// 	} else {
// 		hid_buttons_release(chr, 1);
// 		if (++chr == (hello_world_str + sizeof(hello_world_str))) {
// 			chr = hello_world_str;
// 		}
// 	}
// }

// //===============================================================================================================
// static void button_shift_changed(bool down)
// {
// 	if (down) {
// 		hid_buttons_press(shift_key, 1);
// 	} else {
// 		hid_buttons_release(shift_key, 1);
// 	}
// }

//===============================================================================================================
void num_comp_reply(bool accept)
{
	struct pairing_data_mitm pairing_data;
	struct bt_conn *conn;

	if (k_msgq_get(&mitm_queue, &pairing_data, K_NO_WAIT) != 0) 
	{
		return;
	}

	conn = pairing_data.conn;

	if (accept) 
	{
		bt_conn_auth_passkey_confirm(conn);
		LOG_INF("Numeric Match");
	} 
	else 
	{
		bt_conn_auth_cancel(conn);
		LOG_INF("Numeric Reject");
	}

	bt_conn_unref(pairing_data.conn);

	if (k_msgq_num_used_get(&mitm_queue)) 
	{
		k_work_submit(&pairing_work);
	}
}

//===============================================================================================================
// static void button_changed(uint32_t button_state, uint32_t has_changed)
// {
// 	static bool pairing_button_pressed;

// 	uint32_t buttons = button_state & has_changed;

// 	if (k_msgq_num_used_get(&mitm_queue)) {
// 		if (buttons & KEY_PAIRING_ACCEPT) {
// 			pairing_button_pressed = true;
// 			num_comp_reply(true);

// 			return;
// 		}

// 		if (buttons & KEY_PAIRING_REJECT) {
// 			pairing_button_pressed = true;
// 			num_comp_reply(false);

// 			return;
// 		}
// 	}

// 	/* Do not take any action if the pairing button is released. */
// 	if (pairing_button_pressed &&
// 	    (has_changed & (KEY_PAIRING_ACCEPT | KEY_PAIRING_REJECT))) {
// 		pairing_button_pressed = false;

// 		return;
// 	}

// 	if (has_changed & KEY_TEXT_MASK) {
// 		button_text_changed((button_state & KEY_TEXT_MASK) != 0);
// 	}
// 	if (has_changed & KEY_SHIFT_MASK) {
// 		button_shift_changed((button_state & KEY_SHIFT_MASK) != 0);
// 	}
// #if CONFIG_NFC_OOB_PAIRING
// 	if (has_changed & KEY_ADV_MASK) {
// 		size_t i;

// 		for (i = 0; i < CONFIG_BT_HIDS_MAX_CLIENT_COUNT; i++) {
// 			if (!conn_mode[i].conn) {
// 				advertising_start();
// 				return;
// 			}
// 		}

// 		printk("Cannot start advertising, all connections slots are"
// 		       " taken\n");
// 	}
// #endif
// }

//===============================================================================================================
static void bas_notify(void)
{
	bt_bas_set_battery_level(max17048_charge);
}

//===============================================================================================================
/** @brief Press a button and send report
 *
 *  @note Functions to manipulate hid state are not reentrant
 *  @param keys
 *  @param cnt
 *
 *  @return 0 on success or negative error code.
 */
int hid_buttons_press(const uint8_t *keys, size_t cnt)
{
	while (cnt--)
	{
		int err;

		err = hid_kbd_state_key_set(*keys++);
		if (err) 
		{
			LOG_INF("Cannot set selected key.\n");
			return err;
		}
	}

	return key_report_send();
}

//===============================================================================================================
/** @brief Release the button and send report
 *
 *  @note Functions to manipulate hid state are not reentrant
 *  @param keys
 *  @param cnt
 *
 *  @return 0 on success or negative error code.
 */
int hid_buttons_release(const uint8_t *keys, size_t cnt)
{
	while (cnt--) 
	{
		int err;

		err = hid_kbd_state_key_clear(*keys++);
		if (err) 
		{
			LOG_INF("Cannot clear selected key.\n");
			return err;
		}
	}

	return key_report_send();
}

// 	/* Do not take any action if the pairing button is released. */
// 	if (pairing_button_pressed &&
// 	    (has_changed & (KEY_PAIRING_ACCEPT | KEY_PAIRING_REJECT))) {
// 		pairing_button_pressed = false;

// 		return;
// 	}

// 	if (has_changed & KEY_TEXT_MASK) {
// 		button_text_changed((button_state & KEY_TEXT_MASK) != 0);
// 	}
// 	if (has_changed & KEY_SHIFT_MASK) {
// 		button_shift_changed((button_state & KEY_SHIFT_MASK) != 0);
// 	}
// #if CONFIG_NFC_OOB_PAIRING
// 	if (has_changed & KEY_ADV_MASK) {
// 		size_t i;

// 		for (i = 0; i < CONFIG_BT_HIDS_MAX_CLIENT_COUNT; i++) {
// 			if (!conn_mode[i].conn) {
// 				advertising_start();
// 				return;
// 			}
// 		}

// 		printk("Cannot start advertising, all connections slots are"
// 		       " taken\n");
// 	}
// #endif
// }

//===============================================================================================================
void device_active_time_reset(void)								//start counting time to standby 
{
	device_active_counter=1;
}

//===============================================================================================================
void device_active_time_stop(void)								//stop counting 
{
	device_active_counter=0;
}

//===============================================================================================================
void display_default_time_reset(void)							//start counting time to back display to default state
{
	display_default_counter=1;
}

//===============================================================================================================
void display_default_time_stop(void)							//stop counting 
{
	display_default_counter=0;
}

//---------------------------------------------------------------------------
// Threads 
//---------------------------------------------------------------------------
#ifdef USE_MATRIX_KEYBOARD
	K_THREAD_DEFINE(thread_keyboard_id, THREAD_KEYBOARD_STACKSIZE, thread_keyboard, NULL, NULL, NULL, THREAD_KEYBOARD_PRIORITY, 0, 0);
#endif

#ifdef USE_LED
	K_THREAD_DEFINE(thread_led_id, THREAD_LED_STACKSIZE, thread_led, NULL, NULL, NULL, THREAD_LED_PRIORITY, 0, 0);
#endif 

#ifdef USE_DISPLAY
	K_THREAD_DEFINE(thread_lcd_id, THREAD_LCD_STACKSIZE, thread_lcd, NULL, NULL, NULL, THREAD_LCD_PRIORITY, 0, 0);
#endif

#if defined(USE_LIS2DH) || defined(USE_MAX17048)
	K_THREAD_DEFINE(thread_i2c_devices_id, THREAD_I2C_DEVICES_STACKSIZE, thread_i2c_devices, NULL, NULL, NULL, THREAD_I2C_DEVICES_PRIORITY, 0, 0);
#endif

#ifdef USE_CHARGER
	K_THREAD_DEFINE(thread_charger_id, THREAD_CHARGER_STACKSIZE, thread_charger, NULL, NULL, NULL, THREAD_CHARGER_PRIORITY, 0, 0);
#endif


//---------------------------------------------------------------------------
// Main  
//---------------------------------------------------------------------------
void main(void)
{
	int err;
	
	LOG_INF("START BMK DEVICE\n");
	LOG_INF("%s\n",STR_VER);
	LOG_INF("%s\n",STR_DATE);

//-------------------------------------------------------------------------- GPIO
	err = gpio_init();
	LOG_INF("GPIO init: %d\n", err);
	if(err) 
	{
		LOG_INF("GPIO init failed (err %d)\n", err);
		return;
	}

//-------------------------------------------------------------------------- BLE
	#ifdef USE_BLE	
		err = bt_conn_auth_cb_register(&conn_auth_callbacks);
		if(err) 
		{
			LOG_INF("Failed to register authorization callbacks.\n");
			return;
		}

		err = bt_conn_auth_info_cb_register(&conn_auth_info_callbacks);
		if(err) 
		{
			LOG_INF("Failed to register authorization info callbacks.\n");
			return;
		}

		err = bt_enable(NULL);
		if(err) 
		{
			LOG_INF("Bluetooth init failed (err %d)\n", err);
			return;
		}

		LOG_INF("Bluetooth initialized\n");

		hid_init();

		if (IS_ENABLED(CONFIG_SETTINGS)) 
		{
			settings_load();
		}

		advertising_start();

		k_work_init(&pairing_work, pairing_process);
	#endif
	
//===============================================================================================================
//===============================================================================================================
	while (1) 
	{

//-------------------------------------------------------------- lis2dh interrupt		
		#ifdef USE_LIS2DH 
			if(lis_int1_flag)										
			{
				lis_int1_flag=false;
				release_interrupt();		
				device_active_time_reset();							//start counting
				device_state=BMK_ACTIVE;
				
				if(device_theme==NO_THEME)							//restore last theme
				{
					device_theme = last_theme;
				}
			}	
		#endif	
//--------------------------------------------------------------- timeout
		#ifdef USE_LED 
			if(device_active_counter>0) device_active_counter++;	

			if(device_active_counter>DEVICE_ACTIVE_TIME)			//timeout - display and led power off                  QUESTION: MUTEX?
			{
				#ifdef DEBUG_LOG_DEVICE
					LOG_INF("Timeout\n");		
				#endif
				
				device_active_time_stop();
				last_theme=device_theme;							//remember last theme 
				device_theme=NO_THEME;								//turn off display, led strip and led pwm
				device_state=BMK_STANDBY; 
				led_pwm_charged_counter=0;
			}
		#endif

//--------------------------------------------------------------- display timeout (pairing mode)
		if(display_default_counter>0) display_default_counter++;

		if(display_default_counter>DISPLAY_TO_DEFAULT_TIME)			
		{
			device_state=BMK_ACTIVE;
			device_theme = THEME_INFO;
			lcd_pairing_state=NO_ACTION;
			led_pairing_state=NO_ACTION;

			refresh_screen_flag=true;
			refresh_led_flag=true;

			display_default_time_stop();
			#ifdef DEBUG_LOG_DEVICE
				LOG_INF("Timeout display\n");		
			#endif
		}	

//--------------------------------------------------------------- refresh battery info
		bas_counter++;
		if(bas_counter>BAS_TIME)
		{
			bas_counter=0;
			bas_notify();
		}


//--------------------------------------------------------------- 
		k_sleep(K_MSEC(1000));
    }
	
}

//===============================================================================================================
//===============================================================================================================

#include <zephyr/types.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/byteorder.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <soc.h>

#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>

#include <zephyr/settings/settings.h>

#include <zephyr/sys/printk.h>
#include <zephyr/logging/log.h>

#include "board.h"

//#define USER_BUTTON             DK_BTN1_MSK

const struct gpio_dt_spec led_red = GPIO_DT_SPEC_GET(LEDR_NODE, gpios);
const struct gpio_dt_spec led_green = GPIO_DT_SPEC_GET(LEDG_NODE, gpios);
const struct gpio_dt_spec led_blue = GPIO_DT_SPEC_GET(LEDB_NODE, gpios);

const struct gpio_dt_spec enusbdet = GPIO_DT_SPEC_GET(ENUSBDET_NODE, gpios);
const struct gpio_dt_spec usbdet = GPIO_DT_SPEC_GET(USBDET_NODE, gpios);

const struct gpio_dt_spec chrgdet = GPIO_DT_SPEC_GET(CHRGDET_NODE, gpios);
const struct gpio_dt_spec chrgen = GPIO_DT_SPEC_GET(CHRGEN_NODE, gpios);

const struct gpio_dt_spec vleden = GPIO_DT_SPEC_GET(VLEDEN_NODE, gpios);

const struct gpio_dt_spec buzzer = GPIO_DT_SPEC_GET(BUZZER_NODE, gpios);

const struct gpio_dt_spec accelint1 = GPIO_DT_SPEC_GET(ACCEL1_NODE, gpios);
const struct gpio_dt_spec accelint2 = GPIO_DT_SPEC_GET(ACCEL2_NODE, gpios);

const struct gpio_dt_spec col1 = GPIO_DT_SPEC_GET(COL1_NODE, gpios);
const struct gpio_dt_spec col2 = GPIO_DT_SPEC_GET(COL2_NODE, gpios);
const struct gpio_dt_spec col3 = GPIO_DT_SPEC_GET(COL3_NODE, gpios);
const struct gpio_dt_spec col4 = GPIO_DT_SPEC_GET(COL4_NODE, gpios);
const struct gpio_dt_spec row1 = GPIO_DT_SPEC_GET(ROW1_NODE, gpios);
const struct gpio_dt_spec row2 = GPIO_DT_SPEC_GET(ROW2_NODE, gpios);
const struct gpio_dt_spec row3 = GPIO_DT_SPEC_GET(ROW3_NODE, gpios);

const struct gpio_dt_spec disprst = GPIO_DT_SPEC_GET(DISPRST_NODE, gpios);
const struct gpio_dt_spec dispbk = GPIO_DT_SPEC_GET(DISPBK_NODE, gpios);
const struct gpio_dt_spec dispdc = GPIO_DT_SPEC_GET(DISPDC_NODE, gpios);
const struct gpio_dt_spec dispcs = GPIO_DT_SPEC_GET(DISPCS_NODE, gpios);
//const struct gpio_dt_spec dispdata = GPIO_DT_SPEC_GET(DISPDATA_NODE, gpios);
//const struct gpio_dt_spec dispclk = GPIO_DT_SPEC_GET(DISPCLK_NODE, gpios);

//==================================================================================================================================================
int gpio_init(void)
{
	int ret;

	ret=0;

	if(!device_is_ready(col1.port)) return -1;
	if(!device_is_ready(col2.port)) return -1;
	if(!device_is_ready(col3.port)) return -1;
	if(!device_is_ready(col4.port)) return -1;
	if(!device_is_ready(row1.port)) return -1;
	if(!device_is_ready(row2.port)) return -1;
	if(!device_is_ready(row3.port)) return -1;				//czy to dla wszystkich pinow?

	ret = gpio_pin_configure_dt(&led_red, GPIO_OUTPUT);
	if(ret!=0) return ret;
	gpio_pin_set_dt(&led_red,0);

	ret = gpio_pin_configure_dt(&led_green, GPIO_OUTPUT);
	if(ret!=0) return ret;
	gpio_pin_set_dt(&led_green,0);

	ret = gpio_pin_configure_dt(&led_blue, GPIO_OUTPUT);
	if(ret!=0) return ret;
	gpio_pin_set_dt(&led_blue,0);

	ret = gpio_pin_configure_dt(&buzzer, GPIO_OUTPUT);
	if(ret!=0) return ret;
	gpio_pin_set_dt(&buzzer,0);

	ret = gpio_pin_configure_dt(&vleden, GPIO_OUTPUT);
	if(ret!=0) return ret;
	gpio_pin_set_dt(&vleden,0);

	ret = gpio_pin_configure_dt(&enusbdet, GPIO_OUTPUT);
	if(ret!=0) return ret;
	gpio_pin_set_dt(&enusbdet,0);

	ret = gpio_pin_configure_dt(&usbdet, GPIO_INPUT);
	if(ret!=0) return ret;
	
	ret = gpio_pin_configure_dt(&chrgen, GPIO_OUTPUT);
	if(ret!=0) return ret;
	gpio_pin_set_dt(&chrgen,0);

	ret = gpio_pin_configure_dt(&chrgdet, GPIO_INPUT);
	if(ret!=0) return ret;
		
	// ret = gpio_pin_configure_dt(&disprst, GPIO_OUTPUT);
	// if(ret!=0) return ret;
	// gpio_pin_set_dt(&disprst,1);

	ret = gpio_pin_configure_dt(&dispbk, GPIO_OUTPUT);
	if(ret!=0) return ret;
	gpio_pin_set_dt(&dispbk,0);

	// ret = gpio_pin_configure_dt(&dispdc, GPIO_OUTPUT);
	// if(ret!=0) return ret;
	// gpio_pin_set_dt(&dispdc,0);

	// ret = gpio_pin_configure_dt(&dispcs, GPIO_OUTPUT);
	// if(ret!=0) return ret;
	// gpio_pin_set_dt(&dispcs,1);

	ret = gpio_pin_configure_dt(&accelint1, GPIO_INPUT);
	if(ret!=0) return ret;

	ret = gpio_pin_configure_dt(&accelint2, GPIO_INPUT);
	if(ret!=0) return ret;

	ret = gpio_pin_configure_dt(&col1, GPIO_OUTPUT);
	if(ret!=0) return ret;
	gpio_pin_set_dt(&col1,1);

	ret = gpio_pin_configure_dt(&col2, GPIO_OUTPUT);
	if(ret!=0) return ret;
	gpio_pin_set_dt(&col2,1);
	
	ret = gpio_pin_configure_dt(&col3, GPIO_OUTPUT);
	if(ret!=0) return ret;
	gpio_pin_set_dt(&col3,1);

	ret = gpio_pin_configure_dt(&col4, GPIO_OUTPUT);
	if(ret!=0) return ret;
	gpio_pin_set_dt(&col4,1);

	ret = gpio_pin_configure_dt(&row1, GPIO_INPUT| GPIO_PULL_UP);
	if(ret!=0) return ret;
	ret = gpio_pin_configure_dt(&row2, GPIO_INPUT| GPIO_PULL_UP);
	if(ret!=0) return ret;
	ret = gpio_pin_configure_dt(&row3, GPIO_INPUT| GPIO_PULL_UP);
	if(ret!=0) return ret;

	return ret;
}

//==================================================================================================================================================

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
#include <zephyr/drivers/led_strip.h>
#include <zephyr/drivers/led.h>

#include <zephyr/sys/printk.h>
#include <zephyr/logging/log.h>

#include "board.h"
#include "main.h"
#include "led.h"
#include "matrix_keyboard.h"
#include "config_app.h"
#include "common.h"

LOG_MODULE_REGISTER(my_bmk_led,LOG_LEVEL_DBG);

//--------------------------------------------------------------------------- LED STRIP
#define STRIP_NODE			DT_ALIAS(led_strip)
#define STRIP_NUM_PIXELS	DT_PROP(DT_ALIAS(led_strip), chain_length)


#define RGB(_r, _g, _b) { .r = (_r), .b = (_b), .g = (_g) }

static const struct led_rgb colors[] = {
	RGB(0x00, 0x00, 0x00), 						/* black */
	RGB(0x20, 0x2F, 0x2F), 						/* white */
	RGB(0x2f, 0x00, 0x00), 						/* red */
	RGB(0x00, 0x2f, 0x00), 						/* green */
	RGB(0x00, 0x00, 0x2f), 						/* blue */
	RGB(0x2f, 0x2f, 0x00), 						/* yellow */
	RGB(0x2f, 0x00, 0x2f), 						/* violet */
	RGB(0x00, 0x2f, 0x2f), 						/* turquoise */
	RGB(0x2F, 0x17, 0x00) 						/* orange */
};

struct led_rgb pixels[STRIP_NUM_PIXELS];

static const struct device *const strip = DEVICE_DT_GET(STRIP_NODE);

union Pat{
	struct led_rgb pix[STRIP_NUM_PIXELS];
	uint8_t data[4*STRIP_NUM_PIXELS];
};

static union Pat my_pix;						     						//led strip buffer
const uint8_t *current_pattern;												//pointer to current led strip pattern

//--------------------------------------------------------------------------- LED PWM
#define LED_PWM_NODE_ID	 DT_COMPAT_GET_ANY_STATUS_OKAY(pwm_leds)

const char *led_label[] = {DT_FOREACH_CHILD_SEP_VARGS(LED_PWM_NODE_ID, DT_PROP_OR, (,), label, NULL)};

const int num_leds = ARRAY_SIZE(led_label);

uint16_t level;
uint8_t led_theme;

int err;
const struct device *led_pwm;

//=================================================================================================================
int led_pwm_init(void)
{
	led_pwm = DEVICE_DT_GET(LED_PWM_NODE_ID);
	if (!device_is_ready(led_pwm)) 
	{
		#ifdef DEBUG_LOG_LED
			LOG_ERR("Device %s is not ready", led_pwm->name);
		#endif
		return BUSY;
	}
	else
	{
		return RESULT_OK;
	}
}

//=================================================================================================================
int led_strip_init(void)
{
	if(device_is_ready(strip)) 
	{
        return RESULT_OK;
	} 
	else 
	{
		return RESULT_ERR;
	}
}

//=================================================================================================================
int set_button_color(uint8_t position, uint8_t color)
{
	int rc;
	
	position-=1;
	memcpy(&my_pix.pix[position], &colors[color], sizeof(struct led_rgb));
	rc = led_strip_update_rgb(strip, my_pix.pix, STRIP_NUM_PIXELS);
    return rc;
}
//=================================================================================================================
int set_button_pattern(const uint8_t *pattern)
{
	int rc;

	memcpy(&my_pix.data, pattern, 40);
	rc = led_strip_update_rgb(strip, my_pix.pix, STRIP_NUM_PIXELS);
	return rc;
}

//=================================================================================================================
int turn_off_all_buttons(void)
{
	int rc;

	memcpy(&my_pix.data, &turn_off_pattern, 40);
	rc = led_strip_update_rgb(strip, my_pix.pix, STRIP_NUM_PIXELS);
	return rc;
}

//=================================================================================================================
int set_pattern_without_one_button(uint32_t position)
{
	int rc;

	memcpy(&my_pix.pix[position-1], &colors[COLOR_BLACK], sizeof(struct led_rgb));
	rc = led_strip_update_rgb(strip, my_pix.pix, STRIP_NUM_PIXELS);
	return rc;
}

//=================================================================================================================
void thread_led(void)
{
	led_pwm_init();
	led_strip_init();
	k_msleep(100);
	vled_on();
	k_msleep(100);

//---------------------------------------------------------------------------------- led pwm test
	#ifdef MAKE_LED_PWM_TEST
		for(int i=0;i<5;i++)
		{
			err = led_set_brightness(led_pwm, LED_RED_PWM, 100);
			k_msleep(500);

			err = led_off(led_pwm, LED_RED_PWM); 
			err = led_set_brightness(led_pwm, LED_GREEN_PWM, 100);
			k_msleep(500);

			err = led_off(led_pwm, LED_GREEN_PWM); 
			err = led_set_brightness(led_pwm, LED_BLUE_PWM, 100);
			k_msleep(500);

			err = led_off(led_pwm, LED_BLUE_PWM); 
		}
	#endif

//---------------------------------------------------------------------------------- led strip test
	#ifdef MAKE_LED_STRIP_TEST														 
		for(int i=0;i<5;i++)
		{
			current_pattern = red_pattern;
			set_button_pattern(current_pattern);
			k_msleep(500);
			current_pattern = green_pattern;
			set_button_pattern(current_pattern);
			k_msleep(500);
			current_pattern = blue_pattern;
			set_button_pattern(current_pattern);
			k_msleep(500);
		}

		current_pattern = turn_off_pattern;
		set_button_pattern(current_pattern);

	#endif	
//----------------------------------------------------------------------------------

	device_theme=THEME_INFO;
	set_button_pattern(info_pattern);

 	while(1)
 	{
		if(device_theme!=led_theme)
		{
			if(device_theme==THEME_GTA)
			{
				vled_on()																//led power on
				k_msleep(20);															//wait to led inside driver
				led_theme=device_theme;													//don't repeat this condition all the time 
				current_pattern = gta_pattern;											//set current theme		
				set_button_pattern(current_pattern);									//turn on led strip

				err = led_set_brightness(led_pwm, LED_RED_PWM, 100);					//set appropriate PWM LED PCB bottom
				if (err < 0) { LOG_ERR("err=%d brightness=%d\n", err, 100); }			//QUESTION: WHAT SHOULD I DO WITH EER?

				err = led_off(led_pwm, LED_GREEN_PWM); 
				if (err < 0) { LOG_ERR("err=%d", err); }

				err = led_off(led_pwm, LED_BLUE_PWM); 
				if (err < 0) { LOG_ERR("err=%d", err); }
			}

			if(device_theme==THEME_ALTIUM)												//another theme 
			{
				vled_on()
				k_msleep(20);
				led_theme=device_theme;
				current_pattern = altium_pattern;
				set_button_pattern(current_pattern);	

				err = led_set_brightness(led_pwm, LED_RED_PWM, 100);
				if (err < 0) { LOG_ERR("err=%d brightness=%d\n", err, 100); }

				err = led_set_brightness(led_pwm, LED_GREEN_PWM, 50);
				if (err < 0) { LOG_ERR("err=%d brightness=%d\n", err, 50); }

				err = led_off(led_pwm, LED_BLUE_PWM); 
				if (err < 0) { LOG_ERR("err=%d", err); }
			}

			if(device_theme==THEME_VSC)
			{
				vled_on()
				k_msleep(20);
				led_theme=device_theme;
				current_pattern = vsc_pattern;	
				set_button_pattern(current_pattern);

				err = led_off(led_pwm, LED_RED_PWM); 
				if (err < 0) { LOG_ERR("err=%d", err); }

				err = led_off(led_pwm, LED_GREEN_PWM); 
				if (err < 0) { LOG_ERR("err=%d", err); }

				err = led_set_brightness(led_pwm, LED_BLUE_PWM, 100);
				if (err < 0) { LOG_ERR("err=%d brightness=%d\n", err, 100); }
			}

			if(device_theme==THEME_INFO)
			{
				vled_on()
				k_msleep(20);
				led_theme=device_theme;
				current_pattern = info_pattern;	
				set_button_pattern(current_pattern);

				err = led_set_brightness(led_pwm, LED_RED_PWM, 80);
				if (err < 0) { LOG_ERR("err=%d brightness=%d\n", err, 70); }

				err = led_set_brightness(led_pwm, LED_GREEN_PWM, 70);
				if (err < 0) { LOG_ERR("err=%d brightness=%d\n", err, 70); }

				err = led_set_brightness(led_pwm, LED_BLUE_PWM, 80);
				if (err < 0) { LOG_ERR("err=%d brightness=%d\n", err, 70); }
			}

			if(device_theme==NO_THEME)
			{
				led_theme=device_theme;
				current_pattern = turn_off_pattern;
				set_button_pattern(current_pattern);
			
				err = led_off(led_pwm, LED_RED_PWM); 
				if (err < 0) { LOG_ERR("err=%d", err); }

				err = led_off(led_pwm, LED_GREEN_PWM); 
				if (err < 0) { LOG_ERR("err=%d", err); }
				
				err = led_off(led_pwm, LED_BLUE_PWM); 
				if (err < 0) { LOG_ERR("err=%d", err); }
				vled_off()
			}

		}

		if(led_key_pressed!=0)															//if key pressed
		{
			set_pattern_without_one_button(led_key_pressed);							//turn off pressed key
			k_msleep(250);
			set_button_pattern(current_pattern);										//turn on 
			led_key_pressed=0;															//reset flag
		}

		k_msleep(50);
	}
}

//=================================================================================================================

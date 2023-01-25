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

#include "config_app.h"
#include "board.h"
#include "main.h"
#include "led_pwm.h"
#include "led_strip.h"
#include "matrix_keyboard.h"


#define LED_PWM_NODE_ID	 DT_COMPAT_GET_ANY_STATUS_OKAY(pwm_leds)

const char *led_label[] = {DT_FOREACH_CHILD_SEP_VARGS(LED_PWM_NODE_ID, DT_PROP_OR, (,), label, NULL)};

const int num_leds = ARRAY_SIZE(led_label);

LOG_MODULE_REGISTER(bmk_led_pwm,LOG_LEVEL_DBG);

uint16_t level;
uint8_t led_pwm_theme;

//==================================================================================================================================================
void thread_led_pwm(void)
{
	int err;
	const struct device *led_pwm;
	
	led_pwm = DEVICE_DT_GET(LED_PWM_NODE_ID);
	if (!device_is_ready(led_pwm)) 
	{
		LOG_ERR("Device %s is not ready", led_pwm->name);
	}

//---------------------------------------------------------------------------------- led test
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
//---------------------------------------------------------------------------------- 	

 	while(1)
 	{
		if(device_theme!=led_pwm_theme)
		{
			if(device_theme==MODE_GTA)
			{
				led_pwm_theme=device_theme;

				err = led_set_brightness(led_pwm, LED_RED_PWM, 100);
				if (err < 0) { LOG_ERR("err=%d brightness=%d\n", err, 100); }		//i co dalej jak blad?

				err = led_off(led_pwm, LED_GREEN_PWM); 
				if (err < 0) { LOG_ERR("err=%d", err); }

				err = led_off(led_pwm, LED_BLUE_PWM); 
				if (err < 0) { LOG_ERR("err=%d", err); }
			}

			if(device_theme==MODE_ALTIUM)
			{
				led_pwm_theme=device_theme;

				err = led_set_brightness(led_pwm, LED_RED_PWM, 100);
				if (err < 0) { LOG_ERR("err=%d brightness=%d\n", err, 100); }

				err = led_set_brightness(led_pwm, LED_GREEN_PWM, 5);
				if (err < 0) { LOG_ERR("err=%d brightness=%d\n", err, 50); }

				err = led_off(led_pwm, LED_BLUE_PWM); 
				if (err < 0) { LOG_ERR("err=%d", err); }
			}

			if(device_theme==MODE_VSC)
			{
				led_pwm_theme=device_theme;

				err = led_off(led_pwm, LED_RED_PWM); 
				if (err < 0) { LOG_ERR("err=%d", err); }

				err = led_off(led_pwm, LED_GREEN_PWM); 
				if (err < 0) { LOG_ERR("err=%d", err); }

				err = led_set_brightness(led_pwm, LED_BLUE_PWM, 100);
				if (err < 0) { LOG_ERR("err=%d brightness=%d\n", err, 100); }
			}

			if(device_theme==MODE_INFO)
			{
				led_pwm_theme=device_theme;

				err = led_set_brightness(led_pwm, LED_RED_PWM, 80);
				if (err < 0) { LOG_ERR("err=%d", err); }

				err = led_set_brightness(led_pwm, LED_GREEN_PWM, 80);
				if (err < 0) { LOG_ERR("err=%d", err); }

				err = led_set_brightness(led_pwm, LED_BLUE_PWM, 80);
				if (err < 0) { LOG_ERR("err=%d brightness=%d\n", err, 100); }
			}

		}
		k_msleep(100);
	}
		
}

//==================================================================================================================================================
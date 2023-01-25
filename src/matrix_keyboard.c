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

#include <zephyr/sys/printk.h>
#include <zephyr/logging/log.h>

#include "matrix_keyboard.h"
#include "board.h"
#include "main.h"


uint32_t 	key_pressed;
uint8_t 	device_theme=MODE_INFO;									//color, display, pwm_led, led_strip

#ifdef DEBUG_LOG_MATRIX_KEYBOARD
	LOG_MODULE_REGISTER(my_bmk_keyboard,LOG_LEVEL_DBG);
#endif	

//==================================================================================================================================================
static uint32_t check_keyboard(void)
{
	uint32_t result;
	result=0;

//----------------------------------------------------
	gpio_pin_set_dt(&col1,0);

	if(gpio_pin_get_dt(&row1)==0)	result = 1;
	if(gpio_pin_get_dt(&row2)==0)	result = 4;
	if(gpio_pin_get_dt(&row3)==0)	result = 8;

	gpio_pin_set_dt(&col1,1);

//----------------------------------------------------
	gpio_pin_set_dt(&col2,0);

	if(gpio_pin_get_dt(&row1)==0)	result = 2;
	if(gpio_pin_get_dt(&row2)==0)	result = 5;
	if(gpio_pin_get_dt(&row3)==0)	result = 9;

	gpio_pin_set_dt(&col2,1);

//----------------------------------------------------
	gpio_pin_set_dt(&col3,0);

	if(gpio_pin_get_dt(&row1)==0)	result = 3;
	if(gpio_pin_get_dt(&row2)==0)	result = 6;
	if(gpio_pin_get_dt(&row3)==0)	result = 10;

	gpio_pin_set_dt(&col3,1);

//----------------------------------------------------
	gpio_pin_set_dt(&col4,0);

	if(gpio_pin_get_dt(&row2)==0)	result = 7;

	gpio_pin_set_dt(&col4,1);

	return result;
}	

//==================================================================================================================================================
void thread_keyboard(void)
{
	while(1)
	{
		key_pressed = check_keyboard();																	//key_pressed is deleted after led_strip procces
		if(key_pressed!=0)
		{
			k_msleep(20);
			key_pressed = check_keyboard();
			if(key_pressed!=0)
			{
				if(key_pressed==1)														
				{
					device_theme++;
					if(device_theme>MODE_LAST) device_theme=MODE_FIRST;
				}

				if(key_pressed==3)
				{
					device_theme--;
					if(device_theme<MODE_FIRST) device_theme=MODE_LAST;
				}
			}
			else
			{
				key_pressed=0;
			}

			#ifdef DEBUG_LOG_MATRIX_KEYBOARD
				LOG_INF("KEY PRESSED: %d\n",key_pressed);
			#endif
		}
		k_msleep(100);
	}

}

//==================================================================================================================================================
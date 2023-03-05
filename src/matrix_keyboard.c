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

#include "main.h"
#include "matrix_keyboard.h"
#include "config_app.h"
#include "board.h"
#include "led.h"
#include "display.h"

static uint32_t 	key_pressed;
uint32_t			led_key_pressed;

uint8_t 			device_theme=THEME_INFO;									//color, display, pwm_led, led_strip
uint8_t				last_theme;
static uint32_t		keyboard_blocked;
static uint32_t		key_unlock_counter;

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
static void check_functions_key(void)
{
	switch(key_pressed)
	{
		case 2:
			#ifdef DEBUG_LOG_MATRIX_KEYBOARD
				LOG_INF("FUNC KEY2");
			#endif

			static const uint8_t mik[] = {
 			0xE1,	
 			0x10,	
 			0x0C,	
 			0x0E,
			0x28	
			 };

			hid_buttons_press(&mik[0], 1);
			hid_buttons_press(&mik[1], 1);
			k_msleep(50);
			hid_buttons_release(&mik[1], 1);
			hid_buttons_release(&mik[0], 1);
			k_msleep(50);
			hid_buttons_press(&mik[2], 1);
			k_msleep(50);
			hid_buttons_release(&mik[2], 1);
			hid_buttons_press(&mik[3], 1);
			k_msleep(50);
			hid_buttons_release(&mik[3], 1);
			hid_buttons_press(&mik[4], 1);
			k_msleep(50);
			hid_buttons_release(&mik[4], 1);

		break;

		case 4:



		break;

		case 5:



		break;

		case 6:



		break;

		case 7:



		break;

		case 8:



		break;

		case 9:



		break;

		case 10:



		break;
	}	
}

//==================================================================================================================================================
static void keyboard_handler(void)
{
//-------------------------------------------------------------------------------------- pairing process
	if((lcd_pairing_state==PAIRING)||(lcd_pairing_state==PAIRING_ON_DISPLAY))
	{
		led_key_pressed=key_pressed;													//led blink 
		keyboard_blocked=1;																//keyboard locked
		
		if(key_pressed==1)																//
		{
			num_comp_reply(true);
			#ifdef DEBUG_LOG_MATRIX_KEYBOARD
				LOG_INF("PAIRING OK");
			#endif
		}

		if(key_pressed==3)																//
		{
			num_comp_reply(false);

			device_state=BMK_ACTIVE;
			device_theme = THEME_INFO;
			lcd_pairing_state=NO_ACTION;
			led_pairing_state=NO_ACTION;

			refresh_screen_flag=true;
			refresh_led_flag=true;

			#ifdef DEBUG_LOG_MATRIX_KEYBOARD
				LOG_INF("PAIRING NO");
			#endif

		}
	}
	else
//-------------------------------------------------------------------------------------- themes process
	{
		if(device_theme==NO_THEME)														//restore last theme
		{
			device_active_time_reset();													//reset standby counter	
			device_state=BMK_ACTIVE;
			device_theme = last_theme;
		}	
		
		led_key_pressed=key_pressed;													//led blink 
		keyboard_blocked=1;																//keyboard locked
		if(key_pressed==1)																//next theme											
		{
			device_theme++;
			if(device_theme>THEME_LAST) device_theme=THEME_FIRST;
		}

		if(key_pressed==3)																//previous theme
		{
			device_theme--;
			if(device_theme<THEME_FIRST) device_theme=THEME_LAST;		
		}

		check_functions_key();															//check key with macro functions

	}
}

//==================================================================================================================================================
void thread_keyboard(void)
{
	while(1)
	{
		key_pressed = check_keyboard();																//read keyboard										
		
		if(keyboard_blocked==0)																		//if keyboard not blocked
		{
			if(key_pressed!=0)
			{
				k_msleep(2);
				key_pressed = check_keyboard();														//key detected
				if(key_pressed!=0)
				{
					keyboard_handler();
				}
				else																				//to short key pressed 
				{
					key_pressed=0;
					led_key_pressed=key_pressed;
				}

				#ifdef DEBUG_LOG_MATRIX_KEYBOARD
						LOG_INF("KEY PRESSED: %d\n",key_pressed);
				#endif
			}
		}

		if(key_pressed==0)																			//if key not pressed	
		{
		  	key_unlock_counter++;
			if(key_unlock_counter>1)
			{
				key_unlock_counter=0;
				keyboard_blocked=0;																	//keyboard unlocked
			}
			
		}
		k_msleep(50);
	}

}

//==================================================================================================================================================


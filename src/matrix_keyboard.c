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

#include <zephyr/sys/printk.h>
#include <zephyr/logging/log.h>

#include "main.h"
#include "config_app.h"
#include "board.h"
#include "matrix_keyboard.h"
#include "keyboard_sequences.h"
#include "led.h"
#include "display.h"
//---------------------------------------------------------------------------
// Definitions 
//---------------------------------------------------------------------------
#ifdef DEBUG_LOG_MATRIX_KEYBOARD
	LOG_MODULE_REGISTER(my_bmk_keyboard,LOG_LEVEL_DBG);
#endif	
//---------------------------------------------------------------------------
// Local objects 
//---------------------------------------------------------------------------
static uint32_t 	key_pressed;
static uint32_t		keyboard_blocked;
static uint32_t		key_unlock_counter;

//---------------------------------------------------------------------------
// Global objects 
//---------------------------------------------------------------------------
uint32_t			led_key_pressed;
uint8_t 			device_theme=THEME_INFO;									//color, display, pwm_led, led_strip
uint8_t				last_theme;

//---------------------------------------------------------------------------
// Implementation 
//---------------------------------------------------------------------------

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

//===============================================================================================================
static uint8_t key_sequence(const uint8_t *key_tab)
{
	uint8_t table_size=0;
	uint8_t i=0;

	if(key_tab[i]==0xFF) return 1;

	while((key_tab[i])!=KEY_EOS)
	{
		i++; table_size++;
	 	if(i>32) return 1;
	}
	table_size++;	
	LOG_INF("Table size: %d, ", table_size);	

	for(i=0;i<table_size;i++)
	{
		switch(key_tab[i])
		{
			case KEY_PRESS:
				LOG_INF("Key press: %d",*(key_tab+i+1));
				hid_buttons_press(&key_tab[i+1], 1);
				k_msleep(100);
				hid_buttons_release(&key_tab[i+1], 1);			
				k_msleep(100);
			break;

			case KEY_RELEASE:
				hid_buttons_release(&key_tab[i+1], 1);
				k_msleep(100);
			break;

			case KEY_HOLD:
				hid_buttons_press(&key_tab[i+1], 1);
				k_msleep(100);
			break;

			case KEY_EOS:
				LOG_INF("End of sequence");
				return 0;
			break;
		}

	}
	return 0;
}

//==================================================================================================================================================
static uint8_t check_functions_key(void)
{
	uint8_t offset;

	if((device_theme>THEME_FIRST)&&(device_theme<THEME_LAST+1))
	{
		offset = device_theme-2;
	}
	else 
	{
		return 1;
	}
	
	switch(key_pressed)
	{
		case 2:
			key_sequence(*(ptr_seq_k2+offset));	
		break;

		case 4:
			key_sequence(*(ptr_seq_k4+offset));	
		break;

		case 5:
			key_sequence(*(ptr_seq_k5+offset));
		break;

		case 6:
			key_sequence(*(ptr_seq_k6+offset));	
		break;

		case 7:
			key_sequence(*(ptr_seq_k7+offset));	
		break;

		case 8:
			key_sequence(*(ptr_seq_k8+offset));		
		break;

		case 9:
			key_sequence(*(ptr_seq_k9+offset));		
		break;

		case 10:
			key_sequence(*(ptr_seq_k10+offset));		
		break;
	}
	return 0;	
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
		if(key_pressed==3)																//next theme											
		{
			device_theme++;
			if(device_theme>THEME_LAST) device_theme=THEME_FIRST;
		}

		if(key_pressed==1)																//previous theme
		{
			device_theme--;
			if(device_theme<THEME_FIRST) device_theme=THEME_LAST;		
		}

		check_functions_key();															//check key with macro functions (2,4-10)

	}
}

//==================================================================================================================================================
void thread_keyboard(void)
{
	while(1)
	{
		key_pressed = check_keyboard();													//read keyboard										
		
		if(keyboard_blocked==0)															//if keyboard not blocked
		{
			if(key_pressed!=0)
			{
				k_msleep(2);
				key_pressed = check_keyboard();											//key detected
				if(key_pressed!=0)
				{
					keyboard_handler();
				}
				else																	//to short key pressed 
				{
					key_pressed=0;
					led_key_pressed=key_pressed;
				}
			}
		}

		if(key_pressed==0)																//if key not pressed	
		{
		  	key_unlock_counter++;
			if(key_unlock_counter>1)
			{
				key_unlock_counter=0;
				keyboard_blocked=0;														//keyboard unlocked
			}
			
		}
		k_msleep(50);
	}

}

//==================================================================================================================================================


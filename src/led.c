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

#include <zephyr/sys/printk.h>
#include <zephyr/logging/log.h>

#include "board.h"
#include "led.h"
#include "led_strip.h"

//LOG_MODULE_REGISTER(my_bmk_led,LOG_LEVEL_DBG);

//==================================================================================================================================================
void thread_led(void)
{
	vled_on();

 	while(1)
 	{
		if(mode_counter==MODE_GTA)
		{
			led_red_on(); 
			led_green_off();
			led_blue_off();
		}

		if(mode_counter==MODE_ALTIUM)
		{
			led_red_on(); 
			led_green_on();
			led_blue_off();
		}

		if(mode_counter==MODE_VSC)
		{
			led_red_off(); 
			led_green_off();
			led_blue_on();
		}

		k_msleep(100);
	}
		
}



//==================================================================================================================================================
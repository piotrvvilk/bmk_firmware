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

#include "charger.h"
#include "max17048/max17048.h"
#include "board.h"
#include "main.h"
#include "display.h"
#include "led.h"
#include "config_app.h"

#ifdef DEBUG_LOG_I2C_DEVICES
	LOG_MODULE_REGISTER(bmk_charger_devices,LOG_LEVEL_DBG);
#endif	

charger_data_t      charger_data;
uint32_t 			usb_pin_state;
uint32_t 			usb_pin_old_state;
uint32_t 			charging_pin_state;
uint32_t 			charging_pin_old_state;


//==================================================================================================================================================
void thread_charger(void)
{
	while(1)
	{
		usb_detection_on();																	//turn on voltage divider

		if(gpio_pin_get_dt(&usbdet)==0)                                                		//USB disconnected
		{
			#ifdef DEBUG_LOG_CHARGER
				LOG_INF("USB DISCONNECTED\n");
			#endif
			
			charger_data.usb_status = USB_DISCONNECTED;
			charger_data.charger_status = CHARGER_DISABLE;
			charger_off();

			usb_pin_state=0;
			if(usb_pin_old_state!=usb_pin_state)											//detect when pin state is change
			{
				usb_pin_old_state=usb_pin_state;
				refresh_screen_flag=true;													//only once after connected usb cable
				refresh_led_flag=true;											
			}

		}
		else                                                                                //USB connected
		{
			#ifdef DEBUG_LOG_CHARGER
				LOG_INF("USB CONNECTED\n");
			#endif

			usb_pin_state=1;
			if(usb_pin_old_state!=usb_pin_state)											//detect when pin state is change
			{
				usb_pin_old_state=usb_pin_state;
				refresh_screen_flag=true;													//only once after disconnected usb cable
				refresh_led_flag=true;											
			}


			charger_data.usb_status = USB_CONNECTED;
			charger_on();

			if(gpio_pin_get_dt(&chrgdet)==0)                                              	//full charged
			{
				#ifdef DEBUG_LOG_CHARGER
					LOG_INF("BATTERY IS FULL\n");
				#endif

				charger_data.charged_counter++;

				if(charger_data.charged_counter>2)                                      	//nie pokazuj od razu ze naladowane                
				{
				 	charger_data.charger_status = CHARGER_DONE;
				}

				charging_pin_state=0;
				if(charging_pin_old_state!=charging_pin_state)								//detect when pin state is change
				{
					charging_pin_old_state=charging_pin_state;
					refresh_screen_flag=true;												//only once after stop charging
					refresh_led_flag=true;											
				}
			}
			else                                                                            //still charging	
			{
				#ifdef DEBUG_LOG_CHARGER
					LOG_INF("CHARGING\n");
				#endif

				charger_data.charged_counter=0;
				charger_data.charger_status = CHARGER_CHARGING;	

				charging_pin_state=1;
				if(charging_pin_old_state!=charging_pin_state)								//detect when pin state is change
				{
					charging_pin_old_state=charging_pin_state;
					refresh_screen_flag=true;												//only once after start charging
					refresh_led_flag=true;											
				}
			}
		}
		usb_detection_off();																//turn off voltage divider
		k_msleep(1000);

	}
}

//==================================================================================================================================================
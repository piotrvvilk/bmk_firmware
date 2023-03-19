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
//---------------------------------------------------------------------------
// Global objects 
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// Local objects 
//---------------------------------------------------------------------------
//==================================================================================================================================================
void thread_charger(void)
{
	while(1)
	{
		usb_detection_on();																		//turn on voltage divider

		if(gpio_pin_get_dt(&usbdet)==0)                                                			//USB disconnected
		{
			#ifdef DEBUG_LOG_CHARGE
				LOG_INF("USB DISCONNECTED\n");
			#endif
			
			charger_data.usb_status = USB_DISCONNECTED;
			charger_data.charger_status = CHARGER_DISABLE;
			charger_off();
			charger_data.charger_locked=false;

			charger_data.usb_pin_state=0;
			if(charger_data.usb_pin_old_state!=charger_data.usb_pin_state)						//detect when pin state is change
			{
				charger_data.usb_pin_old_state=charger_data.usb_pin_state;
				refresh_screen_flag=true;														//only once after connected usb cable
				refresh_led_flag=true;											
			}

		}
		else                                                                                	//USB connected
		{
			#ifdef DEBUG_LOG_CHARGER
				LOG_INF("USB CONNECTED\n");
			#endif

			charger_data.usb_pin_state=1;
			if(charger_data.usb_pin_old_state!=charger_data.usb_pin_state)						//detect when pin state is change
			{
				charger_data.usb_pin_old_state=charger_data.usb_pin_state;
				refresh_screen_flag=true;														//only once after disconnected usb cable
				refresh_led_flag=true;											
			}


			charger_data.usb_status = USB_CONNECTED;
			charger_on();

			if(gpio_pin_get_dt(&chrgdet)==0)                                              		//full charged
			{
				#ifdef DEBUG_LOG_CHARGER
					LOG_INF("BATTERY IS FULL\n");
				#endif

				charger_data.charged_counter++;

				if(charger_data.charged_counter>2)                                      		//nie pokazuj od razu ze naladowane                
				{
				 	charger_data.charger_status = CHARGER_DONE;
					charger_data.charger_locked=true;											//lock when charger finishing job	
				}

				charger_data.charging_pin_state=0;
				if(charger_data.charging_pin_old_state!=charger_data.charging_pin_state)    	//detect when pin state is change
				{
					charger_data.charging_pin_old_state=charger_data.charging_pin_state;
					refresh_screen_flag=true;													//only once after stop charging
					refresh_led_flag=true;
					led_pwm_counter=0;											
				}
			}
			else                                                                           	 	//still charging	
			{
				if(charger_data.charger_locked==false)											//only when charger is not locked
				{
					#ifdef DEBUG_LOG_CHARGER
						LOG_INF("CHARGING\n");
					#endif

					charger_data.charged_counter=0;
					charger_data.charger_status = CHARGER_CHARGING;	

					charger_data.charging_pin_state=1;
					if(charger_data.charging_pin_old_state!=charger_data.charging_pin_state)	//detect when pin state is change
					{
						charger_data.charging_pin_old_state=charger_data.charging_pin_state;
						refresh_screen_flag=true;												//only once after start charging
						refresh_led_flag=true;	
						led_pwm_counter=0;											
					}
				}
			}
		}
		usb_detection_off();																	//turn off voltage divider
		k_msleep(1000);

	}
}

//==================================================================================================================================================


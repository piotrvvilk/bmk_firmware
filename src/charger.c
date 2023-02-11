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
#include "config_app.h"

#ifdef DEBUG_LOG_I2C_DEVICES
	LOG_MODULE_REGISTER(bmk_charger_devices,LOG_LEVEL_DBG);
#endif	

charger_data_t     charger_data;

//==================================================================================================================================================
void thread_charger(void)
{
	while(1)
	{
		usb_detection_on();

		if(gpio_pin_get_dt(&usbdet)==0)                                                		//USB disconnected
		{
			if(charger_data.usb_status != USB_DISCONNECTED)                         		//only once after disconnected usb cable
			{
				#ifdef DEBUG_LOG_CHARGER
					LOG_INF("USB DISCONNECTED\n");
				#endif
			
			charger_data.usb_status = USB_DISCONNECTED;


			// 	if(my_led_status.led_battery_state!=LED_STANDBY)
			// 	{
			// 		my_led_status.led_battery_state=LED_BATTERY_NONE;                       //turn off led and LED_STANDBY state          
			// 		display_data.display_on_flag=true;                                      //refresh lcd                    
			// 		display_data.display_on_counter=1;                                      //clear lcd timeout
			// 	}
			}

			// charger_data.charged_counter=0;
			
			// my_led_status.led_charging_one_time_flag=false;
			// my_led_status.led_charged_one_time_flag=false;
			// beep_one_time_flag=false;
			charger_off();
		}
		else                                                                                //USB connected
		{
			#ifdef DEBUG_LOG_CHARGER
				LOG_INF("USB CONNECTED\n");
			#endif

			charger_data.usb_status = USB_CONNECTED;
			charger_on();

			if(gpio_pin_get_dt(&chrgdet)==0)                                              	//full charged
			{
				#ifdef DEBUG_LOG_CHARGER
					LOG_INF("BATTERY IS FULL\n");
				#endif

				// if(beep_one_time_flag==false)
				// {
				// 	beep_one_time_flag=true;
				// 	beep_charging();
				// }

				charger_data.charged_counter++;

				if(charger_data.charged_counter>2)                                      //nie pokazuj od razu ze naladowane                
				{
				 	charger_data.charger_status = CHARGER_DONE;
				// 	my_led_status.led_battery_state=LED_BATTERY_CHARGED;
		
				// 	if(my_led_status.led_charged_one_time_flag==false)                      //zasygnalizuj od razu ze naladowane
				// 	{
				// 		my_led_status.led_charged_one_time_flag=true;
				// 		my_led_status.led_battery_counter=LED_CHARGED_PERIOD-5;
				// 	}
				}
			}
			else                                                                            //still charging	
			{
				#ifdef DEBUG_LOG_CHARGER
					LOG_INF("CHARGING\n");
				#endif

				charger_data.charged_counter=0;
				charger_data.charger_status = CHARGER_CHARGING;	
				// my_led_status.led_battery_state=LED_BATTERY_CHARGING;
		
				// if(my_led_status.led_charging_one_time_flag==false)                         //zasygnalizuj od razu podlaczenie kabla USB przez dzwiek i ledy
				// {
				// 	my_led_status.led_charging_one_time_flag=true;
				// 	my_led_status.led_battery_counter=LED_CHARGING_PERIOD-5;
				// 	display_data.display_on_flag=true;                                      //refresh lcd                    
				// 	display_data.display_on_counter=1;                                      //clear lcd timeou
				// }
			}
		}
		usb_detection_off();
		k_msleep(1000);

	}
}

//==================================================================================================================================================
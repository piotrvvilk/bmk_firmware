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
#include "board.h"
#include "config_app.h"
#include "i2c_devices.h"
#include "lis2dh/lis2dh.h"
#include "max17048/max17048.h"
#include "charger.h"

#ifdef DEBUG_LOG_I2C_DEVICES
	LOG_MODULE_REGISTER(bmk_i2c_devices,LOG_LEVEL_DBG);
#endif	

static uint32_t max17048_read_counter;

uint32_t max17048_voltage;
uint8_t max17048_charge;

//==================================================================================================================================================
void thread_i2c_devices(void)
{
	#if defined(USE_LIS2DH) || defined(USE_MAX17048)
		i2c_init();
	#endif	

	#ifdef USE_LIS2DH
		accel_movement_detect(150);
	#endif
	
	MAX17048GetCharge(&max17048_charge);
	
	while(1)
	{
		#ifdef USE_MAX17048
			max17048_read_counter++;
			if(max17048_read_counter>30)
			{
				max17048_read_counter=0;
				MAX17048GetVoltage(&max17048_voltage);
				MAX17048GetCharge(&max17048_charge);

				if((max17048_charge>94)&&(charger_data.charger_status == CHARGER_DISABLE))		//correction
				{
					max17048_charge=98;
					LOG_INF("98");
				}

				if((max17048_charge>95)&&(charger_data.charger_status == CHARGER_CHARGING))		//correction
				{
					max17048_charge=99;
					LOG_INF("99");
				}

				if((max17048_charge>90)&&(charger_data.charger_status == CHARGER_DONE))			//correction
				{
					max17048_charge=100;
					LOG_INF("100");
				}

				#ifdef DEBUG_LOG_MAX17048
					LOG_INF("VOLTAGE: %dmV \n", max17048_voltage);
					LOG_INF("CHARGE: %d%% \n", max17048_charge);
				#endif

			}
		#endif

		#ifdef USE_LIS2DH
			if(gpio_pin_get_dt(&accelint1))
			{
				lis_int1_flag=true;
				#ifdef DEBUG_LOG_LIS2DH
					LOG_INF("LIS2DH INTERRUPT 1\n");
				#endif
			}
		#endif

		k_msleep(1000);
	}

}

//==================================================================================================================================================
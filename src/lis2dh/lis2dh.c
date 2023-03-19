//---------------------------------------------------------------------------
// Includes 
//---------------------------------------------------------------------------
#include <errno.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/device.h>
#include <zephyr/drivers/i2c.h>

#include <zephyr/sys/printk.h>
#include <zephyr/logging/log.h>

#include "../main.h"
#include "../config_app.h"
#include "lis2dh.h"

//---------------------------------------------------------------------------
// Global objects  
//---------------------------------------------------------------------------
int16_t			x_axis, y_axis, z_axis;
int8_t			x_l_axis, y_l_axis, z_l_axis;
uint8_t 		accel_temp;
bool 			lis_int1_flag;

const struct device *const i2c_dev = DEVICE_DT_GET(DT_NODELABEL(i2c1));

#ifdef DEBUG_LOG_LIS2DH  
	LOG_MODULE_REGISTER(my_bmk_lis,LOG_LEVEL_DBG);
#endif	

//============================================================================================================================================
static int lis2dh_write_reg(uint8_t addr, uint8_t data)
{
	uint8_t wr_addr[2];
	struct i2c_msg msgs[2];

	wr_addr[0] = addr;

	/* Send the address to write to */
	msgs[0].buf = wr_addr;
	msgs[0].len = 1;
	msgs[0].flags = I2C_MSG_WRITE;

	/* Data to be written, and STOP after this. */
	msgs[1].buf = (uint8_t*)&data;
	msgs[1].len = 1;
	msgs[1].flags = I2C_MSG_WRITE | I2C_MSG_STOP;

	return i2c_transfer(i2c_dev, &msgs[0], 2, LIS2DH_SLAVE_ADDRESS);
}

//============================================================================================================================================
static int lis2dh_read_reg(uint16_t addr, uint8_t *data)
{
	uint8_t wr_addr[2];
	struct i2c_msg msgs[2];

	wr_addr[0] = addr;

	/* Send the address to read from */
	msgs[0].buf = wr_addr;
	msgs[0].len = 1;
	msgs[0].flags = I2C_MSG_WRITE;

	/* Read from device. STOP after this. */
	msgs[1].buf = data;
	msgs[1].len = 1;
	msgs[1].flags = I2C_MSG_READ | I2C_MSG_STOP;

	return i2c_transfer(i2c_dev, &msgs[0], 2, LIS2DH_SLAVE_ADDRESS);
}

//============================================================================================================================================
uint32_t i2c_init(void)
{
	if (!device_is_ready(i2c_dev)) 
	{
		#ifdef DEBUG_LOG_LIS2DH
			LOG_INF("I2C: Device is not ready.\n");
		#endif
		return BUSY;
	}
	else
	{
		return RESULT_OK;
	}
}

//============================================================================================================================================
uint8_t get_accel_ID(void)
{
	uint8_t dta;
	
	lis2dh_read_reg(LIS2DH_WHO_AM_I,&dta);
	return dta;
}

//============================================================================================================================================
int8_t get_accel_temp(void)
{
	int8_t t;	
	
	lis2dh_read_reg(LIS2DH_OUT_TEMP_L,&t);		
	lis2dh_read_reg(LIS2DH_OUT_TEMP_H,&t);		
	return t;
}	

//============================================================================================================================================
void release_interrupt(void)
{
	uint8_t dta;
	lis2dh_read_reg(LIS2DH_INT1_SOURCE,&dta);			//dummy read	
}

//============================================================================================================================================
void get_accel_data(int16_t *x, int16_t *y, int16_t *z)
{
	uint8_t 	axes[6];

	lis2dh_read_reg(LIS2DH_OUT_X_L,&axes[0]);		
	lis2dh_read_reg(LIS2DH_OUT_X_H,&axes[1]);		
 			
	lis2dh_read_reg(LIS2DH_OUT_Y_L,&axes[2]);		
	lis2dh_read_reg(LIS2DH_OUT_Y_H,&axes[3]);		
	
	lis2dh_read_reg(LIS2DH_OUT_Z_L,&axes[4]);		
	lis2dh_read_reg(LIS2DH_OUT_Z_H,&axes[5]);		

	*x=(axes[1]<<8)+axes[0];
	*y=(axes[3]<<8)+axes[2];
	*z=(axes[5]<<8)+axes[4];
	
//	float wynikx = (0.6*(x_axis_buf)+0.4*(x_axis));
//	x_axis_buf=(int16_t)wynikx;
//		
//	float wyniky = (0.6*(y_axis_buf)+0.4*(y_axis));
//	y_axis_buf=(int16_t)wyniky;
//		
//	float wynikz = (0.6*(z_axis_buf)+0.4*(z_axis));
//	z_axis_buf=(int16_t)wynikz;
}

//============================================================================================================================================
void get_accel_low_data(int8_t *x, int8_t *y, int8_t *z)
{
	uint8_t 	axes[6];
	
	lis2dh_read_reg(LIS2DH_OUT_X_L,&axes[0]);		
	lis2dh_read_reg(LIS2DH_OUT_X_H,&axes[1]);		
 			
	lis2dh_read_reg(LIS2DH_OUT_Y_L,(uint8_t*)&axes[2]);		
	lis2dh_read_reg(LIS2DH_OUT_Y_H,(uint8_t*)&axes[3]);		
	
	lis2dh_read_reg(LIS2DH_OUT_Z_L,(uint8_t*)&axes[4]);		
	lis2dh_read_reg(LIS2DH_OUT_Z_H,(uint8_t*)&axes[5]);		

	*x=axes[1];
	*y=axes[3];
	*z=axes[5];
}
//============================================================================================================================================
void accel_movement_detect(uint32_t val)
{
	uint8_t sens;
	
	if(val<100) val=100;
	if(val>2000) val=2000;
	sens = val/16;

	lis2dh_write_reg(LIS2DH_REG1,0x2F);								//10Hz, low power mode, xyz enabled		
	//lis2dh_write_reg(LIS2DH_REG1,0x27);							//10Hz, low power mode, xyz enabled		
	//lis2dh_write_reg(LIS2DH_REG2,0x01);							//high pass filter enable for AOI on INT1
	
	//lis2dh_write_reg(LIS2DH_REG2,0x00);							//no HPF
	lis2dh_write_reg(LIS2DH_REG2,0x09);								//HPF enabled
	
	lis2dh_write_reg(LIS2DH_REG3,0x40);								//AOI1 on INT1
	
	lis2dh_write_reg(LIS2DH_REG4,0x80);         					//BDU on, BLE off, 2G, HR=0, no self test
	
	//lis2dh_write_reg(LIS2DH_REG5,0x00);         					//no boot, fifo disable, int1 not latched,4D int1 disable, int2 not latched, 4D int2 disable
	lis2dh_write_reg(LIS2DH_REG5,0x08);         					//int1 latched,
	//lis2dh_write_reg(LIS2DH_REG5,0x0C);         					//int1 latched, 4D int1 enable, 
	
	lis2dh_write_reg(LIS2DH_REG6,0x00);         					//click int2 off, int1 on int2 off, int2 on ont2 off, boot on int2 off, activity on int2 off, int active high
	//lis2dh_write_reg(LIS2DH_REG6,0x02);         					//click int2 off, int1 on int2 off, int2 on ont2 off, boot on int2 off, activity on int2 off, int active high

	lis2dh_write_reg(LIS2DH_INT1_CFG,0x2A);   						//OR combination event, positive axes enabled,
	
	//lis2dh_write_reg(LIS2DH_INT1_CFG,0x0A);   					//OR combination event, positive X and Y axes enabled,
	//lis2dh_write_reg(LIS2DH_INT1_CFG,0x6A);   					//6D movement recognition, positive axes enabled,
	//lis2dh_write_reg(LIS2DH_INT1_CFG,0x7F);   					//6D movement recognition, all axes enabled,
	
	lis2dh_write_reg(LIS2DH_INT1_THS,sens);   						//
	lis2dh_write_reg(LIS2DH_INT1_DURATION,0x00);   					//int1 duration: LSB = 1/ODR
	
	lis2dh_write_reg(LIS2DH_TEMP_CONFIG,0xC0);   					//temp sensor enable
	
	lis2dh_write_reg(LIS2DH_FIFO_CTRL,0x00);
	
	lis2dh_read_reg(LIS2DH_INT1_SOURCE,&sens);						//dummy read	
}

//============================================================================================================================================
void accel_click_detect(uint32_t val)
{
	uint8_t sens;
	
	if(val<100) val=100;
	if(val>2000) val=2000;
	sens = val/16;
	
	lis2dh_write_reg(LIS2DH_REG1,0x5F);								//100Hz, LPEN = 1 (low power mode), xyz enabled		(8/20/30)
	//lis2dh_write_reg(LIS2DH_REG1,0x4F);							//50Hz, LPEN = 1 (low power mode), xyz enabled		
	//lis2dh_write_reg(LIS2DH_REG1,0x2F);							//10Hz, LPEN = 1 (low power mode), xyz enabled		
	
	lis2dh_write_reg(LIS2DH_REG2,0x04);								//HP filter: hpclick
	//lis2dh_write_reg(LIS2DH_REG2,0x0C);							//HP filter: fds+hpclick
	
	lis2dh_write_reg(LIS2DH_REG3,0x80);								//INT1 for click
	
	lis2dh_write_reg(LIS2DH_REG4,0x80);         					//BDU on, BLE off, 2G, HR=0, self test off
	
	lis2dh_write_reg(LIS2DH_REG5,0x00);         					//no boot, fifo disable, int1 not latched,4D int1 disable, int2 not latched, 4D int2 disable
	
	lis2dh_write_reg(LIS2DH_REG6,0x00);         					//click int2 off, int1 on int2 off, int2 on ont2 off, boot on int2 off, activity on int2 off, int active high
	
	//lis2dh_write_reg(LIS2DH_INT1_CFG,0x2A);   					//OR combination event, positive axes enabled,
	//lis2dh_write_reg(LIS2DH_INT1_DURATION,0x00);   				//int1 duration: LSB = 1/ODR
	
	//lis2dh_write_reg(LIS2DH_CLICK_CFG,0x08);   					//double click on YD
	//lis2dh_write_reg(LIS2DH_CLICK_CFG,0x20);   					//double click on ZD
	lis2dh_write_reg(LIS2DH_CLICK_CFG,0x2A);   						//double click on ZD YD XD
	lis2dh_write_reg(LIS2DH_CLICK_THS,5); 	  						//
	
//	lis2dh_write_reg(LIS2DH_TIME_LIMIT,10);							//czas kliku						//8
//	lis2dh_write_reg(LIS2DH_TIME_LATENCY,30);						//czas pomiedzy klikami				//20
//	lis2dh_write_reg(LIS2DH_TIME_WINDOW,20);						//"double-click speed"				//30	
	
	lis2dh_write_reg(LIS2DH_TIME_LIMIT,0x04);						//czas kliku						//8
	lis2dh_write_reg(LIS2DH_TIME_LATENCY,0x24);						//czas pomiedzy klikami				//20
	lis2dh_write_reg(LIS2DH_TIME_WINDOW,0x7F);						//"double-click speed"				//30	
	
	lis2dh_write_reg(LIS2DH_FIFO_CTRL,0x00);
	
	lis2dh_read_reg(LIS2DH_INT1_SOURCE,(uint8_t*)&sens);			//dummy read	
	
	lis2dh_read_reg(LIS2DH_CLICK_SRC,(uint8_t*)&sens);				//read??
	
//-----------------------------------------------------	
	//lis2dh_write_reg(LIS2DH_ACT_THS,sens);   						//sleep to wake, return to sleep
	//lis2dh_write_reg(LIS2DH_ACT_DUR,sens);						//1LSB = (8*1[LSB}+1)/ODR
}

//============================================================================================================================================
void accel_click_detect_yt(uint32_t val)
{
	uint8_t sens;
	
	if(val<100) val=100;
	if(val>2000) val=2000;
	sens = val/16;
	
	lis2dh_write_reg(LIS2DH_REG1,0x77);								//0x20 400Hz, LPEN = 0 (no low power mode), xyz enabled
	//lis2dh_write_reg(LIS2DH_REG1,0x57);							//100Hz, LPEN = 0 (no low power mode), xyz enabled
	//lis2dh_write_reg(LIS2DH_REG1,0x5F);							//100Hz, LPEN = 1 (low power mode), xyz enabled		
	
	lis2dh_write_reg(LIS2DH_REG2,0x04);								//0x21 HP filter: hpclick
	
	lis2dh_write_reg(LIS2DH_REG3,0x80);								//0x22 INT1 for click
	
	lis2dh_write_reg(LIS2DH_REG4,0x88);        						//0x23 BDU on, BLE off, 2G, HR=1, self test off
	
	lis2dh_write_reg(LIS2DH_REG5,0x00);       						//0x24 no boot, fifo disable, int1 not latched,4D int1 disable, int2 not latched, 4D int2 disable
	
	lis2dh_write_reg(LIS2DH_REG6,0x00);         					//0x25 click int2 off, int1 on int2 off, int2 on ont2 off, boot on int2 off, activity on int2 off, int active high
	
	lis2dh_write_reg(LIS2DH_FIFO_CTRL,0x00);						//0x2E
	
	lis2dh_write_reg(LIS2DH_INT1_CFG,0x00);							//0x30
	lis2dh_write_reg(LIS2DH_INT1_THS,0xA5);							//0x32
	lis2dh_write_reg(LIS2DH_INT1_DURATION,0xA5);					//0x33
	
	//lis2dh_write_reg(LIS2DH_CLICK_CFG,0x08);   					//0x38 double click on YD
	lis2dh_write_reg(LIS2DH_CLICK_CFG,0x20);   						//0x38 double click on ZD
	//lis2dh_write_reg(LIS2DH_CLICK_CFG,0x2A);   					//0x38 double click on ZD YD XD
	
	lis2dh_write_reg(LIS2DH_CLICK_THS,0x10); 	  					//0x3A ????????????????????				0xB0
			
	lis2dh_write_reg(LIS2DH_TIME_LIMIT,0x10);						//0x3B czas kliku									0x04
	lis2dh_write_reg(LIS2DH_TIME_LATENCY,0x24);						//0x3C czas pomiedzy klikami			0x24		
	lis2dh_write_reg(LIS2DH_TIME_WINDOW,0x60);						//0x3D "double-click speed"				0x7F	

	lis2dh_write_reg(LIS2DH_ACT_THS,0x00);   						//0x3E sleep to wake, return to sleep 		def:0x05
	
	lis2dh_write_reg(LIS2DH_ACT_DUR,0x00);							//0x3F 1LSB = (8*1[LSB}+1)/ODR						def:0x0F	

	lis2dh_read_reg(LIS2DH_INT1_SOURCE,(uint8_t*)&sens);			//dummy read	
	
	lis2dh_read_reg(LIS2DH_CLICK_SRC,(uint8_t*)&sens);				//read
}


//============================================================================================================================================
void accel_power_down(void)
{
	lis2dh_write_reg(LIS2DH_REG1,0x00);								//power down
}

//============================================================================================================================================


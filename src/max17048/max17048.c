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

#include "max17048.h"

const struct device *const i2c_max17048_dev = DEVICE_DT_GET(DT_NODELABEL(i2c1));

//---------------------------------------------------------------------------
// Implementation 
//---------------------------------------------------------------------------
//===============================================================================================================
static int i2c_write_data(uint8_t addr, uint8_t *data, uint8_t length)
{
	uint8_t wr_addr[2];
	struct i2c_msg msgs[2];

	wr_addr[0] = addr;

	/* Send the address to write to */
	msgs[0].buf = wr_addr;
	msgs[0].len = 1;
	msgs[0].flags = I2C_MSG_WRITE;

	/* Data to be written, and STOP after this. */
	msgs[1].buf = data;
	msgs[1].len = length;
	msgs[1].flags = I2C_MSG_WRITE | I2C_MSG_STOP;

	return i2c_transfer(i2c_max17048_dev, &msgs[0], 2, MAX17048_ADDR);
}

//===============================================================================================================
static int i2c_read_data(uint16_t addr, uint8_t *data, uint8_t length)
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
	msgs[1].len = length;
	msgs[1].flags = I2C_MSG_READ | I2C_MSG_STOP;

	return i2c_transfer(i2c_max17048_dev, &msgs[0], 2, MAX17048_ADDR);
}

//===============================================================================================================
int MAX17048Reset(void) 
{
    uint8_t dta[2];
    dta[0]=0x00;
    dta[1]=0x54;
    
    return i2c_write_data(COMMAND_REGISTER,dta,2);
}

//===============================================================================================================
int MAX17048QuickStart(void) 
{
    uint8_t dta[2];
    dta[0]=0x40;
    dta[1]=0x00;
    
    return i2c_write_data(MODE_REGISTER,dta,2);
}

//===============================================================================================================
int MAX17048SleepMode(void) 
{
    int err;
    uint8_t dta[2];
    uint8_t dta_cfg[2];
    
    err = i2c_read_data(CONFIG_REGISTER, dta_cfg, 2);						    //odczytaj config, w MSB sa ustawienia ogniwa
    if(err==I2C_ERR) return I2C_ERR;
    dta_cfg[1] |=0x80;									

    dta[0]=0x20;																										
    dta[1]=0x00;
    
    err = i2c_write_data(MODE_REGISTER, dta, 2);								//sleep enable
    if(err==I2C_ERR) return I2C_ERR;
    
    err = i2c_write_data(CONFIG_REGISTER, dta_cfg, 2);						    //go to sleep			
    if(err==I2C_ERR) return I2C_ERR;

    return I2C_OK;
	
}

//===============================================================================================================
int MAX17048GetVoltage(uint32_t *data)
{
    int err;
    uint8_t dta[2];
    uint32_t val;
    
    err = i2c_read_data(VCELL_REGISTER, dta, 2);
    
    if(err==I2C_ERR) return I2C_ERR;
    
    val = (dta[0] << 4) | (dta[1] >> 4);	
    val = val * 125;
    val = val / 100;
    
    *data = (uint32_t)val;
    
    return I2C_OK;
}

//===============================================================================================================
int MAX17048GetCharge(uint8_t *data)
{
    int err;
    uint8_t dta[2];
    
    err = i2c_read_data(SOC_REGISTER, dta, 2);
    
    if(err==I2C_ERR) return I2C_ERR;
    
    *data = (uint8_t)dta[0];
    
    return I2C_OK;
}

//===============================================================================================================
int MAX17048GetVersion(uint32_t *data) 
{
    int err;
    uint8_t dta[2];

    err = i2c_read_data(VERSION_REGISTER, dta, 2);
    *data = (uint32_t)(dta[0]<<8|dta[1]);
                    
    if(err==I2C_ERR) return I2C_ERR;
    else return I2C_OK;
}
 
//===============================================================================================================


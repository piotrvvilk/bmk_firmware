#ifndef _MAX17048_H__
#define _MAX17048_H__

//---------------------------------------------------------------------------
// Definitions 
//---------------------------------------------------------------------------
#define 		MAX17048_ADDR			 			0x36					

#define         I2C_OK                              0
#define         I2C_ERR                             1

//---------------------------------------------------------------------------
// MAX17048 REGISTERS
//---------------------------------------------------------------------------
#define 		VCELL_REGISTER						0x02
#define 		SOC_REGISTER						0x04
#define 		MODE_REGISTER						0x06
#define 		VERSION_REGISTER					0x08
#define 		CONFIG_REGISTER						0x0C
#define 		COMMAND_REGISTER					0xFE

//---------------------------------------------------------------------------
#define			BATTERY_OK						    0		
#define			BATTERY_LOW_POWER					1	
#define			BATTERY_DISCHARGED                  2

//---------------------------------------------------------------------------
// Global functions  
//---------------------------------------------------------------------------
int MAX17048Reset(void);
int MAX17048QuickStart(void); 
int MAX17048SleepMode(void); 
int MAX17048GetVoltage(uint32_t *data);
int MAX17048GetCharge(uint8_t *data);
int MAX17048GetVersion(uint32_t *data); 

#endif
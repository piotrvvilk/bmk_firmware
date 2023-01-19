#ifndef __MAX17048_H
#define __MAX17048_H

//====================================================================================
#define 		MAX17048_ADDR			 			0x36					

#define         I2C_OK                              0
#define         I2C_ERR                             1

//====================================================================================
//================================================================= MAX17048 REGISTERS
//====================================================================================
#define 		VCELL_REGISTER						0x02
#define 		SOC_REGISTER						0x04
#define 		MODE_REGISTER						0x06
#define 		VERSION_REGISTER					0x08
#define 		CONFIG_REGISTER						0x0C
#define 		COMMAND_REGISTER					0xFE

//====================================================================================
#define			BATTERY_OK						    0		
#define			BATTERY_LOW_POWER					1	
#define			BATTERY_DISCHARGED                  2	
//====================================================================================
int MAX17048Reset(void);
int MAX17048QuickStart(void); 
int MAX17048SleepMode(void); 
int MAX17048GetVoltage(uint32_t *data);
int MAX17048GetCharge(uint8_t *data);
int MAX17048GetVersion(uint32_t *data); 

//uint8_t MAX17048GetCompensateValue(void);         
//uint8_t MAX17048GetAlertThreshold(void);
//void MAX17048SetAlertThreshold(uint8_t threshold);
//bool MAX17048ReadAlert(void); 
//void MAX17048ClearAlert(void); 
//====================================================================================

#endif
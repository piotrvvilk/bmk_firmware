#ifndef LIS2DH_H__
#define LIS2DH_H__

//==================================================================================== 
extern int16_t x_axis, y_axis, z_axis;
extern int8_t  x_l_axis, y_l_axis, z_l_axis;
extern uint8_t accel_temp;
extern bool lis_int1_flag;

//==================================================================================== 
#define		LIS2DH_SLAVE_ADDRESS			0x18
#define		LIS2DH_ID				        0x33

//====================================================================================
//================================================================== LIS2DSH REGISTERS
//====================================================================================
#define		LIS2DH_STATUS_REG_AUX			0x07

#define		LIS2DH_OUT_TEMP_L				0x0C
#define		LIS2DH_OUT_TEMP_H				0x0D

#define		LIS2DH_INT_COUNTER_REG		    0x0E

#define		LIS2DH_WHO_AM_I					0x0F   

#define		LIS2DH_TEMP_CONFIG				0x1F

#define		LIS2DH_REG1						0x20
#define		LIS2DH_REG2						0x21
#define		LIS2DH_REG3						0x22
#define		LIS2DH_REG4						0x23
#define		LIS2DH_REG5						0x24
#define		LIS2DH_REG6						0x25
#define		LIS2DH_REFERENCE				0x26
#define		LIS2DH_STATUS_REG2				0x27

#define		LIS2DH_OUT_X_L					0x28
#define		LIS2DH_OUT_X_H					0x29
#define		LIS2DH_OUT_Y_L					0x2A
#define		LIS2DH_OUT_Y_H					0x2B
#define		LIS2DH_OUT_Z_L					0x2C
#define		LIS2DH_OUT_Z_H					0x2D

#define		LIS2DH_FIFO_CTRL				0x2E
#define		LIS2DH_FIFO_SRC					0x2F

#define		LIS2DH_INT1_CFG					0x30
#define		LIS2DH_INT1_SOURCE				0x31
#define		LIS2DH_INT1_THS					0x32
#define		LIS2DH_INT1_DURATION			0x33

#define		LIS2DH_INT2_CFG					0x34
#define		LIS2DH_INT2_SOURCE				0x35
#define		LIS2DH_INT2_THS					0x36
#define		LIS2DH_INT2_DURATION			0x37

#define		LIS2DH_CLICK_CFG				0x38
#define		LIS2DH_CLICK_SRC				0x39
#define		LIS2DH_CLICK_THS				0x3A

#define		LIS2DH_TIME_LIMIT				0x3B
#define		LIS2DH_TIME_LATENCY				0x3C
#define		LIS2DH_TIME_WINDOW				0x3D

#define		LIS2DH_ACT_THS					0x3E
#define		LIS2DH_ACT_DUR					0x3F

//============================================================================ 
uint32_t i2c_init(void);
uint8_t get_accel_ID(void);
int8_t get_accel_temp(void);
void release_interrupt(void);
void get_accel_data(int16_t *x, int16_t *y, int16_t *z);
void get_accel_low_data(int8_t *x, int8_t *y, int8_t *z);
void accel_movement_detect(uint32_t val);
void accel_click_detect(uint32_t val);
void accel_click_detect_yt(uint32_t val);
void accel_power_down(void);

//============================================================================ 
#endif

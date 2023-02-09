#ifndef I2C_DEVICES_H__
#define I2C_DEVICES_H__

#define THREAD_I2C_DEVICES_PRIORITY 					7
#define THREAD_I2C_DEVICES_STACKSIZE          			512

extern uint8_t max17048_charge;

void thread_i2c_devices(void);

#endif


#ifndef MAIN_H__
#define MAIN_H__

//-------------------------------------------------------------------- system errors
#define         RESULT_OK                       0
#define         RESULT_ERR                      1
#define         BUSY                            2
#define         TIMEOUT                         3    
#define         BAD_PARAMETER                   4    
#define         UNAVAILABLE                     5
#define         INVALID_COMMAND                 6
#define         INVALID_PARAMETER               7
#define         INVALID_DATA_LENGHT             8    
#define         INVALID_STATE                   9
#define         TERMINATED                      10
#define         SUSPENDED                       11

//-------------------------------------------------------------------- device states
#define         BMK_STANDBY                     0
#define         BMK_ACTIVE                      1

//-------------------------------------------------------------------- pairing state
#define         NO_ACTION                       0
#define         PAIRING                         1
#define         PAIRING_ON_DISPLAY              2
#define         PAIRED                          3
#define         PAIRED_ON_DISPLAY               4
#define         PAIRING_CANCELED                5
#define         PAIRING_CANCELED_ON_DISPLAY     6
#define         PAIRING_ERROR                   7
#define         PAIRING_ERROR_ON_DISPLAY        8
#define         CONNECTED                       9
#define         DISCONNECTED                    10


//-------------------------------------------------------------------- global variables
extern volatile uint32_t        device_active_counter;
extern volatile uint32_t        device_state;
extern volatile uint32_t        lcd_pairing_state;        
extern volatile uint32_t        led_pairing_state;
//-------------------------------------------------------------------- public functions
int hid_buttons_press(const uint8_t *keys, size_t cnt);
int hid_buttons_release(const uint8_t *keys, size_t cnt);
void device_active_time_reset(void);
void device_active_time_stop(void);
void num_comp_reply(bool accept);

//--------------------------------------------------------------------

#endif 

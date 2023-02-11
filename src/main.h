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

//------------------------------------------------------------------- global variables
extern uint32_t     device_active_counter;
extern uint32_t     device_state;

//------------------------------------------------------------------- public functions
void device_active_time_reset(void);
void device_active_time_stop(void);

//-------------------------------------------------------------------

#endif 

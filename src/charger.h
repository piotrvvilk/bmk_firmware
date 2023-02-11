#ifndef CHARGER_H__
#define CHARGER_H__

//------------------------------------------------------- thread
#define THREAD_CHARGER_PRIORITY 					7
#define THREAD_CHARGER_STACKSIZE       			    512

//------------------------------------------------------- usb & charger states
#define                 USB_DISCONNECTED            0
#define                 USB_CONNECTED               1

#define                 CHARGER_DISABLE             0
#define                 CHARGER_CHARGING            1
#define                 CHARGER_DONE                2

//------------------------------------------------------- types
typedef struct charger_data
{
    uint32_t            usb_status;					    
    uint32_t            charger_status;					
    uint32_t            charged_counter;
}charger_data_t;

//------------------------------------------------------- global variables
extern charger_data_t     charger_data;

//------------------------------------------------------- public functions
void thread_charger(void);

#endif


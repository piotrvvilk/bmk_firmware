#ifndef CHARGER_H__
#define CHARGER_H__

//---------------------------------------------------------------------------
// Definitions 
//---------------------------------------------------------------------------
#define THREAD_CHARGER_PRIORITY 					7
#define THREAD_CHARGER_STACKSIZE       			    512

//------------------------------------------------------- usb & charger states
#define                 USB_DISCONNECTED            0
#define                 USB_CONNECTED               1

#define                 CHARGER_DISABLE             0
#define                 CHARGER_CHARGING            1
#define                 CHARGER_DONE                2

typedef struct charger_data_def
{
    uint32_t            usb_status;		                    //connected/disconnected 			    
    uint32_t            charger_status;					    //charging/cherged/disable    
    uint32_t            charged_counter;                    //auxliary counter
    uint32_t 			usb_pin_state;                      //generating event after usb state change
    uint32_t 			usb_pin_old_state;                  //
    uint32_t 			charging_pin_state;                 //generating event after charger state change
    uint32_t 			charging_pin_old_state;             //
    bool 				charger_locked;                     //true when charged first time, prevent continuous switch between charging and charged 
}charger_data_t;

//---------------------------------------------------------------------------
// Global objects 
//---------------------------------------------------------------------------
extern charger_data_t     charger_data;

//---------------------------------------------------------------------------
// Public functions
//---------------------------------------------------------------------------
void thread_charger(void);

#endif


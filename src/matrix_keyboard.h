#ifndef MATRIX_KEYBOARD_H__
#define MATRIX_KEYBOARD_H__

//------------------------------------------------------- thread
#define THREAD_KEYBOARD_PRIORITY 					7
#define THREAD_KEYBOARD_STACKSIZE       			512

//------------------------------------------------------- global variables
extern uint8_t      device_theme;
extern uint8_t      last_theme;
extern uint32_t	    led_key_pressed;

//------------------------------------------------------- public functions
void thread_keyboard(void);

#endif


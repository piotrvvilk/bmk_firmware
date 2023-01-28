#ifndef KEYBOARD_H__
#define KEYBOARD_H__

#define THREAD_KEYBOARD_PRIORITY 					7
#define THREAD_KEYBOARD_STACKSIZE       			512

extern uint8_t      device_theme;
extern uint8_t      last_theme;
extern uint32_t	    led_key_pressed;

void thread_keyboard(void);

#endif


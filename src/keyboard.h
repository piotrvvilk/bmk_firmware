#ifndef KEYBOARD_H__
#define KEYBOARD_H__

#define THREAD_KEYBOARD_PRIORITY 					7
#define THREAD_KEYBOARD_STACKSIZE       			512

extern uint32_t key_pressed;

void thread_keyboard(void);

#endif


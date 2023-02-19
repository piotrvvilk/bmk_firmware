#ifndef LCD_H__
#define LCD_H__

//------------------------------------------------------- thread
#define     THREAD_LCD_PRIORITY 			7
#define     THREAD_LCD_STACKSIZE       		2048

extern uint8_t display_theme;
extern uint32_t refresh_screen_flag;

//------------------------------------------------------- public functions
void display_info_screen(void);
void thread_lcd(void);



#endif

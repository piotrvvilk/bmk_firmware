#ifndef LED_STRIP_H__
#define LED_STRIP_H__

#define		COLOR_BLACK		    0
#define		COLOR_WHITE		    1
#define		COLOR_RED		    2
#define		COLOR_GREEN		    3
#define		COLOR_BLUE		    4
#define		COLOR_YELLOW	    5
#define		COLOR_VIOLET	    6
#define		COLOR_TURQUOISE	    7
#define		COLOR_ORANGE	    8

extern uint8_t gta_pattern[];

int led_strip_init(void);
int set_button_color(uint8_t position, uint8_t color);
int set_button_pattern_gta(void);


#endif


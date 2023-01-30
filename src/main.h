#ifndef MAIN_H__
#define MAIN_H__

#define		THEME_FIRST						1
#define		THEME_LAST						4

#define		THEME_INFO						1
#define		THEME_GTA						2
#define		THEME_ALTIUM					3
#define		THEME_VSC						4

#define		NO_THEME						0

//-------------------------------------------------------------------
extern uint32_t     device_active_counter;

//-------------------------------------------------------------------
void device_active_time_reset(void);
void device_active_time_stop(void);

//-------------------------------------------------------------------

#endif 

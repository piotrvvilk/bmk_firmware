#ifndef CONFIG_APP_H__
#define CONFIG_APP_H__

//======================================================= APPLICATION FEATURES
#define	        USE_DISPLAY                     1
#ifdef          USE_DISPLAY
    #define	    USE_GTA_PICTURE                 1
    #define	    USE_ALTIUM_PICTURE              1
    #define	    USE_VSC_PICTURE                 1
    #define	    USE_LOGO_PICTURE                1
    #define	    USE_BLE_PICTURE                 1
    #define	    USE_BATTERY_PICTURE             1
    #define	    USE_PLUG_PICTURE                1
#endif

#define         USE_BLE                         1 
#define         USE_MATRIX_KEYBOARD             1
#define	        USE_USB                         1
#define	        USE_CHARGER                     1
#define	        USE_LIS2DH                      1
#define	        USE_MAX17048                    1
#define	        USE_LED                         1
#define	        USE_BUZZER                      1

//======================================================= APPLICATION TEST
//#define         MAKE_TEST                       1             
#ifdef          MAKE_TEST
    #define     MAKE_LED_PWM_TEST               1 
    #define     MAKE_LED_STRIP_TEST             1 
#endif

//======================================================= APPLICATION DEBUG LOGGER
#define         DEBUG_LOG_APP                   1
#ifdef          DEBUG_LOG_APP                     
    #define     DEBUG_LOG_DEVICE                1
    //#define     DEBUG_LOG_MATRIX_KEYBOARD       1
    //#define     DEBUG_LOG_LED                   1
    #define     DEBUG_LOG_LIS2DH                1
    #define     DEBUG_LOG_MAX17048              1
    #define     DEBUG_LOG_I2C_DEVICES           1
    //#define     DEBUG_LOG_USB                   1
    //#define     DEBUG_LOG_CHARGER               1
    

#endif

//======================================================= APPLICATION SETTINGS 
#define         DEVICE_ACTIVE_TIME              15*10


//======================================================= 

#endif
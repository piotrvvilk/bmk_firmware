#ifndef LED_PWM_H__
#define LED_PWM_H__

#define     THREAD_LED_PWM_PRIORITY 		7
#define     THREAD_LED_PWM_STACKSIZE    	512

#define     LED_RED_PWM                     0
#define     LED_GREEN_PWM                   1
#define     LED_BLUE_PWM                    2

#define     MAX_BRIGHTNESS	                100
#define     FADE_DELAY_MS	                10
#define     FADE_DELAY	                    K_MSEC(FADE_DELAY_MS)

void thread_led_pwm(void);

#endif


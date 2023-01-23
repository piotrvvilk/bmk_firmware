
#ifndef BOARD_H__
#define BOARD_H__

//UNUSED PINS, BUT DEFINED
//SPI0, WS2812:
//MISO: P1.08 (SIO40)
//SCK:  P1.09 (SIO41)

//SPI3, LCD
//MISO: P0.14 (SIO14)

//----------------------------------------------------------------- 
#define	LEDR_NODE		DT_ALIAS(ledr)
#define	LEDG_NODE		DT_ALIAS(ledg)
#define	LEDB_NODE		DT_ALIAS(ledb)

#define	ENUSBDET_NODE	DT_ALIAS(enusbdet)
#define	USBDET_NODE		DT_ALIAS(usbdet)

#define	CHRGEN_NODE		DT_ALIAS(chargeren)
#define	CHRGDET_NODE	DT_ALIAS(chargerdet)

#define	VLEDEN_NODE		DT_ALIAS(vleden)

#define	BUZZER_NODE		DT_ALIAS(buzzer)

#define	ACCEL1_NODE		DT_ALIAS(accelint1)
#define	ACCEL2_NODE		DT_ALIAS(accelint2)

#define	COL1_NODE		DT_ALIAS(col1)
#define	COL2_NODE		DT_ALIAS(col2)
#define	COL3_NODE		DT_ALIAS(col3)
#define	COL4_NODE		DT_ALIAS(col4)
#define	ROW1_NODE		DT_ALIAS(row1)
#define	ROW2_NODE		DT_ALIAS(row2)
#define	ROW3_NODE		DT_ALIAS(row3)

#define	DISPRST_NODE	DT_ALIAS(disprst)
#define	DISPBK_NODE		DT_ALIAS(dispbk)
#define	DISPCS_NODE		DT_ALIAS(dispcs)
#define	DISPDC_NODE		DT_ALIAS(dispdc)

//----------------------------------------------------------------- 
extern const struct gpio_dt_spec led_red;
extern const struct gpio_dt_spec led_green;
extern const struct gpio_dt_spec led_blue;

extern const struct gpio_dt_spec enusbdet;
extern const struct gpio_dt_spec usbdet;

extern const struct gpio_dt_spec chrgdet;
extern const struct gpio_dt_spec chrgen;

extern const struct gpio_dt_spec vleden;

extern const struct gpio_dt_spec buzzer;

extern const struct gpio_dt_spec accelint1;
extern const struct gpio_dt_spec accelint2;

extern const struct gpio_dt_spec col1;
extern const struct gpio_dt_spec col2;
extern const struct gpio_dt_spec col3;
extern const struct gpio_dt_spec col4;
extern const struct gpio_dt_spec row1;
extern const struct gpio_dt_spec row2;
extern const struct gpio_dt_spec row3;

extern const struct gpio_dt_spec disprst;
extern const struct gpio_dt_spec dispbk;
extern const struct gpio_dt_spec dispcs;
extern const struct gpio_dt_spec dispdc;

// #define     led_red_on()            gpio_pin_set_dt(&led_red,1);         //
// #define     led_red_off()           gpio_pin_set_dt(&led_red,0);
// #define     led_green_on()          gpio_pin_set_dt(&led_green,1);
// #define     led_green_off()         gpio_pin_set_dt(&led_green,0);
// #define     led_blue_on()           gpio_pin_set_dt(&led_blue,1);
// #define     led_blue_off()          gpio_pin_set_dt(&led_blue,0);

#define     usb_detection_on()      gpio_pin_set_dt(&usbdet,1);
#define     usb_detection_off()     gpio_pin_set_dt(&usbdet,0);

#define     vled_on()               gpio_pin_set_dt(&vleden,1);
#define     vled_off()              gpio_pin_set_dt(&vleden,0);

#define     charger_on()            gpio_pin_set_dt(&chrgen,1);
#define     charger_off()           gpio_pin_set_dt(&chrgen,0);

#define     lcd_backlight_on()      gpio_pin_set_dt(&dispbk,1);
#define     lcd_backlight_off()     gpio_pin_set_dt(&diskbk,0);

#define     RST_H()                 gpio_pin_set_dt(&disprst,1);
#define     RST_L()                 gpio_pin_set_dt(&disprst,0);

#define     DC_H()                  gpio_pin_set_dt(&dispdc,1);
#define     DC_L()                  gpio_pin_set_dt(&dispdc,0);

#define     CS_H()                  gpio_pin_set_dt(&dispcs,1);
#define     CS_L()                  gpio_pin_set_dt(&dispcs,0);

//----------------------------------------------------------------- 
int gpio_init(void);



#endif 

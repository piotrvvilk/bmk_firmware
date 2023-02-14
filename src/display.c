#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

#include <zephyr/kernel.h>
#include <zephyr/kernel_structs.h>
#include <zephyr/device.h>
#include <zephyr/types.h>
#include <zephyr/devicetree.h>
#include <zephyr/sys/byteorder.h>
#include <soc.h>
#include <assert.h>
#include <zephyr/spinlock.h>
#include <zephyr/settings/settings.h>

#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/display.h>
#include <lvgl.h>

#include <zephyr/sys/printk.h>
#include <zephyr/logging/log.h>

#include "main.h"
#include "version.h"
#include "board.h"
#include "display.h"
#include "led.h"
#include "matrix_keyboard.h"
#include "config_app.h"
#include "i2c_devices.h"
#include "charger.h"

const struct device *display_dev;

uint32_t lcd_tmp=10;
uint8_t display_theme;

size_t cursor = 0, color = 0;
int rc;

LOG_MODULE_REGISTER(my_bmk_lcd,LOG_LEVEL_DBG);

static uint32_t get_color_value(uint8_t battery_val){
	if (battery_val < 6) return 0xFF0000;
	if (battery_val < 16) return 0x0000FF;
	return 0x00FF00;
}

//==================================================================================================================================================
static void display_battery(uint8_t battery_val)
{
    uint32_t color;
    uint8_t bat;
    unsigned char digits[3], tmp, i;

//-------------------------------------------------------------- charging value to string
    bat=battery_val;
    for(i=0;i<3;i++)
    {
        tmp=bat%10;
        bat/=10;
        digits[2-i]=tmp+0x30;
    }

//-------------------------------------------------------------- charging value font color    
    color = get_color_value(battery_val);
	if(digits[0]=='0')
	{
		digits[0]=' ';
		if(digits[1]=='0') 
		{
			digits[1]=' ';        
		}
	}
//-------------------------------------------------------------- battery icon
	//LV_IMG_DECLARE(battery_hot);
	LV_IMG_DECLARE(battery_cold);
	lv_obj_t * img1 = lv_img_create(lv_scr_act());
	
	// if(charger_data.charger_status==CHARGER_CHARGING)
	// {
	// 	lv_img_set_src(img1, &battery_hot);	
	// }
	// else
	// {
		lv_img_set_src(img1, &battery_cold);
//	}	

	lv_obj_align(img1, LV_ALIGN_CENTER, 0, -44);
	lv_obj_set_size(img1, 80, 32);

//-------------------------------------------------------------- usb plug icon
	LV_IMG_DECLARE(plug_hot);
	LV_IMG_DECLARE(plug_cold);
	lv_obj_t * img2 = lv_img_create(lv_scr_act());
	
	if(charger_data.usb_status==USB_CONNECTED)
	{
		if(charger_data.charger_status==CHARGER_CHARGING)
		{
			lv_img_set_src(img2, &plug_hot);	
		}
		else
		{
			lv_img_set_src(img2, &plug_cold);
		}	
		
	    lv_obj_align(img2, LV_ALIGN_CENTER, 100, -44);
		lv_obj_set_size(img2, 88, 36);
	}

//-------------------------------------------------------------- charging value label
	lv_obj_t * label3 = lv_label_create(lv_scr_act());
	lv_label_set_recolor(label3, true);
	lv_label_set_text(label3, digits);
	lv_obj_set_style_text_color(lv_scr_act(), lv_color_hex(color), LV_PART_MAIN);
	
	if(digits[0]='1')
	{
		lv_obj_align(label3, LV_ALIGN_CENTER, 5, -44);	
	}
	else
	{
		lv_obj_align(label3, LV_ALIGN_CENTER, 0, -44);
	}
}

//==================================================================================================================================================
void thread_lcd(void)
{
	#ifdef USE_DISPLAY

		display_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));

		if (!device_is_ready(display_dev)) {
			LOG_ERR("Device not ready, aborting test");
			return;
		}
		lcd_backlight_on();
			
		lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x000000), LV_PART_MAIN);

		LV_IMG_DECLARE(logo);
		lv_obj_t * img1 = lv_img_create(lv_scr_act());
		lv_img_set_src(img1, &logo);
		lv_obj_align(img1, LV_ALIGN_CENTER, 0, 0);
		lv_obj_set_size(img1, 240, 160);
		lv_task_handler();
		display_blanking_off(display_dev);
    
		while(1)
		{
			if(device_theme!=display_theme)
			{
				if(device_theme==THEME_GTA)
				{
					display_theme=device_theme;
					LV_IMG_DECLARE(gta);
					lv_obj_t * img1 = lv_img_create(lv_scr_act());
					lv_img_set_src(img1, &gta);
					lv_obj_align(img1, LV_ALIGN_CENTER, 0, 0);
					lv_obj_set_size(img1, 320, 190);
					lv_task_handler();
					display_blanking_off(display_dev);
					lcd_backlight_on();
				}

				if(device_theme==THEME_ALTIUM)
				{
					display_theme=device_theme;
					lv_obj_clean(lv_scr_act());
					LV_IMG_DECLARE(altium);
					lv_obj_t * img1 = lv_img_create(lv_scr_act());
					lv_img_set_src(img1, &altium);
					lv_obj_align(img1, LV_ALIGN_CENTER, 0, 0);
					lv_obj_set_size(img1, 220, 160);
					lv_task_handler();
					display_blanking_off(display_dev);
					lcd_backlight_on();
				}


				if(device_theme==THEME_VSC)
				{
					display_theme=device_theme;
					lv_obj_clean(lv_scr_act());
					LV_IMG_DECLARE(vsc);
					lv_obj_t * img1 = lv_img_create(lv_scr_act());
					lv_img_set_src(img1, &vsc);
					lv_obj_align(img1, LV_ALIGN_CENTER, 0, 0);
					lv_obj_set_size(img1, 220, 160);
					lv_task_handler();
					display_blanking_off(display_dev);
					lcd_backlight_on();
				}


				if(device_theme==THEME_INFO)
				{
					display_theme=device_theme;
					lv_obj_clean(lv_scr_act());

					LV_IMG_DECLARE(logo);
					lv_obj_t * img1 = lv_img_create(lv_scr_act());
					lv_img_set_src(img1, &logo);
					lv_obj_align(img1, LV_ALIGN_CENTER, -120, 0);
					lv_obj_set_size(img1, 80, 80);
					
					LV_IMG_DECLARE(ble);
					img1 = lv_img_create(lv_scr_act());
					lv_img_set_src(img1, &ble);
					lv_obj_align(img1, LV_ALIGN_CENTER, 110, 40);
					lv_obj_set_size(img1, 48, 64);
				
					lv_obj_t * label1 = lv_label_create(lv_scr_act());
					lv_obj_t * label2 = lv_label_create(lv_scr_act());
					lv_label_set_recolor(label1, true);
					lv_label_set_recolor(label2, true);
					
					lv_label_set_text(label1, STR_VER);
					lv_obj_set_style_text_color(label1, lv_color_hex(0xffffff), LV_PART_MAIN);
					lv_obj_align(label1, LV_ALIGN_CENTER, 0, 20);
					
					lv_label_set_text(label2, STR_DATE);
					lv_obj_set_style_text_color(label2, lv_color_hex(0xffffff), LV_PART_MAIN);
					lv_obj_align(label2, LV_ALIGN_CENTER, 0, 50);
					
					display_battery(max17048_charge);

					lv_task_handler();
					display_blanking_off(display_dev);
					
					lcd_backlight_on();
				}

				if(device_theme==NO_THEME)
				{
					lcd_backlight_off();
					display_theme=device_theme;
					
				}
			}

			k_msleep(100);
		}

	#endif
	
}

//==================================================================================================================================================


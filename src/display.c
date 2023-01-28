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

#include "board.h"
#include "display.h"
#include "main.h"
#include "matrix_keyboard.h"
#include "config_app.h"

const struct device *display_dev;

uint32_t lcd_tmp=10;
uint8_t display_theme;

size_t cursor = 0, color = 0;
int rc;

LOG_MODULE_REGISTER(my_bmk_lcd,LOG_LEVEL_DBG);

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

		// // /*Create a white label, set its text and align it to the center*/
		// lv_obj_t * label = lv_label_create(lv_scr_act());
		// lv_label_set_text(label, "Hello world");
		// //lv_label_set_text_font(label, &LV_FONT_MONTSERRAT_20);
		// lv_obj_set_style_text_color(lv_scr_act(), lv_color_hex(0xffffff), LV_PART_MAIN);
		// lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);

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
					lv_obj_set_size(img1, 220, 160);
					lv_task_handler();
					display_blanking_off(display_dev);
					lcd_backlight_on();
				}

				if(device_theme==THEME_ALTIUM)
				{
					display_theme=device_theme;
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
					LV_IMG_DECLARE(logo);
					lv_obj_t * img1 = lv_img_create(lv_scr_act());
					lv_img_set_src(img1, &logo);
					lv_obj_align(img1, LV_ALIGN_CENTER, 0, 0);
					lv_obj_set_size(img1, 220, 160);
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


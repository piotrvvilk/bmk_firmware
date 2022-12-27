
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

#include <zephyr/drivers/led_strip.h>

#include <zephyr/sys/printk.h>
#include <zephyr/logging/log.h>

#include "led_strip.h"
#include "keyboard.h"

LOG_MODULE_REGISTER(my_bmk_led_strip,LOG_LEVEL_DBG);

#define STRIP_NODE			DT_ALIAS(led_strip)
#define STRIP_NUM_PIXELS	DT_PROP(DT_ALIAS(led_strip), chain_length)

#define RGB(_r, _g, _b) { .r = (_r), .b = (_b), .g = (_g) }

static const struct led_rgb colors[] = {
	RGB(0x00, 0x00, 0x00), 						/* black */
	RGB(0x20, 0x2F, 0x2F), 						/* white */
	RGB(0x2f, 0x00, 0x00), 						/* red */
	RGB(0x00, 0x2f, 0x00), 						/* green */
	RGB(0x00, 0x00, 0x2f), 						/* blue */
	RGB(0x2f, 0x2f, 0x00), 						/* yellow */
	RGB(0x2f, 0x00, 0x2f), 						/* violet */
	RGB(0x00, 0x2f, 0x2f), 						/* turquoise */
	RGB(0x2F, 0x17, 0x00) 						/* orange */
};

struct led_rgb pixels[STRIP_NUM_PIXELS];

static const struct device *const strip = DEVICE_DT_GET(STRIP_NODE);

union Pat{
	struct led_rgb pix[STRIP_NUM_PIXELS];
	uint8_t data[4*STRIP_NUM_PIXELS];
};

static union Pat my_pix;						     						//led strip buffer
const uint8_t *current_pattern;												//pointer to current led strip pattern
int8_t mode_counter=MODE_GTA;												//mode counter

//=================================================================================================================
int led_strip_init(void)
{
	if(device_is_ready(strip)) 
	{
        return 0;
	} 
	else 
	{
		return 1;
	}
}

//=================================================================================================================
int set_button_color(uint8_t position, uint8_t color)
{
	position -= 1;
	int rc;
	memcpy(&my_pix.pix[position], &colors[color], sizeof(struct led_rgb));
	rc = led_strip_update_rgb(strip, my_pix.pix, STRIP_NUM_PIXELS);
    return rc;
}
//=================================================================================================================
int set_button_pattern(const uint8_t *pattern)
{
	int rc;
	memcpy(&my_pix.data, pattern, 40);
	
	rc = led_strip_update_rgb(strip, my_pix.pix, STRIP_NUM_PIXELS);
	return rc;
}

//=================================================================================================================
int turn_off_all_buttons(void)
{
	int rc;
	memcpy(&my_pix.data, &turn_off_pattern, 40);
	
	rc = led_strip_update_rgb(strip, my_pix.pix, STRIP_NUM_PIXELS);
	return rc;
}

//=================================================================================================================
int set_pattern_without_one_button(uint32_t position)
{
	int rc;
	memcpy(&my_pix.pix[position-1], &colors[COLOR_BLACK], sizeof(struct led_rgb));
	rc = led_strip_update_rgb(strip, my_pix.pix, STRIP_NUM_PIXELS);
	return rc;
}

//==================================================================================================================================================
void thread_led_strip(void)
{
	// set_button_color(1,COLOR_WHITE);
	// set_button_color(2,COLOR_RED);
	// set_button_color(3,COLOR_GREEN);
	// set_button_color(4,COLOR_BLUE);
	// set_button_color(5,COLOR_YELLOW);
	// set_button_color(6,COLOR_VIOLET);
	// set_button_color(7,COLOR_TURQUOISE);
	// set_button_color(8,COLOR_ORANGE);

	//k_sleep(K_MSEC(3000));
	
	//set_button_pattern(gta_pattern);
	//set_button_pattern_gta();
	//set_button_color(4,COLOR_BLACK);

	led_strip_init();
	current_pattern = gta_pattern;
	set_button_pattern(current_pattern);
 	
	while(1)
 	{
		if(key_pressed!=0)
		{
			if(key_pressed==1)
			{
				LOG_INF("LED_KEY: %d\n",key_pressed);
				mode_counter--;
				if(mode_counter<0) mode_counter=MODE_VSC;		
				{
					switch(mode_counter)
					{
					case MODE_GTA:
						current_pattern = gta_pattern;		
						break;
					case MODE_ALTIUM:
						current_pattern = altium_pattern;		
						break;
					case MODE_VSC:
						current_pattern = vsc_pattern;		
						break;
					default:
						break;
					}		
				}

    			set_button_pattern(current_pattern);
				set_pattern_without_one_button(key_pressed);
				k_msleep(250);
				set_button_pattern(current_pattern);
				key_pressed=0;
			}

			else if(key_pressed==3)
			{
				LOG_INF("LED_KEY: %d\n",key_pressed);
				mode_counter++;
				if(mode_counter>MODE_VSC) mode_counter=MODE_GTA;		
				{
					switch (mode_counter)
					{
					case MODE_GTA:
						current_pattern = gta_pattern;		
						break;
					case MODE_ALTIUM:
						current_pattern = altium_pattern;		
						break;
					case MODE_VSC:
						current_pattern = vsc_pattern;		
						break;
					default:
						break;
					}		
				}

    			set_button_pattern(current_pattern);
				set_pattern_without_one_button(key_pressed);
				k_msleep(250);
				set_button_pattern(current_pattern);
				key_pressed=0;
			}

			else if((key_pressed!=1)&&(key_pressed!=3))
			{
				set_pattern_without_one_button(key_pressed);
				k_msleep(250);
				set_button_pattern(current_pattern);
				key_pressed=0;
			}

		}

		k_msleep(100);
	}
		
}

//==================================================================================================================================================
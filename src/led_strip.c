
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

#include <zephyr/kernel.h>
#include <zephyr/kernel_structs.h>
#include <zephyr/device.h>
#include <zephyr/types.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/led_strip.h>

#include "led_strip.h"

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

uint8_t gta_pattern[40] = { 0x00, 0x20, 0x2F, 0x2F, 
							0x00, 0x00, 0x2f, 0x00, 
							0x00, 0x20, 0x2F, 0x2F,
		         			0x00, 0x2f, 0x00, 0x00, 
							0x00, 0x2f, 0x00, 0x00, 
							0x00, 0x2f, 0x00, 0x00, 
							0x00, 0x2f, 0x00, 0x00,
				        	0x00, 0x2f, 0x00, 0x00, 
							0x00, 0x2f, 0x00, 0x00, 
							0x00, 0x2f, 0x00, 0x00};

union Pat{
	struct led_rgb pix[STRIP_NUM_PIXELS];
	uint8_t data[4*STRIP_NUM_PIXELS];
};

union Pat my_pix;

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
	memcpy(&pixels[position], &colors[color], sizeof(struct led_rgb));
	rc = led_strip_update_rgb(strip, pixels, STRIP_NUM_PIXELS);
    return rc;
}

//=================================================================================================================
int set_button_pattern_gta(void)
{
	int rc;
	memcpy(&pixels[0], &colors[COLOR_GREEN], 3); memcpy(&pixels[1], &colors[COLOR_VIOLET], 3); memcpy(&pixels[2], &colors[COLOR_GREEN], 3);
	for(int i=3; i<10; i++)
	{
		memcpy(&pixels[i], &colors[COLOR_RED], 3);		
	}
	
	rc = led_strip_update_rgb(strip, pixels, STRIP_NUM_PIXELS);
	return rc;
}

//=================================================================================================================
int set_button_pattern_my(void)
{
	int rc;
	memcpy(&my_pix.data, &gta_pattern, 40);
	
	rc = led_strip_update_rgb(strip, my_pix.pix, STRIP_NUM_PIXELS);
	return rc;
}

//=================================================================================================================
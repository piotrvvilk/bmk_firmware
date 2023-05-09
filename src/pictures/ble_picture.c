#ifdef __has_include
    #if __has_include("lvgl.h")
        #ifndef LV_LVGL_H_INCLUDE_SIMPLE
            #define LV_LVGL_H_INCLUDE_SIMPLE
        #endif
    #endif
#endif

#include "../config_app.h"

#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
    #include "lvgl.h"
#else
  #ifdef USE_DISPLAY 
    #include "lvgl/lvgl.h"
  #endif
#endif


#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

#ifndef LV_ATTRIBUTE_IMG_BLE
#define LV_ATTRIBUTE_IMG_BLE
#endif


#ifdef USE_BLE_PICTURE

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_BLE uint8_t ble_map[] = {
#if LV_COLOR_DEPTH == 16 && LV_COLOR_16_SWAP != 0
  /*Pixel format: Red: 5 bit, Green: 6 bit, Blue: 5 bit BUT the 2 bytes are swapped*/
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x21, 0x00, 0x63, 0x00, 0x62, 0x00, 0x62, 0x00, 0x62, 0x00, 0x62, 0x00, 0x62, 0x00, 0x62, 0x00, 0x62, 0x00, 0x62, 0x00, 0x63, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x08, 0x02, 0x0f, 0x02, 0x0f, 0x01, 0x8c, 0x04, 0x1f, 0x05, 0x3f, 0x04, 0xff, 0x04, 0xff, 0x04, 0xff, 0x04, 0xff, 0x04, 0xff, 0x04, 0xff, 0x04, 0xff, 0x04, 0xff, 0x05, 0x3f, 0x03, 0x38, 0x01, 0xcd, 0x02, 0x0f, 0x01, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc6, 0x00, 0xe7, 0x02, 0x30, 0x03, 0xfe, 0x04, 0xbf, 0x04, 0x9f, 0x04, 0xbf, 0x04, 0x5f, 0x03, 0xff, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x7f, 0x04, 0xbf, 0x04, 0x9f, 0x03, 0xfe, 0x02, 0x30, 0x01, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x6a, 0x04, 0x1e, 0x04, 0x1f, 0x04, 0x5f, 0x04, 0x5f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x5f, 0x04, 0x5f, 0x04, 0x7f, 0x02, 0x50, 0x01, 0x29, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa5, 0x02, 0x90, 0x04, 0x1f, 0x04, 0x7f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x03, 0xff, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0xbf, 0x04, 0x5f, 0x01, 0x4a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa5, 0x03, 0xb9, 0x04, 0xdf, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x1f, 0x0c, 0x1f, 0x3c, 0xff, 0x1c, 0x7f, 0x03, 0xff, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x5f, 0x04, 0x3e, 0x01, 0x6b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa6, 0x03, 0x79, 0x04, 0x7f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x1f, 0x14, 0x1f, 0xa6, 0x9f, 0xa6, 0x7f, 0x03, 0xdf, 0x03, 0xff, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x5f, 0x04, 0x3e, 0x01, 0x8c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc6, 0x03, 0x9a, 0x04, 0x7f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x0b, 0xff, 0xa6, 0xbf, 0xff, 0xff, 0x86, 0x1f, 0x03, 0xdf, 0x03, 0xff, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x5f, 0x04, 0x3e, 0x01, 0x8c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x4a, 0x04, 0x1e, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x0b, 0xff, 0xa6, 0x9f, 0xff, 0xff, 0xff, 0xff, 0x96, 0x3f, 0x03, 0xff, 0x03, 0xff, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3e, 0x01, 0x6c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x6b, 0x04, 0x5f, 0x04, 0x5f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x0b, 0xff, 0xa6, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x9e, 0x5f, 0x0c, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x9f, 0x03, 0x77, 0x00, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0xb2, 0x04, 0x9f, 0x03, 0xff, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x0b, 0xff, 0xa6, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x96, 0x3e, 0x0b, 0xdf, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x7f, 0x01, 0xee, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xac, 0x04, 0xbf, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x0b, 0xff, 0xa6, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x9e, 0x1e, 0x03, 0xff, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x7f, 0x03, 0x15, 0x00, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x21, 0x02, 0xb4, 0x04, 0x7f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x0b, 0xff, 0xa6, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x96, 0x5f, 0x0c, 0x3f, 0x03, 0xff, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0xdf, 0x02, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x01, 0x8c, 0x04, 0x5f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x0b, 0xff, 0xa6, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xa6, 0x7f, 0x14, 0x3f, 0x03, 0xff, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x5f, 0x03, 0x59, 0x00, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x21, 0x02, 0xf6, 0x04, 0x7f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x0b, 0xff, 0xa6, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xa6, 0x9f, 0x14, 0x1f, 0x03, 0xdf, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x1f, 0x00, 0xa5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x21, 0x02, 0xf7, 0x04, 0x7f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x0b, 0xff, 0xa6, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xa6, 0x7f, 0x14, 0x3f, 0x03, 0xff, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x5f, 0x02, 0xb4, 0x00, 0x21, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x84, 0x03, 0x9b, 0x04, 0x5f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x1f, 0x03, 0xff, 0x03, 0xff, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x0b, 0xff, 0xa6, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x8e, 0x5f, 0x65, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xae, 0x9f, 0x14, 0x5f, 0x03, 0xff, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x7f, 0x03, 0x17, 0x00, 0x21, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x02, 0x0f, 0x04, 0xbf, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x03, 0xbf, 0x03, 0xbf, 0x14, 0x5f, 0x03, 0xff, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x0b, 0xff, 0xa6, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x9e, 0x9f, 0x03, 0x7f, 0x5d, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xae, 0x9f, 0x14, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x1f, 0x01, 0x29, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x01, 0xce, 0x04, 0xbf, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x03, 0xff, 0x03, 0x9f, 0x6d, 0xbf, 0xff, 0xff, 0x7d, 0xff, 0x03, 0xdf, 0x03, 0xff, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x0b, 0xff, 0xa6, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xa6, 0x9f, 0x0c, 0x1f, 0x03, 0x5f, 0x65, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xae, 0xbf, 0x0b, 0xff, 0x03, 0xff, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0xdf, 0x02, 0x0f, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x02, 0xd4, 0x04, 0x7f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x1f, 0x8e, 0x3e, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x8e, 0x5f, 0x0b, 0xff, 0x03, 0xff, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x1f, 0x0b, 0xff, 0xa6, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xa6, 0x9f, 0x0c, 0x1f, 0x04, 0x1f, 0x03, 0x7f, 0x5d, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xb6, 0xbf, 0x14, 0x3f, 0x03, 0xff, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0xbf, 0x01, 0xee, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x63, 0x05, 0x7f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x03, 0xdf, 0x5d, 0x5f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x86, 0x1f, 0x0c, 0x1f, 0x03, 0xff, 0x04, 0x1f, 0x04, 0x1f, 0x0c, 0x1f, 0xa6, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xa6, 0x9f, 0x0c, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x03, 0x9f, 0x6d, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc6, 0xff, 0x14, 0x5f, 0x03, 0xff, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x5f, 0x03, 0xbb, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x42, 0x04, 0xff, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x03, 0xff, 0x2c, 0x9f, 0xcf, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7d, 0xff, 0x03, 0xff, 0x03, 0xff, 0x03, 0xff, 0x0c, 0x1f, 0xa6, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xa6, 0x9f, 0x0c, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x03, 0x9f, 0x54, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3c, 0xdf, 0x03, 0xdf, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x1f, 0x05, 0x3f, 0x00, 0x63, 0x00, 0x00, 
  0x00, 0x21, 0x04, 0xff, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x1f, 0x03, 0xdf, 0x1c, 0x5f, 0xbe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x8e, 0x3f, 0x04, 0x1f, 0x03, 0xdf, 0x0c, 0x1f, 0xa6, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xa6, 0x9f, 0x0c, 0x1f, 0x04, 0x1f, 0x03, 0x9f, 0x5d, 0x1f, 0xef, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xef, 0xbf, 0x5d, 0x5f, 0x03, 0xdf, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0xff, 0x00, 0x21, 0x00, 0x00, 
  0x00, 0xc6, 0x04, 0xdf, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x1f, 0x03, 0xdf, 0x14, 0x3f, 0xbe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x9e, 0x7f, 0x03, 0xdf, 0x0b, 0xff, 0xa6, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xa6, 0x9f, 0x0c, 0x1f, 0x03, 0x7f, 0x5d, 0x1f, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xef, 0xdf, 0x55, 0x1f, 0x03, 0xbf, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0xdf, 0x00, 0xc6, 0x00, 0x00, 
  0x03, 0xbb, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x03, 0xff, 0x24, 0x9f, 0xbe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x9e, 0x3f, 0x03, 0xdf, 0x96, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xa6, 0x9f, 0x03, 0x5f, 0x55, 0x3f, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xef, 0xbf, 0x55, 0x5f, 0x03, 0xff, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x5f, 0x03, 0xbb, 0x00, 0x00, 
  0x04, 0x5f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x1f, 0x03, 0xff, 0x24, 0x7f, 0xcf, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x8e, 0x3f, 0x9e, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x75, 0xdf, 0x45, 0x1f, 0xf7, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xef, 0xbf, 0x55, 0x5f, 0x03, 0xff, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x5f, 0x00, 0x00, 
  0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x03, 0xff, 0x0c, 0x1f, 0xcf, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xef, 0xbf, 0x4c, 0xff, 0x03, 0xdf, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x1f, 0x00, 0x00, 
  0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x03, 0xff, 0x0b, 0xff, 0xcf, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0xdf, 0x44, 0xff, 0x03, 0x9f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x00, 0x00, 
  0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x03, 0xff, 0x0c, 0x3f, 0xc6, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xef, 0xdf, 0x44, 0xff, 0x03, 0x9f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x00, 0x00, 
  0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x03, 0xff, 0x0b, 0xff, 0xcf, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xef, 0xbf, 0x44, 0xff, 0x03, 0xbf, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x00, 0x00, 
  0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x03, 0xff, 0x03, 0xdf, 0xc7, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xbf, 0x34, 0xbf, 0x03, 0x9f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x00, 0x00, 
  0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x03, 0xff, 0x03, 0x9e, 0xf7, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3d, 0x1f, 0x03, 0x5f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x00, 0x00, 
  0x04, 0x3f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x1f, 0x03, 0x5f, 0x75, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x96, 0x5e, 0x03, 0xdf, 0x03, 0xff, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x00, 0x00, 
  0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x03, 0x5f, 0x75, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xa6, 0x9f, 0x03, 0xff, 0x03, 0xff, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x00, 0x00, 
  0x04, 0x3f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x03, 0x9f, 0x7d, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xb6, 0xbf, 0x0c, 0x1f, 0x03, 0xdf, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x00, 0x00, 
  0x04, 0x3f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x03, 0x5f, 0x75, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xae, 0xbf, 0x03, 0xff, 0x03, 0xdf, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x00, 0x00, 
  0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x03, 0x3f, 0x85, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xae, 0xbf, 0x03, 0xff, 0x03, 0xff, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x00, 0x00, 
  0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x1f, 0x03, 0x9f, 0x7d, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0x7e, 0xcf, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7d, 0xff, 0xa6, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xb6, 0xbf, 0x14, 0x3f, 0x03, 0xff, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x1f, 0x00, 0x00, 
  0x04, 0x1f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x03, 0xff, 0x03, 0xdf, 0x7d, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe7, 0x9f, 0x1c, 0x7f, 0x86, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x9e, 0x9f, 0x02, 0xdf, 0xa6, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xb6, 0xdf, 0x1c, 0x7f, 0x03, 0xff, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x5f, 0x00, 0x00, 
  0x04, 0x7f, 0x0c, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x03, 0xff, 0x03, 0xbf, 0x7d, 0xde, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe7, 0x9f, 0x24, 0x9f, 0x03, 0x9f, 0xa6, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xa6, 0x9f, 0x0c, 0x1f, 0x03, 0x3f, 0x9e, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbe, 0xff, 0x1c, 0x5f, 0x03, 0xdf, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x5f, 0x03, 0xbb, 0x00, 0x00, 
  0x02, 0xf5, 0x0c, 0x7f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x03, 0xff, 0x03, 0x7f, 0x7d, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0x7f, 0x34, 0xbf, 0x03, 0x9f, 0x0c, 0x1f, 0xa6, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xa6, 0x9f, 0x0c, 0x1f, 0x03, 0xff, 0x03, 0xdf, 0x9e, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xa6, 0xbf, 0x14, 0x3f, 0x03, 0xdf, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0xdf, 0x00, 0xc6, 0x00, 0x00, 
  0x00, 0x22, 0x04, 0xff, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x03, 0xdf, 0x8d, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0x3f, 0x34, 0xbf, 0x03, 0xbf, 0x04, 0x1f, 0x0b, 0xff, 0xa6, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xa6, 0x9f, 0x0b, 0xff, 0x04, 0x1f, 0x03, 0xff, 0x03, 0xff, 0x8d, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc7, 0x1f, 0x24, 0x7f, 0x03, 0xff, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x05, 0x3f, 0x00, 0x21, 0x00, 0x00, 
  0x00, 0x42, 0x05, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x03, 0xbf, 0x65, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc7, 0x3f, 0x2c, 0x9f, 0x03, 0xff, 0x04, 0x1f, 0x04, 0x1f, 0x0c, 0x1f, 0xa6, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xa6, 0x9f, 0x0b, 0xff, 0x04, 0x1f, 0x04, 0x1f, 0x03, 0x9f, 0x3c, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3c, 0xff, 0x03, 0xdf, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x7f, 0x00, 0x21, 0x00, 0x00, 
  0x00, 0x00, 0x03, 0xbb, 0x04, 0x5f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x03, 0xff, 0x24, 0x9f, 0xd7, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0x3f, 0x34, 0xbf, 0x03, 0xff, 0x04, 0x1f, 0x04, 0x1f, 0x03, 0xff, 0x0c, 0x1f, 0xa6, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xa6, 0x9f, 0x0b, 0xff, 0x04, 0x3f, 0x03, 0xbf, 0x34, 0xdf, 0xef, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0x55, 0x5f, 0x03, 0xff, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x9f, 0x02, 0x30, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x01, 0xee, 0x04, 0x9f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x03, 0xdf, 0x1c, 0x7f, 0xe7, 0x5f, 0xff, 0xff, 0xd7, 0x5f, 0x2c, 0xbf, 0x03, 0xff, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x1f, 0x0c, 0x1f, 0xa6, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xa6, 0x9f, 0x0c, 0x1f, 0x03, 0xbf, 0x0c, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x45, 0x1f, 0x03, 0xdf, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0xbf, 0x01, 0xee, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x02, 0x0f, 0x04, 0xbf, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x03, 0xdf, 0x24, 0x3f, 0xae, 0xde, 0x34, 0x9f, 0x03, 0xdf, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x1f, 0x0b, 0xff, 0xa6, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xa6, 0x9f, 0x03, 0xbf, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0x3c, 0xff, 0x03, 0xdf, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x9f, 0x01, 0xce, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x01, 0x29, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x1f, 0x03, 0x9f, 0x03, 0xff, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x1f, 0x0b, 0xff, 0xa6, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x8e, 0x3f, 0x1c, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe7, 0x9f, 0x45, 0x1f, 0x03, 0xdf, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x7f, 0x02, 0xd5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x21, 0x02, 0xf6, 0x04, 0x7f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x0b, 0xff, 0xa6, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd7, 0x5f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe7, 0x9f, 0x4d, 0x3f, 0x03, 0xdf, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x7f, 0x03, 0x58, 0x00, 0x42, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x42, 0x03, 0x38, 0x04, 0x7f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x0b, 0xff, 0xa6, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe7, 0x9f, 0x55, 0x5f, 0x03, 0xbf, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x5f, 0x02, 0x94, 0x00, 0x21, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x02, 0x10, 0x04, 0x5f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x0b, 0xff, 0xa6, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe7, 0x7f, 0x45, 0x3f, 0x03, 0xbf, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x5f, 0x04, 0x1f, 0x00, 0xa5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x63, 0x03, 0x59, 0x04, 0x5f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x0b, 0xff, 0xa6, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe7, 0x7f, 0x44, 0xff, 0x03, 0xbf, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x5f, 0x03, 0x59, 0x00, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x0e, 0x04, 0xdf, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x0b, 0xff, 0xa6, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0xdf, 0x2c, 0xbf, 0x03, 0xff, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0xdf, 0x02, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x41, 0x02, 0xf5, 0x04, 0x9f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x0b, 0xff, 0xa6, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0xbf, 0x34, 0xbf, 0x03, 0xdf, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x7f, 0x02, 0xf4, 0x00, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xee, 0x04, 0x7f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x0b, 0xff, 0xa6, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe7, 0x9f, 0x2c, 0xdf, 0x03, 0xbf, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x9f, 0x01, 0xef, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x03, 0x77, 0x04, 0x9f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x0b, 0xff, 0xa6, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xe7, 0x9f, 0x34, 0xff, 0x03, 0xdf, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x1f, 0x02, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x6c, 0x04, 0x3e, 0x04, 0x5f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x0b, 0xff, 0xa6, 0x9f, 0xff, 0xff, 0xd7, 0x5f, 0x2c, 0xbf, 0x03, 0xbf, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x5f, 0x03, 0xfc, 0x00, 0xe7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x8c, 0x04, 0x3e, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x0c, 0x1f, 0xae, 0xbf, 0xe7, 0x9f, 0x34, 0xdf, 0x03, 0xbf, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x5f, 0x04, 0x3e, 0x01, 0x8c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x8c, 0x04, 0x3e, 0x04, 0x5f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x0c, 0x1f, 0x75, 0xdf, 0x4d, 0x3f, 0x03, 0xbf, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x7f, 0x04, 0x3e, 0x01, 0x8c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x6b, 0x04, 0x3e, 0x04, 0x9f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x0c, 0x3f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x03, 0x78, 0x01, 0x6b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x4a, 0x02, 0xb2, 0x04, 0x9f, 0x04, 0x7f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x3f, 0x04, 0x3f, 0x04, 0x9f, 0x04, 0xdf, 0x01, 0xef, 0x00, 0x43, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x8c, 0x02, 0x92, 0x04, 0x5f, 0x04, 0x3f, 0x04, 0x7f, 0x04, 0x7f, 0x04, 0x3f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x5f, 0x04, 0x7f, 0x04, 0x7f, 0x04, 0x3f, 0x04, 0x5f, 0x02, 0x92, 0x01, 0x8c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x21, 0x00, 0xe6, 0x01, 0xcd, 0x03, 0x38, 0x03, 0x17, 0x03, 0xbd, 0x04, 0xbf, 0x04, 0xbf, 0x04, 0xbf, 0x04, 0xbf, 0x04, 0xbf, 0x04, 0xbf, 0x04, 0xbf, 0x04, 0xbf, 0x04, 0xbf, 0x04, 0xbf, 0x04, 0xbf, 0x03, 0xbd, 0x03, 0x17, 0x03, 0x38, 0x01, 0xcd, 0x00, 0xe6, 0x00, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x00, 0x21, 0x00, 0xc6, 0x02, 0x30, 0x02, 0x0f, 0x02, 0x0f, 0x02, 0x0f, 0x02, 0x0f, 0x02, 0x0f, 0x02, 0x0f, 0x02, 0x0f, 0x02, 0x0f, 0x02, 0x0f, 0x02, 0x30, 0x00, 0xc6, 0x00, 0x21, 0x00, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

#endif
};

const lv_img_dsc_t ble = {
  .header.cf = LV_IMG_CF_TRUE_COLOR,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 48,
  .header.h = 64,
  .data_size = 1280 * LV_COLOR_SIZE / 8,
  .data = ble_map,
};
#endif
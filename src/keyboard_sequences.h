#ifndef KEYBOARD_SEQUENCES_H__
#define KEYBOARD_SEQUENCES_H__

//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "usb_hid_codes.h"

//---------------------------------------------------------------------------
// Definitions 
//---------------------------------------------------------------------------
#define         KEY_PRESS           1
#define         KEY_PRESS_L         2
#define         KEY_HOLD            3
#define         KEY_RELEASE         4
#define         KEY_WAIT            5
#define         KEY_EOS             6

//------------------------------------------------------------ program 1 - GTA
static const uint8_t seq_p1_k2[] = {KEY_PRESS, KEY_H,                          //hello world
                                    KEY_PRESS, KEY_E,
                                    KEY_PRESS, KEY_L,
                                    KEY_PRESS, KEY_L,
                                    KEY_PRESS, KEY_O,
                                    KEY_PRESS, KEY_SPACE,
                                    KEY_PRESS, KEY_W,
                                    KEY_PRESS, KEY_O,
                                    KEY_PRESS, KEY_R,
                                    KEY_PRESS, KEY_L,
                                    KEY_PRESS, KEY_D,
                                    KEY_EOS};

static const uint8_t seq_p1_k4[] = {KEY_PRESS, KEY_M,                          //sparrow
                                    KEY_PRESS, KEY_DOWN,
                                    KEY_PRESS, KEY_DOWN,
                                    KEY_PRESS, KEY_DOWN,
                                    KEY_PRESS, KEY_DOWN,
                                    KEY_PRESS, KEY_DOWN,
                                    KEY_PRESS, KEY_ENTER,
                                    KEY_PRESS, KEY_DOWN,
                                    KEY_PRESS, KEY_DOWN,
                                    KEY_PRESS, KEY_DOWN,
                                    KEY_PRESS, KEY_DOWN,
                                    KEY_PRESS, KEY_ENTER,
                                    KEY_PRESS, KEY_DOWN,
                                    KEY_PRESS, KEY_ENTER,
                                    KEY_EOS
                                    };

static const uint8_t seq_p1_k5[] = {0xFF};
static const uint8_t seq_p1_k6[] = {KEY_PRESS_L, KEY_UP,                        //mechanic
                                    KEY_PRESS, KEY_RIGHT,
                                    KEY_PRESS, KEY_UP,
                                    KEY_PRESS, KEY_ENTER,
                                    KEY_PRESS, KEY_LEFT,
                                    KEY_PRESS, KEY_LEFT,
                                    KEY_PRESS, KEY_LEFT,
                                    KEY_PRESS, KEY_UP,
                                    KEY_PRESS, KEY_ENTER,
                                    KEY_EOS
                                    };

static const uint8_t seq_p1_k7[] = {KEY_PRESS_L, KEY_UP,                        //Lester
                                    KEY_PRESS, KEY_RIGHT,
                                    KEY_PRESS, KEY_UP,
                                    KEY_PRESS, KEY_ENTER,
                                    KEY_PRESS, KEY_LEFT,
                                    KEY_PRESS, KEY_LEFT,
                                    KEY_PRESS, KEY_LEFT,
                                    KEY_PRESS, KEY_LEFT,
                                    KEY_PRESS, KEY_ENTER,
                                    KEY_EOS
                                    };

static const uint8_t seq_p1_k8[] = {KEY_PRESS, KEY_M,                          //heavy
                                    KEY_PRESS, KEY_DOWN,
                                    KEY_PRESS, KEY_DOWN,
                                    KEY_PRESS, KEY_ENTER,
                                    KEY_PRESS, KEY_DOWN,
                                    KEY_PRESS, KEY_DOWN,
                                    KEY_PRESS, KEY_DOWN,
                                    KEY_PRESS, KEY_DOWN,    
                                    KEY_PRESS, KEY_ENTER,
                                    KEY_PRESS, KEY_DOWN,
                                    KEY_PRESS, KEY_DOWN,
                                    KEY_PRESS, KEY_DOWN,
                                    KEY_PRESS, KEY_ENTER,
                                    KEY_EOS
                                    };

static const uint8_t seq_p1_k9[] = {KEY_PRESS, KEY_M,                          //full
                                    KEY_PRESS, KEY_DOWN,
                                    KEY_PRESS, KEY_DOWN,
                                    KEY_PRESS, KEY_ENTER,
                                    KEY_PRESS, KEY_DOWN,
                                    KEY_PRESS, KEY_DOWN,
                                    KEY_PRESS, KEY_DOWN,
                                    KEY_PRESS, KEY_DOWN,
                                    KEY_PRESS, KEY_ENTER,
                                    KEY_PRESS, KEY_DOWN,
                                    KEY_PRESS, KEY_DOWN,
                                    KEY_PRESS, KEY_DOWN,
                                    KEY_PRESS, KEY_DOWN,
                                    KEY_PRESS, KEY_ENTER,
                                    KEY_EOS                              
                                    };

static const uint8_t seq_p1_k10[] = {KEY_PRESS, KEY_M,                          //food
                                     KEY_PRESS, KEY_DOWN,
                                     KEY_PRESS, KEY_DOWN,
                                     KEY_PRESS, KEY_ENTER,
                                     KEY_PRESS, KEY_DOWN,
                                     KEY_PRESS, KEY_DOWN,
                                     KEY_PRESS, KEY_DOWN,
                                     KEY_PRESS, KEY_DOWN,
                                     KEY_PRESS, KEY_DOWN,
                                     KEY_PRESS, KEY_ENTER,
                                     KEY_PRESS, KEY_ENTER,
                                     KEY_EOS
                                    };

//------------------------------------------------------------ program 2 - ALTIUM
static const uint8_t seq_p2_k2[] =  {KEY_PRESS, KEY_H,                          //hello world
                                    KEY_PRESS, KEY_E,
                                    KEY_PRESS, KEY_L,
                                    KEY_PRESS, KEY_L,
                                    KEY_PRESS, KEY_O,
                                    KEY_PRESS, KEY_SPACE,
                                    KEY_PRESS, KEY_W,
                                    KEY_PRESS, KEY_O,
                                    KEY_PRESS, KEY_R,
                                    KEY_PRESS, KEY_L,
                                    KEY_PRESS, KEY_D,
                                    KEY_EOS
                                    };

static const uint8_t seq_p2_k4[] =  {0xFF};
static const uint8_t seq_p2_k5[] =  {0xFF};

static const uint8_t seq_p2_k6[] =  {KEY_PRESS, KEY_P,
                                     KEY_PRESS, KEY_S,
                                     KEY_EOS
                                    };

static const uint8_t seq_p2_k7[] =  {KEY_PRESS, KEY_Y,
                                     KEY_PRESS, KEY_A,
                                     KEY_EOS
                                    };

static const uint8_t seq_p2_k8[] =  {KEY_PRESS, KEY_P,
                                     KEY_PRESS, KEY_D,
                                     KEY_PRESS, KEY_L,
                                     KEY_EOS
                                    };

static const uint8_t seq_p2_k9[] =  {KEY_PRESS, KEY_P,
                                     KEY_PRESS, KEY_G,
                                     KEY_EOS
                                    };

static const uint8_t seq_p2_k10[] = {KEY_PRESS, KEY_P,
                                     KEY_PRESS, KEY_T,
                                     KEY_EOS
                                    };


//------------------------------------------------------------ program 3
static const uint8_t seq_p3_k2[] = {KEY_PRESS, KEY_H,                          //hello world
                                    KEY_PRESS, KEY_E,
                                    KEY_PRESS, KEY_L,
                                    KEY_PRESS, KEY_L,
                                    KEY_PRESS, KEY_O,
                                    KEY_PRESS, KEY_SPACE,
                                    KEY_PRESS, KEY_W,
                                    KEY_PRESS, KEY_O,
                                    KEY_PRESS, KEY_R,
                                    KEY_PRESS, KEY_L,
                                    KEY_PRESS, KEY_D,
                                    KEY_EOS};
                                    
static const uint8_t seq_p3_k4[] = {0xFF};
static const uint8_t seq_p3_k5[] = {0xFF};
static const uint8_t seq_p3_k6[] = {0xFF};
static const uint8_t seq_p3_k7[] = {0xFF};
static const uint8_t seq_p3_k8[] = {0xFF};
static const uint8_t seq_p3_k9[] = {0xFF};
static const uint8_t seq_p3_k10[] = {KEY_PRESS, KEY_P,
                                     KEY_PRESS, KEY_R,
                                     KEY_PRESS, KEY_3,
                                     KEY_EOS
                                    };

static const uint8_t *ptr_seq_k2[3] = {seq_p1_k2, seq_p2_k2, seq_p3_k2};
static const uint8_t *ptr_seq_k4[3] = {seq_p1_k4, seq_p2_k4, seq_p3_k4};
static const uint8_t *ptr_seq_k5[3] = {seq_p1_k5, seq_p2_k5, seq_p3_k5};
static const uint8_t *ptr_seq_k6[3] = {seq_p1_k6, seq_p2_k6, seq_p3_k6};
static const uint8_t *ptr_seq_k7[3] = {seq_p1_k7, seq_p2_k7, seq_p3_k7};
static const uint8_t *ptr_seq_k8[3] = {seq_p1_k8, seq_p2_k8, seq_p3_k8};
static const uint8_t *ptr_seq_k9[3] = {seq_p1_k9, seq_p2_k9, seq_p3_k9};
static const uint8_t *ptr_seq_k10[3] = {seq_p1_k10, seq_p2_k10, seq_p3_k10};

#endif

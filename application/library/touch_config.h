/**
 *******************************************************************************
 * @file        touch_config.h
 * @author      ABOV R&D Division
 * @brief       Touch setting configure
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _TOUCH_CONFIG_H_
#define _TOUCH_CONFIG_H_

#include "typedef.h"
#include "touch_lib.h"

#if 1
/*************************
    TOUCH CH
*************************/
#define CS00_USE    1   /*  */
#define CS01_USE    1   /*  */
#define CS02_USE    1   /*  */
#define CS03_USE    1   /*  */
#define CS04_USE    1   /*  */
#define CS05_USE    0   /*  */
#define CS06_USE    1   /*  */
#define CS07_USE    1   /*  */
#define CS08_USE    1   /*  */  
#define CS09_USE    1   /*  */
#define CS10_USE    1   /*  */
#define CS11_USE    0   /*  */
#define CS12_USE    0   /*  */
#define CS13_USE    0   /*  */
#define CS14_USE    0   /*  */
#define CS15_USE    0   /*  */
#define CS16_USE    0   /*  */
#define CS17_USE    1   /*  */
#define CS18_USE    0   /*  */
#define CS19_USE    1   /*  */
//1010 0000 0111 1101 1111 = 0xA07DF
/************************************************************** don't modify *************************************************************/
#define ACT_KEY_N       (CS00_USE+CS01_USE+CS02_USE+CS03_USE+CS04_USE+CS05_USE+CS06_USE+CS07_USE+   \
                         CS08_USE+CS09_USE+CS10_USE+CS11_USE+CS12_USE+CS13_USE+CS14_USE+CS15_USE+   \
                         CS16_USE+CS17_USE+CS18_USE+CS19_USE)

#define ACT_CH_BIT     (((uint32_t)CS00_USE<<0)  | ((uint32_t)CS01_USE<<1)  | ((uint32_t)CS02_USE<<2)  | ((uint32_t)CS03_USE<<3)   | ((uint32_t)CS04_USE<<4)  |   \
                        ((uint32_t)CS05_USE<<5)  | ((uint32_t)CS06_USE<<6)  | ((uint32_t)CS07_USE<<7)  | ((uint32_t)CS08_USE<<8)   | ((uint32_t)CS09_USE<<9)  |   \
                        ((uint32_t)CS10_USE<<10) | ((uint32_t)CS11_USE<<11) | ((uint32_t)CS12_USE<<12) | ((uint32_t)CS13_USE<<13) | ((uint32_t)CS14_USE<<14) |    \
                        ((uint32_t)CS15_USE<<15) | ((uint32_t)CS16_USE<<16) | ((uint32_t)CS17_USE<<17) | ((uint32_t)CS18_USE<<18) | ((uint32_t)CS19_USE<<19))
#else
#define ACT_KEY_N       13
#define ACT_CH_BIT      0xE07DF //CS0~4, CS6~10, CS17~19
#endif
/****************************************************************************************************************************************/

/******************************* Touch common parameter **********************************************/
#define TOUCH_CLK_VAL                   TOUCH_FREQ_4M
#define TOUCH_CLK_OFFSET_VAL            4       // set 0x00 ~ 0x3F
#define TOUCH_VHS_VAL                   4000    // set 3000 ~ 5000
#define TOUCH_LPF_C_VAL                 INTENAL_CAPACITOR_10_5pF
#define TOUCH_LPF_R_VAL                 SERIAL_REGISTER_100K
#define TOUCH_MODE_VAL                  TS_MODE_NORMAL
#define TOUCH_PORT_SEL_VAL              MODE_OUT_LOW
#define TOUCH_COMP_REFV_VAL             3840    // set 2700 ~ 4500    /*Hisense mode 3700, normal mode 3840*/
#define DETECT_DEBOUNCE_CNT_VAL         1       // set 0 ~ 5
#define RELEASE_DEBOUNCE_CNT_VAL        1       // set 0 ~ 5
#define FILTER_IIR_GAIN_VAL             0       // set 0 ~ 5
#define TIMER_STARTUP_VAL               300     // set 100ms ~ 500ms
#define TIMER_BASE_SAMPLE_VAL           500     // set 200ms ~ 1000ms
#define BASE_RELEASE_HOLD_CNT_VAL       3       // set 0 ~ 5
#define TIMER_REVERSE_BASE_SAMPLE_VAL   100     // set 100ms ~ 500ms
#define THD_RELEASE_RATE_VAL            70      // set 50% ~ 80%
#define THD_REVERSE_RATE_VAL            50      // set 50% ~ 200%

/******************************************************************************************************/

/******************************* Touch channel parameter **********************************************/
/*************************
    TOUCH SUM_CNT Parameter
    Range [3 ~ 15]
*************************/
#define TOUCH_SUM_CNT_CH00           6
#define TOUCH_SUM_CNT_CH01           6
#define TOUCH_SUM_CNT_CH02           6
#define TOUCH_SUM_CNT_CH03           6
#define TOUCH_SUM_CNT_CH04           6
#define TOUCH_SUM_CNT_CH05           6
#define TOUCH_SUM_CNT_CH06           6
#define TOUCH_SUM_CNT_CH07           6
#define TOUCH_SUM_CNT_CH08           6
#define TOUCH_SUM_CNT_CH09           6
#define TOUCH_SUM_CNT_CH10           6
#define TOUCH_SUM_CNT_CH11           6
#define TOUCH_SUM_CNT_CH12           6
#define TOUCH_SUM_CNT_CH13           6
#define TOUCH_SUM_CNT_CH14           6
#define TOUCH_SUM_CNT_CH15           6
#define TOUCH_SUM_CNT_CH16           6
#define TOUCH_SUM_CNT_CH17           6
#define TOUCH_SUM_CNT_CH18           6
#define TOUCH_SUM_CNT_CH19           6

/*************************
    TOUCH THRESHOLD Parameter (9Pi Criteria) 
*************************/
#define THD_DETECT_CH00         100 /* wheel ch7 */
#define THD_DETECT_CH01         100 /* wheel ch6 */
#define THD_DETECT_CH02         100 /* wheel ch5 */
#define THD_DETECT_CH03         100 /* wheel ch1 */
#define THD_DETECT_CH04         100 /* wheel ch2 */
#define THD_DETECT_CH05         100 /* wheel ch3 */
#define THD_DETECT_CH06         100 /* wheel ch4 */
#define THD_DETECT_CH07         100
#define THD_DETECT_CH08         100
#define THD_DETECT_CH09         100
#define THD_DETECT_CH10         100 /* slide CH5 */
#define THD_DETECT_CH11         100 /* slide CH4 */
#define THD_DETECT_CH12         100 /* slide CH3 */
#define THD_DETECT_CH13         100 /* slide CH2 */
#define THD_DETECT_CH14         100 /* slide CH1 */
#define THD_DETECT_CH15         100 /* slide CH0 */
#define THD_DETECT_CH16         100
#define THD_DETECT_CH17         100
#define THD_DETECT_CH18         100
#define THD_DETECT_CH19         100 /* wheel ch0 */

/*************************
    Base Line Parameter
*************************/
#define BASE_TRACE_SPEED_CH00            1
#define BASE_TRACE_SPEED_CH01            1
#define BASE_TRACE_SPEED_CH02            1
#define BASE_TRACE_SPEED_CH03            1
#define BASE_TRACE_SPEED_CH04            1
#define BASE_TRACE_SPEED_CH05            1
#define BASE_TRACE_SPEED_CH06            1
#define BASE_TRACE_SPEED_CH07            1
#define BASE_TRACE_SPEED_CH08            1
#define BASE_TRACE_SPEED_CH09            1
#define BASE_TRACE_SPEED_CH10            1
#define BASE_TRACE_SPEED_CH11            1
#define BASE_TRACE_SPEED_CH12            1
#define BASE_TRACE_SPEED_CH13            1
#define BASE_TRACE_SPEED_CH14            1
#define BASE_TRACE_SPEED_CH15            1
#define BASE_TRACE_SPEED_CH16            1
#define BASE_TRACE_SPEED_CH17            1
#define BASE_TRACE_SPEED_CH18            1
#define BASE_TRACE_SPEED_CH19            1
/******************************************************************************************************/


uint16_t code TS_COM_CFG[TOUCH_COM_CFG_MAX] = {
TOUCH_CLK_VAL,                                      //TOUCH_CLK                   //0:16Mhz, 1:8Mhz, 2:4Mhz, 3:2Mhz, 4:1Mhz, 5:0.5Mhz, 6:0.25Mhz, 7:0.125Mhz
TOUCH_CLK_OFFSET_VAL,                               //TOUCH_CLK_OFFSET            //
TOUCH_LPF_C_VAL,                                    //TOUCH_LPF_C_VALUE             //
TOUCH_LPF_R_VAL,                                    //TOUCH_LPF_R_VALUE             //
TOUCH_MODE_VAL,                                     //TOUCH_MODE                  //0:normal, 1:adjust, 2:hisense, 3:simul
TOUCH_PORT_SEL_VAL,                                 //TOUCH_PORT_SEL
TOUCH_VHS_VAL,                                      //TOUCH_VHS                   // hisensoe mode only use dis parameter, orther is set VDD
TOUCH_COMP_REFV_VAL,                                //TOUCH_REFV
DETECT_DEBOUNCE_CNT_VAL,                            //DETECT_DEBOUNCE_CN
RELEASE_DEBOUNCE_CNT_VAL,                           //RELEASE_DEBOUNCE_CNT
FILTER_IIR_GAIN_VAL,                                //FILTER_IIR_GAIN
TIMER_STARTUP_VAL,                                  //TIMER_STARTUP
TIMER_BASE_SAMPLE_VAL,                              //TIMER_BASE_SAMPLE
BASE_RELEASE_HOLD_CNT_VAL,                          //BASE_RELEASE_HOLD_CNT
TIMER_REVERSE_BASE_SAMPLE_VAL,                      //TIMER_REVERSE_BASE_SAMPLE
THD_RELEASE_RATE_VAL,                               //THD_RELEASE_RATE
THD_REVERSE_RATE_VAL,                               //THD_REVERSE_RATE
};

uint16_t code TS_CH_CFG[20][TOUCH_CH_CFG_MAX] = {
{TOUCH_SUM_CNT_CH00,THD_DETECT_CH00,BASE_TRACE_SPEED_CH00},
{TOUCH_SUM_CNT_CH01,THD_DETECT_CH01,BASE_TRACE_SPEED_CH01},
{TOUCH_SUM_CNT_CH02,THD_DETECT_CH02,BASE_TRACE_SPEED_CH02},
{TOUCH_SUM_CNT_CH03,THD_DETECT_CH03,BASE_TRACE_SPEED_CH03},
{TOUCH_SUM_CNT_CH04,THD_DETECT_CH04,BASE_TRACE_SPEED_CH04},
{TOUCH_SUM_CNT_CH05,THD_DETECT_CH05,BASE_TRACE_SPEED_CH05},
{TOUCH_SUM_CNT_CH06,THD_DETECT_CH06,BASE_TRACE_SPEED_CH06},
{TOUCH_SUM_CNT_CH07,THD_DETECT_CH07,BASE_TRACE_SPEED_CH07},
{TOUCH_SUM_CNT_CH08,THD_DETECT_CH08,BASE_TRACE_SPEED_CH08},
{TOUCH_SUM_CNT_CH09,THD_DETECT_CH09,BASE_TRACE_SPEED_CH09},
{TOUCH_SUM_CNT_CH10,THD_DETECT_CH10,BASE_TRACE_SPEED_CH10},
{TOUCH_SUM_CNT_CH11,THD_DETECT_CH11,BASE_TRACE_SPEED_CH11},
{TOUCH_SUM_CNT_CH12,THD_DETECT_CH12,BASE_TRACE_SPEED_CH12},
{TOUCH_SUM_CNT_CH13,THD_DETECT_CH13,BASE_TRACE_SPEED_CH13},
{TOUCH_SUM_CNT_CH14,THD_DETECT_CH14,BASE_TRACE_SPEED_CH14},
{TOUCH_SUM_CNT_CH15,THD_DETECT_CH15,BASE_TRACE_SPEED_CH15},
{TOUCH_SUM_CNT_CH16,THD_DETECT_CH16,BASE_TRACE_SPEED_CH16},
{TOUCH_SUM_CNT_CH17,THD_DETECT_CH17,BASE_TRACE_SPEED_CH17},
{TOUCH_SUM_CNT_CH18,THD_DETECT_CH18,BASE_TRACE_SPEED_CH18},
{TOUCH_SUM_CNT_CH19,THD_DETECT_CH19,BASE_TRACE_SPEED_CH19},
};

#endif  /* _TOUCH_CONFIG_H_ */


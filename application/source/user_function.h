/**
 *******************************************************************************
 * @file        user_function.h
 * @author      ABOV R&D Division
 * @brief       User Function code
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _USER_H_
#define _USER_H_

#include "typedef.h"
#include "A96T418.h"

#define LED_DRV_EN          1
#define TS_LED_TIME_DIV     1

/*************************
    Function Feature
*************************/
#define UART_ENABLE                     1
#define I2C_ENABLE                      0
#define WDT_ENABLE                      1
#define HOLD_KEY_RELEASE                1
#define FIRST_KEY_PRIORITY              0
#define MULTI_KEY_RESET                 0
#define TOUCH_FREQ_SEL_EN               1

// If this function enable, must be add gesture.c and gesture.h
#define WHEEL_FUNCTION_EN               0
#define SLIDE_FUNCTION_EN               0

/************************************************************/
/* Option Function. This feature requires the addition of a separate UL60730 Library files */
#define UL60730_SELF_TEST_EN            0               
/************************************************************/


/*************************
   LED COM-SEG
*************************/
#define COM00_EN    1   /* SEG0 */
#define COM01_EN    1   /* SEG1 */
#define COM02_EN    1   /* SEG2, CS11 */
#define COM03_EN    1   /* SEG3, CS12 */
#define COM04_EN    1   /* SEG4, CS13 */
#define COM05_EN    1   /* SEG5, CS14 */
#define COM06_EN    1   /* SEG6, CS15 */
#define COM07_EN    1   /* SEG7, CS16 */
#define SEG00_EN    1   /* COM0 */
#define SEG01_EN    1   /* COM1 */
#define SEG02_EN    1   /* COM2, CS11 */
#define SEG03_EN    1   /* COM3, CS12 */
#define SEG04_EN    1   /* COM4, CS13 */
#define SEG05_EN    1   /* COM5, CS14 */
#define SEG06_EN    1   /* COM6, CS15 */
#define SEG07_EN    1   /* COM7, CS16 */
#define SEG08_EN    1   /* CS3 */
#define SEG09_EN    1   /* CS2 */
#define SEG10_EN    1   /* CS1 */
#define SEG11_EN    1   /* CS0 */
#define SEG12_EN    1   /* CS19 */
#define SEG13_EN    1   /* CS18 */
#define SEG14_EN    1   /* CS17 */
#define SEG15_EN    1   /* CS4 */

/*************************
    T-Type LED
*************************/
#define A1  BIT(0)
#define B1  BIT(0)
#define C1  BIT(0)
#define D1  BIT(0)
#define E1  BIT(0)
#define F1  BIT(0)
#define G1  BIT(1)
#define A2  BIT(1)
#define B2  BIT(1)
#define C2  BIT(1)
#define D2  BIT(2)
#define E2  BIT(2)
#define F2  BIT(2)
#define G2  BIT(2)
#define A3  BIT(3)
#define B3  BIT(3)
#define C3  BIT(4)
#define D3  BIT(4)
#define E3  BIT(6)
#define F3  BIT(3)
#define G3  BIT(3)
#define A4  BIT(3)
#define B4  BIT(3)
#define C4  BIT(3)
#define D4  BIT(7)
#define E4  BIT(7)
#define F4  BIT(7)
#define G4  BIT(7)

/******************************************************************************************************************************************/
/************************************************************** don't modify *************************************************************/
#define P2_COM_IO       ((COM07_EN<<7)+(COM06_EN<<6)+(COM05_EN<<5)+(COM04_EN<<4)+(COM03_EN<<3)+(COM02_EN<<2)+(COM01_EN<<1)+(COM00_EN<<0))
#define P2_SEG_IO       ((SEG07_EN<<7)+(SEG06_EN<<6)+(SEG05_EN<<5)+(SEG04_EN<<4)+(SEG03_EN<<3)+(SEG02_EN<<2)+(SEG01_EN<<1)+(SEG00_EN<<0))
#define P0_SEG_IO       ((SEG08_EN<<7)+(SEG09_EN<<6)+(SEG10_EN<<5)+(SEG11_EN<<4)+(SEG12_EN<<3)+(SEG13_EN<<0))
#define P1_SEG_IO       ((SEG15_EN<<0))
#define P3_SEG_IO       ((SEG14_EN<<1))
#define COMSEL_00_07    ((COM07_EN<<7)+(COM06_EN<<6)+(COM05_EN<<5)+(COM04_EN<<4)+(COM03_EN<<3)+(COM02_EN<<2)+(COM01_EN<<1)+(COM00_EN<<0))
#define SEGSEL_00_07    ((SEG07_EN<<7)+(SEG06_EN<<6)+(SEG05_EN<<5)+(SEG04_EN<<4)+(SEG03_EN<<3)+(SEG02_EN<<2)+(SEG01_EN<<1)+(SEG00_EN<<0))
#define SEGSEL_08_15    ((SEG15_EN<<7)+(SEG14_EN<<6)+(SEG13_EN<<5)+(SEG12_EN<<4)+(SEG11_EN<<3)+(SEG10_EN<<2)+(SEG09_EN<<1)+(SEG08_EN<<0))
/******************************************************************************************************************************************/


#if (FIRST_KEY_PRIORITY == 1)
/*************************
(mapping: software base)
        priority KEY CH : high (1) / Low (0)
*************************/
#define CH00_PRIORITY_USE    1   
#define CH01_PRIORITY_USE    0   
#define CH02_PRIORITY_USE    1   
#define CH03_PRIORITY_USE    0   
#define CH04_PRIORITY_USE    0   
#define CH05_PRIORITY_USE    0   
#define CH06_PRIORITY_USE    0   
#define CH07_PRIORITY_USE    0   
#define CH08_PRIORITY_USE    0   
#define CH09_PRIORITY_USE    0   
#define CH10_PRIORITY_USE    0
#define CH11_PRIORITY_USE    0
#define CH12_PRIORITY_USE    0
#define CH13_PRIORITY_USE    0
#define CH14_PRIORITY_USE    0
#define CH15_PRIORITY_USE    0
#define CH16_PRIORITY_USE    0
#define CH17_PRIORITY_USE    0
#define CH18_PRIORITY_USE    0
#define CH19_PRIORITY_USE    0  

/************************************************************** don't modify *************************************************************/
#define PRIORITY_CH_BIT (((uint32_t)CH00_PRIORITY_USE<<0)|((uint32_t)CH01_PRIORITY_USE<<1)|((uint32_t)CH02_PRIORITY_USE<<2)|((uint32_t)CH03_PRIORITY_USE<<3)|       \
                         ((uint32_t)CH04_PRIORITY_USE<<4)|((uint32_t)CH05_PRIORITY_USE<<5)|((uint32_t)CH06_PRIORITY_USE<<6)|((uint32_t)CH07_PRIORITY_USE<<7)|       \
                         ((uint32_t)CH08_PRIORITY_USE<<8)|((uint32_t)CH09_PRIORITY_USE<<9)|((uint32_t)CH10_PRIORITY_USE<<10)|((uint32_t)CH11_PRIORITY_USE<<11)|     \
                         ((uint32_t)CH12_PRIORITY_USE<<12)|((uint32_t)CH13_PRIORITY_USE<<13)|((uint32_t)CH14_PRIORITY_USE<<14)|((uint32_t)CH15_PRIORITY_USE<<15)|    \
                         ((uint32_t)CH16_PRIORITY_USE<<16)|((uint32_t)CH17_PRIORITY_USE<<17)|((uint32_t)CH18_PRIORITY_USE<<18)|((uint32_t)CH19_PRIORITY_USE<<19))

/******************************************************************************************************************************************/
#endif

#if (MULTI_KEY_RESET == 1)
/*************************
    Function Parameter
*************************/
#define MAX_MULTY_KEY_NUM   2

/*************************
(mapping: software base)
        MULTI KEY CH : Allow multi key
*************************/
#define CH00_MULTI_USE    1
#define CH01_MULTI_USE    1
#define CH02_MULTI_USE    1
#define CH03_MULTI_USE    1
#define CH04_MULTI_USE    0
#define CH05_MULTI_USE    0
#define CH06_MULTI_USE    0
#define CH07_MULTI_USE    0
#define CH08_MULTI_USE    0
#define CH09_MULTI_USE    0
#define CH10_MULTI_USE    0
#define CH11_MULTI_USE    0
#define CH12_MULTI_USE    0
#define CH13_MULTI_USE    0
#define CH14_MULTI_USE    0
#define CH15_MULTI_USE    0
#define CH16_MULTI_USE    0
#define CH17_MULTI_USE    0
#define CH18_MULTI_USE    0
#define CH19_MULTI_USE    0

/************************************************************** don't modify *************************************************************/
#define MULTI_CH_BIT (((uint32_t)CH00_MULTI_USE<<0)|((uint32_t)CH01_MULTI_USE<<1)|((uint32_t)CH02_MULTI_USE<<2)|((uint32_t)CH03_MULTI_USE<<3)|((uint32_t)CH04_MULTI_USE<<4)|          \
                      ((uint32_t)CH05_MULTI_USE<<5)|((uint32_t)CH06_MULTI_USE<<6)|((uint32_t)CH07_MULTI_USE<<7)|((uint32_t)CH08_MULTI_USE<<8)|((uint32_t)CH09_MULTI_USE<<9)|          \
                      ((uint32_t)CH10_MULTI_USE<<10)|((uint32_t)CH11_MULTI_USE<<11)|((uint32_t)CH12_MULTI_USE<<12)|((uint32_t)CH13_MULTI_USE<<13)|((uint32_t)CH14_MULTI_USE<<14)|     \
                      ((uint32_t)CH15_MULTI_USE<<15)|((uint32_t)CH16_MULTI_USE<<16)|((uint32_t)CH17_MULTI_USE<<17)|((uint32_t)CH18_MULTI_USE<<18)|((uint32_t)CH19_MULTI_USE<<19))
/******************************************************************************************************************************************/
#endif

/*************************
    Hold Key reset TIME Parameter
*************************/
#define TIMER_HOLD_KEY_RELEASE      10000   // n X 1ms

#if (LED_DRV_EN == 1)
/*************************
    LED Parameter
*************************/
#define LED_CURRENT                 LED_CURRENT_13mA

#define LED_USE_COM_NUM             8
#define TIME_LED_OPTERATING         10      // n X 1ms
#if (TS_LED_TIME_DIV == 1)
#define TIMER_TOUCH_OPTERATING      5       // n X 1ms
#endif
#endif

#if (UART_ENABLE == 1)
#define DBG_BAUD_RATE   DBG_BAUD_500000
#endif

#if ((MULTI_KEY_RESET | HOLD_KEY_RELEASE | FIRST_KEY_PRIORITY) == 1)
struct tp_param
{
#if (MULTI_KEY_RESET == 1)
    uint32_t multi_ch_bit;
    uint16_t multi_key_check;  
    uint8_t multi_key_limit;
#endif

#if (HOLD_KEY_RELEASE == 1)
    uint16_t hold_key_release_time;
#endif

#if (FIRST_KEY_PRIORITY == 1)
    uint32_t priority_ch_idx;
#endif

#if (UL60730_SELF_TEST_EN == 1)
    uint32_t ul60730_post_result;
    uint32_t ul60730_bist_result;
#endif

};

extern struct tp_param user;
#endif

#if (TOUCH_FREQ_SEL_EN == 1)
void Touch_Freq_Sel(void);
#endif

#if ((HOLD_KEY_RELEASE | MULTI_KEY_RESET | FIRST_KEY_PRIORITY) == 1)
void Touch_Key_Scenario (void);
#endif

#endif  /* _USER_H_ */

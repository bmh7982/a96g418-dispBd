/**
 *******************************************************************************
 * @file        user_timer.h
 * @author      ABOV R&D Division
 * @brief       Timer count 1 user code
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _USERTIMER_H_
#define _USERTIMER_H_

#include "typedef.h"


typedef enum 
{
    UT_MIN              = 0x00,
    UT_INIT_DELAY       = 0x01, 
    UT_REVERSE          = 0x02, 
    UT_BASE_UPDATE      = 0x04,
    UT_HOLD_KEY_RELEASE = 0x08,
    UT_SLIDE_EVENT_HOLD = 0x10, 
    UT_WHEEL_EVENT_HOLD = 0x20,
    UT_7                = 0x40,
    UT_8                = 0x80, 
    UT_MAX              = 0xff
} ut_id;


#define FX_16MHZ    0
#define FX_8MHZ     1
#define FX_4MHZ     2
#define FX_1MHZ     3
struct ut_param
{
    struct{
        uint8_t clock_src   :2;
        uint8_t reserved    :6;
    } flag;
};

void UT_Set_Timer(uint16_t utid, uint32_t timeout);
uint16_t UT_Get_Status(void);
void UT_Clear_Timer(uint16_t utid);
uint8_t UT_Is_Expired(uint16_t utid);
void UT_Run_Timer(void);


#endif  /* _USERTIMER_H_ */

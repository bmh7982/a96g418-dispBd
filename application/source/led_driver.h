/**
 *******************************************************************************
 * @file        led_driver.h
 * @author      ABOV R&D Division
 * @brief       A96T418 LED Driver code
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#include "user_function.h"

#if (LED_DRV_EN == 1)

#ifndef _LED_DRIVER_H_
#define _LED_DRIVER_H_

#include "typedef.h"


#define LED_INIT_DATA   0x00
#define SEG(x)  ((uint16_t)1<<x)
#define COM(x)  ((uint8_t)1<<x)

struct led_cfg
{
    uint8_t com_sel;
    uint16_t seg_sel;
    uint8_t  p0_seg;
    uint8_t  p1_seg;
    uint8_t  p2_seg;
    uint8_t  p3_seg;
    struct{
        uint8_t seg_current     :2;
        uint8_t mode            :3;
        uint8_t reserved        :3;
    }flag;
};

typedef enum
{
    LED_STATE_INIT_IO = 0x00,
    LED_STATE_SET_TIMER,
    LED_STATE_UPDATE_LED,   
}LED_state;

enum{
    LED_CURRENT_8mA     = 0,
    LED_CURRENT_13mA    = 1,
    LED_CURRENT_22mA    = 2,
    LED_CURRENT_26mA    = 3,
};

extern struct led_cfg   led;

void LED_Do_Task(void);
void LED_Set_Actv_Time(uint8_t com_cnt, uint8_t duration);
#if (TS_LED_TIME_DIV == 1)
void Touch_Set_Actv_Time (uint8_t slot_ms);
#endif

#endif  /* _LED_DRIVER_H_ */

#endif

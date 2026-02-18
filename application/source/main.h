/**
 *******************************************************************************
 * @file        main.h
 * @author      ABOV R&D Division
 * @brief       application "TEST-A96T418-GDN-FUNCTION-A"
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/
 
#ifndef _MAIN_H_
#define _MAIN_H_

#include "typedef.h"

/// Main clock Divider
#define Divider_0_5MHz      0x00
#define Divider_1MHz        0x08
#define Divider_2MHz        0x10
#define Divider_4MHz        0x18
#define Divider_8MHz        0x20
#define Divider_16MHz       0x28
#define Test                0x30

#define Internal_16MHz_OSC      0
#define Reserved                1
#define External_OSC            2
#define Internal_128kHz_OSC     3

typedef enum
{   
    TASK_LED = 0,
    TASK_TOUCH,
    TASK_GESTURE,
    TASK_DEBUG,
    TASK_MAX
} e_task;

#define SEG_0   BIT(0)
#define SEG_1   BIT(1)
#define SEG_2   BIT(2)
#define SEG_3   BIT(3)
#define SEG_4   BIT(4)
#define SEG_5   BIT(5)
#define SEG_6   BIT(6)
#define SEG_7   BIT(7)
#define SEG_8   BIT(0)
#define SEG_9   BIT(1)
#define SEG_10  BIT(2)
#define SEG_11  BIT(3)
#define SEG_12  BIT(4)
#define SEG_13  BIT(5)
#define SEG_14  BIT(6)
#define SEG_15  BIT(7)
#define SEG_16  BIT(0)
#define SEG_17  BIT(1)
#define SEG_18  BIT(2)
#define SEG_19  BIT(3)
#define SEG_20  BIT(4)
#define COM_0   BIT(0)
#define COM_1   BIT(1)
#define COM_2   BIT(2)
#define COM_3   BIT(3)
#define COM_4   BIT(4)
#define COM_5   BIT(5)
#define COM_6   BIT(6)
#define COM_7   BIT(7)

#endif /* _MAIN_H_ */
/**
 *******************************************************************************
 * @file        common.h
 * @author      ABOV R&D Division
 * @brief       A96T418 STKS board common header
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/
 
#ifndef _COMMON_H_
#define _COMMON_H_

#include "typedef.h"

#define BIT(n)  ((unsigned long)1 << (n))

//typedef enum { FALSE = 0, TRUE = !FALSE } bool, BOOL;

struct sys_flag 
{
    uint8_t reinit      :1;
    uint8_t calib_ok    :1; 
    uint8_t led_end     :1;
    uint8_t ts_end      :1;
    uint8_t led_en      :1;
    uint8_t dbg_en      :1;
    uint8_t led_io      :1; 
    uint8_t time_div    :1;
};
    
extern struct sys_flag g_sys_flag;

extern bit g_i2c_flag;

#endif /* _COMMON_H_ */
/**
 *******************************************************************************
 * @file        RegisterMap.h
 * @author      ABOV R&D Division
 * @brief       I2C debug register map
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _register_map_en
#define _register_map_en

#include "typedef.h"
#include "user_function.h"

#if (I2C_ENABLE == 1)

#define REG_BOOT_JUMP = 0xF0
enum{
/*  0   */REG_KEY_ID_1,
/*  1   */REG_KEY_ID_2,
/*  2   */REG_KEY_ID_3,
/*  3   */REG_LIB_VERSION,
/*  4   */REG_MODEL_NO,
/*  5   */REG_VENDOR_ID,
/*  6   */REG_06,
/*  7   */REG_07,
/*  8   */REG_08,
/*  9   */REG_09,
/*  A   */REG_0A,
/*  B   */REG_0B,
/*  C   */REG_0C,
/*  D   */REG_0D,
/*  E   */REG_0E,
/*  F   */REG_0F,
/*  10  */REG_DEBUG_10,
/*  11  */REG_DEBUG_11,
/*  12  */REG_DEBUG_12,
/*  13  */REG_DEBUG_13,
/*  14  */REG_DEBUG_14,
/*  15  */REG_DEBUG_15,
/*  16  */REG_DEBUG_16,
/*  17  */REG_DEBUG_17,
/*  18  */REG_DEBUG_18,
/*  19  */REG_DEBUG_19,
/*  1A  */REG_DEBUG_1A,
/*  1B  */REG_DEBUG_1B,
/*  1C  */REG_DEBUG_1C,
/*  1D  */REG_DEBUG_1D,
/*  1E  */REG_DEBUG_1E,
/*  1F  */REG_DEBUG_1F,
/*  20  */REG_DEBUG_20,
/*  21  */REG_DEBUG_21,
/*  22  */REG_DEBUG_22,
/*  23  */REG_DEBUG_23,
/*  24  */REG_DEBUG_24,
/*  25  */REG_DEBUG_25,
/*  26  */REG_DEBUG_26,
/*  27  */REG_DEBUG_27,
/*  28  */REG_DEBUG_28,
/*  29  */REG_DEBUG_29,
/*  2A  */REG_DEBUG_2A,
/*  2B  */REG_DEBUG_2B,
/*  2C  */REG_DEBUG_2C,
/*  2D  */REG_DEBUG_2D,
/*  2E  */REG_DEBUG_2E,
/*  2F  */REG_DEBUG_2F,
/*  30  */REG_MAX,
};

extern uint8_t RegMap[REG_MAX];
#endif

#endif

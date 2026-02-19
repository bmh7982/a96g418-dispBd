/**
 *******************************************************************************
 * @file        a96T418_wdt.h
 * @author      ABOV R&D Division
 * @brief       A96T418 WDT driver Code
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/


#ifndef __WDT_H_
#define __WDT_H_
/*******************************************************************************
* Included File
*******************************************************************************/
#include "A96T418.h"
#include "common.h"
#include "typedef.h"
#include "user_function.h"

#if (WDT_ENABLE == 1)

/*******************************************************************************
* Public Macro
*******************************************************************************/

/*******************************************************************************
* Public Typedef
*******************************************************************************/
enum WDT_rst { 
    WDT_FREE_RUN = 0,
    WDT_RST_ON
};

enum WDT_clk { 
    WDT_BIT_OVER = 0,
    WDT_BIT_OVER_DIV8
};

enum WDT_interrupt { 
    WDT_INT_DIS = 0,
    WDT_INT_EN
};

/*******************************************************************************
* Exported Public Function
*******************************************************************************/
void WDT_Initial(uint8_t rst_on, uint8_t wdtck);
void WDT_Set_4sec_Reset(void);
void WDT_ClearCountData(void);
void WDT_Start(void);
void WDT_ConfigureInterrupt(uint8_t enable);
#endif
#endif  // __WDT_H_
/* --------------------------------- End Of File ------------------------------ */

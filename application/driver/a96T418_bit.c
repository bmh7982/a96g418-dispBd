/**
 *******************************************************************************
 * @file        a96T418_bit.c
 * @author      ABOV R&D Division
 * @brief       Basic Interval Timer
 *
 * Copyright 2020 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/


/*******************************************************************************
* Included File
*******************************************************************************/
#include "a96T418_bit.h"
#include "a96T418.h"

/*******************************************************************************
* Private Pre-processor Definition & Macro
*******************************************************************************/

/*******************************************************************************
* Private Typedef
*******************************************************************************/

/*******************************************************************************
* Private Variable
*******************************************************************************/

/*******************************************************************************
* Private Function Prototype
*******************************************************************************/

/*******************************************************************************
* Public Function
*******************************************************************************/

/**
* @brief    Initialize BIT peripheral
* @param    clock_div    This parameter contains the selection of clock.
*
*                   - BIT_DIV4096           = 0
*                   - BIT_DIV1024           = 1
*                   - BIT_DIV128            = 2
*                   - BIT_DIV16             = 3
*                   - BIT_LSI_DIV32         = 4
* @param    period_sel   This parameter contains the period of BIT.
*
*                   - BIT_X2            = 0
*                   - BIT_X4            = 1
*                   - BIT_X8            = 2
*                   - BIT_X16           = 3
*                   - BIT_X32           = 4
*                   - BIT_X64           = 5
*                   - BIT_X128          = 6
*                   - BIT_X256          = 7
* @return   None
*/
void BIT_Initial(uint8_t clock_div, uint8_t period_sel)
{
    uint8_t temp_reg;
    
    temp_reg = BITCR;
    temp_reg &= ~((0x7 << 4) | (0x7 << 0));
    temp_reg |= ((clock_div << 4) | (period_sel << 0) | (1 << 3));
    
    BITCR = temp_reg;
}


/**
* @brief    Config BIT interrupt
* @param    enable   This parameter contains the enable of interrupt.
*
*                   - FALSE = 0
*                   - TRUE = 1
* @return   None
*/
void BIT_Interrupt_config(uint8_t enable)
{
    if(enable)
    {
        IE3 |=0X10;
    }
    else
    {
        IE3 &= ~(0X10);
    }
}

/**
* @brief    Get the BIT interrupt status.
* @param    None
* @return   Value of status(interrupt occur : 1, not occur : 0)
*/
uint8_t BIT_GetInterruptStatus(void)
{
    return ((BITCR & 0x80) >> 7);
}

/**
* @brief    Clear the BIT interrupt status.
* @param    None
* @return   None
*/
void BIT_ClearInterruptStatus(void)
{
    BITCR &= ~(0x80);
}

/**
* @brief    Get the value of BIT count.
* @param    None
* @return   Value of BIT count(0 ~ 0xFF)
*/
uint8_t BIT_GetCountValue(void)
{
    return BITCNT;
}

/**
* @brief    Clear the value of BIT count.
* @param    None
* @return   None
*/
void BIT_ClearCountValue(void)
{
    BITCR |= 0x08;
}

/* --------------------------------- End Of File ------------------------------ */

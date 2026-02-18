/**
 *******************************************************************************
 * @file        a96T418_wdt.c
 * @author      ABOV R&D Division
 * @brief       Watchdog Timer
 *
 * Copyright 2020 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/


#include "a96T418_wdt.h"
#include "a96T418_bit.h"
/* Private Pre-processor Definition & Macro ----------------------------------*/
/* Private Typedef -----------------------------------------------------------*/
/* Private Variable ----------------------------------------------------------*/
/* Private Function Prototype ------------------------------------------------*/

/**
* @brief	Initialize Watch Dog Timer peripheral
* @param    rst_on	This parameter contains the enable of watch dog timer reset.
*
*					- WDT_FREE_RUN	 = 0
*					- WDT_RST_ON     = 1
* @param    wdtck	This parameter contains the selection of Clock.
*
*					- WDT_BIT_OVER  	= 0
*					- WDT_BIT_OVER_DIV8 = 1
* @return	None
*/
void WDT_Initial(uint8_t rst_on, uint8_t wdtck)
{
	uint8_t temp_reg;
	/* Set timer mode & frequency source */
	temp_reg = WDTCR;
	temp_reg &= ~((1 << 6) | (1 << 1));
	temp_reg |= ((rst_on << 6) | (wdtck << 1));
	
	WDTCR = temp_reg;
}

/**
* @brief	Set Watch Dog Timer data operation
* @param    count	This parameter contains the value of watch dog timer count(0~0xFF).
* @return	None
*/
void WDT_SetDATA(uint8_t count) 
{
	WDTDR = count;
}

/**
* @brief	Set Watch Dog Timer 500msec operation
* @param    None	
* @return	None
*/
void WDT_Set_500msec_Reset(void) 
{
    BIT_Initial(BIT_LSI_DIV32, BIT_X16);
    
   	WDTCR = ((WDT_RST_ON << 6) | (WDT_BIT_OVER << 1));

	WDTDR = 124;
}

/**
* @brief	Set Watch Dog Timer 1sec operation
* @param    None
* @return	None
*/
void WDT_Set_1sec_Reset(void) 
{
    BIT_Initial(BIT_LSI_DIV32, BIT_X32);

   	WDTCR = ((WDT_RST_ON << 6) | (WDT_BIT_OVER << 1));

	WDTDR = 124;
}

/**
* @brief	Set Watch Dog Timer 2sec operation
* @param    None
* @return	None
*/
void WDT_Set_2sec_Reset(void) 
{
    BIT_Initial(BIT_LSI_DIV32, BIT_X64);

   	WDTCR = ((WDT_RST_ON << 6) | (WDT_BIT_OVER << 1));

	WDTDR = 124;
}

/**
* @brief	Set Watch Dog Timer 4sec operation
* @param    None
* @return	None
*/
void WDT_Set_4sec_Reset(void) 
{
    BIT_Initial(BIT_LSI_DIV32, BIT_X64);

   	WDTCR = ((WDT_RST_ON << 6) | (WDT_BIT_OVER << 1));

	WDTDR = 249;
}

/**
* @brief	Get the value of WDT counter data
* @param    None
* @return	The value of watch dog timer data
*/
uint8_t WDT_GetCountValue(void) 
{
	return WDTCNT;
}

/**
* @brief	Clear the value of WDT counter data 
* @param    None
* @return	None
*/
void WDT_ClearCountData(void) 
{
	WDTCR |= 0x20;
}

/**
* @brief	Start Watch Dog Timer operation
* @param    None
* @return	None
*/
void WDT_Start(void) 
{
	WDTCR |= 0x80;
}

/**
* @brief	Stop Watch Dog Timer operation
* @param    None
* @return	None
*/
void WDT_Stop(void) 
{
	WDTCR &= ~0x80;
}

/**
* @brief	Configure Watch Dog Timer interrupt
* @param    enable		This parameter contains the enable of watch dog timer interrupt
*
*					- WDT_INT_DIS = 0
*					- WDT_INT_EN  = 1
* @return	None
*/
void WDT_ConfigureInterrrupt(uint8_t enable) 
{
	if(enable)
			IE3 |= 0x08;
	else
			IE3 &= ~0x08;
}

/* --------------------------------- End Of File ------------------------------ */

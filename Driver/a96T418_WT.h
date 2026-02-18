/**
 *******************************************************************************
 * @file        a96T418_WT.h
 * @author      ABOV R&D Division
 * @brief       Watch Timer Header File
 *
 * Copyright 2020 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/


#ifndef __WT_H_
#define __WT_H_
/*******************************************************************************
* Included File
*******************************************************************************/
#include "A96T418.h"
#include "typedef.h"

/*******************************************************************************
* Public Typedef
*******************************************************************************/
enum WT_Interval { 
		FWCK_DIV128 = 0,
		FWCK_DIV8192,
		FWCK_DIV16384,
		FWCK_DIV16384_WTDR1
};

enum WT_Clock_Source { 
    SUB = 0,
		FX_DIV256,
		FX_DIV128,
		FX_DIV64
};

enum WT_Interrupt { 
		WT_INT_DIS = 0,
		WT_INT_EN
};

/*******************************************************************************
* Exported Public Function
*******************************************************************************/
void WT_Initial(uint8_t wt_interval, uint8_t wtckfreq);
void WT_Start(void);
void WT_Stop(void);
void WT_SetDataValue(uint8_t count); 
uint8_t WT_GetCountValue(void); 
void WT_ClearCountData(void);
void WT_ConfigureInterrrupt(uint8_t enable);

#endif  // __WT_H_
/* --------------------------------- End Of File ------------------------------ */

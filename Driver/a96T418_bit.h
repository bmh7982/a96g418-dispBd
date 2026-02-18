/**
 *******************************************************************************
 * @file        a96T418_bit.h
 * @author      ABOV R&D Division
 * @brief       BIT Header File
 *
 * Copyright 2020 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BIT_H_
#define __BIT_H_
/*******************************************************************************
* Included File
*******************************************************************************/
#include "a96T418.h"
#include "typedef.h"


/*******************************************************************************
* Public Macro
*******************************************************************************/

/*******************************************************************************
* Public Typedef
*******************************************************************************/
enum BITClk { 
    BIT_DIV4096 = 0,
		BIT_DIV1024,
		BIT_DIV128,
		BIT_DIV16,
		BIT_LSI_DIV32,
		BIT_TEMPSENSOR = 7,
};

enum BITPeriod { 
    BIT_X2 = 0,
		BIT_X4,
		BIT_X8,
		BIT_X16,
		BIT_X32,
		BIT_X64,
		BIT_X128,
		BIT_X256,
};

/*******************************************************************************
* Exported Public Function
*******************************************************************************/
void BIT_Initial(uint8_t clock_div, uint8_t period_sel);
void BIT_Interrupt_config(uint8_t enable);
uint8_t BIT_GetInterruptStatus(void);
void BIT_ClearInterruptStatus(void);
uint8_t BIT_GetCountValue(void);
void BIT_ClearCountValue(void);

#endif  /* End of __BIT_H_ */
/* --------------------------------- End Of File ------------------------------ */
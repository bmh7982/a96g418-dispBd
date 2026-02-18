/**
 *******************************************************************************
 * @file        a96T418_timer0.h
 * @author      ABOV R&D Division
 * @brief       TImer0 Header File
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
#ifndef __TIMER0_H_
#define __TIMER0_H_
/*******************************************************************************
* Included File
*******************************************************************************/
#include "A96T418.h"
#include "typedef.h"


/*******************************************************************************
* Public Macro
*******************************************************************************/

/*******************************************************************************
* Public Typedef
*******************************************************************************/
enum Timer0_mode { 
    T0_COUNTER_MODE = 0,
		T0_PWM_MODE,
		T0_CAPTURE_MODE,
};

enum Timer0_freq_div { 
    TIMER_DIV2 = 0,
		TIMER_DIV4,
		TIMER_DIV8,
		TIMER_DIV32,
		TIMER_DIV128,
		TIMER_DIV512,  
		TIMER_DIV2048,
    TIMER_EXT_CLK,
};

enum Timer0_interrupt_mode { 
    MATCH_INT = 0,
		OVERFLOW_INT,
};

/*******************************************************************************
* Exported Public Function
*******************************************************************************/
void Timer0_Initial(uint8_t mode, uint8_t freq);
void Timer0_SetMatchCounter(uint8_t match_count);
void Timer0_SetPWM(uint8_t count) ;
uint8_t Timer0_GetCaptureValue(void);
void Timer0_ClearCountData(void);
void Timer0_Start(void);
void Timer0_Stop(void);
void Timer0_ConfigureInterrupt(uint8_t mode, uint8_t enable);
void Timer0_ClearInterruptFlag(uint8_t mode);
#endif  /* End of __CLOCK_H_ */
/* --------------------------------- End Of File ------------------------------ */
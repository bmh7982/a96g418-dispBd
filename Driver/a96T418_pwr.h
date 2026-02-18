/**
 *******************************************************************************
 * @file        a96T418_pwr.h
 * @author      ABOV R&D Division
 * @brief       Power Header File
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
#ifndef __PWR_H_
#define __PWR_H_
/*******************************************************************************
* Included File
*******************************************************************************/
#include "A96T418.h"
#include "typedef.h"
#include "Intrins.h"

/*******************************************************************************
* Public Macro
*******************************************************************************/
#define PWR_IDLE_MODE		0x01
#define PWR_STOP_MODE  0x03

#define POR_FLAG								0x80
#define EXT_RESET_FLAG		0x40
#define WDT_RESET_FLAG	0x20
#define OCD_RESET_FLAG 	0x10
#define LVR_RESET_FLAG		0x08


/*******************************************************************************
* Public Typedef
*******************************************************************************/
enum  lvr_level{ 
	LVR_1_61 = 0,
	LVR_1_77 = 2,
	LVR_1_88,
	LVR_2_00,
	LVR_2_13,
	LVR_2_28,
	LVR_2_46,
	LVR_2_68,
	LVR_2_81,
	LVR_3_06,
	LVR_3_21,
	LVR_3_56,
	LVR_3_73,
	LVR_3_91,
	LVR_4_25,
};


enum  lvi_level{ 
	LVI_2_28 = 6,
	LVI_2_46,
	LVI_2_68,
	LVI_2_81,
	LVI_3_06,
	LVI_3_21,
	LVI_3_56,
	LVI_3_73,
	LVI_3_91,
	LVI_4_25,
};


/*******************************************************************************
* Exported Public Function
*******************************************************************************/
void PWR_EnterIdle(void);
void PWR_EnterStop(void);
uint8_t PWR_GetResetStatus(void);
void PWR_ClearResetStatus(uint8_t flag);

void PWR_ConfigureLVR(uint8_t select_level, uint8_t enable);
void PWR_ConfigureLVI(uint8_t select_level, uint8_t enable);
void PWR_LVI_ConfigureInterrupt(uint8_t enable);
uint8_t PWR_GetLVIStatus(void);
void PWR_ClearLVIStatus(void);


#endif  /* End of __PWR_H_ */
/* --------------------------------- End Of File ------------------------------ */
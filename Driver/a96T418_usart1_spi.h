/**
 *******************************************************************************
 * @file        a96T418_usart1_spi.h
 * @author      ABOV R&D Division
 * @brief       USART1 SPI Header File
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
#ifndef __USART1_SPI_H_
#define __USART1_SPI_H_
/*******************************************************************************
* Included File
*******************************************************************************/
#include "A96T418.h"
#include "A96T418_clock.h"
#include "typedef.h"
#include "Intrins.h"

/*******************************************************************************
* Public Macro
*******************************************************************************/
#define SPI2_SLAVE_MODE					0
#define SPI2_MASTER_MODE			1

#define SPI2_LSB					0
#define SPI2_MSB					1

#define SPI2_CPOL_LOW					0
#define SPI2_CPOL_HIGH				1

#define SPI2_CPHA_1EDGE				0
#define SPI2_CPHA_2EDGE				1

#define SPI2_TX_RX_MODE			0
#define SPI2_RX_MODE						1
#define SPI2_TX_MODE						2

#define SPI2_SS_HW_DISABLE			0
#define SPI2_SS_HW_ENABLE				1

#define SPI2_MAX_BUFFER_SIZE		8
/*******************************************************************************
* Public Typedef
*******************************************************************************/
enum spi2_interrupt_flag{
	SPI2_RX_COMPLETE_INT = 0,
	SPI2_TX_COMPLETE_INT,
	SPI2_DATA_EMPTY_INT,    	
};

/*******************************************************************************
* Exported Public Function
*******************************************************************************/
void USART1_SPI_Initial(uint8_t mode, uint32_t speed, uint8_t first_bit, uint8_t cpol, uint8_t cpha, uint8_t direction, uint8_t ss_mode);
void USART1_SPI_Enable(uint8_t enable);

void USART1_SPI_SendDataWithPolling(uint8_t *send_data, uint8_t count);
void USART1_SPI_SendDataWithInterrupt(uint8_t *send_data, uint8_t count);
void USART1_SPI_ReceiveDataWithPolling(uint8_t *receive_data, uint8_t count);
void USART1_SPI_ReceiveDataWithInterrupt(uint8_t *receive_data, uint8_t count);

void USART1_SPI_ConfigureInterrupt(uint8_t flag, uint8_t enable);
uint8_t USART1_SPI_GetInterruptStatus(void);

#endif  /* End of __USART1_SPI_H_ */
/* --------------------------------- End Of File ------------------------------ */
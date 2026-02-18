/**
 *******************************************************************************
 * @file        a96T418_usart1_spi.c
 * @author      ABOV R&D Division
 * @brief       USART1 SPI Communication
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
#include "A96T418_usart1_spi.h"

/*******************************************************************************
* Private Pre-processor Definition & Macro
*******************************************************************************/

/*******************************************************************************
* Private Typedef
*******************************************************************************/

/*******************************************************************************
* Private Variable
*******************************************************************************/
uint8_t xdata spi2_writeBuff0[SPI2_MAX_BUFFER_SIZE]_at_ 0x0180;
uint8_t spi2_writeNum0 = 0;
volatile uint8_t spi2_writeIndx0 = 0;

uint8_t *spi2_readBuff0;
uint8_t spi2_readNum0 = 0;
volatile uint8_t spi2_readIndx0 = 0;

/*******************************************************************************
* Private Function Prototype
*******************************************************************************/

/*******************************************************************************
* Public Function
*******************************************************************************/

/**
* @brief		Initialize usart1 spi peripheral
* @param   mode	This parameter contains the enable of master or slave mode(SPI). 
*
*					- SPI2_SLAVE_MODE		 	= 0
* 					- SPI2_MASTER_MODE 			= 1
* @param   speed			This parameter contains the buadrate of SPI.
* @param   first_bit	This parameter contains the transmitted first as SPI.
*
*					- SPI2_LSB 		= 0
*					- SPI2_MSB 		= 1
* @param   cpol	This parameter contains the polarity(CPOL) as SPI. 
*
*					- SPI2_CPOL_LOW 	= 0
*					- SPI2_CPOL_HIGH 	= 1
* @param   cpha	This parameter contains the phase(CPHA) as SPI. 
*
*					- SPI2_CPHA_1EDGE = 0
*					- SPI2_CPHA_2EDGE = 1
* @param   direction	This parameter contains the enable of transmit or receive mode(SPI). 
*
*					- SPI2_TX_RX_MODE 			= 0
* 					- SPI2_RX_MODE				= 1
*					- SPI2_TX_MODE 				= 2
* @param   ss_mode	This parameter contains the enable of SS function(SPI). 
*
*					- SPI2_SS_HW_DISABLE			= 0
*					- SPI2_SS_HW_ENABLE 			= 1
* @return		None
*/
void USART1_SPI_Initial(uint8_t mode, uint32_t speed, uint8_t first_bit, uint8_t cpol, uint8_t cpha, uint8_t direction, uint8_t ss_mode)
{
	uint32_t buadrate_val = 0;
	uint8_t temp_reg;
	
	spi2_writeNum0 = 0;
	spi2_readNum0 = 0;
	
	/*calculate baudrate speed*/
	buadrate_val = ((Clock_GetSystemFreq() / speed )  >> 1) * 10;

	buadrate_val = ((buadrate_val + 5) / 10) - 1; //round
	
	temp_reg = UCTRL2;
	if(direction == SPI2_RX_MODE)
		temp_reg |= RXE;	
	else if(direction == SPI2_TX_MODE)
		temp_reg |= TXE;
	else //SPI_TX_RX_MODE
		temp_reg |= (RXE | TXE);
	
	temp_reg |= USARTEN;
	
	
	USTAT	|= SOFTRST;			// USART block reset
	
	UCTRL1 |= ((0x3 << 6) | (first_bit << 2) | (cpha << 1) | (cpol << 0));  //SPI mode
	UCTRL3 |= ((mode << 7) | (ss_mode << 4));
	
	UBAUD = buadrate_val;
	
	UCTRL2 = temp_reg;
}


/**
* @brief		Enables or disables the SPI peripheral.
* @param   enable   This parameter contains the enable of this function. 
*
*					- FLASE												= 0
*					- TRUE 												= 1
* @return		None
*/
void USART1_SPI_Enable(uint8_t enable)
{

		if(enable == TRUE)
		{
			UCTRL2 |= USARTEN;
		}
		else
		{
			UCTRL2 &= ~USARTEN;
		}
	
}
	uint8_t ttt,ttt2;


/**
* @brief		Transmit data through the SPI peripheral for polling mode.
* @param   send_data   This parameter contains the data to transmit. 
* @param   count   This parameter contains the number of data. 
* @return		None
*/
void USART1_SPI_SendDataWithPolling(uint8_t *send_data, uint8_t count)
{
	uint8_t i=0;
	
	if((USTAT & (TXC)) == TXC)		
		USTAT &= ~(TXC); // TXC clear 
	for(i = 0; i < count ; i++)
	{
		while(!(USTAT & (UDRE)));
		UDATA = send_data[i];
	}
	while((USTAT & (TXC)) != TXC);		// Wait Data out
	USTAT &= ~(TXC); // TXC clear 
}

/**
* @brief		Transmit data through the SPI peripheral for interrupt mode.
* @param   send_data   This parameter contains the data to transmit. 
* @param   count   This parameter contains the number of data. 
* @return		None
*/
void USART1_SPI_SendDataWithInterrupt(uint8_t *send_data, uint8_t count)
{
	uint8_t i;

	USART1_SPI_ConfigureInterrupt(SPI2_RX_COMPLETE_INT, FALSE);
	USART1_SPI_ConfigureInterrupt(SPI2_TX_COMPLETE_INT, FALSE);
	if((USTAT & (TXC)) == TXC)		
		USTAT &= ~(TXC); // TXC clear 

	spi2_writeIndx0 = 0;
	spi2_writeNum0 = count;
	for(i = 0; i < count ; i++)
	{
		spi2_writeBuff0[i] = send_data[i];
	}
	
	USART1_SPI_ConfigureInterrupt(SPI2_TX_COMPLETE_INT, TRUE);
	
	while(!(USTAT & (UDRE)));
	UDATA = spi2_writeBuff0[spi2_writeIndx0++];

	while(spi2_writeIndx0 <= spi2_writeNum0);	//wait for complate 
	NOP;
}

/**
* @brief		Receive data through the SPI peripheral for polling mode.
* @param   receive_data   This parameter contains the data to receive. 
* @param   count   This parameter contains the number of data. 
* @return		None
*/
void USART1_SPI_ReceiveDataWithPolling(uint8_t *receive_data, uint8_t count)
{
	volatile uint8_t i;
	
	if((USTAT & (RXC)) == (RXC)) i=UDATA; //buffer emptying for avoiding overrun	//RXC auto clear 
	if((USTAT & (RXC)) == (RXC)) i=UDATA; //buffer emptying for avoiding overrun	//RXC auto clear 
	for(i = 0; i < count; i++)
	{
		while(!(USTAT & (UDRE)));
		UDATA = 0xFF; //Dummy data
		while((USTAT & (RXC))!= (RXC));		// Wait Data in
		receive_data[i] = UDATA;
		NOP;
	}
	
}

/**
* @brief		Receive data through the SPI peripheral for interrupt mode.
* @return		received data
*/
void USART1_SPI_ReceiveDataWithInterrupt(uint8_t *receive_data, uint8_t count)
{
	volatile uint8_t i=0;

	USART1_SPI_ConfigureInterrupt(SPI2_TX_COMPLETE_INT, FALSE);
	USART1_SPI_ConfigureInterrupt(SPI2_RX_COMPLETE_INT, FALSE);
	if((USTAT & (RXC)) == (RXC)) i=UDATA; //buffer emptying for avoiding overrun
	if((USTAT & (RXC)) == (RXC)) i=UDATA; //buffer emptying for avoiding overrun
	
	spi2_readIndx0 = 0;
	spi2_readNum0 = count;
	spi2_readBuff0 = (uint8_t*)receive_data; 
	
	USART1_SPI_ConfigureInterrupt(SPI2_RX_COMPLETE_INT, TRUE);

	while(!(USTAT & (UDRE)));
	UDATA = 0xFF; //Dummy data	
	
	while(spi2_readIndx0 < spi2_readNum0);	//wait for complate 
	NOP;

}

/**
* @brief		Configure the enable or disable SPI interrupt.
* @param   flag   This parameter contains the selection of this function. 
*
*					- SPI2_RX_COMPLETE_INT 	= 0
*					- SPI2_TX_COMPLETE_INT 	= 1
* 					- SPI2_DATA_EMPTY_INT 	= 2
* @param   enable   This parameter contains the enable of this function. 
*
*					- FLASE												= 0
*					- TRUE 												= 1
* @return		None
*/
void USART1_SPI_ConfigureInterrupt(uint8_t flag, uint8_t enable)
{
	uint8_t temp_reg, temp_reg2;
	
	if(flag == SPI2_TX_COMPLETE_INT)
	{
		temp_reg = IE1;
		temp_reg &= ~(0x1 << 1);
		temp_reg |= (enable << 1);
		
		temp_reg2 = UCTRL2;
		temp_reg2 &= ~(0x1 << (5 + flag));
		temp_reg2 |= (enable << (5 + flag));
		
		IE1 = temp_reg;
		UCTRL2 = temp_reg2;
	}
	else if(flag == SPI2_RX_COMPLETE_INT)
	{
		temp_reg = IE3;
		temp_reg &= ~(0x1 << 1);
		temp_reg |= (enable << 1);
	
		temp_reg2 = UCTRL2;
		temp_reg2 &= ~(0x1 << (5 + flag));
		temp_reg2 |= (enable << (5 + flag));
		
		IE3 = temp_reg;
		UCTRL2 = temp_reg2;
	}
	else if(flag == SPI2_DATA_EMPTY_INT)
	{
		temp_reg = UCTRL2;
		temp_reg &= ~(0x1 << (5 + flag));
		temp_reg |= (enable << (5 + flag));
		
		UCTRL2 = temp_reg;
	}

}

/**
* @brief		Get the USART interrupt status.
* @return		Value of status(interrupt flag)
*/
uint8_t USART1_SPI_GetInterruptStatus()
{
	return USTAT;
}


//==============================================================================
// interrupt routines
//==============================================================================
void USART1_RXInt_Handler() interrupt USART1_RX_VECT
{	
	uint8_t temp;
	
	//master
	if(UCTRL3 & MASTER) 
	{
		if (USTAT & DOR )
		{
			//DATA OVERUN handling(user)
			NOP;
		}
		temp = UDATA;

		if(spi2_readIndx0 < spi2_readNum0) 
		{
			spi2_readBuff0[spi2_readIndx0++] = temp;
			if(spi2_readIndx0 < spi2_readNum0) {
				while(!(USTAT & (UDRE)));
				UDATA=0xFF; //Dummy data
			}
			else
				NOP;
		}
	}
	//slave
	else 
 	{
		//USER CODE		
		if (USTAT & DOR )
		{
			//DATA OVERUN handling(user)
			NOP;
		}
		
		temp = UDATA;
		if(temp == 0xFF)
		{
			NOP;
		}
		else
		{
			extern uint8_t xdata read_data[4];
			read_data[spi2_readNum0++%4] = temp;
		}

		while(!(USTAT & (UDRE)));
		//0x05 ack data
		UDATA = 0x05;
		
		//USER CODE
		
	}
	
}

void USART1_TXInt_Handler() interrupt USART1_TX_VECT
{
	if(spi2_writeIndx0<spi2_writeNum0)
	{
		while(!(USTAT & (UDRE)));
		UDATA = spi2_writeBuff0[spi2_writeIndx0];
		spi2_writeIndx0++;
	}
	else 
		spi2_writeIndx0++;
}


/* --------------------------------- End Of File ------------------------------ */
/**
 *******************************************************************************
 * @file        a96T418_usi_i2c.c
 * @author      ABOV R&D Division
 * @brief       USI I2C Communication
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
#include "A96T418_usi_i2c.h"

/*******************************************************************************
* Private Pre-processor Definition & Macro
*******************************************************************************/

/*******************************************************************************
* Private Typedef
*******************************************************************************/

/*******************************************************************************
* Private Variable
*******************************************************************************/
uint8_t i2c_mode[I2C_MAX_CHANNEL] = {0, };

uint8_t *receiveBuffer0=0;
uint8_t *receiveBuffer1=0;
uint8_t receiveCount[I2C_MAX_CHANNEL] = {0, };
uint8_t receiveNum[I2C_MAX_CHANNEL] = {0, };

uint8_t xdata transmitBuffer0[I2C_MAX_BUFFER_SIZE] _at_ 0x380;
uint8_t xdata transmitBuffer1[I2C_MAX_BUFFER_SIZE] _at_ 0x3a0;
uint8_t transmitCount[I2C_MAX_CHANNEL] = {0, };
uint8_t transmitNum[I2C_MAX_CHANNEL] = {0, };
/*******************************************************************************
* Private Function Prototype
*******************************************************************************/
static void USI_I2C_Start(uint8_t ch, uint8_t enable);
static void USI_I2C_Stop(uint8_t ch, uint8_t enable);
static void USI_I2C_Send7bitAddress(uint8_t ch, uint8_t dev_addr, uint8_t direction);
static void USI_I2C_SlaveProcessData(uint8_t ch);
static void USI_I2C_MasterProcessData(uint8_t ch);
static void USI_I2C_GeneralCallProcess(uint8_t ch);
/*******************************************************************************
* Public Function
*******************************************************************************/
/**
* @brief		Initialize usi(i2c) peripheral
* @param   ch		This parameter contains the channel of USI peripheral.
* @param   speed			This parameter contains the buadrate of i2c.
* @param   addr	This parameter contains the slave address of i2c(address[7:1]bit)
* @param   ack	This parameter contains the enable of acknowledge signal. 
*
*					- I2C_ACK_DISABLE = 0
*					- I2C_ACK_ENABLE = 1
* @return		None
*/
void USI_I2C_Initial(uint8_t ch, uint32_t speed, uint8_t addr, uint8_t ack)
{
	uint32_t period = 0;
	uint8_t temp_reg, temp_reg2, temp_reg3;
	
	receiveNum[ch] = 0;
	transmitNum[ch] = 0;
	if(1) { 
		extern uint8_t xdata read_data[I2C_MAX_BUFFER_SIZE];
		receiveBuffer0 =  (uint8_t*)read_data;
	}
	if(ch == I2C_CH0)
	{
		temp_reg = USI0CR2;
		temp_reg &= ~USI0EN;
		temp_reg |= USI0EN;
		
		temp_reg2 = USI0CR1;
		temp_reg2 &= ~(0x3 << 6);
		temp_reg2 |= USI0MS_I2C;
		
		temp_reg3 = USI0CR4;
		temp_reg3 &= ~(0x1 << 3);
		temp_reg3 |= (ack << 3);
		
		USI0CR2 = temp_reg;
		USI0CR1 = temp_reg2;
		USI0CR4 = temp_reg3;
	
		USI0SAR = addr;
	
		period = ((Clock_GetSystemFreq() / speed) - 4) / 4;
			
		if(period & 0x1)
		{
			USI0SCHR = (period+1) >> 1;
		}
		else
		{
			USI0SCHR = period >> 1;
		}

		USI0SCLR = period >> 1;
		/* SDAn output hold timing */
		USI0SDHR = period >> 2;
			
		USI0ST2 = 0x00;
		
	}
	
}

/**
* @brief		Enables or disables the I2C peripheral.
* @param   ch		This parameter contains the channel of USI peripheral.
* @param   enable   This parameter contains the enable of this function. 
*
*					- FLASE												= 0
*					- TRUE 												= 1
* @return		None
*/
void USI_I2C_Enable(uint8_t ch, uint8_t enable)
{
	if(ch == I2C_CH0)
	{
		if(enable == TRUE)
		{
			USI0CR2 |= USI0EN;
		}
	}

}


/**
* @brief		Enables or disables the I2C general call function.
* @param   ch		This parameter contains the channel of USI peripheral.
* @param   enable   This parameter contains the enable of this function. 
*
*					- FLASE												= 0
*					- TRUE 												= 1
* @return		None
*/
void USI_I2C_ConfigureGerneralCall(uint8_t ch, uint8_t enable)
{
	if(ch == I2C_CH0)
	{
		if(enable == TRUE)
		{
			USI0SAR |= 0x1;
		}
		else
		{
			USI0SAR &= ~0x1;
		}
	}

}

/**
* @brief		Enables or disables the I2C Start condition.
* @param   ch		This parameter contains the channel of USI peripheral.
* @param   enable   This parameter contains the enable of this function. 
*
*					- FLASE												= 0
*					- TRUE 												= 1
* @return		None
*/
void USI_I2C_Start(uint8_t ch, uint8_t enable)
{
	if(ch == I2C_CH0)
	{
		if(enable == TRUE)
		{
			USI0CR4 |= 0x1;
		}
		else
		{
			USI0CR4 &= ~0x1;
		}
	}

}

/**
* @brief		Enables or disables the I2C Stop condition.
* @param   ch		This parameter contains the channel of USI peripheral.
* @param   enable   This parameter contains the enable of this function. 
*
*					- FLASE												= 0
*					- TRUE 												= 1
* @return		None
*/
void USI_I2C_Stop(uint8_t ch, uint8_t enable)
{
	if(ch == I2C_CH0)
	{
		if(enable == TRUE)
		{
			USI0CR4 |= 0x2;
		}
		else
		{
			USI0CR4 &= ~0x2;
		}
	}

}

/**
* @brief		Enables or disables the I2C Software reset
* @param   ch		This parameter contains the channel of USI peripheral.
* @param   enable   This parameter contains the enable of this function. 
*
*					- FLASE												= 0
*					- TRUE 												= 1
* @return		None
*/
void USI_I2C_SoftwareReset(uint8_t ch, uint8_t enable)
{
	if(ch == I2C_CH0)
	{
		if(enable == TRUE)
		{
			USI0CR4 |= 0x20;
		}
		else
		{
			USI0CR4 &= ~0x20;
		}
	}

}


/**
* @brief		Configure the I2C Acknowledge signal.
* @param   ch		This parameter contains the channel of USI peripheral.
* @param   enable   This parameter contains the enable of this function. 
*
*					- FLASE												= 0
*					- TRUE 												= 1
* @return		None
*/
void USI_I2C_ConfigureAcknowledge(uint8_t ch, uint8_t enable)
{
	if(ch == I2C_CH0)
	{
		if(enable == TRUE)
		{
			USI0CR4 |= 0x8;
		}
		else
		{
			USI0CR4 &= ~0x8;
		}
	}

}


/**
* @brief		Write multi bytes by writing as i2c master.
* @param   ch		This parameter contains the channel of USI peripheral.
* @param   dev_addr			This parameter contains the slave address of target.
* @param   *write_data			This parameter contains the write data of i2c(pointer variable)
* @param   write_len			This parameter contains the number of write length.
* @param   *read_data			This parameter contains the read data of i2c(pointer variable)
* @param   read_len			This parameter contains the number of read length.
* @return		None
*/
void USI_I2C_MasterTransferData(uint8_t ch, uint8_t dev_addr, uint8_t *write_data, uint8_t write_len, uint8_t *read_data, uint8_t read_len)
{
	uint8_t i;
	
	if(ch == I2C_CH0)
	{
		for(i = 0; i < I2C_MAX_BUFFER_SIZE; i++)
			transmitBuffer0[i] = write_data[i];
		
		receiveBuffer0 =  (uint8_t*)read_data;
		for(i = 0; i < I2C_MAX_BUFFER_SIZE; i++)
			receiveBuffer0[i] = 0;
	}

	transmitCount[ch] = write_len;
	receiveCount[ch] = read_len;
	
	i2c_mode[ch] = I2C_BUSY;
	
	if(write_len != 0) 
		USI_I2C_Send7bitAddress(ch, dev_addr, I2C_WRITE_MODE);
	else
		USI_I2C_Send7bitAddress(ch, dev_addr, I2C_READ_MODE);
	
	while(i2c_mode[ch] == I2C_BUSY)
	{
		//timeout
	}
}

/**
* @brief		Send slave address as i2c master.
* @param   ch		This parameter contains the channel of USI peripheral.
* @param   dev_addr			This parameter contains the slave address of target.
* @param   direction			This parameter contains the mode of i2c(read or write).
*
*					- I2C_WRITE_MODE 	= 0
*					- I2C_READ_MODE 	= 1
* @return		None
*/
void USI_I2C_Send7bitAddress(uint8_t ch, uint8_t dev_addr, uint8_t direction)
{
	
	if(ch == I2C_CH0)
	{
		if(USI0ST2 == BUSY) 
			USI_I2C_Initial(ch, I2C_SPEED, 0x00, I2C_ACK_ENABLE);
		
		USI0DR = dev_addr | direction;
		if(direction)  
			receiveNum[ch] = 0;
		else 
			transmitNum[ch] = 0;
	}
	
	USI_I2C_ConfigureAcknowledge(ch, TRUE);	//Ack generate
	USI_I2C_Start(ch, TRUE);
	
}

/**
* @brief		Response specific bytes as i2c master.(custom user)
* @param   ch		This parameter contains the channel of USI peripheral.
* @return		None
*/
static void USI_I2C_MasterProcessData(uint8_t ch)
{
	uint8_t i2c_status;
	
	if(ch == I2C_CH0)
	{
		i2c_status = USI0ST2;
	}
	
	if(i2c_status & RXACK)
	{
		// Master Tx mode
		if(i2c_status & TMODE)
		{
			if(transmitCount[ch])
			{
				if(ch == I2C_CH0)
					USI0DR = transmitBuffer0[transmitNum[ch]];		
				
				transmitCount[ch] -= 1;
				transmitNum[ch] += 1;
			}
			else
			{
				if(receiveCount[ch])
				{
					//Restart for Rx
					USI_I2C_Send7bitAddress(ch, I2C_DEVICE_ADDRESS, I2C_READ_MODE);
				}
				else
				{
					// TxLength 0 Stop
					USI_I2C_Stop(ch, TRUE);
				}
			}
		}
		// Master Rx mode
		else
		{
			if(i2c_status&GCALL)
			{
				// Address ACK is received
				if(receiveCount[ch] == 1)
				{
					USI_I2C_ConfigureAcknowledge(ch, FALSE);	// NoAck generate
				}
			}
			else
			{
				receiveCount[ch] -= 1;
				
				if(receiveCount[ch] > 1)
				{
					if(ch == I2C_CH0)
						receiveBuffer0[receiveNum[ch]] = USI0DR;
					
					receiveNum[ch] += 1;
				}
				else if(receiveCount[ch] == 1)
				{
					if(ch == I2C_CH0)
						receiveBuffer0[receiveNum[ch]] = USI0DR;
					
					receiveNum[ch] += 1;
					
					USI_I2C_ConfigureAcknowledge(ch, FALSE);	// NoAck generate
				}
				else
				{
					USI_I2C_Stop(ch, TRUE);
				}
				
			}
		}
	}
	else
	{
		// NoAck data is received
		if(receiveCount[ch] == 1)
		{
			receiveCount[ch] = 0;
			
			if(ch == I2C_CH0)
				receiveBuffer0[receiveNum[ch]] = USI0DR;
		}
		else
			NOP;
		
		// NoAck Stop
		USI_I2C_Stop(ch, TRUE);
		
	}
}

/**
* @brief		Response specific bytes as i2c slave.(custom user)
* @param   ch		This parameter contains the channel of USI peripheral.
* @return		None
*/
static void USI_I2C_SlaveProcessData(uint8_t ch)
{

	uint8_t i2c_status;
	
	if(ch == I2C_CH0)
	{
		i2c_status = USI0ST2;
	}

	if((i2c_status & GCALL))
	{
		USI_I2C_GeneralCallProcess(ch); //USER CODE;
	}
	else
	{
		//USER CODE;
		//USER CODE;
		if(i2c_status & TMODE) // Slave Tx mode
		{
			if(i2c_status & SSEL0) //Slave Select
			{
				transmitNum[ch] = 0;
			}
		
				if(ch == I2C_CH0)
					USI0DR = transmitBuffer0[transmitNum[ch]+1];
					
				transmitCount[ch] -= 1;
				transmitNum[ch] += 1;
					
				if(transmitCount[ch] == 1) 
				{
					i2c_mode[ch] = I2C_IDLE;
				}
		}
		else  // Slave Rx mode
		{
			if(i2c_status & SSEL0) //Slave Select
			{
				receiveNum[ch] = 0;
			}
			
			if(ch == I2C_CH0)	
			{
				receiveBuffer0[receiveNum[ch]] = USI0DR;
				//eco
				transmitBuffer0[receiveNum[ch]] = receiveBuffer0[receiveNum[ch]];
			}
			
			receiveNum[ch] += 1;
			//eco
			transmitCount[ch] = receiveNum[ch];
		}
			//USER CODE;
			//USER CODE;
			
	}
		//END
}

/**
* @brief		Handle general call as i2c process.(custom user)
* @param   ch		This parameter contains the channel of USI peripheral.
* @return		None
*/
static void USI_I2C_GeneralCallProcess(uint8_t ch)
{
	if(ch == I2C_CH0)
		NOP;
	
	//USER CODE
	//USER CODE
}


/**
* @brief		Configure the enable or disable I2C interrupt.
* @param   ch		This parameter contains the channel of USI peripheral.
* @param   enable   This parameter contains the enable of this function. 
*
*					- FLASE												= 0
*					- TRUE 												= 1
* @return		None
*/
void USI_I2C_ConfigureInterrupt(uint8_t ch, uint8_t enable)
{
	if(ch == I2C_CH0)
	{
		if(enable == TRUE)
		{
			IE1 |= 0x04;
			USI0CR4 |= 0x10;
		}
		else
		{
			USI0CR4 &= ~0x10;
			IE1 &= ~0x04;
		}
	}

}

/**
* @brief		Get the I2C interrupt status.
* @param   ch		This parameter contains the channel of USI peripheral.
* @return		Value of status(interrupt flag)
*/
uint8_t USI_I2C_GetInterruptStatus(uint8_t ch)
{
	uint8_t result;

	if(ch == I2C_CH0)
	{
		result = USI0ST2;
	}
	
	return result;
}


/**
* @brief		Configure the enable or disable I2C interrupt.
* @param   ch		This parameter contains the channel of USI peripheral.
* @return		None
*/
void USI_I2C_InterruptHandler(uint8_t ch)
{
	uint8_t i2c_status, i2c_operation;
	
	if(ch == I2C_CH0)
	{
		i2c_status = USI0ST2;
		i2c_operation = USI0CR4;
	}
	
	if((i2c_status & MLOST) || (i2c_status & STOPD))
	{
		i2c_mode[ch] = I2C_IDLE;
		if(i2c_status & MLOST)
			USI_I2C_Initial(ch, I2C_SPEED, I2C_DEVICE_ADDRESS, I2C_ACK_ENABLE);
	}
	else
	{
			if(i2c_operation & 0x4)  //Master mode
			{
				USI_I2C_MasterProcessData(ch);
			}
			else  //Slave mode
			{
				USI_I2C_SlaveProcessData(ch);
			}
	}
	
	
	if(ch == I2C_CH0)
	{
		USI0ST2 = 0x00;
	}
	
}


/**
* @brief		Enables or disables the I2C Wake-Up function.
* @param   ch		This parameter contains the channel of USI peripheral.
* @param   enable   This parameter contains the enable of this function. 
*
*					- FLASE												= 0
*					- TRUE 												= 1
* @return		None
*/
void USI_I2C_ConfigureWakeUp(uint8_t ch, uint8_t enable)
{
	if(ch == I2C_CH0)
	{
		if(enable == TRUE)
			USI0ST1 |= (1<<4);
		else
			USI0ST1 &= ~(1<<4);
	}

}


void I2C0_Int_Handler(void) interrupt USI0_I2C_VECT
{
	USI_I2C_InterruptHandler(I2C_CH0);
}


/* --------------------------------- End Of File ------------------------------ */
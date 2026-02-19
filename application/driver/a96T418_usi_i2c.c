/**
 *******************************************************************************
 * @file        a96T418_usi_i2c.c
 * @author      ABOV R&D Division
 * @brief       A96T418 USI I2C driver Code
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
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
#include <intrins.h>
#include "A96T418_usi_i2c.h"
#include "A96T418.h"
#include "RegisterMap.h"
#include "user_function.h"
#include "touch_lib.h"
#include "common.h"
#include "a96T418_clock.h"

#if (I2C_ENABLE == 1)

/*******************************************************************************
* Private Pre-processor Definition & Macro
*******************************************************************************/

/*******************************************************************************
* Private Typedef
*******************************************************************************/

/*******************************************************************************
* Private Variable
*******************************************************************************/

bit g_sub_add_flag = 0;
bit g_sub_addr_pre_flag=0;
static uint8_t g_i2c_sub_addr = 0;


/*******************************************************************************
* Private Function Prototype
*******************************************************************************/
static void USI_I2C_SlaveProcessData(uint8_t ch);
/*******************************************************************************
* Public Function
*******************************************************************************/
/**
* @brief        Initialize usi(i2c) peripheral
* @param   ch       This parameter contains the channel of USI peripheral.
* @param   speed            This parameter contains the buadrate of i2c.
* @param   addr This parameter contains the slave address of i2c(address[7:1]bit)
* @param   ack  This parameter contains the enable of acknowledge signal.
*
*                   - I2C_ACK_DISABLE = 0
*                   - I2C_ACK_ENABLE = 1
* @return       None
*/

void I2C_Init(uint8_t ch, uint32_t speed, uint8_t addr, uint8_t ack)
{
    uint32_t period = 0;
    uint32_t temp = 0;
    uint8_t temp_reg, temp_reg2, temp_reg3;
       
    if(ch == I2C_CH0)
    {
        temp_reg = USI0CR2;
        temp_reg &= ~0x02;
        temp_reg |= 0x02;
        
        temp_reg2 = USI0CR1;
        temp_reg2 &= ~(0x3 << 6);
        temp_reg2 |= 0x80;
        
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
        USI0SDHR = 1;
            
        USI0ST2 = 0x00;
        
    }

    IP = 0x04; 
    IP1 = 0x04;
    
}

void I2C_Init_in_INT(uint8_t ch, uint32_t speed, uint8_t addr, uint8_t ack)
{
    uint32_t period = 0;
    uint32_t temp = 0;
    uint8_t temp_reg, temp_reg2, temp_reg3;
       
    if(ch == I2C_CH0)
    {
        temp_reg = USI0CR2;
        temp_reg &= ~0x02;
        temp_reg |= 0x02;
        
        temp_reg2 = USI0CR1;
        temp_reg2 &= ~(0x3 << 6);
        temp_reg2 |= 0x80;
        
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
        USI0SDHR = 1;
            
        USI0ST2 = 0x00;
        
    }

    IP = 0x04; 
    IP1 = 0x04;
    
}

/**
* @brief        Response specific bytes as i2c slave.(custom user)
* @param   ch       This parameter contains the channel of USI peripheral.
* @return       None
*/
static void USI_I2C_SlaveProcessData(uint8_t ch)
{
    uint8_t i2c_status = 0;

    if(ch == I2C_CH0)
    {
        i2c_status = USI0ST2;
    }

    if(i2c_status & SSEL)                            // Slave address matchded
    {
        g_sub_addr_pre_flag=0;                       // defence I2C fail 

        if(i2c_status & TMODE)                       // step 3-1.Slave Address + Read
        {
            if(g_i2c_sub_addr < REG_MAX)
            {
                USI0DR = RegMap[g_i2c_sub_addr];
                g_i2c_sub_addr++;
            }
            else
            {
                USI0DR = 0x77;
            }
        }
        else
        {                                           // step 1. Slave Address + Wrtie
            g_sub_add_flag = 0;
        }
    }
    else if(i2c_status&STOPD)                       // I2C STOP 
    {            
        if(g_sub_addr_pre_flag){                    // defence I2C fail 
            g_sub_addr_pre_flag=0;
        }
        else{
        //    g_i2c_flag = 0;
        }
    }
    else                                            // Data transfer (SubAddr or Data)
    {
        g_sub_addr_pre_flag=0;                      // defence I2C fail 

        if(i2c_status & TMODE)                      // slave transmit?
        {                                           // step 3-2. Send Data
            if(i2c_status & RXACK)
            {
                if(g_i2c_sub_addr < REG_MAX)
                {
                    USI0DR = RegMap[g_i2c_sub_addr];
                    g_i2c_sub_addr++;
                }
                else
                {
                    USI0DR = 0x77;
                }
             }
        }
        else
        {
            if(g_sub_add_flag == 0)                 // step 2. SubAddr Check
            {
                g_i2c_sub_addr = USI0DR;

                g_sub_add_flag = 1;
                g_sub_addr_pre_flag=1;           
            }
            else{                                   // step 3. Data Write
                if(g_i2c_sub_addr < REG_MAX)
                {
                    RegMap[g_i2c_sub_addr] = USI0DR;
                    g_i2c_sub_addr++;
                }
            }
        } 
    }
    //USI0ST2 = 0x00;                               // next process continue
}


/**
* @brief        Configure the enable or disable I2C interrupt.
* @param   ch       This parameter contains the channel of USI peripheral.
* @return       None
*/
void USI_I2C_InterruptHandler(uint8_t ch)
{
    uint8_t i2c_status = 0, i2c_operation = 0;

    if(ch == I2C_CH0)
    {
        i2c_status = USI0ST2;
        i2c_operation = USI0CR4;
    }
    
    if((i2c_status & MLOST) || (i2c_status & STOPD))
    {
        if(i2c_status & MLOST)
            I2C_Init_in_INT(ch, I2C_SPEED, I2C_DEVICE_ADDRESS, I2C_ACK_ENABLE);
    }
    else
    {
        if(i2c_operation & 0x4)         // Master mode
        {
            ;
        }
        else                            // Slave mode
        {
            USI_I2C_SlaveProcessData(ch);
        }
    }
    
    
    if(ch == I2C_CH0)
    {
        USI0ST2 = 0x00;
    }
    
}

void I2C0_Int_Handler(void) interrupt USI0_I2C_VECT
{
    EA = 1;
    
    USI_I2C_InterruptHandler(I2C_CH0);
}

/* --------------------------------- End Of File ------------------------------ */
#endif

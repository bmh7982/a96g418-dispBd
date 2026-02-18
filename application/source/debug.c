/**
 *******************************************************************************
 * @file        debug.c
 * @author      ABOV R&D Division
 * @brief       A96T418 data debugging code
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/


/** *******************************************************************
 * @file         debug.c
 * @brief        : USI0-UART/500000bps
                 : DBG_Send_Data() protocol
                     - 3A(STX)
                     - xx(LEN): MODE ~ MSG
                     - 01 10 (MODE)
                     - xx(KEY)
                     - 00(Cycle)
                     - MSG
                     - xx xx(CheckSum)
                     - 0D 0A(CR/LF)
                 : DBG_RX_Check() protocol
                     - 02(STX)
                     - xx(CMD) : 'R'(Get), 'M'(Frequency), 'T'(write), 'w', 'S'
                     - MSG
                     - 03(ETX)
 * @author   ABOV Sensor Solution Team
 *
 * Copyright(C) 2020, ABOV Semiconductor
 * All rights reserved.
 *
 **********************************************************************/
//#include <stdio.h>
#include <stdlib.h>
#include <intrins.h>
#include "A96T418.h" 
#include "common.h"
#include "touch_lib.h"
#include "user_function.h"
#include "debug.h"

#if (SLIDE_FUNCTION_EN | WHEEL_FUNCTION_EN)
#include "gesture.h"
#endif

#if (DBG_FLASH_SAVE == 1)
#include "flash.h"
#include "dbg_flash.h"  
#endif
#if (I2C_ENABLE == 1)
#include "RegisterMap.h"

uint16_t *dataBuff;
#endif

#if (UART_ENABLE == 1)

#define DBG_TS_REG  1

struct dbg_cfg dbg;
struct dbg_uart uart;
static uint8_t idata rx_step = 0;
static uint8_t idata rx_data_buf[DBG_RX_MSG_SIZE];
static uint8_t idata rx_data_idx = 0;

/** *******************************************************************
 * @brief       Set UART baudrate
 * @param[in]   baud : baudrate index
 * @return      void
 *
 *********************************************************************/
void DBG_Set_Baudrate (uint8_t baud)
{
    switch (baud)
    {
        case 0 :
            USI0BD = 3;     /* 500000 */
            break;
        case 1 :
            USI0BD = 16;    /* 115200 */
            break;
        case 2 :
            USI0BD = 51;    /* 38400 */
            break;
        case 3 :
            USI0BD = 51;    /* 9600 */
            break;
        default :
            USI0BD = 51;    /* 9600 */
            break;
    }
    g_sys_flag.dbg_en = 1;
}
/** *******************************************************************
 * @brief       USI0RX Interrupt Service Routine
 * @param[in]   ring buffer
 * @return      void
 *
 *********************************************************************/
static void USI0RX_ISR (void) interrupt USI0_RX_VECT  
{
    uart.rx_queue[uart.rx_write_idx++] = USI0DR;    
    uart.rx_write_idx %= DBG_RX_BUFF_SIZE;
}
/** *******************************************************************
 * @brief       USI0TX Interrupt Service Routine
 * @param[in]   ring buffer
 * @return      void
 *
 *********************************************************************/
static void USI0TX_ISR (void) interrupt USI0_TX_VECT
{
    USI0DR = uart.tx_queue[uart.tx_read_idx++];
    uart.tx_read_idx %= DBG_TX_BUFF_SIZE;
    if (uart.tx_read_idx == uart.tx_write_idx)
    {
        IE1 &= ~BIT(4);
        dbg.flag.busy = 0;
    }
    USI0ST1 &= ~BIT(7);
}

/** *******************************************************************
 * @brief       Set USI0 to UART mode
 * @param[in]   - UART Mode 8N1
                - Double Speed Mode
 * @return      void
 *
 *********************************************************************/
void DBG_Init_UART (void) 
{
    //uint8_t temp;
    P0IO &= ~BIT(1);    // P02 : input
    P0PU |= BIT(1);     // P01 : pull-up
    P0FSRL |= BIT(5)+BIT(4)+BIT(3)+BIT(2);      // RXD0(P01), TXD0(P02) 

    USI0ST1 |= 0x80;
    USI0CR1 =(0<<6) |   /* 0: Async(Normal UART)    */
                        /* 1: Sync(Sync UART)       */
                        /* 2: Reserved              */
                        /* 3: SPI                   */
             (0<<4) |   /* 0: No Parity             */
                        /* 1: Reserved              */
                        /* 2: Even Parity           */
                        /* 3: Odd Parity            */
             (3<<1) |   /* 0: 5bit                  */
                        /* 1: 6bit                  */
                        /* 2: 7bit                  */
                        /* 3: 8bit                  */
                        /* 4: Reserved              */
                        /* 5: Reserved              */
                        /* 6: Reserved              */
                        /* 7: 9bit                  */
             (0<<0);     
    
    USI0CR2 =(0<<7) |   /* 1: When UDRE is set, request an interrupt    */
             (1<<6) |   /* 1: When TXC is set, request an interrupt     */
             (1<<5) |   /* 1: When RXC is set, request an interrupt     */
             (0<<4) |   /* 1: When WAKE is set, request an interrupt    */
             (1<<3) |   /* 1: Transmitter Enable                        */
             (1<<2) |   /* 1: Receiver Enable                           */
             (1<<1) |   /* 1: USART Enable                              */
             (1<<0);    /* 1: Double Speed                              */
             
    USI0CR3 =(0<<7) |   /* 1: Master Mode Output and XCK is output pin          */
             (0<<6) |   /* 1: Loop Back Mode                                    */
             (0<<5) |   /* 1: XCK is active while any frame is on transferring  */
             (0<<4) |   /* 1: SS output to other slave device                   */
             (0<<3) |   /* 1: Exchange MOSIn and MISOn function                 */
             (0<<2) |   /* 1: 2 Stop bit                                        */
             (0<<1) |   /* 1: MSB(9th bit) to be transmitted is '1'             */
             (0<<0);    /* 1: MSB(9th bit) received is '1'                      */
             
    USI0ST1 =(0<<7) |   /* 1: Transmit Buffer is empty                                                                      */
             (0<<6) |   /* 1: Transmit Buffer is empty and the data in transmit shift register are shifted out completely   */
             (0<<5) |   /* 1: There are more than 1 data in the receive buffer                                              */
             (0<<4) |   /* 1: WAKE interrupt is generated                                                                   */
             (0<<3) |   /* 1: Reset USART                                                                                   */
             (0<<2) |   /* 1: Data Over-Run Detected                                                                        */
             (0<<1) |   /* 1: Frame Error Detected                                                                          */
             (0<<0);    /* 1: Parity Error Detected                                                                         */

    //USI0BD = DBG_BAUD_RATE;
    USI0DR = 0;         /* clear 안해주면 처음 이상한 값 출력*/ 

    IE1 |= BIT(3);
}
/** *******************************************************************
 * @brief       Initialize UART variables
 * @param[in]   
 * @return      void
 *
 *********************************************************************/
uint8_t DBG_Init_UART_Param (void)
{
    uint8_t i;

    rx_step = DBG_RX_STEP_STX;
    rx_data_idx = 0;
    uart.rx_write_idx = 0;
    uart.rx_read_idx = 0; 
    for (i = 0; i < DBG_RX_BUFF_SIZE; i++)
    {
        uart.rx_queue[i] = 0;
    }
    for (i = 0; i < DBG_RX_MSG_SIZE; i++)
    {
        rx_data_buf[i] = 0;
    }
    dbg.flag.busy = 0;

    return (1);
}
/** *******************************************************************
 * @brief       Initialize UART variables
 * @param[in]   "1A"(0x31,0x41) -> 0x1A
 * @return      void
 *
 *********************************************************************/
uint8_t Hexstr_To_Binary (uint8_t *str)
{
    uint8_t i;
    uint8_t temp = 0;

    for (i = 0; i < 2; i++)
    {
        temp <<= 4;
        
        if ((*str) >= '0' && (*str) <= '9')
        {
            temp |= ((*str) - '0');
        }
        else if ((*str) >= 'a' && (*str) <= 'f')
        {
            temp |= ((*str) + 10 - 'a');
        }
        else
        {
            return 0xff;
        }
        str++;
    }

    return temp;
}
/** *******************************************************************
 * @brief       check received data fromm smartkey
 * @param[in]   ptr : pointer of pointer of message buffer
 * @return      result : return rx-packet's complete state
 *
 *********************************************************************/
//#define DATA_LEN  8       // | 02 | 52 30 31 30 30 30 32 0D | 03 |
uint8_t DBG_RX_Check(uint8_t **ptr)
{
    uint8_t temp = 0;
    uint8_t result;

    result = DBG_RX_READY;

    while (uart.rx_write_idx != uart.rx_read_idx)   
    {
        temp = uart.rx_queue[uart.rx_read_idx++]; 
        uart.rx_read_idx %= DBG_RX_BUFF_SIZE;
        
        switch (rx_step)
        {
            case DBG_RX_STEP_STX :                      /* STX */
                if (temp == DBG_SMARTKEY_SET_STX)
                {
                    rx_data_idx = 0;
                    rx_step = DBG_RX_STEP_DATA;
                }
                break;                      
            case DBG_RX_STEP_DATA :                         /* MSG */
                rx_data_buf[rx_data_idx++] = temp;
                if (temp == DBG_SMARTKEY_SET_ETX)
                {
                    rx_step = DBG_RX_STEP_STX;
                    result = DBG_RX_COMPLETE;
                    *ptr = &rx_data_buf[0];                 
                }
                break;
            default :
                rx_step = DBG_RX_STEP_STX;
                break;
        }   

        if (result != DBG_RX_READY)
        {
            break;
        }
    }

    return (result);
}

/** *******************************************************************
 * @brief       Initialize debug parameters
 * @param[in]   none
 * @return      void
 *
 *********************************************************************/
void DBG_Init_Variable(void)
{
    #if (DBG_FLASH_SAVE==1)
    uint16_t i;
    for (i = 0; i < FLASH_PAGE_N; i++)
    {
        Flash_Erase_Page(FLASH_START_ADDR+i*FLASH_PAGE_SIZE);
    }
    fla_idx = 0;
    fla_addr_w = FLASH_START_ADDR; 
    fla_addr_r = FLASH_START_ADDR; 
    #endif
    
    dbg.start_idx   = DBG_START_INDX;
    dbg.ch_cnt      = DBG_CH_CNT;
    dbg.mask        = DBG_MASK_ITEM; 
}
/** *******************************************************************
 * @brief       move one byte to tx-buffer
 * @param[in]   dat : data to move
 * @return      void
 *
 *********************************************************************/
void Make_Packet_Byte(uint8_t dat)
{
    uart.tx_queue[uart.tx_write_idx++] = dat;
    uart.tx_checksum += (uint16_t)(0x00ff & dat);   
}
/** *******************************************************************
 * @brief       move two byte to tx-buffer
 * @param[in]   dat : data to move
 * @return      void
 *
 *********************************************************************/
void Make_Packet_Word(uint16_t dat)
{
    uart.tx_queue[uart.tx_write_idx++] = (uint8_t)(dat>>8);
    uart.tx_queue[uart.tx_write_idx++] = (uint8_t)(dat>>0);
    uart.tx_checksum += (uint16_t)(0x00ff & (dat>>8));
    uart.tx_checksum += (uint16_t)(0x00ff & (dat>>0));
}

/** *******************************************************************
 * @brief       transmit debug data to smartkey gui
 * @param[in]   none
 * @return      void
 *
 *********************************************************************/
void DBG_Send_Data(void)
{
    uint8_t i;
    uint8_t len;            /* Keil:Optimization - Level 7AI≫o¿¡¼­ i ¿I Aæμ¹ */
    uint8_t shift_bit;
    uint8_t mask_cnt;

    uart.tx_write_idx = 0;
    uart.tx_read_idx = 0;
    uart.tx_checksum = 0;
    uart.tx_queue[uart.tx_write_idx++] = DBG_SMARTKEY_GET_STX;  /* header[1] */

    /* Length Calc */                   
    mask_cnt = 0;
    shift_bit = 0x01;
    for (i = 0; i < 8; i++)
    {
        if(dbg.mask & shift_bit)
        {
            mask_cnt++;
        }
        shift_bit<<=1;
    }

    #if (DBG_TS_REG == 1)
    len = 4 + dbg.ch_cnt * mask_cnt * 2 + 58; 
    #else
    len = 4 + dbg.ch_cnt * mask_cnt * 2;
    #endif
    len = (len/2)|0x80;     
    Make_Packet_Byte(len);                      /* length[1] */
    Make_Packet_Byte(0x00);                     /* mode[2] */
    Make_Packet_Byte(0x10);
    Make_Packet_Byte(ts.detect_key);            /* key[1] */
    Make_Packet_Byte(ts.touch_lib_ver);         /* cyle[1] */


    for (i = dbg.start_idx; i < dbg.start_idx+dbg.ch_cnt; i++)  
    {   
        if (dbg.mask & DBG_DATA0)                
        {
            Make_Packet_Word(ts.raw_data[i][0]);
        }
        if (dbg.mask & DBG_DATA1)                
        {
            Make_Packet_Word(ts.baseline[i][0]);
        }
        if (dbg.mask & DBG_DATA2)           
        {
            Make_Packet_Word(ts.raw_data[i][1]);
        }
        if (dbg.mask & DBG_DATA3)              
        {
            Make_Packet_Word(ts.baseline[i][1]);
        }
        if (dbg.mask & DBG_DATA4)            
        {
            Make_Packet_Word(ts.diff_data[i]);
        }
        if (dbg.mask & DBG_DATA5)
        {
#if (UL60730_SELF_TEST_EN == 1)
            Make_Packet_Word(user.ul60730_post_result);
#else
            Make_Packet_Word(ts.thd_detect[i]);
#endif
        }
        if (dbg.mask & DBG_DATA6)
        {
#if (UL60730_SELF_TEST_EN == 1)
            Make_Packet_Word(user.ul60730_bist_result);
#else
            Make_Packet_Word(ts.total_cap[i]);
#endif
        }
        if (dbg.mask & DBG_DATA7)
        {
            Make_Packet_Word(ts.detect_key);
        }
    }
    #if (DBG_TS_REG == 1)
    /* SCO */
    for (i = 0; i < 20; i++)                /* 20 x 2 */
    {
        Make_Packet_Word(ts_reg.sco[i]);
    }
    /* touch Register */
    for (i = 0; i < SFR_TS_MAX; i++)        /* 18 */
    {
        Make_Packet_Byte(ts_reg.reg[i]);    
    }
    #endif

    uart.tx_checksum = ((~uart.tx_checksum)&0x00ffff)-1;    
    uart.tx_queue[uart.tx_write_idx++] = (uint8_t)(uart.tx_checksum>>8);
    uart.tx_queue[uart.tx_write_idx++] = (uint8_t)(uart.tx_checksum>>0);
    uart.tx_queue[uart.tx_write_idx++] = DBG_SMARTKEY_GET_CR;
    uart.tx_queue[uart.tx_write_idx++] = DBG_SMARTKEY_GET_LF;
        
    IE1 |= BIT(4);
    USI0DR = uart.tx_queue[uart.tx_read_idx++];
}

/** *******************************************************************
 * @brief       debug task
 * @param[in]   none
 * @return      void
 *
 *********************************************************************/
void DBG_Do_Task(void)
{
    static uint8_t step = 0;
    uint8_t* ptr;
    uint8_t temp;

    if (g_sys_flag.dbg_en == 0)
    {
        return;
    }

    switch (step)
    {
        case 0 :
            DBG_Init_UART();
            DBG_Init_UART_Param();
            DBG_Init_Variable();
            step++;
            break;
        case 1 :
            temp = DBG_RX_Check(&ptr);  /* |02| ~ |0D|03| */    
            if (temp == DBG_RX_COMPLETE)
            {
                switch (*ptr)
                {
                    case 'R':   /* 0x52 */
                        dbg.mask    = Hexstr_To_Binary(ptr+1);              
                        dbg.start_idx= Hexstr_To_Binary(ptr+3); 
                        dbg.ch_cnt  = Hexstr_To_Binary(ptr+5);      
                        #if DBG_FLASH_SAVE == 1
                        dbg.flag.flash_dbg = 1;
                        fla_addr_r = FLASH_START_ADDR;
                        #endif
                        break;
#if (0)                     
                    case 'M':   /* 0x4D FREQ */
                        temp = Hexstr_To_Binary(ptr+1);                     
                        switch (temp)
                        {
                            case 0x10 :
                                //g8_sfrIndx = 0;
                                break;
                            case 0x11 :
                                //g8_sfrIndx = 1;
                                break;
                            case 0x12 :
                                //g8_sfrIndx = 2;
                                break;
                        }   
                        break;                  
                    case 'T':   /* 0x54 SFR */
                        bin1 = Hexstr_To_Binary(ptr+1); //
                        bin2 = Hexstr_To_Binary(ptr+3); 
                        bin3 = Hexstr_To_Binary(ptr+5);
                        if ((bin1>=0x50)&&(bin1<=0x77))         /* SCO */
                        {
                            bin1 -= 0x50;
                            bin1 = bin1/2;
                            ts_reg.sco[bin1] =  (((uint16_t)bin2<<8) + bin3)&0x1fff; 
                            TS_SCO(bin1) = ts_reg.sco[bin1]; 
                        }
                        else if ((bin1>=0x80)&&(bin1<=0x91))    /* REG */
                        {
                            bin1 -= 0x80;
                            ts_reg.reg[bin1] = bin2;
                            TS(bin1) = ts_reg.reg[bin1];
                        }
                        break;
                    case 'w':   
                        bin1 = Hexstr_To_Binary(ptr+1);
                        bin2 = Hexstr_To_Binary(ptr+3);                         
                        g_sys_flag.reinit = 1;
                        break;
                    case 'Z':
                        break;
#endif                          
                    default :
                        break;
                }
            }
            step++;
            break;
        case 2 :
            if ((dbg.flag.busy == 0)&&(g_sys_flag.ts_end == 1))
            {   
                g_sys_flag.ts_end = 0;                  
                #if (DBG_FLASH_SAVE == 1)
                Flash_Write_Data();
                #else
                dbg.flag.busy = 1;
                DBG_Send_Data();    
                #endif
            }           
            step = 1;
            break;
        default :
            step = 0;
            break;
    }
}
#endif


#if (I2C_ENABLE == 1)
void DBG_Do_Task_I2C(void)
{
    RegMap[REG_LIB_VERSION] = ts.touch_lib_ver;
    RegMap[REG_MODEL_NO] = 0x01;
    RegMap[REG_VENDOR_ID] = 0xAB;

    RegMap[REG_KEY_ID_1] = ts.detect_key & 0xFF;
    RegMap[REG_KEY_ID_2] = (ts.detect_key>>8) & 0xFF;
    RegMap[REG_KEY_ID_3] = (ts.detect_key>>16) & 0xFF;

    dataBuff[0] = raw_data[CH_00][0];
    dataBuff[1] = raw_data[CH_10][0];
    dataBuff[2] = raw_data[CH_11][0];
    dataBuff[3] = raw_data[CH_12][0];
    dataBuff[4] = raw_data[CH_04][0];
    dataBuff[5] = raw_data[CH_05][0];
    dataBuff[6] = raw_data[CH_06][0];    

    dataBuff[7] = baseline[CH_00][0];
    dataBuff[8] = baseline[CH_01][0];
    dataBuff[9] = baseline[CH_02][0];
    dataBuff[10] = baseline[CH_03][0];
    dataBuff[11] = baseline[CH_04][0];
    dataBuff[12] = baseline[CH_05][0];
    dataBuff[13] = baseline[CH_06][0];

}
#endif


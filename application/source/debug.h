/**
 *******************************************************************************
 * @file        debug.h
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
 
#ifndef _DEBUG_H_
#define _DEBUG_H_

#include "typedef.h"
#include "user_function.h"

#define DBG_FLASH_SAVE      0   /* project need flash.c, dbg_flash.c, flash_enter.a51 files */

#if (UART_ENABLE == 1)
enum dbg_baud
{
    DBG_BAUD_500000 = 0,    
    DBG_BAUD_115200,
    DBG_BAUD_38400,
    DBG_BAUD_9600,
};

enum dbg_smartkey
{
    DBG_DATA0   = 0x01,
    DBG_DATA1   = 0x02,
    DBG_DATA2   = 0x04,
    DBG_DATA3   = 0x08,
    DBG_DATA4   = 0x10,
    DBG_DATA5   = 0x20,
    DBG_DATA6   = 0x40,
    DBG_DATA7   = 0x80
};
#define DBG_MASK_ITEM       (DBG_DATA0+DBG_DATA1+DBG_DATA2+DBG_DATA3+DBG_DATA4+DBG_DATA5+DBG_DATA6+DBG_DATA7)
#define DBG_START_INDX      0
#define DBG_CH_CNT          2
struct dbg_cfg
{
    uint8_t start_idx;
    uint8_t ch_cnt;
    uint8_t mask;
    struct{
        uint8_t busy        :1;
        uint8_t flash_dbg   :1;
        uint8_t reserved    :6;
    } flag;
};

#define DBG_SMARTKEY_GET_STX    0x3A
#define DBG_SMARTKEY_GET_CR     0x0D
#define DBG_SMARTKEY_GET_LF     0x0A
#define DBG_SMARTKEY_SET_STX    0x02
#define DBG_SMARTKEY_SET_ETX    0x03
#define DBG_SFR_CNT         42
#define DBG_RX_BUFF_SIZE    100
#define DBG_TX_BUFF_SIZE    200
#define DBG_RX_MSG_SIZE     25
struct dbg_uart
{   
    uint16_t rx_write_idx;
    uint16_t rx_read_idx;
    uint8_t  rx_queue[DBG_RX_BUFF_SIZE];
    uint16_t tx_write_idx;
    uint16_t tx_read_idx;
    uint16_t tx_checksum;
    uint8_t  tx_queue[DBG_TX_BUFF_SIZE];
};
enum dbg_rx_step
{
    DBG_RX_STEP_STX = 0,
    DBG_RX_STEP_CMD,
    DBG_RX_STEP_LENGTH,
    DBG_RX_STEP_DATA,
    DBG_RX_STEP_CHKSUM,
    DBG_RX_STEP_ETX,
    DBG_RX_STEP_ERR = 0xff
};

#define DBG_RX_READY        0
#define DBG_RX_COMPLETE     1
#define DBG_RX_ERR          2

void DBG_Do_Task(void);
void DBG_Set_Baudrate(uint8_t baud);
void DBG_Send_Data (void);
void Make_Packet_Byte(uint8_t dat);
void Make_Packet_Word(uint16_t dat);
extern struct dbg_cfg dbg;
extern struct dbg_uart uart;
#endif

#if (I2C_ENABLE == 1)
extern uint16_t *dataBuff;
void DBG_Do_Task_I2C(void);
#endif

#endif  /* _DEBUG_H_ */
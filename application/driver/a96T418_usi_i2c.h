/**
 *******************************************************************************
 * @file        a96T418_usi_i2c.h
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


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USI_I2C_H_
#define __USI_I2C_H_
/*******************************************************************************
* Included File
*******************************************************************************/
#include "A96T418.h" 
#include "common.h"
#include "Intrins.h"
#include "main.h"
#include "typedef.h"

/*******************************************************************************
* Public Macro
*******************************************************************************/
#define I2C_DEVICE_ADDRESS          0x40
#define I2C_SLAVE_OWN_ADDR          0x40
#define I2C_SPEED                   10000

#define I2C_MAX_BUFFER_SIZE         20
#define I2C_MAX_CHANNEL             2

#define I2C_CH0                     0

#define I2C_ACK_DISABLE             0
#define I2C_ACK_ENABLE              1

#define I2C_WRITE_MODE              0
#define I2C_READ_MODE               1
#define I2C_IDLE                    0
#define I2C_BUSY                    1
#define I2C_MATCH_CMD               2

#define I2C_TRUE                    1
#define I2C_FALSE                   0

#define I2C_REG_OFFSET              0x100

enum i2c_id
{
    I2C_ID_0    = 0,                        /**< I2C 0 */
    I2C_ID_1    = 1,                        /**< I2C 1 */
    I2C_ID_MAX  = 2,                        /**< I2C max */
};

/*******************************************************************************
* Public Typedef
*******************************************************************************/
enum  i2c_interrupt_status{ 
    GCALL       = 1 << 7,
    TEND            = 1 << 6,
    STOPD   = 1 << 5,
    SSEL            = 1 << 4,
    MLOST   = 1 << 3,
    BUSY        = 1 << 2,
    TMODE   = 1 << 1,
    RXACK   = 1 << 0,
};

/*******************************************************************************
* Exported Public Function
*******************************************************************************/

void I2C_Init(uint8_t ch, uint32_t speed, uint8_t addr, uint8_t ack);
void I2C_Init_in_INT(uint8_t ch, uint32_t speed, uint8_t addr, uint8_t ack);
void USI_I2C_InterruptHandler(uint8_t ch);

#endif  /* End of __USI_I2C_H_ */
/* --------------------------------- End Of File ------------------------------ */

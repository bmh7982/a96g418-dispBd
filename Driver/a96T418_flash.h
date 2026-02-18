/**
 *******************************************************************************
 * @file        a96T418_flash.h
 * @author      ABOV R&D Division
 * @brief       Flash Header File
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
#ifndef __FLASH_H_
#define __FLASH_H_
/*******************************************************************************
* Included File
*******************************************************************************/
#include "a96T418.h"
#include "intrins.h"
#include "delay.h"
#include "typedef.h"
/*******************************************************************************
* Public Macro
*******************************************************************************/
//Device Description=====================================//
//	Device : A96T418
//	Flash : 32 Kbyte (7FFFh)
//	PageBuf : 64 byte (40h)
//=======================================================//

//Device Dependent=======================================
#define FLASH_SIZE (0x00FFFF)
#define PAGE_BUFFER_SIZE (0x40)

//Modify to use==========================================
//Flash Address for used
#define FLASH_ADDR_USER 0x001000

//Flash Address Min/Max value for permitted area
#define FLASH_ADDR_MIN 0x001000
#define FLASH_ADDR_MAX 0x00107F

//more than 2.0V @ IRC 16MHz
#define FLASH_LVI 0x06	//LVI 2.28V(2.05V~2.35V)

//Flash Dummy Address value, not used area
#define FLASH_ADDR_DUMMY 0x03FF00
//=====================================================

//safety code for operation of flash memory
#define FLASH_KEY 0xAA55
#define FLASH_XOR 0x9C75

#define WAITTIME 163		// 2.5625ms @ LSIRC 128KHz
#define Flash_Exit()	{FECR = 0x30;}	                // Set flash to normal mode.

//Flash Mode Control value
#define FLASH_PAGEBUFFER_RESET 0x01

//Flash User ID value, used password
#define FLASH_USER_ID 0xCC33



/*******************************************************************************
* Public Typedef
*******************************************************************************/

/*******************************************************************************
* Exported Public Function
*******************************************************************************/
void Init_Flash();
void Update_Flash_Buf(unsigned char *buf, unsigned int size);
void Update_Flash(unsigned int key);
unsigned char Erase_Flash(unsigned int key, unsigned long sector_address);
unsigned char Write_Flash(unsigned int key, unsigned long sector_address, unsigned int size, unsigned char *buf);
void Read_Flash(unsigned long sector_address, unsigned int size, unsigned char *buf);

#endif //_FLASH_HEADER_

/* --------------------------------- End Of File ------------------------------ */
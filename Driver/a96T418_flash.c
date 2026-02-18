/**
 *******************************************************************************
 * @file        a96T418_flash.c
 * @author      ABOV R&D Division
 * @brief       Flash Source File
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
#include	"A96T418_flash.h"	

/*******************************************************************************
* Private Pre-processor Definition & Macro
*******************************************************************************/

/*******************************************************************************
* Private Typedef
*******************************************************************************/

/*******************************************************************************
* Private Variable
*******************************************************************************/
// User ID global value
unsigned int User_ID;

unsigned char *PageBufData;
unsigned int PageBufDataSize;
/*******************************************************************************
* Private Function Prototype
*******************************************************************************/

/*******************************************************************************
* Public Function
*******************************************************************************/
// from flash_enter.a51
extern void Flash_LoadData(unsigned char dt, unsigned int add);
extern void Flash_Enter(void);

/**
* @brief	Safety code operation of flash memory initialization.
* @param    None
* @return	None
*/
void Init_Flash()
{
	//Init User_ID
	User_ID = 0;

	// Set Flash Sector Address as Dummy address
	FEARH = (FLASH_ADDR_DUMMY >> 16) & 0x0f;	//Flash Sector Address High Register
	FEARM = (FLASH_ADDR_DUMMY >> 8) & 0xff;	//Flash Sector Address Middle Register
	FEARL = (FLASH_ADDR_DUMMY >> 0) & 0xff;	//Flash Sector Address Low Register
}

/**
* @brief	Update Flash buffer for writing flash memory.
* @param    buf 	This parameter contains the buffer of writing Flash memory.
* @param    buf_size 	This parameter contains the size of data.
* @return	None
*/
void Update_Flash_Buf(unsigned char *buf, unsigned int buf_size)
{
	//Flash Buffer Update
	User_ID = FLASH_USER_ID;
	PageBufData = buf;
	PageBufDataSize = buf_size;
}

/**
* @brief	Update flash memory for writing flash memory.
* @param    key 	This parameter contains the address of Flash memory.
*
*					- safety code for operation of flash memory
* @return	None
*/
void Update_Flash(unsigned int key)
{
	unsigned char i = 0;
	unsigned int s = 0;
	unsigned long addr;
	unsigned char ret = 0;

	if(key == FLASH_KEY)
	{
		if(User_ID == FLASH_USER_ID)
		{		
			addr = FLASH_ADDR_USER;
			s = PageBufDataSize;
			while(PageBufDataSize > 0)
			{
				if(PageBufDataSize < PAGE_BUFFER_SIZE)
				{
					s = PageBufDataSize;
					PageBufDataSize = 0;
				}
				else
				{
					s = PAGE_BUFFER_SIZE;
					PageBufDataSize -= PAGE_BUFFER_SIZE;
				}
				
				ret = Erase_Flash(FLASH_KEY, FLASH_ADDR_USER + (PAGE_BUFFER_SIZE*i));
				if(ret == 1 || ret == 2)
				{
					//error;
					while(1);
				}
				ret = Write_Flash(FLASH_KEY, FLASH_ADDR_USER + (PAGE_BUFFER_SIZE*i), 
							s, PageBufData + (PAGE_BUFFER_SIZE*i));
				if(ret == 1 || ret == 4)
				{
					//error;
					while(1);

				}
				i++;
			}
		}
		User_ID = 0;
	}
}



/**
* @brief	Erase operation of flash memory.
* @param    key 	This parameter contains the address of Flash memory.
*
*					- safety code for operation of flash memory
* @param    sector_address 	This parameter contains the address of Flash memory.
*
*					- address range : 32kbytes(0x0 ~ 0x7FFF)
* @return	status(0 : OK, 1/2 : Failed)
*/
unsigned char Erase_Flash(unsigned int key, unsigned long sector_address)
{
	unsigned char code *rom_addr = 0x0000;
	unsigned char i = 0;
	unsigned char tmp = 0;
	unsigned char tmp2 = 0;
	unsigned char ret = 0;

	//Disable EA
	tmp = IE;
	IE &= (~0x80);

	
	//LVI enalbe, safety code
	tmp2 = LVICR;
	LVICR = 0x10 | FLASH_LVI;

	if(key == FLASH_KEY)
	{
		key ^= FLASH_XOR;

		if(sector_address < (unsigned long)FLASH_SIZE)
		{
			// Enable program mode
			Flash_Enter();
	
			// erase
			FEMR = 0x81;	// Select flash and enable control.
			FECR = 0x02;	// Reset page buffer.
			_nop_( );	//Dummy instruction, This instruction must be needed.
			_nop_( );	//Dummy instruction, This instruction must be needed.
			_nop_( );	//Dummy instruction, This instruction must be needed.
			FEMR = 0x89;	// Select page buffer.

			//write data to pagebuffer
			for(i=0;i<PAGE_BUFFER_SIZE;i++){
				Flash_LoadData(0, sector_address+i);
			}

			FEMR = 0x91;	    // Set Erase mode.
			FETCR = WAITTIME;	// Set Erase time. 

			// Set Flash Sector Address as used area
			FEARH = (sector_address >> 16) & 0xFF;
			FEARM = (sector_address >> 8) & 0xFF;
			FEARL = (sector_address) & 0xFF;

			//Check Power stable by LVI 
			LVICR &= ~0x20;
			if((LVICR & 0x20) == 0x00)
			{
				// Check User_ID
				if(User_ID == FLASH_USER_ID)
				{
					// Check valid of Flash Sector Address range
					if( (unsigned long)FLASH_ADDR_MIN <= sector_address && sector_address <= (unsigned long)FLASH_ADDR_MAX)
					{
						if((key ^ FLASH_XOR) == FLASH_KEY)
						{
							// Flase Erase
							FECR = 0x0B;	// Start Erase.
							_nop_();_nop_();_nop_(); 	//Dummy instruction, This instruction must be needed.

							while( !( FESR & 0x80));		// Read status register.
							_nop_();_nop_();_nop_(); 	//Dummy instruction, This instruction must be needed.
						}
						
						Flash_Exit();			            // Set flash to normal mode.
						//verify data
						for(i = 0; i < PAGE_BUFFER_SIZE; i++)
						{
							if(rom_addr[sector_address + i] != 0x00)
							{
								ret = 2;
							}
						}
					}
				}
				
			}
			else
			{
				ret = 1;//LVI error
			}
			Flash_Exit();			            // Set flash to normal mode.
			// Set Flash Sector Address as Dummy address
			FEARH = (FLASH_ADDR_DUMMY >> 16) & 0x0f;	//Flash Sector Address High Register
			FEARM = (FLASH_ADDR_DUMMY >> 8) & 0xff;		//Flash Sector Address Middle Register
			FEARL = (FLASH_ADDR_DUMMY >> 0) & 0xff;		//Flash Sector Address Low Register
		}
	}
	LVICR = tmp2;
	IE = tmp;
	return ret;
}


/**
* @brief	Wrtie operation of flash memory.
* @param    key 	This parameter contains the address of Flash memory.
*
*					- safety code for operation of flash memory
* @param    sector_address 	This parameter contains the address of Flash memory.
*
*					- address range : 32kbytes(0x0 ~ 0x7FFF)
* @param    buf_size 	This parameter contains the size of writing Flash data.
* @param    buf 	This parameter contains the buffer of writing Flash data
* @return	status(0 : OK, 1/4 : Failed)
*/
unsigned char Write_Flash(unsigned int key, unsigned long sector_address, unsigned int buf_size, unsigned char *buf)
{
	unsigned char *pdt;
	unsigned char code *rom_addr=0x0000;
	unsigned char i = 0;
	unsigned char tmp = 0;
	unsigned char tmp2 = 0;
	unsigned char ret = 0;

	//Disable EA
	tmp = IE;
	IE &= (~0x80);
	
	//LVI enalbe, 2.32V
	tmp2 = LVICR;
	LVICR = 0x10 | FLASH_LVI;

	if(key == FLASH_KEY)
	{
		key ^= FLASH_XOR;

		if(sector_address < (unsigned long)FLASH_SIZE)
		{
			// Enable program mode
			Flash_Enter();
			
			// write
			FEMR = 0x81;	// Select flash and enable control.
			FECR = 0x02;	// Reset page buffer.
			_nop_( );	//Dummy instruction, This instruction must be needed.
			_nop_( );	//Dummy instruction, This instruction must be needed.
			_nop_( );	//Dummy instruction, This instruction must be needed.
			FEMR = 0x89;	// Select page buffer.

			//write data to pagebuffer			
			pdt = buf;
			for(i=0;i<buf_size;i++){
				Flash_LoadData(*pdt, sector_address+i);
				pdt++;
			}

			FEMR = 0xA1;            // Set write mode.
			FETCR = WAITTIME;       // Set Erase time. 
			
			// Set Flash Sector Address as used area
			FEARH = (sector_address >> 16) & 0xFF;
			FEARM = (sector_address >> 8) & 0xFF;
			FEARL = (sector_address) & 0xFF;
			
			//Check Power stable by LVI 
			LVICR &= ~0x20;
			if((LVICR & 0x20) == 0x00)
			{
				// Check User_ID1/2
				if(User_ID == FLASH_USER_ID)
				{
					// Check valid of Flash Sector Address range
					if( (unsigned long)FLASH_ADDR_MIN <= sector_address && sector_address <= (unsigned long)FLASH_ADDR_MAX)
					{
						if((key ^ FLASH_XOR) == FLASH_KEY)
						{
							// Flase Write
							FECR = 0x0B;		        // Start program.
							_nop_();_nop_();_nop_(); 	//Dummy instruction, This instruction must be needed.
							
							while ( !( FESR & 0x80));       //
							_nop_();_nop_();_nop_(); 	//Dummy instruction, This instruction must be needed.
	
						}

						Flash_Exit();			            // Set flash to normal mode.
						//verify data
						pdt = buf;
						for(i = 0; i < PAGE_BUFFER_SIZE; i++)
						{
							if(rom_addr[sector_address + i] != *pdt)
							{
								ret = 4;
							}
							
							pdt++;
						}
					}
				}

			}
			else
			{
				ret = 1;//LVI error
			}
			Flash_Exit();			            // Set flash to normal mode.
			// Set Flash Sector Address as Dummy address
			FEARH = (FLASH_ADDR_DUMMY >> 16) & 0x0f;	//Flash Sector Address High Register
			FEARM = (FLASH_ADDR_DUMMY >> 8) & 0xff;		//Flash Sector Address Middle Register
			FEARL = (FLASH_ADDR_DUMMY >> 0) & 0xff;		//Flash Sector Address Low Register
		}
	}
	LVICR = tmp2;
	IE = tmp;
	return ret;
}


/**
* @brief	Read operation of flash memory.
* @param    sector_address 	This parameter contains the address of Flash memory.
*
*					- address range : 32kbytes(0x0 ~ 0x7FFF)
* @param    size 	This parameter contains the size of reading Flash data.
* @param    buf 	This parameter contains the data to read flash memory.
* @return	NONE
*/
void Read_Flash(unsigned long sector_address, unsigned int buf_size, unsigned char *buf)
{
	unsigned char code *rom_addr=0x0000;
	unsigned int i = 0;

	for(i = 0; i < buf_size; i++)
	{
		buf[i] = rom_addr[sector_address + i];
	}
}

/* --------------------------------- End Of File ------------------------------ */
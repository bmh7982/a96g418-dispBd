/**
 *******************************************************************************
 * @file        led_driver.c
 * @author      ABOV R&D Division
 * @brief       A96T418 LED Driver code
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#include "A96T418.h" 
#include "user_function.h"
#include "common.h"
#include "touch_lib.h"
#include "led_driver.h"

#if (LED_DRV_EN == 1)

struct led_cfg  led;

/** *******************************************************************
 * @brief       Set the LED operation duration
 * @param[in]   com_cnt : number of COMs to use
                duration : LED operation section in milli second.
 * @return      void
 *
 *********************************************************************/
void LED_Set_Actv_Time (uint8_t com_cnt, uint8_t duration)
{
    uint16_t temp;
    
    /*----------------------------
    slot_ms = (1/16M)*(PRESD+1)*(COMPWID+1)*COM_N*1000
    slot_ms*16000/((PRESD+1)*COM_N)-1 = COMPWID
    if PRESD = 127, then (16000>>7) = 125;
    ----------------------------*/
    PRESD  = 255;       /* led clock prescale, 16MHz/(PRESD+1), if 255, 62.5Khz, 16us */
    temp = ((((uint16_t)duration*125)/2/(uint16_t)com_cnt)-1);

    if(temp > 0xFF)
        COMPWID = 0xFF;
    else
        COMPWID = (uint8_t)temp;

    if (g_sys_flag.time_div != 0)
    {
        led.flag.mode = 2;
    }
    else
    {
        led.flag.mode = 0;
    }   
    g_sys_flag.led_en = 1;
}
#if (TS_LED_TIME_DIV == 1)
/** *******************************************************************
 * @brief       When the touch and LED are operated by time-division,
                set the touch occupancy time.
 * @param[in]   slot_ms : touch occupancy time in mili-second
 * @return  void
 *
 *********************************************************************/
void Touch_Set_Actv_Time(uint8_t slot_ms)
{
    uint32_t idata stop_cnt;
    
    /*----------------------------
    slot_ms = (1/16M)*(LEDSTPD+1)*1000;
    slot_ms*16000-1 = LEDSTPD
    ----------------------------*/
    stop_cnt = (uint32_t)slot_ms*16000-1;
    LEDSTPD2 = (uint8_t)((stop_cnt&0x0f0000)>>16);
    LEDSTPD1 = (uint8_t)((stop_cnt&0x00ff00)>>8);
    LEDSTPD0 = (uint8_t)((stop_cnt&0x0000ff)>>0);
}
#endif

/** *******************************************************************
 * @brief       LED Interrupt Service Routine
 * @param[in]   In the case of time-division operation with touch,
                start the touch operation here.
 * @return      
 *
 *********************************************************************/
static void LED_ISR(void) interrupt LED_VECT 
{
    EA = 1;

    g_sys_flag.led_end = 1;
    if ((g_sys_flag.calib_ok == 1) && (g_sys_flag.time_div != 0))
    {
        TS(SFR_TS_CON) = 0x00;
        Touch_Start_Touch(ts.actv_ch_idx);
    }   
}
/** *******************************************************************
 * @brief       When the LED is in the inactive state, it sets the SEG/
                COM I/O state.
 * @param[in]   none
 * @return      void
 *
 *********************************************************************/
void LED_Init_IO(void)
{
    P0      &= ~led.p0_seg;
    P0IO    |= led.p0_seg;
    P1      &= ~led.p1_seg;
    P1IO    |= led.p1_seg;
    P2      &= ~led.p2_seg;
    P2IO    |= led.p2_seg;
    P3      &= ~led.p3_seg;
    P3IO    |= led.p3_seg;

    /* COM Port Output High */
    P2      |= led.com_sel;
    P2IO    |= led.com_sel;

    g_sys_flag.led_io = 1;
}

/* T-type LED */
#if (1)
uint8_t code t_type_digit[4][10][8] = { 
{
    {0,     A1,     B1,     C1,     D1,     0,      E1,     F1},        /* 0 : ABCDEF   */
    {0,     0,      B1,     C1,     0,      0,      0,      0},         /* 1 : BC       */
    {0,     A1,     B1,     0,      D1,     0,      E1,     G1},        /* 2 : ABDEG    */
    {0,     A1,     B1,     C1,     D1,     0,      0,      G1},        /* 3 : ABCDG    */
    {0,     0,      B1,     C1,     0,      0,      0,      F1+G1},     /* 4 : BCFG     */
    {0,     A1,     0,      C1,     D1,     0,      0,      F1+G1},     /* 5 : ACDFG    */
    {0,     A1,     0,      C1,     D1,     0,      E1,     F1+G1},     /* 6 : ACDEFG   */
    {0,     A1,     B1,     C1,     0,      0,      0,      F1},        /* 7 : ABCF     */
    {0,     A1,     B1,     C1,     D1,     0,      E1,     F1+G1},     /* 8 : ABCDEFG  */
    {0,     A1,     B1,     C1,     D1,     0,      0,      F1+G1}      /* 9 : ABCDFG   */
},{
    {0,     0,      C2,     B2+D2,  A2+E2,  0,      F2,     0},         /* 0 : ABCDEF   */
    {0,     0,      C2,     B2,     0,      0,      0,      0},         /* 1 : BC       */
    {0,     0,      0,      B2+D2,  A2+E2,  0,      0,      G2},        /* 2 : ABDEG    */
    {0,     0,      C2,     B2+D2,  A2,     0,      0,      G2},        /* 3 : ABCDG    */
    {0,     0,      C2,     B2,     0,      0,      F2,     G2},        /* 4 : BCFG     */
    {0,     0,      C2,     D2,     A2,     0,      F2,     G2},        /* 5 : ACDFG    */
    {0,     0,      C2,     D2,     A2+E2,  0,      F2,     G2},        /* 6 : ACDEFG   */
    {0,     0,      C2,     B2,     A2,     0,      F2,     G2},        /* 7 : ABCF     */
    {0,     0,      C2,     B2+D2,  A2+E2,  0,      F2,     G2},        /* 8 : ABCDEFG  */
    {0,     0,      C2,     B2+D2,  A2,     0,      F2,     G2}         /* 9 : ABCDFG   */
},{
    {0,     0,      0,      0,      B3,     0,      A3+C3,  D3+E3+F3},  /* 0 : ABCDEF   */  
    {0,     0,      0,      0,      B3,     0,      C3,     0},         /* 1 : BC       */
    {0,     0,      0,      0,      B3,     G3,     A3,     D3+E3},     /* 2 : ABDEG    */
    {0,     0,      0,      0,      B3,     G3,     A3+C3,  D3},        /* 3 : ABCDG    */
    {0,     0,      0,      0,      B3,     G3,     C3,     F3},        /* 4 : BCFG     */
    {0,     0,      0,      0,      0,      G3,     A3+C3,  D3+F3},     /* 5 : ACDFG    */
    {0,     0,      0,      0,      0,      G3,     A3+C3,  D3+E3+F3},  /* 6 : ACDEFG   */
    {0,     0,      0,      0,      B3,     0,      A3+C3,  F3},        /* 7 : ABCF     */
    {0,     0,      0,      0,      B3,     G3,     A3+C3,  D3+E3+F3},  /* 8 : ABCDEFG  */
    {0,     0,      0,      0,      B3,     G3,     A3+C3,  D3+F3}      /* 9 : ABCDFG   */
},{
    {C4,    B4,     A4+F4,  E4,     0,      D4,     0,      0},         /* 0 : ABCDEF   */
    {C4,    B4,         0,  0,      0,      0,      0,      0},         /* 1 : BC       */
    {0,     B4+G4,  A4,     E4,     0,      D4,     0,      0},         /* 2 : ABDEG    */
    {C4,    B4+G4,  A4,     0,      0,      D4,     0,      0},         /* 3 : ABCDG    */
    {C4,    B4+G4,  F4,     0,      0,      0,      0,      0},         /* 4 : BCFG     */
    {C4,    G4,     A4+F4,  0,      0,      D4,     0,      0},         /* 5 : ACDFG    */
    {C4,    G4,     A4+F4,  E4,     0,      D4,     0,      0},         /* 6 : ACDEFG   */
    {C4,    B4,     A4+F4,  0,      0,      0,      0,      0},         /* 7 : ABCF     */
    {C4,    B4+G4,  A4+F4,  E4,     0,      D4,     0,      0},         /* 8 : ABCDEFG  */
    {C4,    B4+G4,  A4+F4,  0,      0,      D4,     0,      0}          /* 9 : ABCDFG   */
}}; 
#endif
/* M-type LED */
uint8_t code m_type_digit[14][8] = {
    {0x00,0x3f,0xff,0xc0,0x00,0x3f,0xff,0xc0},  /* 0        */
    {0x00,0x00,0x00,0xff,0x00,0x01,0x01,0xff},  /* 1        */
    {0x00,0x43,0xc7,0xcc,0x00,0x63,0xf3,0xd8},  /* 2        */
    {0x00,0x3b,0xff,0xc4,0x00,0x21,0xe5,0xc4},  /* 3        */
    {0x00,0x10,0xff,0xff,0x00,0x18,0x1e,0x97},  /* 4        */
    {0x00,0xb8,0xfc,0xc4,0x00,0xa7,0xe7,0xc4},  /* 5        */
    {0x00,0x39,0xfd,0xc4,0x00,0x3f,0xff,0xc4},  /* 6        */
    {0x00,0x81,0x8f,0xfe,0x00,0x80,0x80,0xf0},  /* 7        */
    {0x00,0x3b,0xff,0xc4,0x00,0x3b,0xff,0xc4},  /* 8        */
    {0x00,0x3f,0xff,0xc8,0x00,0x27,0xef,0xc8},  /* 9        */
    {0x60,0x78,0x1e,0x97,0x60,0x78,0x1e,0x97},  /* A        */
    {0x00,0x3b,0xfb,0xc4,0x00,0xff,0xff,0xc4},  /* B        */
    {0x00,0x21,0xe1,0xc0,0x1e,0x3f,0xe1,0xc0},  /* C        */
    {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff}   /* nothing  */
};

/** *******************************************************************
 * @brief       Update the LED display data.
                Refer to the "AN_T-TYPE LED Structure" document & 
                "Design_MDS_STKS-A96T418-GDN-TOUCH-A V1.0_Final" schematic.
 * @param[in]   none
 * @return      void
 *
 *********************************************************************/
void LED_Renew_Data(void)
{
    uint8_t seg_low[8];
    uint8_t seg_high[8];
    uint8_t *disp_addr;
    uint8_t digit[4];

    uint8_t com_idx;
    uint8_t num_idx;

    disp_addr = (uint8_t*)(&DISPLAYRAM0L);

    /***********  clear led data  *************/
    for (com_idx = 0; com_idx < 8; com_idx++)
    {
        seg_high[com_idx] = 0;
        seg_low[com_idx] = 0;
    }
    #if (1)
    /***********  T-TYPE 4DIGIT 7-SEGMENT  *************/
    for (num_idx = 0; num_idx < 4; num_idx++)
    {
        digit[num_idx] = ((ts.detect_key>>(num_idx*4)) & 0x0f);
        if (digit[num_idx] > 9)             /* clamp: t_type_digit[][10][] only holds 0-9 */
        {
            digit[num_idx] = 0;
        }
    }
    for (num_idx = 0; num_idx < 4; num_idx++)       /* 4DIGIT */
    {
        for (com_idx = 0; com_idx < 8; com_idx++)   /* COM0~7 */
        {
            seg_low[com_idx] |= t_type_digit[num_idx][digit[num_idx]][com_idx]; 
        }
    }
    #endif
    
    /***********  M-TYPE 8x8 : '0'~'C' display  *************/
    for (num_idx = 0; num_idx < 13; num_idx++)
    {
        if (ts.detect_flag & BIT(num_idx))
        {
            break;
        }
    }
    for (com_idx = 0; com_idx < 8; com_idx++)   /* COM0~7 */        
    {
        seg_high[com_idx] |= m_type_digit[num_idx][com_idx];
    }
    /***********  renew led data  *************/
    for (com_idx = 0; com_idx < 8; com_idx++)
    {
        *(disp_addr+com_idx*2+1) = seg_high[com_idx];
        *(disp_addr+com_idx*2+0) = seg_low[com_idx];
    }   
}

/** *******************************************************************
 * @brief       Set the LED driver registers.
                mode - time-division : stop count mode
                     - independent : auto mod
                overlap time - 125ns
                
 * @param[in]   none
 * @return      void
 *
 *********************************************************************/
//#define TEST_SEG0   *(volatile uint8_t xdata *) 0x2F7D
#define DIMM_MINUS  1
void LED_Init_Reg(void)
{
    LEDCON1 =   (led.flag.mode<<2) |    /* 0:Auto, 1:HandShake, 2:StopCount, 3:SmartShare, 4:Alone */
                (1<<1) |                /* Enable */
                (0<<0);                 /* Start */           
    LEDCON2 =   (1<<7) |                /* 1: overlap time = 1/8MHz Fix. 125ns */
                (7<<4) |                /* overlap time, 0:64us, 1:32, 2:24, 3:21, 4:12, 5:9, 6:6, 7:3us */
                (0<<3);                 /* 0:SEG floating, 1: SEG LOW */
    LEDCON3 =   (5<<4) |                /* sst time, 0:1us, 1:2, 2:4, 3:6, ... 15:32us */
                (5<<0);                 /* clear time, 0:1us, 1:2, 2:4, 3:6, ... 15:32us */
    CCSCOARSE = (led.flag.seg_current<<0);  /* seg current. 0:8.66, 1:13.22, 2:19.49, 3:22.06mA */
    LEDSR =     (0<<3) |                /* 1:matched */
                (0<<2) |                /* 1:interrupt flag */
                (1<<1) |                /* 1:interrupt enable */
                (0<<0);                 /* 1:operation ended */
    
    COMOE  =    led.com_sel;
    SEGOE1 =    (uint8_t)((led.seg_sel>>0)&0x00ff);
    SEGOE2 =    (uint8_t)((led.seg_sel>>8)&0x00ff);

    CSER   =    led.com_sel; 

    //PRESD  = 255;     // led clock prescale, 16MHz/(PRESD+1), if 255, 62.5Khz, 16us   
    //COMPWID = 70;     // COM width, led clock/(COMPWID+1) 
//###GUN : 201007 - TEST_SEG0=0x00, DIMM_MINUS=0x00 -> TEST_SEG0=0xff, DIMM_MINUS=0x11 �� ���� 
    TEST_SEG0 = 0xff;
    CDIMM0 =    (DIMM_MINUS<<4) |       /* COM1 dimming(-) */
                (DIMM_MINUS<<0);        /* COM0 */
    CDIMM1 =    (DIMM_MINUS<<4) |       /* COM3 */
                (DIMM_MINUS<<0);        /* COM2 */
    CDIMM2 =    (DIMM_MINUS<<4) |       /* COM5 */
                (DIMM_MINUS<<0);        /* COM4 */
    CDIMM3 =    (DIMM_MINUS<<4) |       /* COM7 */
                (DIMM_MINUS<<0);        /* COM6 */
         
    DISPLAYRAM0L = LED_INIT_DATA;   /* com0 : seg value */
    DISPLAYRAM0M = LED_INIT_DATA;
    DISPLAYRAM1L = LED_INIT_DATA;   /* com1 : seg value */
    DISPLAYRAM1M = LED_INIT_DATA;
    DISPLAYRAM2L = LED_INIT_DATA;   /* com2 : seg value */
    DISPLAYRAM2M = LED_INIT_DATA;
    DISPLAYRAM3L = LED_INIT_DATA;   /* com3 : seg value */
    DISPLAYRAM3M = LED_INIT_DATA;   
    DISPLAYRAM4L = LED_INIT_DATA;   /* com4 : seg value */
    DISPLAYRAM4M = LED_INIT_DATA;
    DISPLAYRAM5L = LED_INIT_DATA;   /* com5 : seg value */
    DISPLAYRAM5M = LED_INIT_DATA;
    DISPLAYRAM6L = LED_INIT_DATA;   /* com6 : seg value */
    DISPLAYRAM6M = LED_INIT_DATA;
    DISPLAYRAM7L = LED_INIT_DATA;   /* com7 : seg value */
    DISPLAYRAM7M = LED_INIT_DATA;

    IE |= BIT(2);
    LEDCON1 |= BIT(0);  // LED Start !  
}
/*************************************************************
 - FUNCTION & CLASS NAME
    : void LED_Do_Task(void)
    
 - DESCRIPTION
    : 
    
 - PARAMETER & RETURN
    : 
    
*************************************************************/
void LED_Do_Task(void)
{
    static uint8_t state = LED_STATE_INIT_IO;

    if (g_sys_flag.led_en == 0)
    {
        return;
    }
    switch (state)
    {
        case LED_STATE_INIT_IO:
            LED_Init_IO();
            state = LED_STATE_SET_TIMER;
            break;
        case LED_STATE_SET_TIMER:
            if (g_sys_flag.calib_ok == 1)
            {
                LED_Init_Reg();
                state = LED_STATE_UPDATE_LED;   
            }
            break;
        case LED_STATE_UPDATE_LED:
            LED_Renew_Data();
            break;
        default:
            state = LED_STATE_INIT_IO;
            break;
    }
}

#endif


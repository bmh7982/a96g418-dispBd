/**
 *******************************************************************************
 * @file        main.c
 * @author      ABOV R&D Division
 * @brief       application "TEST-A96T418-GDN-FUNCTION-A"
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
#include "common.h"
#include "user_function.h"
#if (LED_DRV_EN == 1)
#include "led_driver.h"
#endif
#if (UART_ENABLE|I2C_ENABLE)
#include "debug.h"
#endif
#include "touch_lib.h"
#include "user_timer.h"
#include "main.h"
#include "a96T418_wdt.h"
#include "a96T418_bit.h"

#if (SLIDE_FUNCTION_EN | WHEEL_FUNCTION_EN)
#include "gesture.h"
#endif

#if (UL60730_SELF_TEST_EN == 1)
#include "A96T418_clock.h"
#include "A96T418_usart1_uart.h"
#include "UL60730_user_V01.h"
#endif

#if (I2C_ENABLE == 1)
#include "A96T418_usi_i2c.h"
#include "RegisterMap.h"
#endif


bit g_i2c_flag = 0;

struct sys_flag g_sys_flag;

/** *******************************************************************
 * @brief       Set the GPIO (as output low)
 * @param[in]   none
 * @return      void
 *
 *********************************************************************/
void Init_GPIO(void)
{
    P0 = 0x00;          // output low
    P0IO = 0xFF;        // 0 : input, 1 : output
    P0PU = 0x00;        // 0 : pull-up off, 1 : pull up on
    P0OD = 0x00;        // 0 : Push-pull output, 1 : open-drain output

    P1 = 0x00;          // output low
    P1IO = 0xFF;        // 0 : input, 1 : output
    P1PU = 0x00;        // 0 : pull-up off, 1 : pull up on
    P1OD = 0x00;        // 0 : Push-pull output, 1 : open-drain output

    P2 = 0x00;          // output low
    P2IO = 0xFF;        // 0 : input, 1 : output
    P2PU = 0x00;        // 0 : pull-up off, 1 : pull up on
    P2OD = 0x00;        // 0 : Push-pull output, 1 : open-drain output

    P3 = 0x00;          // output low
    P3IO = 0xFF;        // 0 : input, 1 : output
    P3PU = 0x00;        // 0 : pull-up off, 1 : pull up on

    
    P0FSRH = 0x00;
    P0FSRL = 0x00;
    P1FSRH = 0x00;
    P1FSRL = 0x00;
    P2FSRH = 0x00;
    P2FSRL = 0x00;
    P3FSR = 0x00;

    P0DB = 0x00;        // debont set
    P123DB = 0x00;      // b4:P31, b3:P26, b2:p25, b1:p12, b0:P11

}

void Init_Touch (void)
{
    ts.state                    = TS_STATE_INIT;
    ts.flag.touch_freq_sel_mode = TOUCH_FREQ_SEL_EN;

    Library_Data_Assign();
    Touch_Config_Set();

    g_sys_flag.calib_ok = 0;
    g_sys_flag.led_io = 0;
    g_sys_flag.time_div = TS_LED_TIME_DIV;

    UT_Run_Timer();  
}
/** *******************************************************************
 * @brief       Specifies the variable location for library use.
 * @param[in]   none
 * @return      void
 *
 *********************************************************************/
void Init_User_Function(void)
{
#if (UART_ENABLE == 1)
    DBG_Set_Baudrate(DBG_BAUD_RATE);      
#endif

#if (I2C_ENABLE == 1)
    dataBuff = (uint16_t*)&RegMap[REG_DEBUG_10];
#endif
    
#if (TOUCH_FREQ_SEL_EN == 1)
    func_p_Touch_Freq_Sel = Touch_Freq_Sel;
#endif

#if (FIRST_KEY_PRIORITY == 1)
    user.priority_ch_idx = PRIORITY_CH_BIT;
#endif

#if (HOLD_KEY_RELEASE == 1)
    user.hold_key_release_time = TIMER_HOLD_KEY_RELEASE;
#endif

#if (MULTI_KEY_RESET == 1)
    user.multi_key_check  = 0;
    user.multi_ch_bit = MULTI_CH_BIT;
    user.multi_key_limit = MAX_MULTY_KEY_NUM;
    if(user.multi_key_limit < 1)    
    {
        user.multi_key_limit = 1;
    }
#endif

#if (LED_DRV_EN == 1)
    led.flag.seg_current = LED_CURRENT;       
    led.flag.mode = 2;  //200729?
    led.com_sel = (uint8_t)COMSEL_00_07;
    led.seg_sel = (uint16_t)((SEGSEL_08_15<<8)+SEGSEL_00_07);
    led.p0_seg = P0_SEG_IO;
    led.p1_seg = P1_SEG_IO;
    led.p2_seg = P2_SEG_IO;
    led.p3_seg = P3_SEG_IO;

    LED_Set_Actv_Time(LED_USE_COM_NUM,TIME_LED_OPTERATING);    
#if (TS_LED_TIME_DIV == 1)
    Touch_Set_Actv_Time(TIMER_TOUCH_OPTERATING);
#endif
#endif  

#if (SLIDE_FUNCTION_EN == 1)
    Slide_ch_set();
#endif
    
#if (WHEEL_FUNCTION_EN == 1)
    Wheel_ch_set();
#endif
        
#if (I2C_ENABLE == 1)
    P0FSRL |= (0x03 <<(1<<1));
    P0FSRL |= (0x03 <<(2<<1));
    I2C_Init(I2C_CH0, I2C_SPEED, I2C_DEVICE_ADDRESS, I2C_ACK_ENABLE);
    USI0_I2C_EN();
    USI0CR4 |= 0x10;
#endif

#if (WDT_ENABLE == 1)
    WDT_Set_4sec_Reset();   // BIT + WDTCR + WDTDR 설정 (WDT_Initial()은 즉시 덮어쓰이므로 생략)
    WDT_ConfigureInterrupt(WDT_INT_EN);
    WDT_Start();
#endif

}

/** *******************************************************************
 * @brief       main function
 * @param[in]   none
 * @return      void
 *
 *********************************************************************/
void main(void)
{   
    e_task task;    
    
    DI();
    
    // system clock 16MHz
    SCCR = Internal_16MHz_OSC;
    OSCCR = Divider_16MHz;   // fx = 16MHz
    
    Init_GPIO(); 
    
    Init_Touch(); 
    
    Init_User_Function();
    
    #if (UL60730_SELF_TEST_EN == 1)
    user.ul60730_post_result = UL60730_selfTest_init(ts.actv_ch_bit);              /* UL60730 Power On self test */  
    #endif

    EI();

    task = TASK_LED;

    while (1)
    {
        switch (task)
        {           
            case TASK_LED :
                #if (LED_DRV_EN  == 1)
                LED_Do_Task();
                #endif
                break;          
            case TASK_TOUCH :
                Touch_Do_Task();   // lib function
                #if (WDT_ENABLE == 1)
                WDT_ClearCountData();
                #endif           
                if (ts.flag.touch_sensing_end == 1)
                {
                    #if ((HOLD_KEY_RELEASE | MULTI_KEY_RESET | FIRST_KEY_PRIORITY) == 1)
                    Touch_Key_Scenario();
                    #endif
                    ts.flag.touch_sensing_end = 0;
                }
				// break; �� ������ ������ ������ ���ӿ��� ������ Ȯ���� ��
            case TASK_GESTURE :
				//�׻� �������� ����
                #if (SLIDE_FUNCTION_EN | WHEEL_FUNCTION_EN)
                GESTURE_Do_Task(&diff_data[0]);
                #endif
                break;
            case TASK_DEBUG :
                #if (UART_ENABLE == 1)
                DBG_Do_Task();
                #endif
                #if (I2C_ENABLE == 1)
                DBG_Do_Task_I2C();
                #endif
                break;
            default :
                break;
        }

        task++;
        if (task == TASK_MAX)
        {
            task = TASK_LED;
        }

        #if (UL60730_SELF_TEST_EN == 1)
        if(ts.flag.ts_status == TS_COMPLETE)
        { 
            if( (g_sys_flag.led_en == 1) && (g_sys_flag.time_div == 1) )
            {

                IE &= (~BIT(2));            // LED interrupt disable
                LEDCON1 &= (~0x01); 
            }
            TS(SFR_TS_CON) = 0;

            user.ul60730_bist_result = UL60730_selfTest_run(ts.actv_ch_bit);    

            if( (g_sys_flag.led_en == 1) && (g_sys_flag.time_div == 1) )
            {
                IE |= BIT(2);               // LED interrupt enable
                LEDCON1 |= 0x01; 
            }
        }
        #endif

    }
}

//##########################################################################
//##########################################################################

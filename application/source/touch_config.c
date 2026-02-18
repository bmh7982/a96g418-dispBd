/**
 *******************************************************************************
 * @file        touch_config.c
 * @author      ABOV R&D Division
 * @brief       Touch setting configure
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#include <stdlib.h>
#include "A96T418.h" 
#include "user_function.h"
#include "touch_config.h"
#include "touch_lib.h"
#if (UL60730_SELF_TEST_EN ==1)
#include "ul60730_testc_touch_V01.h"
#endif


/************************************************/

uint16_t raw_data[ACT_KEY_N][2];
uint16_t pre_raw_data[ACT_KEY_N][2];
uint16_t baseline[ACT_KEY_N][2];
uint16_t diff_data[ACT_KEY_N];

#if (TOUCH_FREQ_SEL_EN == 1)
uint16_t noise_sum[ACT_KEY_N][2];
uint8_t noise_cnt[ACT_KEY_N];
#endif
uint8_t noise_frq_sel[ACT_KEY_N];

uint16_t sco_buf[ACT_KEY_N];
uint16_t total_cap[ACT_KEY_N];

uint8_t base_hold_cnt[ACT_KEY_N];
uint8_t base_track_speed[ACT_KEY_N];
uint8_t debounce_cnt[ACT_KEY_N];
uint16_t thd_detect[ACT_KEY_N];
uint8_t actv_ch_num[ACT_KEY_N];

uint32_t raw_sum_data[ACT_KEY_N][2];
uint16_t raw_avrg_data[ACT_KEY_N][2];
uint8_t touch_sum_cnt[ACT_KEY_N];

/************************************************/

void Library_Data_Assign(void)
{
    ts.actv_ch_bit      = ACT_CH_BIT;
    ts.actv_ch_cnt      = ACT_KEY_N;
    
    ts.rc_filter_buf    = ((uint8_t)TS_COM_CFG[TOUCH_LPF_C_VALUE] 
                         | (uint8_t)TS_COM_CFG[TOUCH_LPF_R_VALUE]);

    ts.raw_data         = &raw_data[0];
    ts.pre_raw_data     = &pre_raw_data[0];
    ts.baseline         = &baseline[0];
    ts.diff_data        = &diff_data[0];
    
#if (TOUCH_FREQ_SEL_EN == 1)
    ts.fluct_sum        = &noise_sum[0];   
    ts.fluct_cnt        = &noise_cnt[0];
#endif
    ts.fluct_frq_sel    = &noise_frq_sel[0]; 
    
    ts.sco_buf          = &sco_buf[0];
    ts.total_cap        = &total_cap[0];

    ts.thd_detect       = &thd_detect[0];
    ts.hold_cnt_buf     = &base_hold_cnt[0];   
    ts.debounce_cnt_buf = &debounce_cnt[0];
    ts.ch_num_buf       = &actv_ch_num[0];
    ts.touch_sum_cnt    = &touch_sum_cnt[0];
    ts.base_track_iir   = &base_track_speed[0];

    ts.raw_sum_buf      = &raw_sum_data[0];
    ts.raw_avrg_buf     = &raw_avrg_data[0];   
}

void Touch_Config_Set (void)
{
    uint8_t ch;
    
    /* Touch Library API */ 
    ts.mode                     = (uint8_t)TS_COM_CFG[TOUCH_MODE];    
    ts.op_freq                  = (uint8_t)TS_COM_CFG[TOUCH_CLK];
    ts.delta_osc                = (uint8_t)TS_COM_CFG[TOUCH_CLK_OFFSET];
    ts.inact_port               = (uint8_t)TS_COM_CFG[TOUCH_PORT_SEL];
    ts.release_rate             = (uint8_t)TS_COM_CFG[THD_RELEASE_RATE];
    ts.reverse_rate             = (uint8_t)TS_COM_CFG[THD_REVERSE_RATE];
    ts.debounce_cnt_detect      = (uint8_t)TS_COM_CFG[DETECT_DEBOUNCE_CNT];
    ts.debounce_cnt_release     = (uint8_t)TS_COM_CFG[RELEASE_DEBOUNCE_CNT];
    ts.iir_offset_cnt           = (uint8_t)TS_COM_CFG[FILTER_IIR_GAIN];
    ts.base_release_hold_cnt    = (uint8_t)TS_COM_CFG[BASE_RELEASE_HOLD_CNT];
    ts.reverse_time             = TS_COM_CFG[TIMER_REVERSE_BASE_SAMPLE];
    ts.base_track_period        = TS_COM_CFG[TIMER_BASE_SAMPLE];
    ts.init_delay               = TS_COM_CFG[TIMER_STARTUP];
    ts.comp_ref                 = TS_COM_CFG[TOUCH_REFV]/5;
    ts.vhs                      = TS_COM_CFG[TOUCH_VHS]/5;

    for(ch = 0; ch < ts.actv_ch_cnt; ch++)
    {
        ts.touch_sum_cnt[ch]    = (uint8_t)TS_CH_CFG[ch][SUM_CNT];
        ts.base_track_iir[ch]   = (uint8_t)TS_CH_CFG[ch][BASE_TRACE_SPEED];
        ts.thd_detect[ch]       = TS_CH_CFG[ch][THRESHOLD];
    }
}


/**
 *******************************************************************************
 * @brief       Interrupt handler for UL60730 Touch test.
 * @param       None
 * @return      None
 ******************************************************************************/
void TOUCH_IRQHandler(void) interrupt TOUCH_VECT 
{
    EA = 1;
#if (UL60730_SELF_TEST_EN == 1)         
    if(UL_t.touch_isr_en == 1)
    {
        UL60730_TOUCH_ISR();
        return;
    }
    else
#endif    
    {   
        USER_TOUCH_ISR();
        return;
    }
}



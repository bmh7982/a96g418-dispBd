/**
 *******************************************************************************
 * @file        user_function.c
 * @author      ABOV R&D Division
 * @brief       User Function code
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
#include "common.h"
#include "touch_lib.h"
#include "user_function.h"
#include "user_timer.h"

/*********** touch api end **************/

#if ((MULTI_KEY_RESET | HOLD_KEY_RELEASE | FIRST_KEY_PRIORITY) == 1)
struct tp_param user;
#endif

#if (TOUCH_FREQ_SEL_EN == 1)
void Touch_Freq_Sel(void)
{
    uint8_t idata i;
    int16_t idata delta[2];
    
    for (i = 0; i < ts.actv_ch_cnt; i++)
    {
        ts.raw_data[i][0] = ((((uint32_t)ts.pre_raw_data[i][0]*ts.iir_offset_cnt)+ts.raw_data[i][0])/(ts.iir_offset_cnt+1));
        ts.raw_data[i][1] = ((((uint32_t)ts.pre_raw_data[i][1]*ts.iir_offset_cnt)+ts.raw_data[i][1])/(ts.iir_offset_cnt+1));

        delta[0] = (int16_t)(ts.raw_data[i][0]-ts.pre_raw_data[i][0]);
        delta[1] = (int16_t)(ts.raw_data[i][1]-ts.pre_raw_data[i][1]);

        ts.fluct_sum[i][0] += abs(delta[0]);
        ts.fluct_sum[i][1] += abs(delta[1]);
        ts.fluct_cnt[i]++;
        ts.fluct_cnt[i] %= 5;

        if (ts.fluct_cnt[i] == 0)
        {
            if (ts.fluct_sum[i][0] < ts.fluct_sum[i][1])
            {
                ts.fluct_frq_sel[i] = 0;
            }
            else
            {
                ts.fluct_frq_sel[i] = 1;
            }

            ts.fluct_sum[i][0] = 0;
            ts.fluct_sum[i][1] = 0;
        }

        ts.pre_raw_data[i][0] = ts.raw_data[i][0];
        ts.pre_raw_data[i][1] = ts.raw_data[i][1];
    }
}

#endif

#if ((HOLD_KEY_RELEASE | MULTI_KEY_RESET | FIRST_KEY_PRIORITY) == 1)

void Touch_Key_Scenario (void)
{
    uint8_t i;
    
#if (MULTI_KEY_RESET == 1)
    user.multi_key_check = 0;

    for (i = 0; i < ts.actv_ch_cnt; i++)
    {
        if (ts.detect_flag & BIT(i))    /* release check */     
        {
            if((user.multi_ch_bit & BIT(i)))
            {
                // if enter another key, count
                user.multi_key_check++;
            }
        }
    }

    if(user.multi_key_check > user.multi_key_limit)
    {
        ts.state = TS_STATE_INIT;
        TOUCH_INT_DIS();
    }
#endif

#if (FIRST_KEY_PRIORITY == 1)
    if(user.priority_ch_idx & ts.detect_flag)
    {
        ts.detect_flag = user.priority_ch_idx & ts.detect_flag;
        ts.detect_key = ts.detect_flag;
    }
#endif

#if (HOLD_KEY_RELEASE == 1)
    if (ts.detect_flag) 
    {
        if(ts.pre_detect_flag == 0)
        {
            UT_Set_Timer(UT_HOLD_KEY_RELEASE, user.hold_key_release_time);
        }
        else if (UT_Is_Expired(UT_HOLD_KEY_RELEASE) == 1)
        {
            for (i = 0; i < ts.actv_ch_cnt; i++)
            {
                ts.baseline[i][0] = ts.raw_data[i][0];
                ts.baseline[i][1] = ts.raw_data[i][1];

                //baseline sum buff zero init
                ts.raw_sum_buf[i][0] = 0;
                ts.raw_sum_buf[i][1] = 0;
                ts.raw_avrg_buf[i][0] = 0;
                ts.raw_avrg_buf[i][1] = 0;
            }
            ts.raw_sum_cnt = 0;
            UT_Set_Timer(UT_BASE_UPDATE, ts.base_track_period);
        }
    }
    else
    {
        UT_Clear_Timer(UT_HOLD_KEY_RELEASE);
    }
#endif

    ts.pre_detect_flag = ts.detect_flag;
}
#endif


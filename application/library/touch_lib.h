/**
 *******************************************************************************
 * @file        touch_lib.h
 * @author      ABOV R&D Division
 * @brief       Touch Sensor operating code 
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _TOUCH_LIB_H_
#define _TOUCH_LIB_H_

#include "typedef.h"
#include "user_function.h"

#define TS_BREAK_TIME   0x01
#define TS_COMPLETE     0x02

typedef enum
{
    TS_STATE_INIT = 0x00,
    TS_STATE_CAL,
    TS_STATE_SENSING,
    TS_STATE_COMPLETE,
    TS_STATE_INIT_BASE,
    TS_STATE_MAKE_DATA,
    TS_STATE_DICISION_KEY,
    TS_STATE_UPDATE_BASE,
    TS_STATE_NONE
}ts_state ;

enum{
    TS_MODE_NORMAL    = 0x00,
    TS_MODE_ADJUST    = 0x01,
    TS_MODE_HISENSE   = 0x02,
    TS_MODE_SIMULT    = 0x03    // normally no use
};

enum{
    TOUCH_FREQ_16M      = 0x00,
    TOUCH_FREQ_8M       = 0x01,
    TOUCH_FREQ_4M       = 0x02,
    TOUCH_FREQ_2M       = 0x03,
    TOUCH_FREQ_1M       = 0x04,
    TOUCH_FREQ_0_5M     = 0x05,
    TOUCH_FREQ_0_25M    = 0x06,
    TOUCH_FREQ_0_125M   = 0x07,
};
    
enum{
    MODE_FLOATING   = 0x00,
    MODE_OUT_LOW    = 0x01,
    MODE_OUT_HIGH   = 0x02
};

enum{
    CH_00 = 0,
    CH_01,
    CH_02,
    CH_03,
    CH_04,
    CH_05,
    CH_06,
    CH_07,
    CH_08,
    CH_09,
    CH_10,
    CH_11,
    CH_12,
    CH_13,
    CH_14,
    CH_15,
    CH_16,
    CH_17,
    CH_18,
    CH_19,
    CH_MAX
};

enum{
    INTENAL_CAPACITOR_OPEN        = 0x00,
    INTENAL_CAPACITOR_1_5pF       = 0x10,
    INTENAL_CAPACITOR_3_0pF       = 0x20,
    INTENAL_CAPACITOR_4_5pF       = 0x30,
    INTENAL_CAPACITOR_6_0pF       = 0x40,
    INTENAL_CAPACITOR_7_5pF       = 0x50,
    INTENAL_CAPACITOR_9_0pF       = 0x60,
    INTENAL_CAPACITOR_10_5pF      = 0x70, /* Default */
    INTENAL_CAPACITOR_12_0pF      = 0x80,
    INTENAL_CAPACITOR_13_5pF      = 0x90,
    INTENAL_CAPACITOR_15_0pF      = 0xA0,
    INTENAL_CAPACITOR_16_5pF      = 0xB0,
    INTENAL_CAPACITOR_18_0pF      = 0xC0,
    INTENAL_CAPACITOR_19_5pF      = 0xD0,
    INTENAL_CAPACITOR_21_0pF      = 0xE0,
    INTENAL_CAPACITOR_22_5pF      = 0xF0,
};

enum{
    SERIAL_REGISTER_OPEN    = 0x00,
    SERIAL_REGISTER_SHORT   = 0x01,
    SERIAL_REGISTER_5K      = 0x02,
    SERIAL_REGISTER_100K    = 0x04, /* Default */
    SERIAL_REGISTER_200K    = 0x08,
    SERIAL_REGISTER_33K     = 0x06,
    SERIAL_REGISTER_67K     = 0x0C,
    SERIAL_REGISTER_40K     = 0x0A,
    SERIAL_REGISTER_28K     = 0x0E,
};

typedef enum
{
    TOUCH_CLK = 0x00,
    TOUCH_CLK_OFFSET,
    TOUCH_LPF_C_VALUE,
    TOUCH_LPF_R_VALUE,
    TOUCH_MODE,
    TOUCH_PORT_SEL,
    TOUCH_VHS,
    TOUCH_REFV,
    DETECT_DEBOUNCE_CNT,
    RELEASE_DEBOUNCE_CNT,
    FILTER_IIR_GAIN,
    TIMER_STARTUP,
    TIMER_BASE_SAMPLE,
    BASE_RELEASE_HOLD_CNT,
    TIMER_REVERSE_BASE_SAMPLE,
    THD_RELEASE_RATE,
    THD_REVERSE_RATE,
    TOUCH_COM_CFG_MAX,
}ts_common_cfg;

typedef enum
{
    SUM_CNT = 0x00,
    THRESHOLD,
    BASE_TRACE_SPEED,
    TOUCH_CH_CFG_MAX,
}ts_channel_cfg;


/************************************************/
extern uint16_t diff_data[];
extern uint16_t raw_data[][2];
extern uint16_t pre_raw_data[][2];
extern uint16_t baseline[][2];

extern uint16_t sco_buf[];
extern uint16_t total_cap[];
extern uint8_t base_hold_cnt[];
extern uint8_t base_track_speed[];
extern uint8_t debounce_cnt[];
extern uint16_t thd_detect[];
extern uint8_t actv_ch_num[];

extern uint16_t noise_sum[][2];
extern uint8_t noise_cnt[];
extern uint8_t noise_frq_sel[];

extern uint32_t raw_sum_data[][2];
extern uint16_t raw_avrg_data[][2];
extern uint8_t touch_sum_cnt[];
/************************************************/

struct ts_param
{ 
    ts_state state;

    uint16_t *thd_detect;       
   
    uint8_t *fluct_cnt;
    uint8_t *fluct_frq_sel; 

    uint16_t *diff_data;

    uint16_t *sco_buf;
    uint16_t *total_cap;
    uint8_t max_cap_idx;
    
    uint8_t *hold_cnt_buf; 
    uint8_t *debounce_cnt_buf;
    uint8_t *ch_num_buf;
    uint32_t detect_key;     
    uint32_t detect_flag;
    uint32_t pre_detect_flag;
    uint8_t actv_ch_idx;
    uint8_t actv_ch_cnt;
    uint32_t actv_ch_bit;   
    uint8_t mode;
    uint8_t *touch_sum_cnt;
    uint8_t debounce_cnt_detect;
    uint8_t debounce_cnt_release;
    uint8_t iir_offset_cnt;
    uint16_t reverse_time;
    uint8_t reverse_rate;
    uint8_t release_rate;
    uint8_t reverse_ch_idx;
    
    uint8_t *base_track_iir;
    uint16_t base_track_period;
    uint8_t base_release_hold_cnt;
    
    uint16_t raw_sum_cnt;
    uint8_t inact_port;

    uint8_t rc_filter_buf;
    uint16_t init_delay;
        
    uint8_t op_freq;
    uint16_t comp_ref;
    uint16_t vhs;   
    uint8_t delta_osc;  
    uint8_t touch_lib_ver;

    uint32_t wheel_detect;
    uint32_t wheel_act_ch_bit;
    uint32_t slide_detect;
    uint32_t slide_act_ch_bit;

    struct
    {
        uint8_t base_init           :1;
        uint8_t ts_status           :2;        
        uint8_t touch_sensing_end   :1;
        uint8_t touch_freq_sel_mode :1;
        uint8_t reserved            :3;
    } flag;

    uint16_t (*fluct_sum)[2];
    uint32_t (*raw_sum_buf)[2];
    uint16_t (*raw_avrg_buf)[2];
    uint16_t (*filter_one_sensing)[2];
    uint16_t (*pre_raw_data)[2];    /* point to freqA[1], freqB[0] touch base data storage location */
    uint16_t (*raw_data)[2];        /* point to freqA[1], freqB[0] touch raw data storage location */
    uint16_t (*baseline)[2];        /* point to freqA[1], freqB[0] touch base data storage location */
};
struct ts_register
{
    uint16_t sco[TS_MAX_KEY];
    uint8_t reg[18];
};
extern struct ts_param ts;
extern struct ts_register idata ts_reg;

extern void (*func_p_Touch_Freq_Sel)(void);

void Touch_Do_Task (void);
void Touch_Start_Touch (uint8_t idx);

extern void Library_Data_Assign(void);
extern void Touch_Config_Set (void);
extern void USER_TOUCH_ISR(void);


#endif  /* _TOUCH_LIB_H_ */


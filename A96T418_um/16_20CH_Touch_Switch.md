# 16 20-Channel Touch Switch

## 16.1 Features

- 10V Conducted Susceptibility (CS) Immunity
- Self-Capacitive Touch Key Sensor
- Total 20-channel Touch Key Support
- 16-bits Sensing Resolutions
- Fast Initial Self Calibration
- Key Detection Mode: Single / Multi-Mode
- Clock Frequency during Sensing Operation: 16 MHz
- The Improvement of the SNR by Bias-Calibration in Analog Sensing Block
- VDD Operating Voltage: 2.7 V ~ 5.5 V
- Current Consumption: T.B.D.
- Current Consumption @ STOP mode: < 1 uA
- Operation Temperature: -40°C ~ 105°C

---

## 16.2 Block Diagram

> **Figure 114. 16-bit Touch Block Diagram** *(refer to original datasheet)*

### CAPN Port

Connect the negative terminal of the reference capacitor Cs to CAPN port, and the positive terminal of the Cs capacitor to VDD. Cs capacitors must use 5% precision polyester plug-in capacitors, 10% high precision NPO or X7R chip capacitors. C0G type or Mylar Capacitors recommended for applications with severe temperature changes.

> **Figure 115. CAPN Pin with Cs Capacitor** *(refer to original datasheet)*

---

## 16.3 Register Map

**Table 40. Touch Register Map**

| Name          | Address | Direction | Default | Description                                              |
|---------------|---------|-----------|---------|----------------------------------------------------------|
| SUM_CH0_F0_H  | 2E00H   | R         | 00H     | Touch Sensor Ch0 Freq0 Sum High-Byte Register            |
| SUM_CH0_F0_L  | 2E01H   | R         | 00H     | Touch Sensor Ch0 Freq0 Sum Low-Byte Register             |
| SUM_CH0_F1_H  | 2E02H   | R         | 00H     | Touch Sensor Ch0 Freq1 Sum High-Byte Register            |
| SUM_CH0_F1_L  | 2E03H   | R         | 00H     | Touch Sensor Ch0 Freq1 Sum Low-Byte Register             |
| ⋮             | ⋮       | ⋮         | ⋮       | ⋮                                                        |
| SUM_CH19_F0_H | 2E4CH   | R         | 00H     | Touch Sensor Ch19 Freq0 Sum High-Byte Register           |
| SUM_CH19_F0_L | 2E4DH   | R         | 00H     | Touch Sensor Ch19 Freq0 Sum Low-Byte Register            |
| SUM_CH19_F1_H | 2E4EH   | R         | 00H     | Touch Sensor Ch19 Freq1 Sum High-Byte Register           |
| SUM_CH19_F1_L | 2E4FH   | R         | 00H     | Touch Sensor Ch19 Freq1 Sum Low-Byte Register            |
| SCO0_H        | 2E50H   | R/W       | 00H     | Touch Sensor Offset Capacitor Selection High-Byte for Ch0 |
| SCO0_L        | 2E51H   | R/W       | 00H     | Touch Sensor Offset Capacitor Selection Low-Byte for Ch0  |
| ⋮             | ⋮       | ⋮         | ⋮       | ⋮                                                        |
| SCO19_H       | 2E76H   | R/W       | 00H     | Touch Sensor Offset Capacitor Selection High-Byte for Ch19 |
| SCO19_L       | 2E77H   | R/W       | 00H     | Touch Sensor Offset Capacitor Selection Low-Byte for Ch19  |
| TS_CON        | 2E80H   | R/W       | 00H     | Touch Sensor Control Register                            |
| TS_MODE       | 2E81H   | R/W       | 00H     | Touch Sensor Mode Register                               |
| TS_SUM_CNT    | 2E82H   | R/W       | 01H     | Touch Sensor Sum Repeat Count Register                   |
| TS_CH_SELH    | 2E83H   | R/W       | 00H     | Touch Sensor Channel Selection High-Byte Register        |
| TS_CH_SELM    | 2E84H   | R/W       | 00H     | Touch Sensor Channel Selection Middle-Byte Register      |
| TS_CH_SELL    | 2E85H   | R/W       | 00H     | Touch Sensor Channel Selection Low-Byte Register         |
| TS_S1_WIDH    | 2E86H   | R/W       | 15H     | S1 Minimum Time Register                                 |
| TS_SLP_CON    | 2E87H   | R/W       | 74H     | Touch Sensor Low Pass Filter Control Register            |
| Reserved      | 2E88H   | —         | —       | Reserved                                                 |
| TS_TRIM       | 2E89H   | R/W       | 07H     | Touch Sensor Trimming Register                           |
| TS_CLK_CFG    | 2E8AH   | R/W       | 02H     | Touch Sensor Clock Configuration Register                |
| TRIM_OSC      | 2E8BH   | R/W       | 20H     | Touch Sensor RING Oscillator Trimming Selection Register  |
| DELTA_OSC     | 2E8CH   | R/W       | 01H     | Touch Sensor RING Oscillator Delta Register              |
| TLED          | 2E8DH   | R/W       | 30H     | LED Stable Time Register                                 |
| TS_VHS_H      | 2E8EH   | R/W       | 02H     | Touch Sensor High Sense Voltage High-Byte Register       |
| TS_VHS_L      | 2E8FH   | R/W       | 80H     | Touch Sensor High Sense Voltage Low-Byte Register        |
| TS_VREF_H     | 2E90H   | R/W       | 02H     | Touch Sensor COMP Reference Voltage High-Byte Register   |
| TS_VREF_L     | 2E91H   | R/W       | 10H     | Touch Sensor COMP Reference Voltage Low-Byte Register    |

---

## 16.4 Register Description for Touch Sensing

### SUM_CHx_Fy — Touch Sensor Sum Registers

CH0 ~ CH19 각각에 Freq0(F0), Freq1(F1)의 High/Low 바이트 레지스터가 있으며 모두 읽기 전용(R)입니다.

#### SUM_CH0_F0_H (2E00H) / SUM_CH0_F0_L (2E01H)

| Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 |
|-------|-------|-------|-------|-------|-------|-------|-------|
| R     | R     | R     | R     | R     | R     | R     | R     |

**Initial value: 00H**

#### 전체 SUM 레지스터 주소 목록

| Register         | Address | Register         | Address |
|------------------|---------|------------------|---------|
| SUM_CH0_F0_H     | 2E00H   | SUM_CH0_F0_L     | 2E01H   |
| SUM_CH0_F1_H     | 2E02H   | SUM_CH0_F1_L     | 2E03H   |
| SUM_CH1_F0_H     | 2E04H   | SUM_CH1_F0_L     | 2E05H   |
| SUM_CH1_F1_H     | 2E06H   | SUM_CH1_F1_L     | 2E07H   |
| SUM_CH2_F0_H     | 2E08H   | SUM_CH2_F0_L     | 2E09H   |
| SUM_CH2_F1_H     | 2E0AH   | SUM_CH2_F1_L     | 2E0BH   |
| SUM_CH3_F0_H     | 2E0CH   | SUM_CH3_F0_L     | 2E0DH   |
| SUM_CH3_F1_H     | 2E0EH   | SUM_CH3_F1_L     | 2E0FH   |
| SUM_CH4_F0_H     | 2E10H   | SUM_CH4_F0_L     | 2E11H   |
| SUM_CH4_F1_H     | 2E12H   | SUM_CH4_F1_L     | 2E13H   |
| SUM_CH5_F0_H     | 2E14H   | SUM_CH5_F0_L     | 2E15H   |
| SUM_CH5_F1_H     | 2E16H   | SUM_CH5_F1_L     | 2E17H   |
| SUM_CH6_F0_H     | 2E18H   | SUM_CH6_F0_L     | 2E19H   |
| SUM_CH6_F1_H     | 2E1AH   | SUM_CH6_F1_L     | 2E1BH   |
| SUM_CH7_F0_H     | 2E1CH   | SUM_CH7_F0_L     | 2E1DH   |
| SUM_CH7_F1_H     | 2E1EH   | SUM_CH7_F1_L     | 2E1FH   |
| SUM_CH8_F0_H     | 2E20H   | SUM_CH8_F0_L     | 2E21H   |
| SUM_CH8_F1_H     | 2E22H   | SUM_CH8_F1_L     | 2E23H   |
| SUM_CH9_F0_H     | 2E24H   | SUM_CH9_F0_L     | 2E25H   |
| SUM_CH9_F1_H     | 2E26H   | SUM_CH9_F1_L     | 2E27H   |
| SUM_CH10_F0_H    | 2E28H   | SUM_CH10_F0_L    | 2E29H   |
| SUM_CH10_F1_H    | 2E2AH   | SUM_CH10_F1_L    | 2E2BH   |
| SUM_CH11_F0_H    | 2E2CH   | SUM_CH11_F0_L    | 2E2DH   |
| SUM_CH11_F1_H    | 2E2EH   | SUM_CH11_F1_L    | 2E2FH   |
| SUM_CH12_F0_H    | 2E30H   | SUM_CH12_F0_L    | 2E31H   |
| SUM_CH12_F1_H    | 2E32H   | SUM_CH12_F1_L    | 2E33H   |
| SUM_CH13_F0_H    | 2E34H   | SUM_CH13_F0_L    | 2E35H   |
| SUM_CH13_F1_H    | 2E36H   | SUM_CH13_F1_L    | 2E37H   |
| SUM_CH14_F0_H    | 2E38H   | SUM_CH14_F0_L    | 2E39H   |
| SUM_CH14_F1_H    | 2E3AH   | SUM_CH14_F1_L    | 2E3BH   |
| SUM_CH15_F0_H    | 2E3CH   | SUM_CH15_F0_L    | 2E3DH   |
| SUM_CH15_F1_H    | 2E3EH   | SUM_CH15_F1_L    | 2E3FH   |
| SUM_CH16_F0_H    | 2E40H   | SUM_CH16_F0_L    | 2E41H   |
| SUM_CH16_F1_H    | 2E42H   | SUM_CH16_F1_L    | 2E43H   |
| SUM_CH17_F0_H    | 2E44H   | SUM_CH17_F0_L    | 2E45H   |
| SUM_CH17_F1_H    | 2E46H   | SUM_CH17_F1_L    | 2E47H   |
| SUM_CH18_F0_H    | 2E48H   | SUM_CH18_F0_L    | 2E49H   |
| SUM_CH18_F1_H    | 2E4AH   | SUM_CH18_F1_L    | 2E4BH   |
| SUM_CH19_F0_H    | 2E4CH   | SUM_CH19_F0_L    | 2E4DH   |
| SUM_CH19_F1_H    | 2E4EH   | SUM_CH19_F1_L    | 2E4FH   |

---

### SCOx — Touch Sensor Offset Capacitor Selection Registers

CH0 ~ CH19 각각에 High/Low 바이트 레지스터가 있으며 읽기/쓰기(R/W)입니다.

#### SCO0_H (2E50H) / SCO0_L (2E51H)

| Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 |
|-------|-------|-------|-------|-------|-------|-------|-------|
| R/W   | R/W   | R/W   | R/W   | R/W   | R/W   | R/W   | R/W   |

**Initial value: 00H**

#### 전체 SCO 레지스터 주소 목록

| Register  | Address | Register  | Address |
|-----------|---------|-----------|---------|
| SCO0_H    | 2E50H   | SCO0_L    | 2E51H   |
| SCO1_H    | 2E52H   | SCO1_L    | 2E53H   |
| SCO2_H    | 2E54H   | SCO2_L    | 2E55H   |
| SCO3_H    | 2E56H   | SCO3_L    | 2E57H   |
| SCO4_H    | 2E58H   | SCO4_L    | 2E59H   |
| SCO5_H    | 2E5AH   | SCO5_L    | 2E5BH   |
| SCO6_H    | 2E5CH   | SCO6_L    | 2E5DH   |
| SCO7_H    | 2E5EH   | SCO7_L    | 2E5FH   |
| SCO8_H    | 2E60H   | SCO8_L    | 2E61H   |
| SCO9_H    | 2E62H   | SCO9_L    | 2E63H   |
| SCO10_H   | 2E64H   | SCO10_L   | 2E65H   |
| SCO11_H   | 2E66H   | SCO11_L   | 2E67H   |
| SCO12_H   | 2E68H   | SCO12_L   | 2E69H   |
| SCO13_H   | 2E6AH   | SCO13_L   | 2E6BH   |
| SCO14_H   | 2E6CH   | SCO14_L   | 2E6DH   |
| SCO15_H   | 2E6EH   | SCO15_L   | 2E6FH   |
| SCO16_H   | 2E70H   | SCO16_L   | 2E71H   |
| SCO17_H   | 2E72H   | SCO17_L   | 2E73H   |
| SCO18_H   | 2E74H   | SCO18_L   | 2E75H   |
| SCO19_H   | 2E76H   | SCO19_L   | 2E77H   |

---

### TS_CON — Touch Sensor Control Register (2E80H)

| Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2  | Bit 1 | Bit 0  |
|-------|-------|-------|-------|-------|--------|-------|--------|
| —     | —     | —     | —     | —     | TS_IF  | —     | TS_RUN |
| —     | —     | —     | —     | —     | R/W    | —     | R/W    |

**Initial value: 00H**

| Bit | Field  | Description |
|-----|--------|-------------|
| [2] | TS_IF  | Touch Sensor Interrupt Flag. To start new sensing, this bit must be cleared after reading SUM registers. If this bit changes from 1 to 0, the SUM registers are reset to 0.<br>`0` = No new sensing results<br>`1` = New sensing results are generated (normal mode) |
| [0] | TS_RUN | Touch Sensor Enable<br>`0` = Touch Sensor Disable (Default)<br>`1` = Touch Sensor Enable |

---

### TS_MODE — Touch Sensor Mode Register (2E81H)

| Bit 7 | Bit 6   | Bit 5        | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 |
|-------|---------|--------------|-------|-------|-------|-------|-------|
| —     | SC_GAIN | S1_SWEEP_DIS | MODE2 | MODE1 | MODE0 | PORT1 | PORT0 |
| —     | R/W     | R/W          | R/W   | —     | R/W   | R/W   | R/W   |

**Initial value: 00H**

| Bit    | Field        | Description |
|--------|--------------|-------------|
| [6]    | SC_GAIN      | Gain Calibration Capacitor Enable<br>`0` = Disable, `1` = Enable |
| [5]    | S1_SWEEP_DIS | S1 Width Sweep Disable<br>`0` = Sweep enable (Default), `1` = Sweep disable |
| [4:2]  | MODE[2:0]    | Touch Sensor Mode<br>`000` = Normal sensing mode<br>`001` = High sensing mode<br>`010` = Channel Adjust sensing mode<br>`011` = Offset Calibration sensing mode<br>`100` = Simultaneous sensing for all selected channels (reduces sensing time) |
| [1:0]  | PORT[1:0]    | Port Configuration During Inactive Status<br>`00` = Input Floating<br>`01` = Output Low<br>`10` = Output High |

---

### TS_SUM_CNT — Touch Sensor Sum Repeat Count Register (2E82H)

| Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 |
|-------|-------|-------|-------|-------|-------|-------|-------|
| R/W   | R/W   | R/W   | R/W   | R/W   | R/W   | R/W   | R/W   |

**Initial value: 01H**

---

### TS_CH_SEL_H — Touch Sensor Channel Selection High-Byte Register (2E83H)

| Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3    | Bit 2    | Bit 1    | Bit 0    |
|-------|-------|-------|-------|----------|----------|----------|----------|
| —     | —     | —     | —     | CH19_SEL | CH18_SEL | CH17_SEL | CH16_SEL |
| —     | —     | —     | —     | R/W      | R/W      | R/W      | R/W      |

**Initial value: 00H**

| Bit | Field    | Description |
|-----|----------|-------------|
| [3] | CH19_SEL | Channel 19 Enable: `0` = Disable (Default), `1` = Enable Touch Key by P03 |
| [2] | CH18_SEL | Channel 18 Enable: `0` = Disable (Default), `1` = Enable Touch Key by P00 |
| [1] | CH17_SEL | Channel 17 Enable: `0` = Disable (Default), `1` = Enable Touch Key by P31 |
| [0] | CH16_SEL | Channel 16 Enable: `0` = Disable (Default), `1` = Enable Touch Key by P27 |

---

### TS_CH_SEL_M — Touch Sensor Channel Selection Middle-Byte Register (2E84H)

| Bit 7    | Bit 6    | Bit 5    | Bit 4    | Bit 3    | Bit 2    | Bit 1   | Bit 0   |
|----------|----------|----------|----------|----------|----------|---------|---------|
| CH15_SEL | CH14_SEL | CH13_SEL | CH12_SEL | CH11_SEL | CH10_SEL | CH9_SEL | CH8_SEL |
| R/W      | R/W      | R/W      | R/W      | R/W      | R/W      | R/W     | R/W     |

**Initial value: 00H**

| Bit | Field    | Description |
|-----|----------|-------------|
| [7] | CH15_SEL | Channel 15 Enable: `0` = Disable (Default), `1` = Enable Touch Key by P26 |
| [6] | CH14_SEL | Channel 14 Enable: `0` = Disable (Default), `1` = Enable Touch Key by P25 |
| [5] | CH13_SEL | Channel 13 Enable: `0` = Disable (Default), `1` = Enable Touch Key by P24 |
| [4] | CH12_SEL | Channel 12 Enable: `0` = Disable (Default), `1` = Enable Touch Key by P23 |
| [3] | CH11_SEL | Channel 11 Enable: `0` = Disable (Default), `1` = Enable Touch Key by P22 |
| [2] | CH10_SEL | Channel 10 Enable: `0` = Disable (Default), `1` = Enable Touch Key by P17 |
| [1] | CH9_SEL  | Channel 9 Enable:  `0` = Disable (Default), `1` = Enable Touch Key by P16 |
| [0] | CH8_SEL  | Channel 8 Enable:  `0` = Disable (Default), `1` = Enable Touch Key by P15 |

---

### TS_CH_SEL_L — Touch Sensor Channel Selection Low-Byte Register (2E85H)

| Bit 7   | Bit 6   | Bit 5   | Bit 4   | Bit 3   | Bit 2   | Bit 1   | Bit 0   |
|---------|---------|---------|---------|---------|---------|---------|---------|
| CH7_SEL | CH6_SEL | CH5_SEL | CH4_SEL | CH3_SEL | CH2_SEL | CH1_SEL | CH0_SEL |
| R/W     | R/W     | R/W     | R/W     | R/W     | R/W     | R/W     | R/W     |

**Initial value: 00H**

| Bit | Field   | Description |
|-----|---------|-------------|
| [7] | CH7_SEL | Channel 7 Enable: `0` = Disable (Default), `1` = Enable Touch Key by P14 |
| [6] | CH6_SEL | Channel 6 Enable: `0` = Disable (Default), `1` = Enable Touch Key by P12 |
| [5] | CH5_SEL | Channel 5 Enable: `0` = Disable (Default), `1` = Enable Touch Key by P11 |
| [4] | CH4_SEL | Channel 4 Enable: `0` = Disable (Default), `1` = Enable Touch Key by P10 |
| [3] | CH3_SEL | Channel 3 Enable: `0` = Disable (Default), `1` = Enable Touch Key by P07 |
| [2] | CH2_SEL | Channel 2 Enable: `0` = Disable (Default), `1` = Enable Touch Key by P06 |
| [1] | CH1_SEL | Channel 1 Enable: `0` = Disable (Default), `1` = Enable Touch Key by P05 |
| [0] | CH0_SEL | Channel 0 Enable: `0` = Disable (Default), `1` = Enable Touch Key by P04 |

---

### TS_S1_WIDTH — S1 Timing Register (2E86H)

| Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 |
|-------|-------|-------|-------|-------|-------|-------|-------|
| R/W   | R/W   | R/W   | R/W   | R/W   | R/W   | R/W   | R/W   |

**Initial value: 20H**

> S1 width is randomly varied from `2 × TS_S1_WIDTH` to `4 × TS_S1_WIDTH`.

---

### TS_SLP_CON — Touch Sensor Low Pass Filter Control Register (2E87H)

| Bit 7  | Bit 6  | Bit 5  | Bit 4  | Bit 3  | Bit 2  | Bit 1  | Bit 0  |
|--------|--------|--------|--------|--------|--------|--------|--------|
| SLP_C3 | SLP_C2 | SLP_C1 | SLP_C0 | SLP_R3 | SLP_R2 | SLP_R1 | SLP_R0 |
| R/W    | R/W    | R/W    | R/W    | R/W    | R/W    | R/W    | R/W    |

**Initial value: 74H**

#### SLP_C[3:0] — Capacitor Trimming for Input Low Pass Filter

| Value | Capacitance |
|-------|-------------|
| 0000  | 0.0 pF      |
| 0001  | 1.5 pF      |
| 0010  | 3.0 pF      |
| 0011  | 4.5 pF      |
| 0100  | 6.0 pF      |
| 0101  | 7.5 pF      |
| 0110  | 9.0 pF      |
| 0111  | 10.5 pF *(Default)* |
| 1000  | 12.0 pF     |
| 1001  | 13.5 pF     |
| 1010  | 15.0 pF     |
| 1011  | 16.5 pF     |
| 1100  | 18.0 pF     |
| 1101  | 19.5 pF     |
| 1110  | 21.0 pF     |
| 1111  | 22.5 pF     |

#### SLP_R[3:0] — Resistor Trimming for Input Low Pass Filter

| Value | Resistance        |
|-------|-------------------|
| 0000  | Open              |
| 0001  | 0 KΩ              |
| 0010  | 5 KΩ              |
| 0100  | 100 KΩ *(Default)* |
| 1000  | 200 KΩ            |
| 0110  | 33 KΩ             |
| 1100  | 67 KΩ             |
| 1010  | 40 KΩ             |
| 1110  | 28 KΩ             |

---

### TS_TRIM — Touch Sensor Trimming Register (2E89H)

| Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3    | Bit 2    | Bit 1    | Bit 0    |
|-------|-------|-------|-------|----------|----------|----------|----------|
| —     | —     | —     | HC    | IB_TRIM3 | IB_TRIM2 | IB_TRIM1 | IB_TRIM0 |
| —     | —     | —     | R/W   | R/W      | R/W      | R/W      | R/W      |

**Initial value: 07H**

| Bit    | Field       | Description |
|--------|-------------|-------------|
| [4]    | HC          | High Current Enable: `0` = Disable, `1` = Enable |
| [3:0]  | IB_TRIM[3:0] | Current Bias Trimming Value |

#### IB_TRIM[3:0] — Current Bias Trimming

| Value | Current          |
|-------|------------------|
| 0000  | 1.0 uA (N)       |
| 0001  | 1.5 uA (N)       |
| 0010  | 2.0 uA (N)       |
| 0011  | 2.5 uA (N)       |
| 0100  | 3.0 uA (N)       |
| 0101  | 3.5 uA (N)       |
| 0110  | 4.0 uA (N)       |
| 0111  | 4.5 uA (N) *(Default)* |
| 1000  | 5.0 uA (N)       |
| 1001  | 5.5 uA (N)       |
| 1010  | 6.0 uA (N)       |
| 1011  | 6.5 uA (N)       |
| 1100  | 7.0 uA (N)       |
| 1101  | 7.5 uA (N)       |
| 1110  | 8.0 uA (N)       |
| 1111  | 8.5 uA (N)       |

---

### TS_CLK_CFG — Touch Sensor Clock Configuration Register (2E8AH)

| Bit 7   | Bit 6  | Bit 5    | Bit 4    | Bit 3   | Bit 2      | Bit 1      | Bit 0      |
|---------|--------|----------|----------|---------|------------|------------|------------|
| SCLK_EN | PAT_EN | CLKSEL1  | CLKSEL0  | TSCLKOE | TSCLKDIV2  | TSCLKDIV1  | TSCLKDIV0  |
| R/W     | R/W    | R/W      | R/W      | R/W     | R/W        | R/W        | R/W        |

**Initial value: 02H**

| Bit    | Field         | Description |
|--------|---------------|-------------|
| [7]    | SCLK_EN       | Enable/disable system clock as touch clock<br>`0` = Disable (Default), `1` = Enable |
| [6]    | PAT_EN        | Enable/disable pattern for S2 & S3<br>`0` = Disable (Default), `1` = Enable |
| [5:4]  | CLKSEL[1:0]   | Touch Clock source select<br>`00` = Two touch sensor clocks used<br>`01` = Touch clock A only<br>`1x` = Touch clock B only |
| [3]    | TSCLKOE       | Divided Touch Sensor Clock Output Enable<br>`0` = Clock Output Disable (Default), `1` = Clock Output Enable |
| [2:0]  | TSCLKDIV[2:0] | Touch Sensor Clock Divider<br>`000` = OSCts / 1 — 16 MHz (Default)<br>`001` = OSCts / 2<br>`010` = OSCts / 4<br>`011` = OSCts / 8<br>`100` = OSCts / 16<br>`101` = OSCts / 32<br>`110` = OSCts / 64<br>`111` = OSCts / 128 |

---

### TRIM_OSC — Touch Sensor RING Oscillator Trimming Selection Register (2E8BH)

| Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 |
|-------|-------|-------|-------|-------|-------|-------|-------|
| —     | —     | R/W   | R/W   | R/W   | R/W   | R/W   | R/W   |

**Initial value: 20H**

TRIM_OSC[5:0] — Touch Sensor RING Oscillator Trimming Selection

| Value | Frequency        |
|-------|------------------|
| 3FH   | +23.25% (19.72 MHz) |
| 3EH   | +22.50%          |
| ⋮     | ⋮                |
| 21H   | +0.75%           |
| 20H   | 16 MHz *(Default)* |
| 1FH   | −0.75%           |
| ⋮     | ⋮                |
| 01H   | −23.25%          |
| 00H   | −24.00% (12.16 MHz) |

**Frequency of Touch clock B:**
```
Frequency = 16MHz + 16MHz × ((TRIM_OSC − 0x20) × 0.0075)
```

---

### DELTA_OSC — Touch Sensor RING Oscillator Delta Register (2E8CH)

| Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 |
|-------|-------|-------|-------|-------|-------|-------|-------|
| R/W   | R/W   | R/W   | R/W   | R/W   | R/W   | R/W   | R/W   |

**Initial value: 01H**

**Frequency of Touch clock A:**
```
Frequency = 16MHz + 16MHz × (((TRIM_OSC + DELTA_OSC) − 0x20) × 0.0075)
```

---

### TLED — LED Stable Time Register (2E8DH)

| Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 |
|-------|-------|-------|-------|-------|-------|-------|-------|
| R/W   | R/W   | R/W   | R/W   | R/W   | R/W   | R/W   | R/W   |

**Initial value: 00H**

To run touch sensing again after LED working, 25~30 us stable time is required. This counter operates based on the system clock.

---

### TS_VHS_H / TS_VHS_L — Touch Sensor High Sense Voltage Registers

#### TS_VHS_H (2E8EH)

| Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1    | Bit 0    |
|-------|-------|-------|-------|-------|-------|----------|----------|
| —     | —     | —     | —     | —     | —     | TS_VHS_H | TS_VHS_H |
| —     | —     | —     | —     | —     | —     | R/W      | R/W      |

**Initial value: 02H**

#### TS_VHS_L (2E8FH)

| Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 |
|-------|-------|-------|-------|-------|-------|-------|-------|
| R/W   | R/W   | R/W   | R/W   | R/W   | R/W   | R/W   | R/W   |

**Initial value: 80H**

---

### TS_VREF_H / TS_VREF_L — Touch Sensor COMP Reference Voltage Registers

#### TS_VREF_H (2E90H)

| Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2  | Bit 1    | Bit 0    |
|-------|-------|-------|-------|-------|--------|----------|----------|
| —     | —     | —     | —     | —     | —      | TS_VREF_H | TS_VREF_H |
| —     | —     | —     | —     | —     | —      | R/W      | R/W      |

**Initial value: 02H**

#### TS_VREF_L (2E91H)

| Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 |
|-------|-------|-------|-------|-------|-------|-------|-------|
| R/W   | R/W   | R/W   | R/W   | R/W   | R/W   | R/W   | R/W   |

**Initial value: 10H**

---

## 16.5 User Programming Procedure

> **Figure 116. User Programming Procedure**

```c
Start

    TS_SUM_CNT  = 0x04;   // Touch Sensor Sum Repeat Count Register
    TS_S1_WIDTH = 0x2A;   // S1 Width
    TS_MODE     = 0x00;   // TS enable
    TS_CH_SEL   = 0xFFFF; // TS channel enable

    //------ Offset Capacitor Selection
    SCO00 = 0x10;  // Touch Sensor Offset Capacitor Selection Register
    SCO01 = 0x10;  // Touch Sensor Offset Capacitor Selection Register
    SCO02 = 0x10;  // Touch Sensor Offset Capacitor Selection Register
    SCO03 = 0x10;  // Touch Sensor Offset Capacitor Selection Register
    SCO04 = 0x10;  // Touch Sensor Offset Capacitor Selection Register
    SCO05 = 0x10;  // Touch Sensor Offset Capacitor Selection Register
    SCO06 = 0x10;  // Touch Sensor Offset Capacitor Selection Register
    SCO07 = 0x10;  // Touch Sensor Offset Capacitor Selection Register
    SCO08 = 0x10;  // Touch Sensor Offset Capacitor Selection Register
    SCO09 = 0x10;  // Touch Sensor Offset Capacitor Selection Register
    SCO10 = 0x10;  // Touch Sensor Offset Capacitor Selection Register
    SCO11 = 0x10;  // Touch Sensor Offset Capacitor Selection Register
    SCO12 = 0x10;  // Touch Sensor Offset Capacitor Selection Register
    SCO13 = 0x10;  // Touch Sensor Offset Capacitor Selection Register
    SCO14 = 0x10;  // Touch Sensor Offset Capacitor Selection Register
    SCO15 = 0x10;  // Touch Sensor Offset Capacitor Selection Register
    SCO16 = 0x10;  // Touch Sensor Offset Capacitor Selection Register
    SCO17 = 0x10;  // Touch Sensor Offset Capacitor Selection Register
    SCO18 = 0x10;  // Touch Sensor Offset Capacitor Selection Register
    SCO19 = 0x10;  // Touch Sensor Offset Capacitor Selection Register

    TS_CON = 0x01;              // TS run
    while (!(TS_CON & 0x04));   // Wait for sensing complete (TS_IF flag)
```

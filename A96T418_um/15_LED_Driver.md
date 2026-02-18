# 15 LED Driver

## 15.1 Overview

LED drive contains 8 COM / 16 SEG output pins. They are also shared with Touch sensing pins. By setting LED CONTROL REGISTER 1 (LEDCON1), there are 5 modes that can be shared (or not shared) with touch sensing function. The controller consists of display data RAM memory, COM and SEG generator. COM0–COM7 are shared with SEG0–SEG7. It is selected by CSER register. SEG8~SEG15 is dedicated only SEG function in LED function. COM and SEG pin can also be used as I/O pins. COMOE, and SEGOE1, SEGOE2 registers are used to select SEG0–SEG14, COM0–COM7.

During the power-on reset, reset pin, BOD reset or watchdog reset, LED are turned off.

---

## 15.2 Block Diagram

> **Figure 105. LED Driver Block Diagram** *(refer to original datasheet)*

---

## 15.3 Register Map

**Table 37. LED Driver Register Map**

| Name      | Address | Direction | Default | Description                          |
|-----------|---------|-----------|---------|--------------------------------------|
| COMOE     | 2F00H   | R/W       | 00H     | LED COM Output Enable Register       |
| SEGOE1    | 2F01H   | R/W       | 00H     | LED SEG Output Enable 1 Register     |
| SEGOE2    | 2F02H   | R/W       | 00H     | LED SEG Output Enable 2 Register     |
| PRESD     | 2F03H   | R/W       | 00H     | LED Prescale Data Register           |
| CSER      | 2F04H   | R/W       | 00H     | LED COM or SEG Enable Register       |
| COMPWID   | 2F05H   | R/W       | 00H     | LED COM Pulse Width Control Register |
| STPD0     | 2F0AH   | R/W       | 00H     | LED Stop Duration 0 Register         |
| STPD1     | 2F0BH   | R/W       | 00H     | LED Stop Duration 1 Register         |
| STPD2     | 2F0CH   | R/W       | 00H     | LED Stop Duration 2 Register         |
| LEDSR     | 2F0DH   | R/W       | 01H     | LED Status Register                  |
| LEDCON3   | 2F0EH   | R/W       | 00H     | LED Control 3 Register               |
| LEDCON2   | 2F0FH   | R/W       | 00H     | LED Control 2 Register               |
| LEDCON1   | 2F10H   | R/W       | 00H     | LED Control 1 Register               |
| CCLSR     | 2F30H   | R/W       | 01H     | Constant Current Level Select Register |
| TEST_COM  | 2F7CH   | R/W       | 00H     | COM Register for Test                |
| TEST_SEG0 | 2F7DH   | R/W       | 00H     | SEG Register for Test                |
| TEST_SEG1 | 2F7EH   | R/W       | 00H     | SEG Register for Test                |

---

## 15.4 Register Description for LED Driver

### COMOE — LED COM Output Enable Register (2F00H)

| Bit 7   | Bit 6   | Bit 5   | Bit 4   | Bit 3   | Bit 2   | Bit 1   | Bit 0   |
|---------|---------|---------|---------|---------|---------|---------|---------|
| COMOE7  | COMOE6  | COMOE5  | COMOE4  | COMOE3  | COMOE2  | COMOE1  | COMOE0  |
| R/W     | R/W     | R/W     | R/W     | R/W     | R/W     | R/W     | R/W     |

**Initial value: 00H**

| Bit    | Field  | Description            |
|--------|--------|------------------------|
| [7]    | COMOE7 | COM7 Output Enable: `0` = Disable, `1` = Enable |
| [6]    | COMOE6 | COM6 Output Enable: `0` = Disable, `1` = Enable |
| [5]    | COMOE5 | COM5 Output Enable: `0` = Disable, `1` = Enable |
| [4]    | COMOE4 | COM4 Output Enable: `0` = Disable, `1` = Enable |
| [3]    | COMOE3 | COM3 Output Enable: `0` = Disable, `1` = Enable |
| [2]    | COMOE2 | COM2 Output Enable: `0` = Disable, `1` = Enable |
| [1]    | COMOE1 | COM1 Output Enable: `0` = Disable, `1` = Enable |
| [0]    | COMOE0 | COM0 Output Enable: `0` = Disable, `1` = Enable |

---

### SEGOE1 — LED SEG Output Enable 1 Register (2F01H)

| Bit 7     | Bit 6     | Bit 5     | Bit 4     | Bit 3     | Bit 2     | Bit 1     | Bit 0     |
|-----------|-----------|-----------|-----------|-----------|-----------|-----------|-----------|
| SEGOE1.7  | SEGOE1.6  | SEGOE1.5  | SEGOE1.4  | SEGOE1.3  | SEGOE1.2  | SEGOE1.1  | SEGOE1.0  |
| R/W       | R/W       | R/W       | R/W       | R/W       | R/W       | R/W       | R/W       |

**Initial value: 00H**

| Bit    | Field     | Description            |
|--------|-----------|------------------------|
| [7]    | SEGOE1.7  | SEG7 Output Enable: `0` = Disable, `1` = Enable |
| [6]    | SEGOE1.6  | SEG6 Output Enable: `0` = Disable, `1` = Enable |
| [5]    | SEGOE1.5  | SEG5 Output Enable: `0` = Disable, `1` = Enable |
| [4]    | SEGOE1.4  | SEG4 Output Enable: `0` = Disable, `1` = Enable |
| [3]    | SEGOE1.3  | SEG3 Output Enable: `0` = Disable, `1` = Enable |
| [2]    | SEGOE1.2  | SEG2 Output Enable: `0` = Disable, `1` = Enable |
| [1]    | SEGOE1.1  | SEG1 Output Enable: `0` = Disable, `1` = Enable |
| [0]    | SEGOE1.0  | SEG0 Output Enable: `0` = Disable, `1` = Enable |

---

### SEGOE2 — LED SEG Output Enable 2 Register (2F02H)

| Bit 7     | Bit 6     | Bit 5     | Bit 4     | Bit 3     | Bit 2     | Bit 1     | Bit 0     |
|-----------|-----------|-----------|-----------|-----------|-----------|-----------|-----------|
| SEGOE2.7  | SEGOE2.6  | SEGOE2.5  | SEGOE2.4  | SEGOE2.3  | SEGOE2.2  | SEGOE2.1  | SEGOE2.0  |
| R/W       | R/W       | R/W       | R/W       | R/W       | R/W       | R/W       | R/W       |

**Initial value: 00H**

| Bit    | Field     | Description             |
|--------|-----------|-------------------------|
| [7]    | SEGOE2.7  | SEG15 Output Enable: `0` = Disable, `1` = Enable |
| [6]    | SEGOE2.6  | SEG14 Output Enable: `0` = Disable, `1` = Enable |
| [5]    | SEGOE2.5  | SEG13 Output Enable: `0` = Disable, `1` = Enable |
| [4]    | SEGOE2.4  | SEG12 Output Enable: `0` = Disable, `1` = Enable |
| [3]    | SEGOE2.3  | SEG11 Output Enable: `0` = Disable, `1` = Enable |
| [2]    | SEGOE2.2  | SEG10 Output Enable: `0` = Disable, `1` = Enable |
| [1]    | SEGOE2.1  | SEG9 Output Enable: `0` = Disable, `1` = Enable  |
| [0]    | SEGOE2.0  | SEG8 Output Enable: `0` = Disable, `1` = Enable  |

---

### PRESD — LED Prescale Data Register (2F03H)

| Bit 7   | Bit 6   | Bit 5   | Bit 4   | Bit 3   | Bit 2   | Bit 1   | Bit 0   |
|---------|---------|---------|---------|---------|---------|---------|---------|
| PRESD7  | PRESD6  | PRESD5  | PRESD4  | PRESD3  | PRESD2  | PRESD1  | PRESD0  |
| R/W     | R/W     | R/W     | R/W     | R/W     | R/W     | R/W     | R/W     |

**Initial value: 00H**

| Bits   | Field      | Description |
|--------|------------|-------------|
| [7:0]  | PRESD[7:0] | Prescale value of LED Clock<br>**LED Clock = fCLK / (PRESD + 1)**<br>(fCLK is a selected input clock) |

---

### CSER — LED COM or SEG Enable Register (2F04H)

| Bit 7    | Bit 6    | Bit 5    | Bit 4    | Bit 3    | Bit 2    | Bit 1    | Bit 0    |
|----------|----------|----------|----------|----------|----------|----------|----------|
| CS_SEL7  | CS_SEL6  | CS_SEL5  | CS_SEL4  | CS_SEL3  | CS_SEL2  | CS_SEL1  | CS_SEL0  |
| R/W      | R/W      | R/W      | R/W      | R/W      | R/W      | R/W      | R/W      |

**Initial value: 00H**

| Bit    | Field    | Description |
|--------|----------|-------------|
| [7]    | CS_SEL7  | Select COM7/SEG7: `0` = Select SEG7, `1` = Select COM7 |
| [6]    | CS_SEL6  | Select COM6/SEG6: `0` = Select SEG6, `1` = Select COM6 |
| [5]    | CS_SEL5  | Select COM5/SEG5: `0` = Select SEG5, `1` = Select COM5 |
| [4]    | CS_SEL4  | Select COM4/SEG4: `0` = Select SEG4, `1` = Select COM4 |
| [3]    | CS_SEL3  | Select COM3/SEG3: `0` = Select SEG3, `1` = Select COM3 |
| [2]    | CS_SEL2  | Select COM2/SEG2: `0` = Select SEG2, `1` = Select COM2 |
| [1]    | CS_SEL1  | Select COM1/SEG1: `0` = Select SEG1, `1` = Select COM1 |
| [0]    | CS_SEL0  | Select COM0/SEG0: `0` = Select SEG0, `1` = Select COM0 |

---

### COMPWID — LED COM Pulse Width Control Register (2F05H)

| Bit 7     | Bit 6     | Bit 5     | Bit 4     | Bit 3     | Bit 2     | Bit 1     | Bit 0     |
|-----------|-----------|-----------|-----------|-----------|-----------|-----------|-----------|
| COMPWID7  | COMPWID6  | COMPWID5  | COMPWID4  | COMPWID3  | COMPWID2  | COMPWID1  | COMPWID0  |
| R/W       | R/W       | R/W       | R/W       | R/W       | R/W       | R/W       | R/W       |

**Initial value: 00H**

| Bits   | Field        | Description |
|--------|--------------|-------------|
| [7:0]  | COMPWID[7:0] | Maximum Pulse width for COM<br>**COM Width = LED CLK / (COMPWID + 1)**<br>(LED CLK is a Prescaler output clock) |

---

### STPD0 — LED Stop Duration 0 Register (2F0AH)

| Bit 7  | Bit 6  | Bit 5  | Bit 4  | Bit 3  | Bit 2  | Bit 1  | Bit 0  |
|--------|--------|--------|--------|--------|--------|--------|--------|
| STPD7  | STPD6  | STPD5  | STPD4  | STPD3  | STPD2  | STPD1  | STPD0  |
| R/W    | R/W    | R/W    | R/W    | R/W    | R/W    | R/W    | R/W    |

**Initial value: 00H**

---

### STPD1 — LED Stop Duration 1 Register (2F0BH)

| Bit 7   | Bit 6   | Bit 5   | Bit 4   | Bit 3   | Bit 2  | Bit 1  | Bit 0  |
|---------|---------|---------|---------|---------|--------|--------|--------|
| STPD15  | STPD14  | STPD13  | STPD12  | STPD11  | STPD10 | STPD9  | STPD8  |
| R/W     | R/W     | R/W     | R/W     | R/W     | R/W    | R/W    | R/W    |

**Initial value: 00H**

---

### STPD2 — LED Stop Duration 2 Register (2F0CH)

| Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3   | Bit 2   | Bit 1   | Bit 0   |
|-------|-------|-------|-------|---------|---------|---------|---------|
| —     | —     | —     | —     | STPD19  | STPD18  | STPD17  | STPD16  |
| —     | —     | —     | —     | R/W     | R/W     | R/W     | R/W     |

**Initial value: 00H**

| Bits    | Field       | Description |
|---------|-------------|-------------|
| [19:0]  | STPD[19:0]  | LED stop duration. Valid in LED Stop Count mode or Smart Share mode.<br>**LED Stop Duration Width = fCLK / (STPD + 1)**<br>(fCLK is a selected input clock) |

---

### LEDSR — LED Status Register (2F0DH)

| Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3  | Bit 2   | Bit 1    | Bit 0    |
|-------|-------|-------|-------|--------|---------|----------|----------|
| —     | —     | —     | —     | MATCHF | LED_INT | LED_INTE | LED_ENDF |
| —     | —     | —     | —     | R/W    | R/W     | R/W      | R/W      |

**Initial value: 01H**

| Bit    | Field    | Description |
|--------|----------|-------------|
| [3]    | MATCHF   | Set when the internal counter value matches the STPD register. Cleared automatically after LED display.<br>`0` = Unmatched, `1` = Matched |
| [2]    | LED_INT  | LED Interrupt flag when LED_INTE is set.<br>`0` = LED interrupt not generated, `1` = LED interrupt generated |
| [1]    | LED_INTE | LED Interrupt Enable.<br>`0` = Disable, `1` = Enable |
| [0]    | LED_ENDF | LED Operation Flag.<br>`0` = Under LED Operation, `1` = LED Operation is ended |

---

### LEDCON3 — LED Control 3 Register (2F0EH)

| Bit 7      | Bit 6      | Bit 5      | Bit 4      | Bit 3      | Bit 2      | Bit 1      | Bit 0      |
|------------|------------|------------|------------|------------|------------|------------|------------|
| SET_TIME3  | SET_TIME2  | SET_TIME1  | SET_TIME0  | CLR_TIME3  | CLR_TIME2  | CLR_TIME1  | CLR_TIME0  |
| R/W        | R/W        | R/W        | R/W        | R/W        | R/W        | R/W        | R/W        |

**Initial value: 00H**

#### SET_TIME[3:0] — SEG GND Start Position

Valid only when SRTEN (LEDCON2[3]) is High. fCLK = 16 MHz

| Value | Delay |
|-------|-------|
| 0000  | 1 us  |
| 0001  | 2 us  |
| 0010  | 4 us  |
| 0011  | 6 us  |
| 0100  | 8 us  |
| 0101  | 10 us |
| 0110  | 12 us |
| 0111  | 14 us |
| 1000  | 16 us |
| 1001  | 18 us |
| 1010  | 20 us |
| 1011  | 22 us |
| 1100  | 24 us |
| 1101  | 26 us |
| 1110  | 28 us |
| 1111  | 32 us |

#### CLR_TIME[3:0] — SEG GND End Position

Valid only when SRTEN (LEDCON2[3]) is High. fCLK = 16 MHz.
OVERTS is bit[6:4] of LEDCON2.

| Value | Delay          |
|-------|----------------|
| 0000  | OVERTS − 1 us  |
| 0001  | OVERTS − 2 us  |
| 0010  | OVERTS − 4 us  |
| 0011  | OVERTS − 6 us  |
| 0100  | OVERTS − 8 us  |
| 0101  | OVERTS − 10 us |
| 0110  | OVERTS − 12 us |
| 0111  | OVERTS − 14 us |
| 1000  | OVERTS − 16 us |
| 1001  | OVERTS − 18 us |
| 1010  | OVERTS − 20 us |
| 1011  | OVERTS − 22 us |
| 1100  | OVERTS − 24 us |
| 1101  | OVERTS − 26 us |
| 1110  | OVERTS − 28 us |
| 1111  | OVERTS − 32 us |

---

### LEDCON2 — LED Control 2 Register (2F0FH)

| Bit 7   | Bit 6    | Bit 5    | Bit 4    | Bit 3 | Bit 2 | Bit 1 | Bit 0 |
|---------|----------|----------|----------|-------|-------|-------|-------|
| OVERLAP | OVERTS2  | OVERTS1  | OVERTS0  | SRTEN | —     | —     | —     |
| R/W     | R/W      | R/W      | R/W      | R/W   | —     | —     | —     |

**Initial value: 00H**

| Bit    | Field       | Description |
|--------|-------------|-------------|
| [7]    | OVERLAP     | How to make Overlap Time<br>`0` = Overlap time = 3 us ~ 64 us @ fCLK = 16 MHz<br>`1` = Overlap time = fCLK/2 |
| [6:4]  | OVERTS[2:0] | Overlap Time Select (valid only when OVERLAP = 0)<br>`000` = 64 us, `001` = 32 us, `010` = 24 us, `011` = 21 us<br>`100` = 12 us, `101` = 9 us, `110` = 6 us, `111` = 3 us |
| [3]    | SRTEN       | SEG GND Select: `0` = Non-select, `1` = Select |

---

### LEDCON1 — LED Control 1 Register (2F10H)

| Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 |
|-------|-------|-------|-------|-------|-------|-------|-------|
| —     | —     | —     | MD2   | MD1   | MD0   | LEDEN | LEDST |
| —     | —     | —     | R/W   | R/W   | R/W   | R/W   | R/W   |

**Initial value: 00H**

| Bit    | Field     | Description |
|--------|-----------|-------------|
| [4:2]  | MD[2:0]   | Mode Select<br>`000` = LED Auto Mode<br>`001` = Hand Shake Mode<br>`010` = LED Stop Count Mode<br>`011` = Smart Share Mode<br>`1xx` = LED Alone Mode |
| [1]    | LEDEN     | LED Enable: `0` = LED Disable, `1` = LED Enable |
| [0]    | LEDST     | LED Start or Stop (under LEDEN = 1)<br>`0` = Stop LED Operation, `1` = Start LED Operation |

---

### CCLSR — Constant Current Level Select Register (2F30H)

| Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 |
|-------|-------|-------|-------|-------|-------|-------|-------|
| —     | —     | —     | —     | —     | —     | COA1  | COA0  |
| —     | —     | —     | —     | —     | —     | R/W   | R/W   |

**Initial value: 01H**

| COA[1:0] | SEG Current |
|----------|-------------|
| 00       | 8.66 mA     |
| 01       | 13.22 mA *(default)* |
| 10       | 19.49 mA    |
| 11       | 22.06 mA    |

---

### TEST_COM — TEST COM Register for Test (2F7CH)

| Bit 7  | Bit 6  | Bit 5  | Bit 4  | Bit 3  | Bit 2  | Bit 1  | Bit 0  |
|--------|--------|--------|--------|--------|--------|--------|--------|
| TCOM7  | TCOM6  | TCOM5  | TCOM4  | TCOM3  | TCOM2  | TCOM1  | TCOM0  |
| R/W    | R/W    | R/W    | R/W    | R/W    | R/W    | R/W    | R/W    |

**Initial value: 00H**

---

### TEST_SEG0 — TEST SEG Low Byte Register for Test (2F7DH)

| Bit 7   | Bit 6   | Bit 5   | Bit 4   | Bit 3   | Bit 2   | Bit 1   | Bit 0   |
|---------|---------|---------|---------|---------|---------|---------|---------|
| TSEG07  | TSEG06  | TSEG05  | TSEG04  | TSEG03  | TSEG02  | TSEG01  | TSEG00  |
| R/W     | R/W     | R/W     | R/W     | R/W     | R/W     | R/W     | R/W     |

**Initial value: 00H**

---

### TEST_SEG1 — TEST SEG High Byte Register for Test (2F7EH)

| Bit 7   | Bit 6   | Bit 5   | Bit 4   | Bit 3   | Bit 2   | Bit 1   | Bit 0   |
|---------|---------|---------|---------|---------|---------|---------|---------|
| TSEG17  | TSEG16  | TSEG15  | TSEG14  | TSEG13  | TSEG12  | TSEG11  | TSEG10  |
| R/W     | R/W     | R/W     | R/W     | R/W     | R/W     | R/W     | R/W     |

**Initial value: 00H**

---

## 15.5 LED RAM

**Table 38. LED RAM**

| Address | Name  | bit7/15 | bit6/14 | bit5/13 | bit4/12 | bit3/11 | bit2/10 | bit1/9 | bit0/8 |
|---------|-------|---------|---------|---------|---------|---------|---------|--------|--------|
| 2F13H   | COM0L | SEG7    | SEG6    | SEG5    | SEG4    | SEG3    | SEG2    | SEG1   | —      |
| 2F14H   | COM0H | SEG15   | SEG14   | SEG13   | SEG12   | SEG11   | SEG10   | SEG9   | SEG8   |
| 2F15H   | COM1L | SEG7    | SEG6    | SEG5    | SEG4    | SEG3    | SEG2    | —      | SEG0   |
| 2F16H   | COM1H | SEG15   | SEG14   | SEG13   | SEG12   | SEG11   | SEG10   | SEG9   | SEG8   |
| 2F17H   | COM2L | SEG7    | SEG6    | SEG5    | SEG4    | SEG3    | —       | SEG1   | SEG0   |
| 2F18H   | COM2H | SEG15   | SEG14   | SEG13   | SEG12   | SEG11   | SEG10   | SEG9   | SEG8   |
| 2F19H   | COM3L | SEG7    | SEG6    | SEG5    | SEG4    | —       | SEG2    | SEG1   | SEG0   |
| 2F1AH   | COM3H | SEG15   | SEG14   | SEG13   | SEG12   | SEG11   | SEG10   | SEG9   | SEG8   |
| 2F1BH   | COM4L | SEG7    | SEG6    | SEG5    | —       | SEG3    | SEG2    | SEG1   | SEG0   |
| 2F1CH   | COM4H | SEG15   | SEG14   | SEG13   | SEG12   | SEG11   | SEG10   | SEG9   | SEG8   |
| 2F1DH   | COM5L | SEG7    | SEG6    | —       | SEG4    | SEG3    | SEG2    | SEG1   | SEG0   |
| 2F1EH   | COM5H | SEG15   | SEG14   | SEG13   | SEG12   | SEG11   | SEG10   | SEG9   | SEG8   |
| 2F1FH   | COM6L | SEG7    | —       | SEG5    | SEG4    | SEG3    | SEG2    | SEG1   | SEG0   |
| 2F20H   | COM6H | SEG15   | SEG14   | SEG13   | SEG12   | SEG11   | SEG10   | SEG9   | SEG8   |
| 2F21H   | COM7L | —       | SEG6    | SEG5    | SEG4    | SEG3    | SEG2    | SEG1   | SEG0   |
| 2F22H   | COM7H | SEG15   | SEG14   | SEG13   | SEG12   | SEG11   | SEG10   | SEG9   | SEG8   |

> **Note:** `—` means no affect to SEG output

---

## 15.6 Example Circuit

### 15.6.1 T-Type Matrix

> **Figure 106. T-Type Matrix** *(refer to original datasheet)*

---

### 15.6.2 M-Type Matrix

> **Figure 107. M-Type Matrix** *(refer to original datasheet)*

---

### 15.6.3 Circuit for LED and Touch by Common Pin

When implementing touch and LED functions on a common pin by time-division, the touch sensitivity may be very poor due to the parasitic capacitance caused by LED matrix structure. This problem can be minimized by adding a diode in front of the LED matrix. Refer to the diode's capacitance specification, and select a diode less than 4 pF. It is recommended to use the following circuit and diodes.

> **Figure 108. Circuit for LED and Touch by common pin** *(refer to original datasheet)*

**Table 39. Recommended Diodes**

| No | IC-NAME       | Vendor      | Capacitance |
|----|---------------|-------------|-------------|
| 1  | 1N4148-B      | RECTRON     | 4 pF        |
| 2  | 1N4148W       | TAIWAN SEMI | 4 pF        |
| 3  | 1N4148W-7-F   | DIODES      | 2 pF        |
| 4  | 1N4148W-E3-08 | VISHAY      | 4 pF        |
| 5  | 1N4148W-G3-18 | VISHAY      | 4 pF        |
| 6  | 1N4148WS      | ON SEMI     | 4 pF        |
| 7  | 1N4148WSF-7   | DIODES      | 1.5 pF      |

---

## 15.7 Mode Functions

By depending on how set MD values (LEDCON1[4:2]), there are five operation modes.

> **Prerequisite:** All modes below require LEDEN (LEDCON1[1]) = `1` before operation.

---

### 15.7.1 LED Auto Mode

LED Auto Mode operates independently from the touch sensing function. LED starts when `1` is written to LEDST.

- When LEDST is set `1` (point **A**), LED operates continuously.
- An interrupt occurs at point **B** where the LED 1-frame operation ends (when LED_INTE is set).
- Overlap time **(k)** between consecutive COM outputs is controllable by the program.

> **Figure 109. LED Auto Mode** *(CSER = 0100_0001B, refer to original datasheet)*

---

### 15.7.2 LED Alone Mode

LED Alone Mode operates independently from the touch sensing function. LED can be restarted by writing `1` to LEDST.

- An interrupt occurs at point **A** where the LED operation ends (when LED_INTE is set).
- When LEDST is rewritten `1` (point **B**), LED starts again.
- Overlap time **(k)** between consecutive COM outputs is controllable by the program.

> **Figure 110. LED Alone Mode** *(CSER = 0100_0001B, refer to original datasheet)*

---

### 15.7.3 Hand Shake Mode

Hand Shake Mode informs the touch sensing when LED is finished and restarts LED when the TOUCH_END signal is received from the touch sensing.

- Frame cycle = LED operation time **(1)** + touch key scan time **(2)** — the minimum cycle without flicker.
- An interrupt occurs at point **A** where the LED operation ends (when LED_INTE is set).
- Touch sensing continues to send `1` until LED_ENDF changes to `0` at point **(B)**, after which LED starts again.

> **Figure 111. Hand Shake Mode** *(CSER = 0000_0001B, refer to original datasheet)*

---

### 15.7.4 LED Stop Count Mode

LED Stop Count Mode determines the start of the next LED operation based on the LED stop duration register (STPD) value after the previous LED operation ends.

- Used to define the frame period that prevents LED flicker.
- An interrupt occurs at point **A** when the LED operation ends (when LED_INTE is set).
- At the same time, a 20-bit counter starts incrementing.
- When the 20-bit counter matches LEDSTPD:
  - MATCHF (LEDSR[3]) is set to `1`
  - LED_ENDF is cleared to `0`
  - The 20-bit counter is cleared to `0`
  - LED starts again (point **B**)

> **Figure 112. LED Stop Count Mode** *(CSER = 1000_0000B, refer to original datasheet)*

---

### 15.7.5 Smart Share Mode

Smart Share Mode prevents the next LED operation from starting until the current pending touch key scan ends, even after MATCHF (LEDSR[3]) is generated following the previous LED operation end.

- Used to execute as many touch key scans as possible during the touch scan time.
- An interrupt occurs at point **A** when the LED operation ends (when LED_INTE is set).
- The 20-bit counter starts incrementing, and when it matches the STPD register, MATCHF (LEDSR[3]) is set to `1`.
- LED_ENDF cannot clear to `0` and LED cannot restart until the TOUCH_END signal from the touch sensing becomes active (point **B**).

> **Note:** If no more LED display is needed, it is highly recommended to set LEDEN (LEDCON1[1]) = `0` between the end of LED operation **(A)** and LED restart **(B)** to prevent flicker.

> **Figure 113. Smart Share Mode** *(CSER = 1000_0000B, refer to original datasheet)*

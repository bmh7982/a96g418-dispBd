# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

Bare-metal embedded C firmware for the **ABOV A96T418 (A31T418GDN)** 8-bit MCS-51 microcontroller, intended as a display board controller. Based on `Example_STKS-A96T418-GDN-TOUCH-A V1.0.9 (2024-07-12)`.

## Build System

**Keil µVision IDE only** — there is no Makefile or CLI build. To build:

1. Open `application/keil/a96t418_application.uvproj` in Keil µVision
2. Build with `Project → Build Target` (F7)
3. Output hex file: `application/keil/out/t418code.hex`

No automated test suite exists. Verification is done via hardware + UART serial debug at 500 kbps.

## Architecture

### Task Scheduler (`application/source/main.c`)

Main loop cycles through 4 tasks in round-robin order:

```
TASK_LED → TASK_TOUCH → TASK_GESTURE → TASK_DEBUG → (repeat)
```

No RTOS. LED multiplexing and touch sensing are interrupt-driven (Timer 1/2); task loop handles non-time-critical work.

### Configuration (`application/source/user_function.h`)

All feature flags live here. Current settings:

| Macro | Value | Purpose |
|---|---|---|
| `LED_DRV_EN` | 1 | LED COM/SEG matrix driver |
| `UART_ENABLE` | 1 | UART debug at 500 kbps |
| `I2C_ENABLE` | 0 | I2C register-map debug (disabled) |
| `WDT_ENABLE` | 1 | 4-second watchdog reset |
| `TOUCH_FREQ_SEL_EN` | 1 | Frequency hopping for touch |
| `HOLD_KEY_RELEASE` | 1 | Auto-release after 10 s hold |
| `FIRST_KEY_PRIORITY` | 0 | First-key priority (disabled) |
| `MULTI_KEY_RESET` | 0 | Multi-key reset (disabled) |

LED matrix: 8 COM lines × 16 SEG lines (all enabled). Touch: up to 20 channels.

### Directory Structure

```
application/
├── source/     # Application logic (main.c, user_function.h, led_driver.c, debug.c, touch_config.c, ...)
├── driver/     # HAL drivers for GPIO, Timer1/2, UART, I2C, WDT, clock, delay
├── library/    # Compiled touch sensor library (library_touch_V109_20240705.LIB) + headers
└── keil/       # Keil project files; out/ = build artifacts, list/ = assembly listings
```

The `driver/` files were sourced from Example_STKS. Note: `a96T418_usi_i2c.c/.h` and `a96T418_wdt.c/.h` differ significantly from the ABOV Example_Code V1.01 baseline.

### Key Source Files

- `source/main.c` — init sequence and main task loop
- `source/user_function.h` — **all feature toggles and LED/touch parameters**
- `source/user_function.c` — `Touch_Key_Scenario()`, `Touch_Freq_Sel()`
- `source/led_driver.c/.h` — LED matrix time-division multiplexing
- `source/debug.c/.h` — UART/I2C packet protocol with checksum
- `source/touch_config.c/.h` — touch channel configuration passed to the binary library
- `source/user_timer.c/.h` — software timer management
- `source/common.h` — `struct sys_flag g_sys_flag` and shared flags
- `source/A96T418.h` — SFR (Special Function Register) definitions for the MCU

### Interrupt Architecture

| Vector | Source | Handler | Location |
|---|---|---|---|
| `T0_MATCH_VECT` | Timer0 (1 ms tick) | `Timer0_ISR` | `user_timer.c` |
| `LED_VECT` | LED scan complete | `LED_ISR` | `led_driver.c` |
| `TOUCH_VECT` | Touch sensing complete | `TOUCH_IRQHandler` | `touch_config.c` |
| `USI0_RX_VECT` | UART RX | `USI0RX_ISR` | `debug.c` |
| `USI0_TX_VECT` | UART TX | `USI0TX_ISR` | `debug.c` |

Touch sensing end is polled via `ts.flag.touch_sensing_end` in the main loop.

## Coding Constraints (MCS-51 / 8-bit)

- **File encoding**: all source files must be saved in **EUC-KR** encoding
- **No dynamic memory**: `malloc` / `free` are forbidden — no heap
- **No recursion**: stack is only tens of bytes
- **No floating point**: no FPU; software emulation is too slow
- **Keil memory qualifiers**: use `idata` (internal RAM), `xdata` (external RAM), `code` (ROM flash) where appropriate
- **`uint32_t` atomicity**: 8-bit MCU requires multiple cycles for 32-bit operations — not atomic in ISR context; protect with interrupt disable/enable (`IE2`)

## ⚠️ Do Not Modify — Intentional Patterns

These patterns look like bugs but are deliberate. Do not "fix" them without explicit instruction.

- **`EA = 1` inside ISRs** (`LED_ISR`, `Timer0_ISR`, `TOUCH_IRQHandler`): re-enables global interrupts to allow nested interrupts. Required for correct time-division operation between LED and touch. Do not remove.
- **`TASK_TOUCH` fall-through to `TASK_GESTURE`** (`main.c:236`): the missing `break` after `case TASK_TOUCH` is intentional — when gesture is enabled, gesture processing runs immediately after touch in the same cycle. Do not add a `break`.
- **`#if (FLAG_A | FLAG_B) == 1` pattern**: bitwise OR of 0/1 feature flags then compare to 1 is the project convention for "at least one flag is enabled." Do not change to logical OR (`||`).

## Known Issues

현재 미해결 이슈 없음.

### 해결된 이슈 이력

| Location | Description | Status |
|---|---|---|
| `debug.c:88-94` | Case 3 (9600 bps) divisor `51` → `207` 수정 | ✅ Fixed |
| `debug.c:281` | `rx_data_idx` 경계 검사 추가 | ✅ Fixed |
| `user_timer.c:273` | `if((ut_slide_event_hold_timer == 0)` 괄호 — 현재 코드에서 정상 확인 | ✅ Verified |
| `led_driver.c:224` | `digit[]` 인덱스 0–9 클램핑 추가 | ✅ Fixed |
| `a96T418_wdt.c:38-61` | `WDT_Initial()` dead code — `main.c`에서 호출 제거 | ✅ Fixed |

## Feature Activation Requirements

| Feature Flag | Additional Work Required |
|---|---|
| `SLIDE_FUNCTION_EN=1` | Add `gesture.c` / `gesture.h` |
| `WHEEL_FUNCTION_EN=1` | Add `gesture.c` / `gesture.h` |
| `UL60730_SELF_TEST_EN=1` | Add `UL60730_user_V01.h` and the separate UL60730 library |
| `I2C_ENABLE=1` | Usable standalone or alongside `UART_ENABLE` |

## LED / Touch Parameter Modification

- **LED COM/SEG lines**: edit only `COMxx_EN` / `SEGxx_EN` macros in `user_function.h`.
  The derived macros (`P*_COM_IO`, `P*_SEG_IO`, `COMSEL_*`, `SEGSEL_*`) are auto-calculated — do not edit them directly.
- **Touch thresholds**: edit `TS_CH_CFG[ch][THRESHOLD]` in `touch_config.h`
- **Hold-key release time**: `TIMER_HOLD_KEY_RELEASE` in `user_function.h` (unit: ms)

## UART Debug Protocol (500 kbps)

**TX (firmware → PC):** `3A | LEN | 00 10 | KEY | CYCLE | DATA... | CHECKSUM(2B) | 0D 0A`

**RX (PC → firmware):** `02 | CMD | MSG... | 03`
- CMD `'R'` (0x52): data request — sets `mask`, `start_idx`, `ch_cnt` in `dbg`

## Notes

- Touch sensing uses a pre-compiled binary library (`library/library_touch_V109_20240705.LIB`); its internals are not modifiable.
- `TS_LED_TIME_DIV=1` means touch and LED share timer time-slicing; LED active time = 10 ms, touch active time = 5 ms.
- UL60730 safety self-test is disabled (`UL60730_SELF_TEST_EN=0`) and requires a separate library if enabled.
- Gesture functions (slide/wheel) are disabled; enabling them requires adding `gesture.c/.h`.
- WDT is kicked only in `TASK_TOUCH` (`WDT_ClearCountData()`); the round-robin loop must complete within 4 seconds or the MCU resets.

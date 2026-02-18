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

- **Timer interrupt** — drives LED scan and triggers touch sensing cycle
- **UART RX interrupt** — buffered receive for debug packets
- Touch sensing end is polled via `ts.flag.touch_sensing_end` in the main loop

## Notes

- Touch sensing uses a pre-compiled binary library (`library/library_touch_V109_20240705.LIB`); its internals are not modifiable.
- `TS_LED_TIME_DIV=1` means touch and LED share timer time-slicing; LED active time = 10 ms, touch active time = 5 ms.
- UL60730 safety self-test is disabled (`UL60730_SELF_TEST_EN=0`) and requires a separate library if enabled.
- Gesture functions (slide/wheel) are disabled; enabling them requires adding `gesture.c/.h`.

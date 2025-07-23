# LCDShiftView

Control HD44780-compatible LCD displays using a 74HC595 shift register on Arduino with flexible pin mapping and full feature access.

---

##  Overview

`LCDShiftView` is a lightweight and flexible Arduino library that allows you to control LCD displays (based on the HD44780 controller) using only **one shift register (74HC595)**. This helps reduce the number of I/O pins required while still giving you full control over the LCD including:

- Custom character support
- Backlight control
- Cursor and display control
- Flexible mapping of LCD pins to any shift register output (S0–S7)

---

##  Features

- Supports 16x2, 20x4, and other standard HD44780 LCDs
- Assign any LCD pin (RS, E, D4–D7, Backlight) to any shift register output
- Control LCD with just 3 Arduino pins (Data, Clock, Latch)
- Fully compatible with the official `LiquidCrystal` API
- Supports custom characters and symbols
- Open-source and easy to extend

---

##  Wiring Example

**LCD** connected to **74HC595**:

| LCD Pin | Description | Connect to 74HC595 |
|---------|-------------|--------------------|
| RS      | Register Select | S0 |
| E       | Enable           | S1 |
| D4      | Data Bit 4       | S2 |
| D5      | Data Bit 5       | S3 |
| D6      | Data Bit 6       | S4 |
| D7      | Data Bit 7       | S5 |
| BL      | Backlight (optional) | S6 |

**Shift Register (74HC595)** connected to Arduino:

| 74HC595 Pin | Connect to Arduino |
|-------------|--------------------|
| DS          | Data pin (e.g., 8) |
| SHCP        | Clock pin (e.g., 12) |
| STCP        | Latch pin (e.g., 10) |

*You can change all pin assignments in code.*

---

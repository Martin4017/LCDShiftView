# LCDShiftView

`LCDShiftView` is an Arduino library that allows you to control standard HD44780-based LCD displays using a single 74HC595 shift register. This helps you save precious I/O pins and gives you full flexibility to define which shift register outputs are connected to which LCD pins.

---

## Features

- Control LCD (16x2, 20x4...) via **shift register (74HC595)**.
- Define any pin mapping from the shift register (Q0–Q6) to LCD pins.
- Default mapping is:
  - RS → Q0
  - E   → Q1
  - D4 → Q2
  - D5 → Q3
  - D6 → Q4
  - D7 → Q5
- Built-in support for:
  - Custom characters.
  - Different LCD sizes.
  - Clear and easy API similar to LiquidCrystal.

---

## Installation

### Via Library Manager

1. Open **Arduino IDE**.
2. Go to **Sketch → Include Library → Manage Libraries**.
3. Search for **LCDShiftView**.
4. Click **Install**.

### Manual Installation

1. Download the library from GitHub:  
   [https://github.com/Martin4017/LCDShiftView/releases/tag/1.0.1](https://github.com/Martin4017/LCDShiftView/releases/tag/1.0.1)
2. Extract the `.zip` file.
3. Move the folder to `Documents/Arduino/libraries/`.

---

## Wiring Example

| LCD Pin | Connected to Shift Register Pin |
|---------|---------------------------------|
| RS      | Q0                              |
| E       | Q1                              |
| D4      | Q2                              |
| D5      | Q4                              |
| D6      | Q5                              |
| D7      | Q6                              |
| A       | Q8  (Backlight pin (Optional))  | 

**Shift register inputs:**

- **SER (data)** → Arduino pin 12
- **SRCLK (clock)** → Arduino pin 11
- **RCLK (latch)** → Arduino pin 10

---

## Quick Start Example

```cpp
#include <LCDShiftView.h>

// Shift Register Pins: data, clock, latch
LCDShiftView lcd(2, 3, 4); 

void setup() {
  lcd.begin(16, 2);       // Set LCD size (columns, rows)
  lcd.print("Hello, World!");
}

void loop() {}
```

---

## Custom Pin Mapping (Optional)

If your LCD is wired differently, use setPins():

```cpp
lcd.setPins(0, 1, 2, 3, 4, 5);
// RS, E, D4, D5, D6, D7 (Q0–Q6 are valid) Q7 is Backlight pin. "cannot be change"
```

---

## Custom Characters Example

```cpp
#include <LCDShiftView.h>

byte smiley[8] = {
  B00000,
  B01010,
  B01010,
  B00000,
  B00000,
  B10001,
  B01110,
  B00000
};

void setup() {
  lcd.begin(16, 2);
  lcd.createChar(0, smiley);
  lcd.setCursor(0, 0);
  lcd.write(byte(0));
}
```

---

## Example Sketches

The library comes with example sketches to help you get started.
You can find them under:

File → Examples → LCDShiftView

---

## License

This library is released under the MIT License.  
Feel free to use, modify, and distribute.

---

## Author

Made by Martin4017

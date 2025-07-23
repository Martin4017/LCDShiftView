/*
  LCDShiftView Library - Autoscroll

 Demonstrates the use a 16x2 LCD display.  The LCDShiftView
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch demonstrates the use of the autoscroll()
 and noAutoscroll() functions to make new text scroll or not.

 The circuit: 
 * 74HC595 DS pin to D10
 * 74HC595 SHCP pin to D11
 * 74HC595 STCP pin to D12
 * 74HC595 MR pin to +5V

 * LCD RS pin to Q0 of 74HC595
 * LCD E  pin to Q1 of 74HC595
 * LCD D4 pin to Q2 of 74HC595
 * LCD D5 pin to Q3 of 74HC595
 * LCD D6 pin to Q4 of 74HC595
 * LCD D7 pin to Q5 of 74HC595
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 23 Jul 2025
 by Martin
 example added 23 Jul 2025
 by Martin
 
*/

// include the library code:
#include <LCDShiftView.h>

const int dataPin  = 10; // DS connected to pin D10 on Arduino 
const int clockPin = 11; // SHCP connected to pin D11 on Arduino
const int latchPin = 12; // STCP connected to pin D12 on Arduino

LCDShiftView lcd(dataPin, clockPin, latchPin); pin out of 74HC595

// setPins(0, 1, 2, 3, 4, 5)   // Use This command to change the defalt pin connection of LCD
//       (RS, E, D4, D5, D6, D7)

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
}

void loop() {
  // set the cursor to (0,0):
  lcd.setCursor(0, 0);
  // print from 0 to 9:
  for (int thisChar = 0; thisChar < 10; thisChar++) {
    lcd.print(thisChar);
    delay(500);
  }

  // set the cursor to (16,1):
  lcd.setCursor(16, 1);
  // set the display to automatically scroll:
  lcd.autoscroll();
  // print from 0 to 9:
  for (int thisChar = 0; thisChar < 10; thisChar++) {
    lcd.print(thisChar);
    delay(500);
  }
  // turn off automatic scrolling
  lcd.noAutoscroll();

  // clear screen for the next loop:
  lcd.clear();
}


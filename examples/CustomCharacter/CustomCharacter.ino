/*
  LCDSiftView Library - Custom Characters

 Demonstrates how to add custom characters on an LCD  display.
 The LCDSiftView library works with all LCD displays that are
 compatible with the  Hitachi HD44780 driver. There are many of
 them out there, and you can usually tell them by the 16-pin interface.

 This sketch prints "I <heart> Arduino!" and a little dancing man
 to the LCD.

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

// make some custom characters:
byte heart[8] = {
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000
};

byte smiley[8] = {
  0b00000,
  0b00000,
  0b01010,
  0b00000,
  0b00000,
  0b10001,
  0b01110,
  0b00000
};

byte frownie[8] = {
  0b00000,
  0b00000,
  0b01010,
  0b00000,
  0b00000,
  0b00000,
  0b01110,
  0b10001
};

byte armsDown[8] = {
  0b00100,
  0b01010,
  0b00100,
  0b00100,
  0b01110,
  0b10101,
  0b00100,
  0b01010
};

byte armsUp[8] = {
  0b00100,
  0b01010,
  0b00100,
  0b10101,
  0b01110,
  0b00100,
  0b00100,
  0b01010
};

void setup() {
  // initialize LCD and set up the number of columns and rows:
  lcd.begin(16, 2);

  // create a new character
  lcd.createChar(0, heart);
  // create a new character
  lcd.createChar(1, smiley);
  // create a new character
  lcd.createChar(2, frownie);
  // create a new character
  lcd.createChar(3, armsDown);
  // create a new character
  lcd.createChar(4, armsUp);

  // set the cursor to the top left
  lcd.setCursor(0, 0);

  // Print a message to the lcd.
  lcd.print("I ");
  lcd.write(byte(0)); // when calling lcd.write() '0' must be cast as a byte
  lcd.print(" Arduino! ");
  lcd.write((byte)1);

}

void loop() {
  // read the potentiometer on A0:
  int sensorReading = analogRead(A0);
  // map the result to 200 - 1000:
  int delayTime = map(sensorReading, 0, 1023, 200, 1000);
  // set the cursor to the bottom row, 5th position:
  lcd.setCursor(4, 1);
  // draw the little man, arms down:
  lcd.write(3);
  delay(delayTime);
  lcd.setCursor(4, 1);
  // draw him arms up:
  lcd.write(4);
  delay(delayTime);
}

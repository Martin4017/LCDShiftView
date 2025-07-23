#include "LCDShiftView.h"

#define RS_BIT 0
#define E_BIT  1
#define D4_BIT 2
#define D5_BIT 3
#define D6_BIT 4
#define D7_BIT 5

#define LCD_4BITMODE 0x00
#define LCD_1LINE 0x00
#define LCD_2LINE 0x08
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

LCDShiftView::LCDShiftView(uint8_t dataPin, uint8_t clockPin, uint8_t latchPin)
  : _dataPin(dataPin), _clockPin(clockPin), _latchPin(latchPin), _state(0),
    _displayfunction(0x00), _displayControl(0x00), _displayMode(0x00), _numlines(1) {}

void LCDShiftView::begin(uint8_t cols, uint8_t rows, uint8_t charsize) {
    pinMode(_dataPin, OUTPUT);
    pinMode(_clockPin, OUTPUT);
    pinMode(_latchPin, OUTPUT);

    if (!_customPinsSet) {
        _rsPin = 0;
        _ePin  = 1;
        _d4Pin = 2;
        _d5Pin = 3;
        _d6Pin = 4;
        _d7Pin = 5;
    }

    _rows = rows;
    _cols = cols;
    _displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x10DOTS;

    _rowOffsets[0] = 0x00;
    _rowOffsets[1] = 0x40;
    _rowOffsets[2] = 0x00 + cols;
    _rowOffsets[3] = 0x40 + cols;

    _backlightState = true;
    _shiftOut(_currentValue);

    _displayfunction = 0x00;
    if (rows > 1) _displayfunction |= LCD_2LINE;
    if (charsize != 0 && rows == 1) _displayfunction |= 0x04;

    delayMicroseconds(50000);
    _write4Bits(0x03);
    delayMicroseconds(4500);
    _write4Bits(0x03);
    delayMicroseconds(4500);
    _write4Bits(0x03);
    delayMicroseconds(150);
    _write4Bits(0x02);

    command(0x20 | _displayfunction);

    _displayControl = 0x04;
    display();
    clear();

    _displayMode = 0x02;
    command(0x04 | _displayMode);
    _numlines = rows;
}

void LCDShiftView::clear() {
    command(0x01);
    delayMicroseconds(2000);
}

void LCDShiftView::home() {
    command(0x02);
    delayMicroseconds(2000);
}

void LCDShiftView::setCursor(uint8_t col, uint8_t row) {
    if (row >= _numlines) row = _numlines - 1;
    command(0x80 | (col + _rowOffsets[row]));
}

void LCDShiftView::noDisplay() {
    _displayControl &= ~0x04;
    command(0x08 | _displayControl);
}

void LCDShiftView::display() {
    _displayControl |= 0x04;
    command(0x08 | _displayControl);
}

void LCDShiftView::noBlink() {
    _displayControl &= ~0x01;
    command(0x08 | _displayControl);
}

void LCDShiftView::blink() {
    _displayControl |= 0x01;
    command(0x08 | _displayControl);
}

void LCDShiftView::noCursor() {
    _displayControl &= ~0x02;
    command(0x08 | _displayControl);
}

void LCDShiftView::cursor() {
    _displayControl |= 0x02;
    command(0x08 | _displayControl);
}

void LCDShiftView::scrollDisplayLeft(void) {
    command(0x18);
}

void LCDShiftView::scrollDisplayRight(void) {
    command(0x1C);
}

void LCDShiftView::leftToRight(void) {
    _displayMode |= 0x02;
    command(0x04 | _displayMode);
}

void LCDShiftView::rightToLeft(void) {
    _displayMode &= ~0x02;
    command(0x04 | _displayMode);
}

void LCDShiftView::autoscroll(void) {
    _displayMode |= 0x01;
    command(0x04 | _displayMode);
}

void LCDShiftView::noAutoscroll(void) {
    _displayMode &= ~0x01;
    command(0x04 | _displayMode);
}

void LCDShiftView::createChar(uint8_t location, const uint8_t charmap[]) {
    location &= 0x7;
    command(0x40 | (location << 3));
    for (int i = 0; i < 8; i++) {
        write(charmap[i]);
    }
}

void LCDShiftView::print(const char* str) {
    while (*str) write(*str++);
}

void LCDShiftView::command(uint8_t value) {
    _send(value, false);
}

size_t LCDShiftView::write(uint8_t value) {
    _send(value, true);
    return 1;
}

void LCDShiftView::_send(uint8_t value, bool mode) {
    if (mode)
        _state |= (1 << _rsPin);
    else
        _state &= ~(1 << _rsPin);

    _write4Bits(value >> 4);
    _write4Bits(value & 0x0F);
    delayMicroseconds(50);
}

void LCDShiftView::_write4Bits(uint8_t value) {
    _state &= ~(1 << _d4Pin);
    _state &= ~(1 << _d5Pin);
    _state &= ~(1 << _d6Pin);
    _state &= ~(1 << _d7Pin);

    if (value & 0x01) _state |= (1 << _d4Pin);
    if (value & 0x02) _state |= (1 << _d5Pin);
    if (value & 0x04) _state |= (1 << _d6Pin);
    if (value & 0x08) _state |= (1 << _d7Pin);

    _shiftOut(_state);
    _pulseEnable();
}

void LCDShiftView::_pulseEnable(void) {
    _state |= (1 << _ePin);
    _shiftOut(_state);
    delayMicroseconds(1);
    _state &= ~(1 << _ePin);
    _shiftOut(_state);
    delayMicroseconds(100);
}

void LCDShiftView::_shiftOut(uint8_t value) {
    _currentValue = value;
    value |= (_backlightState << 7);

    digitalWrite(_latchPin, LOW);
    shiftOut(_dataPin, _clockPin, MSBFIRST, value);
    digitalWrite(_latchPin, HIGH);
}

void LCDShiftView::print(String str) {
    for (size_t i = 0; i < str.length(); i++) {
        write(str[i]);
    }
}

void LCDShiftView::print(char c) {
    write(c);
}

void LCDShiftView::print(int n) {
    print(String(n));
}

void LCDShiftView::print(unsigned int n) {
    print(String(n));
}

void LCDShiftView::print(long n) {
    print(String(n));
}

void LCDShiftView::print(unsigned long n) {
    print(String(n));
}

void LCDShiftView::print(double n, int digits) {
    print(String(n, digits));
}

void LCDShiftView::println() {
    write('\n');
}

void LCDShiftView::println(const char* str) {
    print(str);
    println();
}

void LCDShiftView::println(String str) {
    print(str);
    println();
}

void LCDShiftView::println(char c) {
    print(c);
    println();
}

void LCDShiftView::println(int n) {
    print(n);
    println();
}

void LCDShiftView::println(unsigned int n) {
    print(n);
    println();
}

void LCDShiftView::println(long n) {
    print(n);
    println();
}

void LCDShiftView::println(unsigned long n) {
    print(n);
    println();
}

void LCDShiftView::println(double n, int digits) {
    print(n, digits);
    println();
}

uint8_t LCDShiftView::getRowOffset(uint8_t row) {
    return _rowOffsets[row % 4];
}

void LCDShiftView::setPins(uint8_t rs, uint8_t e, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7) {
  _rsPin = rs;
  _ePin  = e;
  _d4Pin = d4;
  _d5Pin = d5;
  _d6Pin = d6;
  _d7Pin = d7;
  _customPinsSet = true;
}

void LCDShiftView::backlight(bool state) {
  _backlightState = state;
  _updateOutputs();
}

void LCDShiftView::_updateOutputs() {
  for (uint8_t i = 0; i < 8; ++i) {
    bitWrite(_currentValue, i, _outputBits[i]);
  }

  if (_backlightState) {
    bitSet(_currentValue, 7);
  } else {
    bitClear(_currentValue, 7);
  }

  digitalWrite(_latchPin, LOW);
  shiftOut(_dataPin, _clockPin, MSBFIRST, _currentValue);
  digitalWrite(_latchPin, HIGH);
}
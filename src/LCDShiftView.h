#ifndef LCDShiftView_h
#define LCDShiftView_h

#include <Arduino.h>
#include <Print.h>

class LCDShiftView : public Print {
public:
    LCDShiftView(uint8_t dataPin, uint8_t clockPin, uint8_t latchPin);

    void begin(uint8_t cols = 16, uint8_t rows = 2, uint8_t charsize = 0x00);
    void clear();
    void home();
    void print(const char* str);
    void print(String str);
    void print(char c);
    void print(int n);
    void print(unsigned int n);
    void print(long n);
    void print(unsigned long n);
    void print(double n, int digits = 2);

    void println();
    void println(const char* str);
    void println(String str);
    void println(char c);
    void println(int n);
    void println(unsigned int n);
    void println(long n);
    void println(unsigned long n);
    void println(double n, int digits = 2);

    void setCursor(uint8_t col, uint8_t row);
    void command(uint8_t cmd);
    void backlight(bool state);
    virtual size_t write(uint8_t data);

    void display();
    void noDisplay();
    void cursor();
    void noCursor();
    void blink();
    void noBlink();
    void scrollDisplayLeft();
    void scrollDisplayRight();
    void leftToRight();
    void rightToLeft();
    void autoscroll();
    void noAutoscroll();
    void createChar(uint8_t location, const uint8_t charmap[]);
    void setPins(uint8_t rs, uint8_t e, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);
    uint8_t getRowOffset(uint8_t row);

private:
    uint8_t _dataPin, _clockPin, _latchPin;
    uint8_t _state;
    uint8_t _cols, _rows;
    uint8_t _displayControl;
    uint8_t _displayMode;
    uint8_t _rsPin = 1;
    uint8_t _ePin  = 2;
    uint8_t _d4Pin = 3;
    uint8_t _d5Pin = 4;
    uint8_t _d6Pin = 5;
    uint8_t _d7Pin = 6;
    uint8_t _currentValue = 0;
    uint8_t _displayfunction;
    uint8_t _numlines;
    uint8_t _rowOffsets[4] = {0x00, 0x40, 0x14, 0x54};

    bool _customPinsSet = false;
    bool _backlightState = true;
    bool _outputBits[8];

    void _updateOutputs();
    void _pulseEnable();
    void _write4Bits(uint8_t nibble);
    void _send(uint8_t value, bool isData);
    void _shiftOut(uint8_t value);
};

#endif

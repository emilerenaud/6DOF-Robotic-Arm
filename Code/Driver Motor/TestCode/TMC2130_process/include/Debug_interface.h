#ifndef DEBUG_H
#define DEBUG_H

#include "Arduino.h"
#include "GPIO_driver.h"

class DebugClass {
  private:
    GPIOClass _red;
    GPIOClass _green;
    GPIOClass _blue;
    uint8_t _actifState;
  public:
    DebugClass();
    DebugClass(uint8_t red, uint8_t green, uint8_t blue, uint8_t actifState);
    void Write(bool redState, bool greenState, bool blueState); 
    void showError(uint8_t errorCode);
    void open_red(void);
    void open_green(void);
    void open_blue(void);
    void close_red(void);
    void close_green(void);
    void close_blue(void);

};


//---------- ERROR CODES ----------//
#define standard_error 0b100
#define COM_error 0b010
#endif
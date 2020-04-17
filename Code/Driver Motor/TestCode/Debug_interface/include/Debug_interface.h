#ifndef DEBUG_H
#define DEBUG_H

#include "Arduino.h"
#include "GPIO_driver.h"

class DebugClass {
  private:
    GPIOClass _red;
    GPIOClass _green;
    GPIOClass _blue;
  public:
    DebugClass();
    DebugClass(uint32_t red, uint32_t green, uint32_t blue);
    void Write(int R, int G, int B);  
};

#endif
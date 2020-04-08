#ifndef ANALOG_H
#define ANALOG_H

#include "Arduino.h"

class AnalogClass {
  private:
    uint32_t _pin;
  public:
    AnalogClass();
    AnalogClass(uint32_t pin, uint32_t mode);
    uint32_t Read(void);  
    void Write(uint32_t val);  
};

#endif
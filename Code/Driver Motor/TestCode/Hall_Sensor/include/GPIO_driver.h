#ifndef GPIO_H
#define GPIO_H

#include "Arduino.h"

class GPIOClass {
  private:
    uint32_t _pin;
    uint32_t _invert = HIGH;
  public:
    GPIOClass();
    GPIOClass(uint32_t pin, uint32_t mode);
    uint32_t Read(void);  
    void Write(uint32_t val);   
    void Toggle();
};

#endif
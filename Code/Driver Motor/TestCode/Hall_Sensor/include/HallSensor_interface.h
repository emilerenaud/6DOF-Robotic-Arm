#ifndef HALLSENSOR_H
#define HALLSENSOR_H

#include "Arduino.h"
#include "GPIO_driver.h"

class HallSensorClass {
  private:
    GPIOClass _hall;
  public:
    HallSensorClass();
    HallSensorClass(uint32_t pin);
    bool Read(void);  
};

#endif
#ifndef TEMPSENSOR_H
#define TEMPSENSOR_H

#include "Arduino.h"
#include "Analog_driver.h"

class TempSensorClass{
  private:
    AnalogClass _value;
  public:
    TempSensorClass();
    TempSensorClass(uint32_t pin);
    int Temperature(void);  
};

#endif
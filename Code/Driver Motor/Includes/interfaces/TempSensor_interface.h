#ifndef TEMPSENSOR_H
#define TEMPSENSOR_H

#include "Arduino.h"
#include "Analog_driver.h"
#include "RS485_driver.h"
#include <string.h>

class TempSensorClass{
  private:
    AnalogClass _value;
    RS485Class  _transmit = RS485Class(19200);
  public:
    TempSensorClass();
    TempSensorClass(uint32_t pin);
    int Temperature(void);  
};

#endif
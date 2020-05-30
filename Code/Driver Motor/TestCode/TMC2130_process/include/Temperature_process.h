#ifndef TEMP_PROCESS_H
#define TEMP_PROCESS_H

#include "Arduino.h"
#include "TempSensor_interface.h"
#include "Fan_interface.h"

class Temperature_process{
  private:
    TempSensorClass _temp = TempSensorClass(TEMP);
    int _tempHigh = 26;
    int _tempLow = 22;
  public:
    FanClass _fan = FanClass(FAN);
    Temperature_process();
    void Control();  
};

#endif
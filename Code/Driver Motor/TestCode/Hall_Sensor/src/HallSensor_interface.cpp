#include "HallSensor_interface.h"

HallSensorClass::HallSensorClass(){
}

HallSensorClass::HallSensorClass(uint32_t pin){
    _hall = GPIOClass(pin, INPUT_PULLUP);
}

bool HallSensorClass::Read(void){
     if(_hall.Read() == 0)
     {
         return HIGH;
     }
     else
     {
         return LOW;
     } 
}

#include "TempSensor_interface.h"

TempSensorClass::TempSensorClass(){
}

TempSensorClass::TempSensorClass(uint32_t pin){
    _value = AnalogClass(pin, INPUT);
}

int TempSensorClass::Temperature(){
    return (int) ((((float)_value.Read() - 807.286) / 1.65) - 32) * 5 / 9;

    //    return (int) ((float)_value.Read() - 807.286) / 2.157;

}


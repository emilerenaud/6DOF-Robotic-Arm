#include "Analog_driver.h"

AnalogClass::AnalogClass(){
}

AnalogClass::AnalogClass(uint32_t pin, uint32_t mode){
    pinMode(pin, mode);
    _pin = pin;
}

uint32_t AnalogClass::Read(void){
    return analogRead(_pin);
}

void AnalogClass::Write(uint32_t val){
     analogWrite(_pin, val);
}

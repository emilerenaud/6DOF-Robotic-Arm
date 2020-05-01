#include "GPIO_driver.h"

GPIOClass::GPIOClass(){
}

GPIOClass::GPIOClass(uint32_t pin, uint32_t mode){
    pinMode(pin, mode);
    _pin = pin;
}

uint32_t GPIOClass::Read(void){
    return digitalRead(_pin);
}

void GPIOClass::Write(uint32_t val){
    digitalWrite(_pin, val);
}

void GPIOClass::Toggle(){
    _invert = !_invert;
    digitalWrite(_pin, _invert);
}


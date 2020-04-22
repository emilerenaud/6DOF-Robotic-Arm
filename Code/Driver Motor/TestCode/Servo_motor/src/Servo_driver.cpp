#include "Servo_driver.h"

ServoClass::ServoClass(){
}

ServoClass::ServoClass(uint32_t pin){
    _servo.attach(pin);
}

void ServoClass::Write(uint32_t val){
    _servo.writeMicroseconds(val);
}
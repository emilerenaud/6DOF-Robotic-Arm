#include "Servo_driver.h"

ServoClass::ServoClass(){
}

ServoClass::ServoClass(uint32_t pin){
    _servo.attach(SERVO);
}

void ServoClass::Write(uint32_t val){
    val = map(val, 0, 1023, 0, 180);
    _servo.write(val);
}
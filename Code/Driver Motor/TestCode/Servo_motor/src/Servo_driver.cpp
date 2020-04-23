#include "Servo_driver.h"

ServoClass::ServoClass(){
}

ServoClass::ServoClass(uint32_t pin){
    if(_servo.attach(pin) == 0)
    {
        Serial.println("Erreur");
    }
    else
    {
        Serial.println("Sucess");
    }
    
}

void ServoClass::set_pin(uint8_t pin)
{
    _servo.attach(pin);
}

void ServoClass::Write(uint32_t angle){
    _servo.write(angle);
}
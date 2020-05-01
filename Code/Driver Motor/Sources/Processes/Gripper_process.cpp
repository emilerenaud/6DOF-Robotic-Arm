#include "Gripper_process.h"

GripperClass::GripperClass(){
}

GripperClass::GripperClass(uint32_t pin){
    if(_servo.attach(pin) == 0)
    {
        Serial.println("Erreur");
    }
    else
    {
        Serial.println("Sucess");
    }
}

void GripperClass::set_pin(uint8_t pin)
{
    _servo.attach(pin);
}

void GripperClass::Position(uint32_t angle){
    _servo.write(angle);
}
#ifndef GRIPPER_H
#define GRIPPER_H

#include "Arduino.h"
#include "Servo.h"
#include "configuration.h"

class GripperClass {
  private:
    Servo _servo;
  public:
    GripperClass();
    GripperClass(uint32_t pin);
    void set_pin(uint8_t pin);
    void Position(uint32_t val);  
};

#endif
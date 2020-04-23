#ifndef SERVO_DRIVER_H
#define SERVO_DRIVER_H

#include "Arduino.h"
#include "Servo.h"
#include "configuration.h"

class ServoClass {
  private:
    Servo _servo;
  public:
    ServoClass();
    ServoClass(uint32_t pin);
    void set_pin(uint8_t pin);
    void Write(uint32_t val);  
};

#endif
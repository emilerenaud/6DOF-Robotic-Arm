#ifndef TMC2130_PROCESS_H
#define TMC2130_PROCESS_H

#include <Arduino.h>
#include <TMC2130_interface.h>
#include <HallSensor_interface.h>

class TMC2130_process
{
private:
    
    HallSensorClass _hall = HallSensorClass(HALL);
    int _rotation = 0;
    int _degree_counter = 0;
    int _direction;
public:
    TMC2130Class _tmc = TMC2130Class();
    TMC2130_process();
    int Rotation(float position, float microstep);
    int Homing(float microstep);
};

#endif
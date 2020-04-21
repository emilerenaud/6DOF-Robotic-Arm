#ifndef TMC2130_PROCESS_H
#define TMC2130_PROCESS_H

#include <Arduino.h>
#include <TMC2130_interface.h>
#include <HallSensor_interface.h>

class TMC2130_process
{
private:
    TMC2130Class _tmc = TMC2130Class();
    HallSensorClass _hall = HallSensorClass(HALL);
    int _rotation = 0;
    int _degree_counter = 0;
public:
    TMC2130_process();
    int Rotation(float degree, float microstep, int direction);
    int Homing(float microstep);
};

#endif
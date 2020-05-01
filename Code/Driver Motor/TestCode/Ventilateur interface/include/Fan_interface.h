#ifndef FAN_INTERFACE_H
#define FAN_INTERFACE_H

#include <Arduino.h>
#include <Timer_driver.h>

class FanClass
{
private:
    uint8_t _pin;
    uint8_t _power;

public:
    FanClass(uint8_t pin);
    void set_power(uint8_t power);
    void start(void);
    void stop(void);
};

#endif
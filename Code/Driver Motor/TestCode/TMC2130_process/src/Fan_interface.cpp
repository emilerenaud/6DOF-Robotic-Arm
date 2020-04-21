#include <Fan_interface.h>

FanClass::FanClass(uint8_t pin)
{
    _pin = pin;
    pinMode(_pin,OUTPUT);
    init_PWM(_pin,1);
}

void FanClass::set_power(uint8_t power)
{
    set_PWM(power);
}

void FanClass::start(void)
{
    start_PWM();
}

void FanClass::stop(void)
{
    stop_PWM();
}
#include <Fan_interface.h>

FanClass::FanClass(uint8_t pin)
{
    _pin = pin;
    pinMode(_pin,OUTPUT);
    init_timer_PWM(_pin);
    set_power(0);
    start();
}

void FanClass::set_power(uint8_t power)
{
    if(power == 100)
        power = 99;
    set_dutyCycle_Timer_PWM(power);
}

void FanClass::start(void)
{
    start_timer_PWM();
}

void FanClass::stop(void)
{
    stop_timer_PWM();
}
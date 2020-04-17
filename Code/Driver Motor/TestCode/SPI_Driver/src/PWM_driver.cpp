#include "PWM_driver.h"

uint8_t _cycleCount = 0;
uint8_t _dutyCycle = 0;
uint8_t _pin;
bool _actifState = 1;

HardwareTimer *timer = new HardwareTimer(TIM1);

void callback_IT_timer(HardwareTimer*)
{
  if(_cycleCount <= _dutyCycle)
    digitalWrite(_pin,1); // enable gpio.
  else
  {
    digitalWrite(_pin,0); // disable gpio.
    if(_cycleCount == 100)
      _cycleCount = 0;
  }
  _cycleCount ++;
}

void init_PWM(uint8_t pin, uint8_t actifState)
{
    _pin = pin;
    _actifState = actifState;
    pinMode(_pin,OUTPUT);

    timer->setOverflow(10000, HERTZ_FORMAT); // 10 Hz
    timer->attachInterrupt(callback_IT_timer);
    stop_PWM();
}

void set_PWM(uint8_t dutyCycle)
{
    _dutyCycle = dutyCycle;
}

void start_PWM(void)
{
    timer->resume();
}

void stop_PWM(void)
{
    timer->pause();
}

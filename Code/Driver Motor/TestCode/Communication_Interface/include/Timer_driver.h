#ifndef TIMER_DRIVER_H
#define TIMER_DRIVER_H
#include <Arduino.h>


void init_timer_COM(void);
void setFunction_timer_COM(void(*pFunctionToSet)(void));
void callback_timer_COM(HardwareTimer*);


//---------- TIMER PWM ----------//
void init_timer_PWM(void);
void callback_timer_PWM(HardwareTimer*);
void start_timer_PWM(void);
void stop_timer_PWM(void);
void set_pin_Timer_PWM(uint8_t pin);
void set_dutyCycle_Timer_PWM(uint8_t dutyCycle);

#endif
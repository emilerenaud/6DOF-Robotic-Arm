#ifndef PWM_DRIVER_H
#define PWM_DRIVER_H

#include <Arduino.h>
#include "configuration.h"
#include "HardwareTimer.h"


void init_PWM(uint8_t pin, uint8_t actifState);
void set_PWM(uint8_t dutyCycle);
void start_PWM(void);
void stop_PWM(void);

#endif

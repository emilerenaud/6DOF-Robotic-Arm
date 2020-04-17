#include "PWM_driver.h"
#include <Arduino.h>
#include "PinConfigured.h"

uint32_t g_anOutputPinConfiguredTest[MAX_NB_PORT] = {0};

static inline uint32_t mapResolution(uint32_t value, uint32_t from, uint32_t to)
{
  if (from != to) {
    if (from > to) {
      value = (value < (uint32_t)(1 << (from - to))) ? 0 : ((value + 1) >> (from - to)) - 1;
    } else {
      if (value != 0) {
        value = ((value + 1) << (to - from)) - 1;
      }
    }
  }
  return value;
}

void write_pwm(const int ulPin,int ulValue)
{
    //analogWrite(pin,pwm);
    PinName p = digitalPinToPinName(ulPin);
    if (pin_in_pinmap(p, PinMap_PWM)) {
        if (is_pin_configured(p, g_anOutputPinConfiguredTest) == false) {
          set_pin_configured(p, g_anOutputPinConfiguredTest);
        }
        ulValue = mapResolution(ulValue, 8, PWM_RESOLUTION);
        pwm_start(p, 1000, ulValue);
    }
}
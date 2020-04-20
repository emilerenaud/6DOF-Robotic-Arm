#include <Arduino.h>
#include <PWM_driver.h>
#include <Fan_interface.h>
#include <GPIO_driver.h>

FanClass fan(FAN);

void setup() {
  fan.set_power(30);
  fan.start();
}

void loop() {
  

}
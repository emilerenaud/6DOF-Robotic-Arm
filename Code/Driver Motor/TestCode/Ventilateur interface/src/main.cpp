#include <Arduino.h>
#include <Timer_driver.h>
#include <Fan_interface.h>
#include <GPIO_driver.h>

FanClass fan(FAN);

void setup() {
  fan.set_power(40);
  fan.start();
}

void loop() {
  

}
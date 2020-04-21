#include <Arduino.h>
#include <TMC2130_process.h>
#include <GPIO_driver.h>
#include <TMC2130_interface.h>
#include <Temperature_process.h>

TMC2130_process _tmc = TMC2130_process();
int once = true;

//Temperature_process temp = Temperature_process();

void setup() {
}

void loop() {
  
  
  //temp.Control();
  
  if (once)
  {
  
    while(_tmc.Rotation(27, 256, CW) == 0);
  
    once = false;
    delay(1000);
  }

  else
  {
      while(_tmc.Homing(256) == 0);
      once = true;
      delay(1000);
  }
}
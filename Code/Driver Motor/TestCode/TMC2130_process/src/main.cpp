#include <Arduino.h>
#include <TMC2130_process.h>
#include <GPIO_driver.h>
#include <TMC2130_interface.h>
#include <Temperature_process.h>

TMC2130_process _tmc = TMC2130_process();
int once = true;
int i = 0;
//Temperature_process temp = Temperature_process();

void setup() {
}

void loop() {
  
  
  //temp.Control();
  
  if (once)
  {
    i ++;
    while(_tmc.Rotation(i, 256, CW) == 0);
    if(i == 360)
      i = 0;
    // _tmc._tmc.ReadRegisters();
    // while(_tmc.Rotation(20, 256, CW) == 0);
    once = false;
    delay(20);
  }

  else
  {
      // while(_tmc.Homing(256) == 0);
      once = true;
      // delay(1000);
  }
}
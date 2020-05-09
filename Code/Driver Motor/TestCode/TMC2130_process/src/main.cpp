#include <Arduino.h>
#include <TMC2130_process.h>
#include <GPIO_driver.h>
#include <Temperature_process.h>
#include <Timer_driver.h>
#include <Communication_process.h>
#include <TMC2130_process.h>
#include <Debug_interface.h>
#include <Fan_interface.h>
#include <init_stm32.h>


ComProcess com = ComProcess();
TMC2130_process tmc = TMC2130_process();
DebugClass debug = DebugClass(LEDR, LEDG, LEDB);
FanClass fan = FanClass(FAN);

void process_COM(void)
{
  com.DecodeData();
}

void setup() {
  pinMode(LEDB, OUTPUT);
  init_stm32();
  init_timer_COM(process_COM);
}

void loop() {
  if(com._endis == ACTIVE)
  {
    tmc.Rotation(com._position, 256);
  }

  if(com._homing == ACTIVE)
  {
    tmc.Homing(256);
  }
  debug.Write(com._red, com._green, com._blue);
  if(com._fan > 0)
  {
    fan.set_power(com._fan);
    fan.start();
  }
  else
  {
    fan.stop();
  }
  

}
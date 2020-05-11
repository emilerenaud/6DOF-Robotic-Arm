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
DebugClass debug = DebugClass(LEDR, LEDG, LEDB,LOW);
FanClass fan = FanClass(FAN);

void process_COM(void)
{
  com.DecodeData();
}

void setup() {
  init_stm32();
  init_timer_COM(process_COM);
}

void loop() {
   
  tmc._tmc.checkDiag();
    
  if(com._endis == ACTIVE)
  {
    if(tmc.Rotation(com._position, 256) == DONE)
    {
      com._readyForNewData= 1;
    }
    else
    {
      com._readyForNewData = 0;
    }
  }

  if(com._homing == ACTIVE)
  {
    if(tmc.Homing(256) == DONE)
    {
      com._readyForNewData = 1;
    }
    else
    {
      com._readyForNewData = 0;
    }
  }
  debug.Write(com._red, com._green, com._blue);

  fan.set_power(com._fan);
  

  
  

}
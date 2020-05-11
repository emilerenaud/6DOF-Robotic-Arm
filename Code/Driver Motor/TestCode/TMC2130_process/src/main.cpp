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
  // init_stm32();
  init_timer_COM(process_COM);
}

void loop() {
  // process_COM();
  // if(com._com._receive.receiveBytes.firstByte == 0x00)
  // {
  //   debug.Write(0,1,1);
  // }
  // if(com._com._receive.receiveBytes.firstByte == 0x40)
  // {
  //   debug.Write(1,0,1);
  // }
  tmc._tmc.checkDiag();
  
  if(com._endis == ACTIVE)
  {
    tmc.Rotation(com._position, 256);
  }

  if(com._homing == ACTIVE)
  {
    tmc.Homing(256);
  }
  debug.Write(com._red, com._green, com._blue);

  fan.set_power(com._fan);
  
  

}
#include <Arduino.h>
#include <init_stm32.h>
#include <GPIO_driver.h>
#include <Timer_driver.h>

#include <Debug_interface.h>

#include <Temperature_process.h>
#include <Gripper_process.h>
#include <Communication_process.h>
#include <TMC2130_process.h>


DebugClass debug = DebugClass(LEDR, LEDG, LEDB,LOW);
Temperature_process fan = Temperature_process();

ComProcess com = ComProcess();
TMC2130_process tmc = TMC2130_process();

/*Last axis: comment TEMP_SENSOR and uncomment SERVO_EN in configuration.h.
             uncomment every gripper line to use gripper.*/
//GripperClass gripper;

void process_COM(void);
void process_motor(void);
void process_debug(void);
void MovingAxis(void);

void setup() {
  //gripper.set_pin(SERVO);   
  init_stm32();
  init_timer_COM(process_COM);
}

void loop() {
  process_COM();
  process_debug();
  process_motor();
}

void process_COM(void)
{
  com.DecodeData();
}

void process_motor(void)
{
  if(com._adress == DRIVER)
  {
    fan.Control();
    MovingAxis();
    //gripper.Position(com._gripper);
  }
}

void process_debug(void)
{
  if(com._adress == DEBUG)
  {
    MovingAxis();
    //gripper.Position(com._gripper)
    fan._fan.set_power(com._fan);
    

    debug.Write(com._red, com._green, com._blue);

    tmc._tmc.checkDiag();
  }
}

void MovingAxis(void)
{
    if(com._endis == ACTIVE)
    {
      if(com._homing == ACTIVE)
      {
        if(tmc.Homing(256) == DONE)
          com._readyForNewData = 1;
        else
          com._readyForNewData = 0;
      }
      else
      {
        if(tmc.Rotation(com._position, 256) == DONE)
          com._readyForNewData = 1;
        else
          com._readyForNewData = 0;
      }
    }
    else
    {
      tmc.Disable();
    }
}
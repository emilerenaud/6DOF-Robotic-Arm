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

bool doOnce = 1;
bool sens = 1;
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
  // if(doOnce)
  // {
  //   com._endis = 1;
  //   if(sens)
  //   {
  //     com._position = 300;
  //     sens = 0;
  //   }
  //   else
  //   {
  //     com._position = 0;
  //     sens = 1;
  //   }
  //   doOnce = 0;
  //   delay(1000);
  // }
  // if(tmc.Rotation(com._position, 256) == DONE)
  //   doOnce = 1;


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
    fan._fan.start();

    debug.Write(com._red, com._green, com._blue);
  }
}

void MovingAxis(void)
{
    if(com._endis == ACTIVE)
    {
      if(com._homing == ACTIVE)
      {
        if(tmc.Homing(256) == DONE)
        //if(tmc.Homing(32) == DONE) // For non-TMC driver.
        {
          com._readyForNewData = 1;
          com._homing = 0;
        }
        else
          com._readyForNewData = 0;
      }
      else
      {
        if(tmc.Rotation(com._position, 256) == DONE)
        //if(tmc.Rotation(com._position, 32) == DONE) // For non-TMC driver.
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
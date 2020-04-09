#include <Arduino.h>
#include "configuration.h"
#include "TMC2130_interface.h"
#include "TMC2130_config.h"

TMC2130Class tmc;
TMC t;

void setup() 
{ 
}

void loop() 
{
    // tmc.GeneralConfig();
    // tmc.ChopConfig();
    // tmc.CoolConfig();
    // tmc.PWMConfig();

    tmc.ReadRegisters();

    delay(200);
}
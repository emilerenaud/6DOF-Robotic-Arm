#include <Arduino.h>
#include "configuration.h"
#include "TMC2130_interface.h"
#include "TMC2130_config.h"

TMC2130Class tmc;


void setup() 
{
    tmc.Init();
}

void loop() 
{
    tmc.Rotation(5,256,HIGH);
}
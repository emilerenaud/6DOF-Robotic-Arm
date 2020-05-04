#include <Arduino.h>
#include "configuration.h"
#include "TMC2130_interface.h"
#include "TMC2130_config.h"

TMC2130Class tmc;

int doOnce = 1;

void setup() 
{
    tmc.Init();
}

void loop() 
{
    if(doOnce)
    {
        doOnce = 0;
        tmc.Rotation(5, 256, HIGH, NEMA17); 
    }
    
}
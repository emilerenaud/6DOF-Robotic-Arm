#include <Arduino.h>
#include "configuration.h"
#include "TMC2130_interface.h"
#include "TMC2130_config.h"

TMC2130Class tmc;


void setup() 
{
    pinMode(LEDG, OUTPUT);
    tmc.Init();
}

void loop() 
{
    tmc.Rotation(5, 256, HIGH, NEMA17);
}
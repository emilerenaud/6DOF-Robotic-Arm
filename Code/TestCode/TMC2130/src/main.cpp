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
    tmc_read dataIn;
    tmc_add add;

    add.address = 0x91;
    add.readWrite = LOW;

    dataIn = tmc.Write(add, t.g_conf.sendBytes);
    delay(200);
}
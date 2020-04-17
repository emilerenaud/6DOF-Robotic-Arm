#include <Arduino.h>
#include <configuration.h>
#include <Debug_interface.h>

DebugClass debug = DebugClass(LEDR, LEDG, LEDB);

void setup() {
}

void loop() {
    debug.Write(LOW,LOW,LOW);
}
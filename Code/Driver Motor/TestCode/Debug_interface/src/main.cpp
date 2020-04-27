#include <Arduino.h>
#include <configuration.h>
#include <Debug_interface.h>

DebugClass debug = DebugClass(LEDR, LEDG, LEDB, LOW);

void setup() {
}

void loop() {
    debug.Write(LOW,LOW,LOW);
    delay(500);
    debug.close_red();
    debug.close_green();
    debug.close_blue();
    delay(500);
    debug.open_red();
    debug.close_green();
    debug.close_blue();
    delay(500);
    debug.close_red();
    debug.open_green();
    debug.close_blue();
    delay(500);
    debug.close_red();
    debug.close_green();
    debug.open_blue();
    delay(500);
    debug.close_blue();
    delay(500);
    debug.showError(standard_error);
    delay(500);
}
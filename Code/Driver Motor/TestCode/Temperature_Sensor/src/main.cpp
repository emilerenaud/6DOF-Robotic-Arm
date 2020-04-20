#include <Arduino.h>
#include <configuration.h>
#include <RS485_driver.h>
#include <TempSensor_interface.h> 
#include <string.h>

TempSensorClass temp = TempSensorClass(TEMP);
RS485Class tx = RS485Class(19200);

void setup() {
    pinMode(LEDR, OUTPUT);
}

void loop() {
    digitalWrite(LEDR, HIGH);
    char arrTemp[50];
    sprintf(arrTemp, "Temp: %i\n", temp.Temperature());
    tx.Print(arrTemp);
    delay(2000);
}
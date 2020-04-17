#include <Arduino.h>
#include <configuration.h>
#include <RS485_driver.h>
#include <TempSensor_interface.h> 
#include <string.h>

TempSensorClass temp = TempSensorClass(TEMP);
RS485Class tx = RS485Class(19200);

void setup() {
}

void loop() {
    char arrTemp[50];
    sprintf(arrTemp, "Temp: %i\n", temp.Temperature());
    tx.Write(arrTemp);
    delay(2000);
}
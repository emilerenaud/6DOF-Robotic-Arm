#include <Arduino.h>
#include <configuration.h>
#include <RS485_driver.h>
#include <HallSensor_interface.h> 
#include <string.h>

HallSensorClass hall = HallSensorClass(HALL);
RS485Class tx = RS485Class(19200);

void setup() {
}

void loop() {
    if(hall.Read())
        tx.Write("SOMETHING\n");
    else
        tx.Write("NOTHING\n");
    
    delay(2000);
}
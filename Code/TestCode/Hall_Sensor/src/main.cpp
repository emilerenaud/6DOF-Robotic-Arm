#include <Arduino.h>
#include <configuration.h>
#include <RS485_driver.h>
#include <HallSensor_interface.h> 
#include <string.h>

HallSensorClass hall = HallSensorClass(HALL);
RS485Class tx(19200);
int threshold = 500;

void setup() {
    Serial.begin(9600);
}

void loop() {
    if(hall.Read())
        //tx.Write("SOMETHING\n");
        Serial.println("Hall On");
    else
        //tx.Write("NOTHING\n");
        Serial.println("Hall Off");
  
    
    delay(500);
}
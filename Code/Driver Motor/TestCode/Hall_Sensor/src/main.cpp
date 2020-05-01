#include <Arduino.h>
#include <configuration.h>
#include <HallSensor_interface.h> 
#include <string.h>

HallSensorClass hall = HallSensorClass(HALL);
bool doOnce = 1;

void setup() {
    pinMode(LEDB,OUTPUT);
    pinMode(FAN,OUTPUT);
    pinMode(LEDG,OUTPUT);
    pinMode(LEDR,OUTPUT);
    digitalWrite(LEDR,HIGH);
    digitalWrite(LEDG,HIGH);
    digitalWrite(LEDB,HIGH);
}

void loop() {

    if(doOnce)
    {
        doOnce = 0;
        digitalWrite(LEDR,LOW);
        delay(200);
        digitalWrite(LEDR,HIGH);
        delay(200);
        digitalWrite(LEDR,LOW);
        delay(200);
        digitalWrite(LEDR,HIGH);
        
        delay(200);
        digitalWrite(LEDG,LOW);
        delay(200);
        digitalWrite(LEDG,HIGH);
        delay(200);
        digitalWrite(LEDG,LOW);
        delay(200);
        digitalWrite(LEDG,HIGH);

        delay(200);
        digitalWrite(LEDB,LOW);
        delay(200);
        digitalWrite(LEDB,HIGH);
        delay(200);
        digitalWrite(LEDB,LOW);
        delay(200);
        digitalWrite(LEDB,HIGH);
    }
    
    if(hall.Read())
    {
        digitalWrite(LEDR,LOW);
    }
        
    else
    {
        digitalWrite(LEDR,HIGH);
    }
        
}
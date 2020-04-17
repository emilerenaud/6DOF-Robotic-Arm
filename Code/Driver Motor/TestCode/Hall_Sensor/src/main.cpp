#include <Arduino.h>
#include <configuration.h>
#include <RS485_driver.h>
#include <HallSensor_interface.h> 
#include <string.h>

HallSensorClass hall = HallSensorClass(HALL);
// RS485Class tx(19200);
bool doOnce = 1;

void setup() {
    Serial.begin(9600);
    pinMode(LEDB,OUTPUT);
    pinMode(FAN,OUTPUT);
    pinMode(LEDG,OUTPUT);
    pinMode(LEDR,OUTPUT);
    digitalWrite(LEDR,HIGH);
    digitalWrite(LEDG,HIGH);
    digitalWrite(LEDB,HIGH);

    // pinMode(HALL,INPUT);
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
    
    // if(digitalRead(HALL))
    // {
    //     digitalWrite(FAN,LOW);
    // }
    // else
    // {
    //     digitalWrite(FAN,HIGH);
    // }
    if(hall.Read())
    {
        //tx.Write("SOMETHING\n");
        // Serial.println("Hall On");
        digitalWrite(LEDR,LOW);
    }
        
    else
    {
        //tx.Write("NOTHING\n");
        // Serial.println("Hall Off");
        digitalWrite(LEDR,HIGH);
    }
        
}
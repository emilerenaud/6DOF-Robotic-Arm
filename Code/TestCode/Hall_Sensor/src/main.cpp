#include <Arduino.h>
#include <configuration.h>
#include <RS485_driver.h>
#include <HallSensor_interface.h> 
#include <Debug_interface.h>

HallSensorClass hall = HallSensorClass(HALL);
DebugClass debug = DebugClass(LEDR,LEDG,LEDB);

void setup() {
}

void loop() {
    if(hall.Read())
        debug.Write(LOW,LOW,LOW);
    else
        debug.Write(HIGH,HIGH,HIGH);       
}
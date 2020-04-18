#include <Arduino.h>
#include <GPIO_driver.h>
#include <PWM_driver.h>
#include <RS485_driver.h>
#include <configuration.h>


RS485Class rs485(9600);

bool doOnce = 1;

void setup() {
  pinMode(LEDB,OUTPUT);
  digitalWrite(LEDB,LOW);
  delay(500);
  digitalWrite(LEDB,HIGH);
delay(500);
digitalWrite(LEDB,LOW);
  // put your setup code here, to run once:
}

void loop() {
  if(doOnce)
  {
    doOnce = 0;
    rs485.Write(0x12);
    delay(10);
    rs485.Write(0x12);
    
  }
  // put your main code here, to run repeatedly:
}
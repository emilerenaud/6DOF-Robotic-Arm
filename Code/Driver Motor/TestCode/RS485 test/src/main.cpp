#include <Arduino.h>
#include <GPIO_driver.h>
#include <PWM_driver.h>
#include <RS485_driver.h>
#include <configuration.h>


RS485Class rs485(9600);

bool doOnce = 1;

void setup() {
  pinMode(FAN,OUTPUT);
  digitalWrite(FAN,LOW);
  delay(100);
  digitalWrite(FAN,HIGH);
  delay(100);
  digitalWrite(FAN,LOW);
  // put your setup code here, to run once:
}

void loop() {
  int data = rs485.Read();
  if(data != -1)
  {
    if(data == 0x12)
    {
      digitalWrite(FAN,HIGH);
      delay(500);
      rs485.Write(0x55);
      delay(5);
      rs485.set_input();
    }
    else
    {
      digitalWrite(FAN,LOW);
    }
    
  }
  // put your main code here, to run repeatedly:
}
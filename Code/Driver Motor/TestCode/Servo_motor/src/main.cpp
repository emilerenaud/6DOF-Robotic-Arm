#include <Arduino.h>
#include "Servo_driver.h"


ServoClass servo;

void setup() {
  Serial.begin(9600);
  Serial.println("Setup");
  servo.set_pin(SERVO);
}

void loop() {
  for(int i = 0; i<180; i++)
  {
    servo.Write(i);
    delay(5);
  }
  delay(1000);
  for(int i = 180; i>0; i--)
  {
    servo.Write(i);
    delay(5);
  }
  // servo.Write(1000);
  // delay(1000);

  // servo.Write(2000);
  // delay(1000);

  // servo.Write(1500);
  // delay(1000);
}
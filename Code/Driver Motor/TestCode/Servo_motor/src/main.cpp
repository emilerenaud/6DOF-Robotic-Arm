#include <Arduino.h>
#include "Servo_driver.h"

ServoClass servo = ServoClass(SERVO);

void setup() {
}

void loop() {
  servo.Write(1000);
  delay(1000);

  servo.Write(2000);
  delay(1000);

  servo.Write(1500);
  delay(1000);
}
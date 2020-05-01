#include <Arduino.h>
#include "Gripper_process.h"


GripperClass gripper;

void setup() {
  gripper.set_pin(SERVO);
}

void loop() {
  gripper.Position(0);
}
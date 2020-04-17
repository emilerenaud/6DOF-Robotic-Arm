#include <Arduino.h>
#include "configuration.h"
#include "SPI_driver.h"
#include "PWM_driver.h"


int doOnce = 0;
SPIClass spi(SCK,MISO,MOSI,CS_TMC2130);



void setup()
{
  init_PWM(FAN,1);
  set_PWM(50);
  start_PWM();
}


void loop()
{
  set_PWM(10);
  delay(1000);
  set_PWM(20);
  delay(1000);
  set_PWM(30);
  delay(1000);
  set_PWM(40);
  delay(1000);
  set_PWM(50);
  delay(1000);
  set_PWM(60);
  delay(1000);
  set_PWM(70);
  delay(1000);
  set_PWM(80);
  delay(1000);
}

#include <Arduino.h>
#include "configuration.h"
#include "SPI_driver.h"
#include "PWM_driver.h"

int doOnce = 0;


void setup() 
{
  pinMode(onBoardLED,OUTPUT);
  spi_init(CS_TMC2130);
}

void loop() 
{
  if(!doOnce)
  {
    spi_writeByte(0x55);
    spi_writeByte(0xAA);
    spi_writeByte(0x00);
    doOnce = 1;
  }
  //digitalToggle(onBoardLED);
  for(int i = 0; i < 255; i++)
  {
   write_pwm(onBoardLED,i);
   delay(5);
  }
  for(int i = 255; i > 0; i--)
  {
   write_pwm(onBoardLED,i);
   delay(5);
  }
  delay(100);
}
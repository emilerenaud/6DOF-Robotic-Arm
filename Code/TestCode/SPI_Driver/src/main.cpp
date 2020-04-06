#include <Arduino.h>
#include "configuration.h"
#include "SPI_driver.h"
#include "PWM_driver.h"

int doOnce = 0;
SPIClass spi(SCK,MISO,MOSI,CS_TMC2130);

void setup() 
{
  pinMode(onBoardLED,OUTPUT);
  
}

void loop() 
{
  if(!doOnce)
  {
    spi.enableDevice();
    spi.writeByte(0x55);
    spi.writeByte(0x72);
    spi.disableDevice();

    spi.enableDevice();
    unsigned char byte = spi.readByte();
    spi.disableDevice();

    spi.enableDevice();
    spi.writeByte(byte);
    spi.disableDevice();
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
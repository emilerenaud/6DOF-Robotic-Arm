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
    spi.writeByte(0xAA);
    spi.writeByte(0x51);
    spi.disableDevice();

    spi.enableDevice();
    unsigned char byte = 0;
    byte = spi.readByte();
    spi.disableDevice();

    spi.enableDevice();
    spi.writeByte(byte);
    spi.disableDevice();

    spi.enableDevice();
    byte = spi.readWritebyte(0xF6);
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
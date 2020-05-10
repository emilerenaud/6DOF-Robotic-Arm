#ifndef TMC2130_INTERFACE_H
#define TMC2130_INTERFACE_H

#include <Arduino.h>
#include "configuration.h"
#include "TMC2130_config.h"
#include "SPI_driver.h"
#include "GPIO_driver.h"
#include "math.h"


class TMC2130Class
{
private:
    SPIClass _spi   = SPIClass(SCK,MISO,MOSI,CS_TMC2130);
    GPIOClass _en   = GPIOClass(EN, OUTPUT);
    GPIOClass _dir  = GPIOClass(DIR, OUTPUT);
    GPIOClass _step = GPIOClass(STEP, OUTPUT);
public:
    TMC2130Class();
    void Write(tmc_add add, tmc_write dataOut);
    tmc_read Read(tmc_add add);
    void Init();
    int Rotation(float degree, float microstep, int direction);
    void GeneralConfig();
    void IHoldIrunConfig();
    void TPowerDownConfig();
    void TPWMConfig();
    void ReadRegisters();
    void SPIModeConfig();
    void ChopConfig();
    void CoolConfig();
    void TCoolThreshHold();
    void PWMConfig();
};

#endif
#ifndef TMC2130_INTERFACE_H
#define TMC2130_INTERFACE_H

#include <Arduino.h>
#include "configuration.h"
#include "TMC2130_config.h"
#include "SPI_driver.h"


class TMC2130Class
{
private:
    SPIClass _spi = SPIClass(SCK,MISO,MOSI,CS_TMC2130);
public:
    TMC2130Class();
    void Write(tmc_add add, tmc_write dataOut);
    tmc_read Read(tmc_add add);
    void GeneralConfig();
    void ReadRegisters();
    void SPIModeConfig();
    void ChopConfig();
    void CoolConfig();
    void MicroSteppingConfig();
    void PWMConfig();
};

#endif
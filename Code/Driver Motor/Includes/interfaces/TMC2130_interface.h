#ifndef TMC2130_INTERFACE_H
#define TMC2130_INTERFACE_H

#include <Arduino.h>
#include "configuration.h"
#include "TMC2130_config.h"
#include "SPI_driver.h"
#include "GPIO_driver.h"
#include "math.h"
#include "Debug_interface.h"


class TMC2130Class
{
private:
    SPIClass _spi   = SPIClass(SCK,MISO,MOSI,CS_TMC2130);
    GPIOClass _en   = GPIOClass(EN, OUTPUT);
    GPIOClass _dir  = GPIOClass(DIR, OUTPUT);
    GPIOClass _step = GPIOClass(STEP, OUTPUT);
    GPIOClass _diag0 = GPIOClass(DIAG0,INPUT_PULLUP);
    GPIOClass _diag1 = GPIOClass(DIAG1,INPUT_PULLUP);
    DebugClass _debug = DebugClass(LEDR,LEDG,LEDB,LOW);

    unsigned long _stepsToDo;
    bool _calcStep = true;

public:
    TMC2130Class();
    void Write(tmc_add add, tmc_write dataOut);
    tmc_read Read(tmc_add add);
    void Init();
    void checkDiag(void);
    int Rotation(float degree, float microstep, int direction);
    void Endis(bool endis);
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
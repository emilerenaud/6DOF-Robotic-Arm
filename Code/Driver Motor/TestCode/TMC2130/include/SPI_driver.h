#ifndef SPI_DRIVER_H
#define SPI_DRIVER_H

#include <Arduino.h>
#include "configuration.h"


class SPIClass
{
private:
    int _SCK;
    int _MISO;
    int _MOSI;
    int _CS;

    void spi_delay(void);
    void clock_low(void);
    void clock_high(void);
    
public:
    SPIClass(const int inSCK, const int inMISO, const int inMOSI, const int inCS);
    void enableDevice(void);
    void disableDevice(void);
    unsigned char readByte(void);
    void writeByte(unsigned char byte);
    unsigned char readWritebyte(unsigned char byte);

};

#endif
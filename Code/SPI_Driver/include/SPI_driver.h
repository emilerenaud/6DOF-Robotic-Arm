#ifndef SPI_DRIVER_H
#define SPI_DRIVER_H

#include <Arduino.h>
#include "configuration.h"

void spi_init(const int chip_select);
void spi_writeByte(unsigned char data);
unsigned char spi_readByte(void);
void clock_low(void);
void clock_high(void);
void spi_delay(void);

#endif
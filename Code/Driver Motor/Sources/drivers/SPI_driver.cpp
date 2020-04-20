#include "SPI_driver.h"

SPIClass::SPIClass(const int inSCK, const int inMISO, const int inMOSI, const int inCS)
{
    _SCK = inSCK;
    _MISO = inMISO;
    _MOSI = inMOSI;
    _CS = inCS;

    // Init pin
    pinMode(_SCK,OUTPUT);
    pinMode(_MISO,INPUT);
    pinMode(_MOSI,OUTPUT);
    pinMode(_CS,OUTPUT);

    SPIClass::disableDevice();  // Disable device.
    SPIClass::clock_high();       // Pull down clock.
}   // end SPIClass

void SPIClass::enableDevice()
{
    digitalWrite(_CS,LOW);  // Enable device.
}   // end enableDevice

void SPIClass::disableDevice()
{
    digitalWrite(_CS,HIGH);  // Disable device.
}   // end disableDevice

unsigned char SPIClass::readByte()
{
    unsigned char byte = 0;
    for(int i=0; i<8; i++)    // Send 8 bits
    {
        byte = byte << 1;
        SPIClass::clock_low();
        SPIClass::spi_delay();
        SPIClass::clock_high();
        if(digitalRead(_MISO))
            byte = byte + 0x01;
        
    }   // end for.
    return byte;
}   // end readbyte

void SPIClass::writeByte(unsigned char byte)
{
    for(int i=0; i<8; i++)    // Send 8 bits
    {
        
        if(byte & 0x80)                 // MSB is 1
            digitalWrite(_MOSI,HIGH);   // Pull high data line.
        else                            // MSB is 0
            digitalWrite(_MOSI,LOW);    // Pull down data line.
        SPIClass::clock_low();          // Pull down clock line.
        SPIClass::spi_delay();
        SPIClass::clock_high();         // Pull high clock line. The chip now see data.
        byte = byte << 1;               // Shift byte to send the next bit.
    }   // end for.
}   // end writeByte

unsigned char SPIClass::readWritebyte(unsigned char dataOut)
{
    unsigned char dataIn = 0;
    for(int i=0; i<8; i++)
    {
        dataIn = dataIn << 1;
        if(dataOut & 0x80)                 // MSB is 1
            digitalWrite(_MOSI,HIGH);   // Pull high data line.
        else                            // MSB is 0
            digitalWrite(_MOSI,LOW);    // Pull down data line.
        SPIClass::clock_low();
        SPIClass::spi_delay();
        SPIClass::clock_high();
        if(digitalRead(_MISO))
            dataIn = dataIn + 0x01;
        dataOut = dataOut << 1;               // Shift byte to send the next bit.
    }
    return dataIn;
}

// Private Function SPIClass

void SPIClass::clock_low()
{
    digitalWrite(_SCK,LOW);
}   // end clock_low

void SPIClass::clock_high()
{
    digitalWrite(_SCK,HIGH);
}   // end clock_high

void SPIClass::spi_delay()
{
    for(int j = 0; j<5; j++); 
}   // end spi_delay


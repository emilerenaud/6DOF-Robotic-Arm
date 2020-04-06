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
    SPIClass::clock_low();       // Pull down clock.
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
    for(int i = 0; i<8; i++)    // Send 8 bits
    {
        SPIClass::clock_high();
        SPIClass::spi_delay();
        if(digitalRead(_MISO))
            byte = byte + 0x01;
        byte = byte << 1;
        SPIClass::clock_low();
        
    }   // end for.
    return byte;
}   // end readbyte

void SPIClass::writeByte(unsigned char byte)
{
    for(int i = 0; i<8; i++)    // Send 8 bits
    {
        if(byte & 0x80)                 // MSB is 1
            digitalWrite(_MOSI,HIGH);   // Pull high data line.
        else                            // MSB is 0
            digitalWrite(_MOSI,LOW);    // Pull down data line.
        SPIClass::clock_high();         // Pull high clock line. The chip now see data.
        SPIClass::spi_delay();
        SPIClass::clock_low();          // Pull down clock line.
        byte = byte << 1;               // Shift byte to send the next bit.
    }   // end for.
}   // end writeByte

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


#include "SPI_driver.h"

int cs = 0;

void spi_init(const int chip_select)
{
    #ifndef SPI_EN
    #define SPI_EN
    #endif
    cs = chip_select;
    // Init pin
    pinMode(SCK,OUTPUT);
    pinMode(MISO,INPUT);
    pinMode(MOSI,OUTPUT);
    pinMode(cs,OUTPUT);

    digitalWrite(cs,HIGH);  // disable device.
    digitalWrite(SCK,LOW);  // pull down clock.
}

void spi_writeByte(unsigned char data)
{
    digitalWrite(cs,LOW);       // Activate chip.
    for(int i = 0; i<8; i++)    // Send 8 bits
    {
        if(data & 0x80)                 // MSB is 1
            digitalWrite(MOSI,HIGH);    // Pull high data line.
        else                            // MSB is 0
            digitalWrite(MOSI,LOW);     // Pull down data line.
        clock_low();                    // Pull down clock line.
        spi_delay();
        clock_high();                   // Pull high clock line. The chip now see data.
        data = data << 1;               // Shift byte to send the next bit.
    }   // end for.
}   // end spi_writeByte.

unsigned char spi_readByte(void)
{
    unsigned char data = 0;
    digitalWrite(cs,LOW);       // Activate chip.
    for(int i = 0; i<8; i++)    // Send 8 bits
    {
        clock_low();
        spi_delay();
        clock_high();
        if(digitalRead(MISO))
            data = data + 0x01;
        data = data << 1;
    }   // end for.
    return data;
}   // end spi_readByte.

void clock_low()
{
    digitalWrite(SCK,LOW);
}

void clock_high()
{
    digitalWrite(SCK,HIGH);
}

void spi_delay()
{
    for(int j = 0; j<5; j++);
}
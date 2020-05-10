#include "init_stm32.h"

void init_stm32()
{
    pinMode(PA0,OUTPUT);        // CS_TMC2130
    pinMode(PA1,INPUT_PULLUP);  // HALL
    pinMode(PA2,OUTPUT);        // EN
    pinMode(PA3,OUTPUT);        // STEP
    pinMode(PA4,OUTPUT);        // DIR
    pinMode(PA5,OUTPUT);        // SCK
    pinMode(PA6,INPUT);         // MISO
    pinMode(PA7,OUTPUT);        // MOSI
    pinMode(PA8,INPUT_PULLUP);  // NOTHING
    pinMode(PA9,INPUT_PULLUP);  // NOTHING
    pinMode(PA10,INPUT_PULLUP); // NOTHING
    pinMode(PA11,INPUT_PULLUP); // NOTHING
    pinMode(PA12,OUTPUT);       // FAN
    // pinMode(PA13,INPUT_PULLUP); // SWDIO
    // pinMode(PA14,INPUT_PULLUP); // SWCLK
    pinMode(PA15,INPUT_PULLUP); // NOTHING

    pinMode(PB0,INPUT);         // TEMP
    pinMode(PB1,INPUT_PULLUP);  // NOTHING
    pinMode(PB2,INPUT);         // BOOT1
    pinMode(PB3,INPUT_PULLUP);  // NOTHING
    pinMode(PB4,INPUT_PULLUP);  // NOTHING;
    pinMode(PB5,OUTPUT);        // LEDR
    pinMode(PB6,OUTPUT);        // LEDG
    pinMode(PB7,OUTPUT);        // LEDB
    pinMode(PB8,INPUT_PULLUP);  // DIAG0
    pinMode(PB9,INPUT_PULLUP);  // DIAG1
    pinMode(PB10,OUTPUT);       // Tx
    pinMode(PB11,INPUT);        // Rx
    pinMode(PB12,OUTPUT);       // RxTx_En
    pinMode(PB13,INPUT_PULLUP); // DCO
    pinMode(PB14,OUTPUT);       // DCEN
    pinMode(PB15,OUTPUT);       // DCIN

    pinMode(PC13,INPUT_PULLUP); // NOTHING
    pinMode(PC14,INPUT_PULLUP); // NOTHING
    pinMode(PC15,INPUT_PULLUP); // NOTHING

}
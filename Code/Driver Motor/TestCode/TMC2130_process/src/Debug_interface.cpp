#include "Debug_interface.h"

DebugClass::DebugClass(){
}

DebugClass::DebugClass(uint8_t red, uint8_t green, uint8_t blue,uint8_t actifState){
    
    _red = GPIOClass(red, OUTPUT);
    _green = GPIOClass(green, OUTPUT);
    _blue = GPIOClass(blue, OUTPUT);
    _actifState = actifState;

    _red.Write(!_actifState);   /*Turned off on start*/
    _green.Write(!_actifState);
    _blue.Write(!_actifState);
}

void DebugClass::Write(bool redState, bool greenState, bool blueState){
    _red.Write(redState);
    _green.Write(greenState);
    _blue.Write(blueState);
}

void DebugClass::showError(uint8_t errorCode)
{
    if((errorCode & 0x04) == 0x04) // bit for Red.
        open_red();
    else
        close_red();
    
    if((errorCode & 0x02) == 0x02) // bit for Green.
        open_green();
    else
        close_green();
    
    if((errorCode & 0x01) == 0x01) // bit for Green.
        open_blue();
    else
        close_blue();
}

void DebugClass::open_red(void)
{
    _red.Write(_actifState);
}

void DebugClass::open_green(void)
{
    _green.Write(_actifState);
}

void DebugClass::open_blue(void)
{
    _blue.Write(_actifState);
}

void DebugClass::close_red(void)
{
    _red.Write(!_actifState);
}

void DebugClass::close_green(void)
{
    _green.Write(!_actifState);
}

void DebugClass::close_blue(void)
{
    _blue.Write(!_actifState);
}

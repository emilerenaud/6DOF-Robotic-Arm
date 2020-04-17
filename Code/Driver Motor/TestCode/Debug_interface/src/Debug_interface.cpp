#include "Debug_interface.h"

DebugClass::DebugClass(){
}

DebugClass::DebugClass(uint32_t red, uint32_t green, uint32_t blue){
    
    _red = GPIOClass(red, OUTPUT);
    _green = GPIOClass(green, OUTPUT);
    _blue = GPIOClass(blue, OUTPUT);

    _red.Write(HIGH);   /*Turned off on start*/
    _green.Write(HIGH);
    _blue.Write(HIGH);
}

void DebugClass::Write(int R, int G, int B){
    _red.Write(R);
    _green.Write(G);
    _blue.Write(B);
}

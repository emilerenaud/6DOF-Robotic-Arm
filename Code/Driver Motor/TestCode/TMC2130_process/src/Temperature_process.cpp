#include "Temperature_process.h"

Temperature_process::Temperature_process(){
}

/*ADJUST SPEED*/
void Temperature_process::Control(){

    int temp = _temp.Temperature();
    int speed = 0;

    if(temp > _tempHigh)
    {
        speed = 30 + (temp + 10 / 2);
        if(speed >= 100)
        {
            speed = 100;
        }
        _fan.set_power(speed);
        _fan.start(); // Needed. Not sur why.
    }
    else if(temp < _tempLow)    // Hysterisis Low
    {
        _fan.set_power(0);
    }
    
}
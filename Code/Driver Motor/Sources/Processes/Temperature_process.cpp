#include "Temperature_process.h"

Temperature_process::Temperature_process(){
}

/*ADJUST SPEED*/
void Temperature_process::Control(){

    int temp = _temp.Temperature();
    int speed = 0;

    if(temp > 25)
    {
        if((speed = temp * 1.5) > 99)
        {
            speed = 99;
        }
        _fan.set_power(speed);
        _fan.start();
    }
    else
    {
        _fan.stop();
    }
    
}
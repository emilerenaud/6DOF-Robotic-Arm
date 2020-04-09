#ifndef THERMISTOR_H
#define THERMISTOR_H

#include <Arduino.h>
     
// resistance at 25 degrees C
#define THERMISTORNOMINAL 100000      
// temp. for nominal resistance (almost always 25 C)
#define TEMPERATURENOMINAL 25  
// how many samples to take and average, more takes longer
// but is more 'smooth'
#define NUMSAMPLES 10
// The beta coefficient of the thermistor (usually 3000-4000)
#define BCOEFFICIENT 3950
// the value of the 'other' resistor
#define SERIESRESISTOR 100000

class thermistorClass
{
private:
    int _pin;
    int _samples[NUMSAMPLES];
    float _average;
    float _temperature;
    float read(void);
public:
    thermistorClass(const int pin);
    float readC(void);
    float readF(void);
};

#endif
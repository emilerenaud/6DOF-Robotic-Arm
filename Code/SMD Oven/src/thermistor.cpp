#include <thermistor.h>

thermistorClass::thermistorClass(const int pin)
{
    _pin = pin;
    analogReference(EXTERNAL);
}

float thermistorClass::read()
{
    // take N samples in a row, with a slight delay
    for(int i=0; i< NUMSAMPLES; i++) {
        _samples[i] = analogRead(_pin);
        delay(10);
    }

    // average all the samples out
    _average = 0;
    for (int i=0; i< NUMSAMPLES; i++) {
        _average += _samples[i];
    }
    _average /= NUMSAMPLES;

    // convert the value to resistance
    _average = 1023 / _average - 1;
    _average = SERIESRESISTOR / _average;

    return _average;
}

float thermistorClass::readF()
{
    _temperature = 0;
    _temperature = thermistorClass::read() / THERMISTORNOMINAL;     // (R/Ro)
    _temperature = log(_temperature);                  // ln(R/Ro)
    _temperature /= BCOEFFICIENT;                   // 1/B * ln(R/Ro)
    _temperature += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)
    _temperature = 1.0 / _temperature;                 // Invert
    
    return _temperature;
}

float thermistorClass::readC()
{
    _temperature = thermistorClass::readF();
    _temperature -= 273.15;             // convert to C
    
    return _temperature;
}
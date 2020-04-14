#include <oven.h>

Oven::Oven()
{
    _tempPreheat = 0;
    _maxTimePreheat = 0;
    _tempReflow = 0;
    _maxTimeReflow = 0;
}

Oven::Oven(int tempPreheat, int maxTimePreheat, int tempReflow, int maxTimeReflow, const int relayHighPin, const int relayLowPin)
{
    _tempPreheat = tempPreheat;
    _maxTimePreheat = maxTimePreheat;
    _tempReflow = tempReflow;
    _maxTimeReflow = maxTimeReflow;
    _relayHighPin = relayHighPin;
    _relayLowPin = relayLowPin;
    _startTimer = 0;
    _safetyTimeReflow = 0;

    pinMode(_relayLowPin,OUTPUT);
    digitalWrite(_relayLowPin,LOW);
    pinMode(_relayHighPin,OUTPUT);
    digitalWrite(_relayHighPin,LOW);

    _thermistor = thermistorClass(A0);
}

void Oven::set_tempPreheat(int tempPreheat)
{
    _tempPreheat = tempPreheat;
}

void Oven::set_maxTimePreheat(int maxTimePreheat)
{
    _maxTimePreheat = maxTimePreheat;
}

void Oven::set_tempReflow(int tempReflow)
{
    _tempReflow = tempReflow;
}

void Oven::set_maxTimeReflow(int maxTimeReflow)
{
    _maxTimeReflow = maxTimeReflow;
}

int Oven::get_tempPreheat()
{
    return _tempPreheat;
}

int Oven::get_maxTimePreheat()
{
    return _maxTimePreheat;
}

int Oven::get_tempReflow()
{   
    return _tempReflow;
}

int Oven::get_maxTimeReflow()
{
    return _maxTimeReflow;
}

int Oven::get_currentTemp()
{
    return _thermistor.readC();
}

bool Oven::preheat()
{
    if(_thermistor.readC() < (_tempPreheat - 5))
    {
        Oven::startHeat();
    }
    else if(_thermistor.readC() > (_tempPreheat + 5))
    {
        Oven::stopHeat();
    }
    else
    {
        // Right spot
        if(_startTimer == 0)
        {
            _startTimer = 1;
            secondCounter = 0;
        }
        if(secondCounter > _maxTimePreheat)
        {
            _startTimer = 0;
            return 1;
        }
        else
        {
            Serial.println("seconde = " + String(secondCounter));
        }
        
        
    }
    return 0;
}


bool Oven::reflow()
{
    if(_thermistor.readC() < (_tempReflow - 2))
    {
        Oven::startHeat();
    }
    else if(_thermistor.readC() > (_tempReflow + 2))
    {
        Oven::stopHeat();
    }
    else
    {
        // Right spot
        if(_startTimer == 0)
        {
            _startTimer = 1;
            secondCounter = 0;
            _safetyTimeReflow = millis();
        }
        if(secondCounter > _maxTimeReflow)
        {
            _startTimer = 0;
            return 1;
        }
        else
        {
            Serial.println("seconde = " + String(secondCounter));
        }
        unsigned long elapsedTime = millis() - _safetyTimeReflow;
        if(elapsedTime > 75000)
        {
            Oven::stopHeat();
            Serial.println("Safety trigged");
            return 1;
        }
    }
    return 0;
}

bool Oven::cooling()
{

    Oven::stopHeat();
    return 1;
}

void Oven::startHeat()
{
    digitalWrite(_relayLowPin,LOW);
    digitalWrite(_relayHighPin,HIGH);
}

void Oven::stopHeat()
{
    digitalWrite(_relayLowPin,LOW);
    digitalWrite(_relayHighPin,LOW);
}
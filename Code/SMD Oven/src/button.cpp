#include <button.h>


button::button(int pin, bool pushState, int ledPin, bool onState)
{
    _pin = pin;
    _pushState = pushState;
    _lastState = !pushState;
    _ledPin = ledPin;
    _ledOnState = onState;

    pinMode(_pin,INPUT);
    pinMode(_ledPin,OUTPUT);
}

bool button::read()
{
    _state = digitalRead(_pin);
    if(_state != _lastState)
    {
        delay(20); // rebond
        if(_state == _pushState)
        {
            _lastState = _state;
            return 1;
        }
        else
        {
            _lastState = _state;
            return 0;
        }
        
    }
    return 0;
}

void button::ledOn()
{
    digitalWrite(_ledPin,_ledOnState);
}

void button::ledOff()
{
    digitalWrite(_ledPin, (!_ledOnState));
}
#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

class button
{
private:
    int _pin;
    bool _state;
    bool _lastState;
    bool _pushState;

    int _ledPin;
    bool _ledOnState;

public:
    button(int pin, bool pushState, int ledPin, bool onState);
    bool read(void);
    void set_pin(const int pin);
    void ledOn(void);
    void ledOff(void);

};

#endif
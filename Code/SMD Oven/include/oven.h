#ifndef OVEN_H
#define OVEN_H

#include <Arduino.h>
#include <thermistor.h>

extern int secondCounter;

class Oven
{
private:
    int _tempPreheat;
    int _maxTimePreheat;
    int _tempReflow;
    int _maxTimeReflow;
    int _currentTemp;
    int _relayHighPin;
    int _relayLowPin;
    int _startTimer;
    unsigned long _safetyTimeReflow;

    thermistorClass _thermistor;

    void startHeat(void);
    void stopHeat(void);

public:
    Oven();
    Oven(int tempPreheat, int maxTimePreheat, int tempReflow, int maxTimeReflow, const int relayHighPin, const int relayLowPin);
    
    void set_tempPreheat(int tempPreheat);
    void set_maxTimePreheat(int maxTimePreheat);
    void set_tempReflow(int tempReflow);
    void set_maxTimeReflow(int maxTimeReflow);

    int get_tempPreheat(void);
    int get_maxTimePreheat(void);
    int get_tempReflow(void);
    int get_maxTimeReflow(void);
    int get_currentTemp(void);

    bool preheat(void);
    bool reflow(void);
    bool cooling(void);
};



#endif
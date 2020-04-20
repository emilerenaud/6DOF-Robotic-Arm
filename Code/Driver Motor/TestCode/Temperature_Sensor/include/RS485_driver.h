#ifndef RS485_H
#define RS485_H

#include "Arduino.h"
#include <configuration.h>


class RS485Class {   
  private:
    HardwareSerial _rxtx = HardwareSerial(USART3);
  public:
    RS485Class();
    RS485Class(unsigned long baud);
    int Read(void);  
    void Write(int data); 
    void Print(const char * data); 
};

#endif
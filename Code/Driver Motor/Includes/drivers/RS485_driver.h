#ifndef RS485_H
#define RS485_H

#define START LOW
#define STOP  HIGH

#include "Arduino.h"
#include <configuration.h>


class RS485Class {   
  private:
    HardwareSerial _rxtx = HardwareSerial(USART3);
  public:
    RS485Class();
    RS485Class(unsigned long baud);
    void set_input(void);
    int Read(void);  
    void Write(int data); 
};

#endif
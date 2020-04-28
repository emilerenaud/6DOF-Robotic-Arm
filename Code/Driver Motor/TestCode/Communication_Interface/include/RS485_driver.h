#ifndef RS485_H
#define RS485_H

#define START LOW
#define STOP  HIGH

#include "Arduino.h"
#include <configuration.h>


class RS485Class {   
  private:
    HardwareSerial _rxtx = HardwareSerial(USART3);
    int _dataRead;
  public:
    RS485Class();
    RS485Class(unsigned long baud);
    void set_input(void);
    bool data_available(void);
    int Read(void);  
    void Write(int data); 
};

#endif
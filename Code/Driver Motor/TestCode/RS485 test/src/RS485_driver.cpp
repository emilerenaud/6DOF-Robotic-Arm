#include "RS485_driver.h"

RS485Class::RS485Class(){
}

RS485Class::RS485Class(unsigned long baud){
  pinMode(RXTX_EN, OUTPUT);
  set_input();
  _rxtx.begin(baud);
  
}

void RS485Class::set_input(void)
{
  digitalWrite(RXTX_EN, READ);
}

uint8_t RS485Class::data_available()
{
  if(_rxtx.available() > 0)
    return _rxtx.available();               // return 1 if there are data in the buffer.
  else
    return 0;
}


int RS485Class::Read(void){
  digitalWrite(RXTX_EN, READ);
  _dataRead = _rxtx.read();
  if(_dataRead != -1)
    return _dataRead;
  else
    return 0;
}


void RS485Class::Write(int data){
  digitalWrite(RXTX_EN, WRITE);
  delay(1);
  _rxtx.write(data);
  delay(1);     // seems to work fine.
  _rxtx.read(); // read to clear the input buffer.
}


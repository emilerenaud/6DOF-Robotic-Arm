#include "RS485_driver.h"

RS485Class::RS485Class(){
}

RS485Class::RS485Class(unsigned long baud){
  pinMode(RXTX_EN, OUTPUT);
  _rxtx.begin(baud);
}

int RS485Class::Read(void){
  digitalWrite(RXTX_EN, READ);
  return _rxtx.read();
}

void RS485Class::Write(int data){
  digitalWrite(RXTX_EN, WRITE);
  _rxtx.write(data);
}
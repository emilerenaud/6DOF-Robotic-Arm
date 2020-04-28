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

bool RS485Class::data_available()
{
  if(_rxtx.available() > 0)
    return 1;
  else
    return 0;
}

int RS485Class::Read(void){
  digitalWrite(RXTX_EN, READ);
  return _rxtx.read();
}


void RS485Class::Write(int data){
  digitalWrite(RXTX_EN, WRITE);
  _rxtx.write(data);
  delay(2);     // seems to work fine.
  set_input();  // Always set in input after write.
}


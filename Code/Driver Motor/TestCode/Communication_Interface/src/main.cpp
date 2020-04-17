#include <Arduino.h>
#include <Communication_interface.h>

ComClass com = ComClass();

void setup() {
  
}

void loop() {
  SEND_U send;
  RECEIVE_U receive;

  send.sendBytes.firstByte = 0x11;
  send.sendBytes.secondByte = 0x22;
  send.sendBytes.thirdByte = 0x33;
  com.Write(send);

  receive = com.Read();

  send.sendBytes.firstByte = receive.receiveBytes.firstByte;
  send.sendBytes.secondByte = receive.receiveBytes.secondByte;
  send.sendBytes.thirdByte = receive.receiveBytes.thirdByte;
  com.Write(send);

  delay(200);
}
#include <Arduino.h>
#include <Communication_interface.h>
#include <Timer_driver.h>

ComClass com = ComClass();

uint8_t buffer[64];
uint8_t i = 0;
SEND_U send;
RECEIVE_U receive;

void checkData(void)
{
  com.checkData();

}

void setup() {
  pinMode(LEDB,OUTPUT);
  pinMode(LEDR,OUTPUT);
  digitalWrite(LEDB,HIGH);
  digitalWrite(LEDR,HIGH);
  init_timer_COM(checkData);
}

void loop() {
  // send.sendBytes.firstByte = 0x11;
  // send.sendBytes.secondByte = 0x22;
  // send.bits.debug = 0x61;
  // com.Write(send); // works well.
  // digitalWrite(LEDB,HIGH);
  // i = 0;
  // while(com.rs485.data_available())
  // {
  //   buffer[i] = com.rs485.Read();
  //   i++;
  // }
  // for(int j = 0; j <= i; j ++)
  // {
  //   com.rs485.Write(buffer[j]);
  // }

  // delay(100);
  // digitalWrite(LEDB,LOW);
  delay(3000);
}
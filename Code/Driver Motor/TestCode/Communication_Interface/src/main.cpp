#include <Arduino.h>
#include <Communication_interface.h>
#include <Timer_driver.h>

ComClass COM = ComClass();

void process_COM(void)
{
  COM.processData();
}

void setup() {
  pinMode(LEDB,OUTPUT);
  init_timer_COM(process_COM);
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
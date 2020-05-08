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
  pinMode(LEDG,OUTPUT);
  pinMode(LEDR,OUTPUT);
  init_timer_COM(process_COM);
}

void loop() {
  uint16_t position = (uint16_t(COM._receive.bits.position) << 1) + COM._receive.bits.firstbit;

  if(position == 186)
  {
    digitalWrite(LEDR, LOW);
  }
  else
  {
    digitalWrite(LEDR, HIGH);
  }
  
  if(position == 2)
  {
    digitalWrite(LEDG, LOW);
  }
  else
  {
     digitalWrite(LEDG, HIGH);
   }

  if(position == 300)
  {
    digitalWrite(LEDB, LOW);
  }
  else
  {
    digitalWrite(LEDB, HIGH);
  }

  delay(500);
}
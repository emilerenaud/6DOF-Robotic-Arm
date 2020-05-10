#include <Arduino.h>


#define PB5pin PB5
HardwareTimer *timerCOM = new HardwareTimer(TIM2);
HardwareSerial _rxtx = HardwareSerial(USART3);

void Update_IT_callback(HardwareTimer*)
{ // Toggle pin. 10hz toogle --> 5Hz PWM
  digitalWrite(PB5, !digitalRead(PB5));
  Serial.println(_rxtx.available());


}

void setup() {
  
  Serial.begin(9600);
  Serial.println("Start");
  pinMode(PB5,OUTPUT);
  pinMode(PB12,OUTPUT);
  digitalWrite(PB12,LOW);
  _rxtx.begin(9600);
  // timerCOM->setMode()
  timerCOM->setOverflow(10,HERTZ_FORMAT);
  timerCOM->attachInterrupt(Update_IT_callback);
  timerCOM->resume();
  
  //timerCOMput your setup code here, to run once:
}

void loop() {
  Serial.println("Loop");
  if(_rxtx.available() > 0)
  {
    _rxtx.read();
    digitalToggle(PB5);
  }
  // put your main code here, to run repeatedly:
  delay(500);
}
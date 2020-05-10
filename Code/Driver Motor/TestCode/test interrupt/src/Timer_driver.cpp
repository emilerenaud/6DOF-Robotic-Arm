#include <Timer_driver.h>
#define DEBUG_TIMER_DRIVER_COM
HardwareTimer *timerPWM = new HardwareTimer(TIM1);
HardwareTimer *timerCOM = new HardwareTimer(TIM2);



//---------- TIMER SERIAL ----------//
// VARIABLE
void (*pFunction)(void);

void init_timer_COM(void(*pFunctionToSet)(void))
{
    pFunction = (*pFunctionToSet);

    #ifdef DEBUG_TIMER_DRIVER_COM
    timerCOM->setOverflow(10, HERTZ_FORMAT); // 10ms
    pinMode(LEDR,OUTPUT);
    #else
    timerCOM->setOverflow(100, HERTZ_FORMAT); // 10ms
    #endif

    timerCOM->attachInterrupt(callback_timer_COM);
    timerCOM->resume();
}

void setFunction_timer_COM(void(*pFunctionToSet)(void))
{
    pFunction = (*pFunctionToSet);
}

void callback_timer_COM(HardwareTimer*)
{
    (*pFunction)();
    
    #ifdef DEBUG_TIMER_DRIVER_COM
    digitalWrite(LEDR,!digitalRead(LEDR)); // Debug
    #endif
}


//---------- TIMER PWM ----------//
// VARIABLES 
uint8_t PWM_pin;
uint8_t PWM_cycleCount = 0;
uint8_t PWM_dutyCycle = 0;

// FUNCTIONS
void init_timer_PWM(uint8_t pin)
{
    PWM_pin = pin;
    timerPWM->setOverflow(1000, HERTZ_FORMAT); // 1ms
    timerPWM->attachInterrupt(callback_timer_PWM);
    timerPWM->resume();
}

void callback_timer_PWM(HardwareTimer*)
{
  if(PWM_cycleCount <= PWM_dutyCycle)
    digitalWrite(PWM_pin,1); // enable gpio.
  else
  {
    digitalWrite(PWM_pin,0); // disable gpio.
    if(PWM_cycleCount == 100)
      PWM_cycleCount = 0;
  }
  PWM_cycleCount ++;
}

void start_timer_PWM(void)
{
    timerPWM->resume();
}

void stop_timer_PWM(void)
{
    timerPWM->pause();
}

void set_pin_Timer_PWM(uint8_t pin)
{
    PWM_pin = pin;
}

void set_dutyCycle_Timer_PWM(uint8_t dutyCycle)
{
    PWM_dutyCycle = dutyCycle;
}



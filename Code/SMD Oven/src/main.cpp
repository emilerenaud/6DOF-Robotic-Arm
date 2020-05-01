#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <button.h>
#include <thermistor.h>
#include <oven.h>


// Define PIN
#define relayHighPin 12
#define relayLowPin 13

// Oven Mode
#define IDLE 0
#define PREHEAT 1
#define REFLOW 2
#define COOLING 3
#define INIT 4

// Setup Choice
#define PREHEAT_TEMP 0
#define PREHEAT_TIME 1
#define REFLOW_TEMP 2
#define REFLOW_TIME 3

// Prototype
void lcdPrint(char lcdToPrint[4][21]);
void gestionOven(void);
void setupTimer(void);

// Objects & Var
int secondCounter = 0;
LiquidCrystal_I2C lcd(0x27,20,4);
bool readyToPrint = 1;


char lcdMain[4][21] = { {"      SMD Oven      "},
                        {"                    "},
                        {"                    "},
                        {"                    "}};

char lcdOld[4][21] =  { {"                    "},
                        {"                    "},
                        {"                    "},
                        {"                    "}};

char lcdSetup[4][21] = {{" PreHeat Temp:    *C"},
                        {" Preheat Time:     S"},
                        {" Reflow  Temp:    *C"},
                        {" Reflow  Time:     S"}};

char setupChoice = PREHEAT_TEMP;
bool prepToReflow = 0;

char okCounter = 0;
char tempVar = 0;

button buttonOk(3,0,8,1);
button buttonUp(4,0,9,1);
button buttonDown(5,0,10,1);
button buttonSetup(6,0,11,1);

Oven oven(150,90,217,50,relayHighPin,relayLowPin);

int ovenState = IDLE;
int oldTemperature = 0;
int counter = 0;
int diviseur = 0;

void setup() {

  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  lcdPrint(lcdMain);

  setupTimer();  

  Serial.begin(9600);

}

void loop()
{
  if(buttonSetup.read())
  {
    if(ovenState == IDLE)
      ovenState = INIT;
    else if(ovenState == INIT)
      ovenState = IDLE;
  }

  gestionOven();
}

void setupTimer()
{
  cli();//stop interrupts

  //set timer1 interrupt at 1Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 15624;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12 and CS10 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  sei();//allow interrupts
}

ISR(TIMER1_COMPA_vect)
{
  secondCounter++;
}

void lcdPrint(char lcdToPrint[4][21])
{
  bool printOnLcd = 0;
  for(int i=0; i<4; i++)
    {
      for(int j=0; j<20; j++)
        if(lcdOld[i][j] != lcdToPrint[i][j])
          printOnLcd = 1;
    } 

  if(printOnLcd)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(lcdToPrint[0]);
    lcd.setCursor(0,1);
    lcd.print(lcdToPrint[1]);
    lcd.setCursor(0,2);
    lcd.print(lcdToPrint[2]);
    lcd.setCursor(0,3);
    lcd.print(lcdToPrint[3]);

    for(int i=0; i<4; i++)
    {
      for(int j=0; j<20; j++)
        lcdOld[i][j] = lcdToPrint[i][j];
    }  
  }
}

void gestionOven()
{
  if(ovenState != INIT)
  {
      if(oven.get_currentTemp() != oldTemperature)
      {
      lcd.setCursor(0,3);
      lcd.print("Current Temp : ");
      lcd.print(oven.get_currentTemp());
      oldTemperature = oven.get_currentTemp();
      lcd.print("*C ");
      }
    
  }
  switch(ovenState)
  {
    case INIT:
      oldTemperature = 0;
      prepToReflow = 0;
      if(buttonOk.read())
      {
        okCounter ++;
        okCounter &= 0x01;
      }
      if(buttonUp.read())
      {
        if(okCounter == 0)
        {
          setupChoice --;
          if(setupChoice < 0)
            setupChoice = 0;
        }
        else
        {
          tempVar ++;
        }
      }
      if(buttonDown.read())
      {
        if(okCounter == 0)
        {
          setupChoice ++;
          if(setupChoice > 3)
            setupChoice = 3;
        }
        else
        {
          tempVar --;
        }
        
      }
      switch(setupChoice)
      {
        char stringTemp[3];

        case PREHEAT_TEMP:
          if(tempVar != 0)
          {
            oven.set_tempPreheat(oven.get_tempPreheat() + tempVar);
            tempVar = 0;
          }
          lcdSetup[0][0] = '>';
          sprintf(stringTemp, "%d", oven.get_tempPreheat());
          lcdSetup[0][14] = stringTemp[0];
          lcdSetup[0][15] = stringTemp[1];
          lcdSetup[0][16] = stringTemp[2];
          lcdSetup[0][18] = '*';
          lcdSetup[0][19] = 'C';
          lcdSetup[1][0] = ' ';
          lcdSetup[2][0] = ' ';
          lcdSetup[3][0] = ' ';
        break;
        case PREHEAT_TIME:
          if(tempVar != 0)
          {
            oven.set_maxTimePreheat(oven.get_maxTimePreheat() + tempVar);
            tempVar = 0;
          }
          lcdSetup[0][0] = ' ';
          lcdSetup[1][0] = '>';
          sprintf(stringTemp, "%d", oven.get_maxTimePreheat());
          lcdSetup[1][14] = stringTemp[0];
          lcdSetup[1][15] = stringTemp[1];
          if(oven.get_maxTimePreheat() >= 100)
            lcdSetup[1][16] = stringTemp[2];
          lcdSetup[1][19] = 'S';
          lcdSetup[2][0] = ' ';
          lcdSetup[3][0] = ' ';
        break;
        case REFLOW_TEMP:
          if(tempVar != 0)
          {
            oven.set_tempReflow(oven.get_tempReflow() + tempVar);
            tempVar = 0;
          }
          lcdSetup[0][0] = ' ';
          lcdSetup[1][0] = ' ';
          lcdSetup[2][0] = '>';
          sprintf(stringTemp, "%d", oven.get_tempReflow());
          lcdSetup[2][14] = stringTemp[0];
          lcdSetup[2][15] = stringTemp[1];
          lcdSetup[2][16] = stringTemp[2];
          lcdSetup[2][18] = '*';
          lcdSetup[2][19] = 'C';
          lcdSetup[3][0] = ' ';
        break;
        case REFLOW_TIME:
          if(tempVar != 0)
          {
            oven.set_maxTimeReflow(oven.get_maxTimeReflow() + tempVar);
            tempVar = 0;
          }
          lcdSetup[0][0] = ' ';
          lcdSetup[1][0] = ' ';
          lcdSetup[2][0] = ' ';
          lcdSetup[3][0] = '>';
          sprintf(stringTemp, "%d", oven.get_maxTimeReflow());
          lcdSetup[3][14] = stringTemp[0];
          lcdSetup[3][15] = stringTemp[1];
          if(oven.get_maxTimeReflow() >= 100)
            lcdSetup[3][16] = stringTemp[2];
          lcdSetup[3][19] = 'S';
      }
      lcdPrint(lcdSetup);

    break;

    case IDLE:
      lcdPrint(lcdMain);
      if(buttonOk.read())
      {
        if(prepToReflow == 0)
        {
          lcd.setCursor(0,1);
          lcd.print("Start the Oven ?    ");
          lcdPrint(lcdMain);
          prepToReflow = 1;
        }
        else if(prepToReflow == 1)
        {
          lcd.setCursor(0,1);
          lcd.print("Starting the Oven...");
          lcdPrint(lcdMain);
          ovenState = PREHEAT;
          readyToPrint = 1;
        }
      }
    break;

    case PREHEAT:
      if(buttonOk.read())
      {
        ovenState = COOLING;
        prepToReflow = 0;
        readyToPrint = 1;
        return;
      }
      if(readyToPrint)
      {
        lcd.setCursor(0,1);
        lcd.print("State : Preheat     ");
        readyToPrint = 0;
      }
      if(diviseur == 4)
      {
        diviseur = 0;
        if(oven.preheat())
        {
          ovenState = REFLOW;
          readyToPrint = 1;
        }
      }
        diviseur ++;
    break;

    case REFLOW:
      if(buttonOk.read())
      {
        ovenState = COOLING;
        prepToReflow = 0;
        readyToPrint = 1;
        return;
      }
      if(readyToPrint)
      {
        lcd.setCursor(0,1);
        lcd.print("State : Reflow      ");
        readyToPrint = 0;
      }
      if(diviseur == 4)
      {
        diviseur = 0;
        if(oven.reflow())
        {
          ovenState = COOLING;
          readyToPrint = 1;
        }
      }
      diviseur ++;
      
    break;

    case COOLING:
      if(readyToPrint)
      {
        lcd.setCursor(0,1);
        lcd.print("State : Cooling     ");
        readyToPrint = 0;
      }
      if(oven.cooling())
      {
        ovenState = IDLE;
        readyToPrint = 1;
      }
    break;
  }
}
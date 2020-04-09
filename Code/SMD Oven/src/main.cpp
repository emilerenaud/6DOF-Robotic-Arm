#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <button.h>
#include <thermistor.h>

#define relayInit pinMode(13,OUTPUT);
#define relayOn digitalWrite(13,HIGH);
#define relayOff digitalWrite(13,LOW);
// Prototype
void lcdMenu(void);

// Objects & Var
LiquidCrystal_I2C lcd(0x27,20,4);
float temperature = 0;
char lcd_Row_1[21] = {"      SMD Oven      "};
char lcd_Row_2[21] = {"Temp:     *C        "};
char lcd_Row_3[21] = {"                    "};
char lcd_Row_4[21] = {"                    "};

thermistorClass thermistor(A0);
button button1(3,0,8,1);
button button2(4,0,9,1);
button button3(5,0,10,1);
button button4(6,0,11,1);

int counter = 0;

void setup() {

  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  lcd.setCursor(5,0);
  lcd.print("SMD Oven");
  pinMode(8,OUTPUT);
  relayInit;
  Serial.begin(9600);

}

void loop()
{
  temperature = thermistor.readC();
  lcdMenu();
  lcd.setCursor(5,1);
  lcd.print(temperature);
  if(button1.read() == 1)
  {
    
    counter ++;
    Serial.println(counter);
  }
  if(counter & 0x01)
  {
    relayOn;
    button1.ledOn();
    lcd.setCursor(0,1);
  }
  else
  {
    relayOff;
    button1.ledOff();
    lcd.setCursor(0,1);
  }
  
  
  delay(100);
 
}

void lcdMenu()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(lcd_Row_1);
  lcd.setCursor(0,1);
  lcd.print(lcd_Row_2);
  lcd.setCursor(0,2);
  lcd.print(lcd_Row_3);
  lcd.setCursor(0,3);
  lcd.print(lcd_Row_4);
}
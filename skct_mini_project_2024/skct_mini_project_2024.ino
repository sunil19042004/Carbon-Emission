#include <ThingSpeak.h>
#include <LCD_I2C.h>
#include "ESP_Wahaj.h"
#include <Wire.h>
int flag2=0;
String st = "";
uint32_t tsLastReport = 0;
LCD_I2C lcd(0x27);
int flag=0;
const int threshold = 60; // Gas level threshold
int gasAboveThresholdCount = 0; // Counter for consecutive readings above threshold

void setup()
{
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("VEHICLE");
  lcd.setCursor(0, 1);
  lcd.print("SMOKE DETECTION");
  delay(5000);
  lcd.clear();
     start("Project","12345678");

  // Your existing setup code
  pinMode(D5, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(A0, INPUT);

  digitalWrite(D5, LOW);
  digitalWrite(D4, HIGH);

  // Start ThingSpeak
  ThingSpeak.begin(client);
}

void loop()
{
  int a = analogRead(A0);
  lcd.setCursor(0, 0);
  lcd.print("GAS LEVEL");
  lcd.setCursor(0, 1);
  lcd.print(a);
  delay(2000);
  lcd.clear();

  if ((a > threshold)&&flag2==0)
  {
    flag=1;
    gasAboveThresholdCount++;

    // Buzzer on and display on LCD for every gas level above 500
    digitalWrite(D5, HIGH);
    lcd.print(gasAboveThresholdCount);
    lcd.setCursor(0, 1);
    lcd.print("CARBON DETECTED");
    delay(500);
    lcd.clear();
    st = "TN45TH1004";
      ThingSpeak.setField(1, gasAboveThresholdCount);
      ThingSpeak.setField(2, a); // Assuming 'a' is the gas level
      ThingSpeak.setField(3, st);
      int x = ThingSpeak.writeFields(558170, "3CGD9PV3LKUFI6NY");
      int per = ThingSpeak.readIntField(549041, 1);  
    if (gasAboveThresholdCount >= 3)
    {
      gasAboveThresholdCount=0;
      // If gas level above 500 for 3 consecutive times, set D4 low and send data to ThingSpeak
      if(flag==0)
      {
        flag=1;
      digitalWrite(D4, LOW);
      
      }
      
if(per==2)
{
  digitalWrite(D4, HIGH);
  }
  else if(per==3)
  {
    
    digitalWrite(D4, LOW);
    }
      // Reset the counter after taking action
      
    }
  }
  else if(a < threshold){
    flag2=0;
    digitalWrite(D5, LOW);
     int per = ThingSpeak.readIntField(549041, 1);  
if(per==2)
{
  digitalWrite(D4, HIGH);
  }
    }
 

  // Your existing ThingSpeak code
}

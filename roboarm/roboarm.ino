#include <FastIO.h>
#include <I2CIO.h>
/*#include <LCD.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal_I2C_ByVac.h>
#include <LiquidCrystal_SR.h>
#include <LiquidCrystal_SR1W.h>
#include <LiquidCrystal_SR2W.h>
#include <LiquidCrystal_SR3W.h>*/

#include<Wire.h>

#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

Servo servo1; Servo servo2; Servo servo3;
byte serial[4];
byte serialOld[3];
boolean firstTime=false;
boolean one=false;
boolean two=false;
boolean three=false;
boolean all=false;

int ledPin =  13;      // the number of the LED pin
int buttonPin = 7;
int buttonState = 0;

void setup() 
{
  pinMode(buttonPin, INPUT);
  pinMode(7, OUTPUT);   //Magnet control pin
  pinMode(ledPin, OUTPUT);
  
  lcd.begin(16,2);

  pinMode(1,OUTPUT);
  servo1.attach(9); 
  servo2.attach(10); 
  servo3.attach(11); 
  
  //pinMode(11,OUTPUT);
  //pinMode(11,LOW);
  Serial.begin(9600);
}

void loop() {
  if(!firstTime)
  {
    serial[0]=70;
    serial[1]=40;
    serial[2]=120;
    serialOld[0]=70;
    serialOld[1]=40;
    serialOld[2]=120;
    servo1.write(serial[0]);
    servo2.write(serial[1]);
    servo3.write(serial[2]);
    firstTime=true;
  }
  while(Serial.available()>3)
  {

    for(int i=0; i<4; i++)
      serial[i]=Serial.read();
    one=false;
    two=false;
    three=false;
  }
   
//-----------------------This section accounts for innacuracies in the elbow and end servo potentiometers
  serial[1] = map(serial[1], 0, 180, 20, 180);
  
  serial[2] = map(serial[2], 0, 180, 20, 180);
//------------------------
      
  while(!one||!two||!three)
  {    
  if(serial[0]>serialOld[0])
  {
    serialOld[0]++;
    servo1.write(serialOld[0]);
  }
  if(serial[0]<serialOld[0])
  {
    serialOld[0]--;
    servo1.write(serialOld[0]);
  }
  if(serial[0]==serialOld[0])
    one=true;
    
    
  if(serial[1]>serialOld[1])
  {
    serialOld[1]++;
    servo2.write(serialOld[1]);
  }
  if(serial[1]<serialOld[1])
  {
    serialOld[1]--;
    servo2.write(serialOld[1]);
  }
  if(serial[1]==serialOld[1])
    two=true;
    
    
  if(serial[2]>serialOld[2])
  {
    serialOld[2]++;
    servo3.write(serialOld[2]);
  }
  if(serial[2]<serialOld[2])
  {
    serialOld[2]--;
    servo3.write(serialOld[2]);
  }
  if(serial[2]==serialOld[2])
    three=true;
    
  /*if(one)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(int(serial[0]));
  
    lcd.setCursor(5, 0);
    lcd.print(int(serial[1]));
  
    lcd.setCursor(10, 0);
    lcd.print(int(serial[2]));
  }*/
  
  
  //button control for magnet 
  //buttonState = digitalRead(buttonPin);
  
  if (serial[3] == HIGH) 
  {     
    // Magnet on:    
    digitalWrite(8, HIGH);
    digitalWrite(ledPin, HIGH);
  } 
  else 
  {
    // Magnet off:
    digitalWrite(8, LOW);
    digitalWrite(ledPin, LOW);
  }
  
  delay(50);
  }
}

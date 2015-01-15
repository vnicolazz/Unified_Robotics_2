#include <FastIO.h>
#include <I2CIO.h>
#include <LCD.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal_I2C_ByVac.h>
#include <LiquidCrystal_SR.h>
#include <LiquidCrystal_SR1W.h>
#include <LiquidCrystal_SR2W.h>
#include <LiquidCrystal_SR3W.h>

#include<Wire.h>

#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

Servo servo1; Servo servo2; Servo servo3;
char serial[3];
char serialOld[3];
boolean firstTime=false;
boolean one=false;
boolean two=false;
boolean three=false;
boolean all=false;



void setup() 
{
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
    serial[1]=30;
    serial[2]=120;
    serialOld[0]=70;
    serialOld[1]=30;
    serialOld[2]=120;
    servo1.write(serial[0]);
    servo2.write(serial[1]);
    servo3.write(serial[2]);
    firstTime=true;
  }
  while(Serial.available()>2)
  {
    for(int i=0;i<3;i++)
      serial[i]=Serial.read();
    one=false;
    two=false;
    three=false;
  }
  
  if(serial[0] < 0)
    serial[0] += 256;
  if(serial[1] < 0)
    serial[1] += 256;
  if(serial[2] < 0)
    serial[2] += 256;
    
  if(serialOld[0] < 0)
    serialOld[0] += 256;
  if(serialOld[1] < 0)
    serialOld[1] += 256;
  if(serialOld[2] < 0)
    serialOld[2] += 256;
      
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
    
  //lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(int(serial[0]));
  
  lcd.setCursor(5, 0);
  lcd.print(int(serial[1]));
  
  lcd.setCursor(10, 0);
  lcd.print(int(serial[2]));
  delay(50);
  }
}

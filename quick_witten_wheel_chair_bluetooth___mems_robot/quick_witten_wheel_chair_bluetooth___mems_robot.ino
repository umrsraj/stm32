
#include<stdlib.h>
#include <String.h>
#include <LiquidCrystal.h> // include the LCD library

LiquidCrystal lcd(PB12, PB13, PB14, PB15, PA8, PA9); //Initialize the LCD// rs,e,d4,d5.d6,d7

#define m1a PB8
#define m1b PB7
#define m2a PB6
#define m2b PB5

#define ir PB11
#define buzzer PA1
#define memsx PA4
#define memsy PA5
#define ldrPin PA6

#define led PB9

int x = 0;
int y = 0;
int ldr = 0;
int light = 0;
int obs = 0;

int flag = 0;

String read_msg = "\0";

#define SIM900 Serial2

void beep ()
{
  digitalWrite(buzzer,HIGH); delay(1000);
  digitalWrite(buzzer,LOW); delay(100);
  
}
void forward()
{
  digitalWrite(m1a,HIGH);
  digitalWrite(m1b,LOW);
  digitalWrite(m2a,HIGH);
  digitalWrite(m2b,LOW);
  delay(100);
}
void backward()
{
  digitalWrite(m1b,HIGH);
  digitalWrite(m1a,LOW);
  digitalWrite(m2b,HIGH);
  digitalWrite(m2a,LOW);
  delay(100);
}
void left()
{
  digitalWrite(m1a,HIGH);
  digitalWrite(m1b,LOW);
  digitalWrite(m2a,LOW);
  digitalWrite(m2b,HIGH);
  delay(800);
   digitalWrite(m1a,LOW);
  digitalWrite(m1b,LOW);
  digitalWrite(m2a,LOW);
  digitalWrite(m2b,LOW);
}
void right ()
{
  digitalWrite(m1b,HIGH);
  digitalWrite(m1a,LOW);
  digitalWrite(m2b,LOW);
  digitalWrite(m2a,HIGH);
  delay(800);
   digitalWrite(m1a,LOW);
  digitalWrite(m1b,LOW);
  digitalWrite(m2a,LOW);
  digitalWrite(m2b,LOW);
}
void stop_motor ()
{
   digitalWrite(m1a,LOW);
  digitalWrite(m1b,LOW);
  digitalWrite(m2a,LOW);
  digitalWrite(m2b,LOW);
  delay(100);
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
SIM900.begin(9600);
lcd.begin(16, 2);
Serial.println("power up");
pinMode(m1a,OUTPUT);
pinMode(m1b,OUTPUT);
pinMode(m2a,OUTPUT);
pinMode(m2b,OUTPUT);
pinMode(ir,INPUT);
pinMode(buzzer,OUTPUT);
pinMode(memsx,INPUT);
pinMode(memsy,INPUT);
pinMode(led,OUTPUT);
pinMode(ldrPin,INPUT);
 
 lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("  QUICK WITTED  "); 
  lcd.setCursor(0, 1);//coloumn , row
  lcd.print("  WHEEL CHAIR  ");
  delay(2000); 

}

void loop() {
  // put your main code here, to run repeatedly:
 
 ShowSerialData() ;
if((read_msg.indexOf("forward")!=(-1))||(read_msg.indexOf("front")!=(-1))||(read_msg.indexOf("1")!=(-1)))
 {
 read_msg = "\0";
flag = 0;
  Serial.println("forward......");
lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("forward");
  lcd.setCursor(0,1);
  lcd.print("OBS: "+String(obs)+ " L: "+String(light));
  delay(10);
  forward ();
  delay(100);
 }
else  if((read_msg.indexOf("backword")!=(-1))||(read_msg.indexOf("back")!=(-1))||(read_msg.indexOf("2")!=(-1)))
 {
 read_msg = "\0";
flag = 0;
  Serial.println("backward......");
lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("backward");
  lcd.setCursor(0,1);
  lcd.print("OBS: "+String(obs)+ " L: "+String(light));
  delay(10);
  backward ();
  delay(100);
 }
else  if((read_msg.indexOf("right")!=(-1))||(read_msg.indexOf("4")!=(-1)))
 {
   read_msg = "\0";
flag = 0;
  Serial.println("right......");
lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Right");
  lcd.setCursor(0,1);
  lcd.print("OBS: "+String(obs)+ " L: "+String(light));
  delay(10);
  right ();
  delay(100);
 }
 else  if((read_msg.indexOf("left")!=(-1))||(read_msg.indexOf("3")!=(-1)))
 {
   read_msg = "\0";
flag = 0;
  Serial.println("left......");
lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Left");
  lcd.setCursor(0,1);
  lcd.print("OBS: "+String(obs)+ " L: "+String(light));
  delay(10);
  left ();
  delay(100);
 }
 else  if((read_msg.indexOf("stop")!=(-1))||(read_msg.indexOf("5")!=(-1))||(read_msg.indexOf("yes")!=(-1))||(read_msg.indexOf("s")!=(-1)))
 {
 
   read_msg = "\0";
flag = 0;
  Serial.println("stop......");
lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("STOP");
  lcd.setCursor(0,1);
  lcd.print("OBS: "+String(obs)+ " L: "+String(light));
  delay(10);
  stop_motor ();
  delay(100);
 }
/////////////////////////////////////////////////////////
 ldr = analogRead(ldrPin);
 delay(5);
 x = analogRead(memsx);
 y = analogRead(memsy);
Serial.println("x= "+String(x));
Serial.println("y= "+String(y));
Serial.println("ldr= "+String(ldr));

if (ldr > 3000)
{
  digitalWrite(led,HIGH);
  delay(500);
  light = 1;
  lcd.setCursor(0,1);
  lcd.print("OBS: "+String(obs)+ " L: "+String(light));
  delay(100);  
}
else
{
 digitalWrite(led,LOW);
  delay(500);
  light = 0;
  lcd.setCursor(0,1);
  lcd.print("OBS: "+String(obs)+ " L: "+String(light));
  delay(100);   
}
if (digitalRead(ir) == HIGH)
{
  obs = 1;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" OBSTACLE ALERT ");
  lcd.setCursor(0,1);
  lcd.print("      STOP      ");
  stop_motor ();
  left ();
  beep ();
  delay(100);
}
else
{
 obs = 0;
 if (y < 1700)
 {
  Serial.println("mems -- forward");
  flag = 1;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("forward");
  lcd.setCursor(0,1);
  lcd.print("OBS: "+String(obs)+ " L: "+String(light));
  delay(10);
  forward ();
  delay(100);
 }
 else  if (y > 2300)
 {
  Serial.println("mems -- backward");
  flag = 1;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("backword");
  lcd.setCursor(0,1);
  lcd.print("OBS: "+String(obs)+ " L: "+String(light));
  delay(10);
  backward ();
  delay(100);
 }
 else  if (x < 1700)
 {
  Serial.println("mems -- right");
  flag = 1;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("right");
  lcd.setCursor(0,1);
  lcd.print("OBS: "+String(obs)+ " L: "+String(light));
  delay(10);
  right ();
  delay(100);
 }
 else  if (x > 2300)
 {
  Serial.println("mems -- left");
  flag = 1;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("left");
  lcd.setCursor(0,1);
  lcd.print("OBS: "+String(obs)+ " L: "+String(light));
  delay(10);
  left ();
  delay(100);
 }
 else
 {
  if(flag == 1)
  {
    
  Serial.println("mems -- stop");
    lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("stop");
  lcd.setCursor(0,1);
  lcd.print("OBS: "+String(obs)+ " L: "+String(light));
  delay(100);
  stop_motor ();
  delay(100);
  }
 }
}
}//loop
void ShowSerialData()
{
  while(SIM900.available()!=0)
   read_msg = SIM900.readString();
   if(read_msg != "\0")
   {
  Serial.println("read_msg is = "); Serial.println(read_msg);
   delay(1);
   }
}

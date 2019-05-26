#include<stdlib.h>
#include <String.h>
#include <LiquidCrystal.h> // include the LCD library
LiquidCrystal lcd(PB12, PB13, PB14, PB15, PA8, PA9); //Initialize the LCD// rs,e,d4,d5.d6,d7

#define m1a PC13
#define m1b PC14
#define m2a PC15
#define m2b PA0
#define metPin PA1
#define buzzer PA4
#define ir PA5


#define blu Serial2
#define SIM900 Serial1

String read_msg = "\0";
String read_msg1 = "\0";
int met = 0;

void beep ()
{
  digitalWrite(buzzer,HIGH);
  delay(1000);
  digitalWrite(buzzer,LOW);
  delay(100);
}


void forward ()
{
  Serial.println("forward----------------");
  digitalWrite(m1a,HIGH);
  digitalWrite(m1b,LOW);
  digitalWrite(m2a,HIGH);
  digitalWrite(m2b,LOW);
  delay(50);
}
void backward ()
{
  Serial.println("backward----------------");
  digitalWrite(m1a,LOW);
  digitalWrite(m1b,HIGH);
  digitalWrite(m2a,LOW);
  digitalWrite(m2b,HIGH);
  delay(50);
}
void left ()
{
  Serial.println("left---------------");
    digitalWrite(m1a,HIGH);
  digitalWrite(m1b,LOW);
  digitalWrite(m2a,LOW);
  digitalWrite(m2b,HIGH);
  delay(3500);
  digitalWrite(m1a,LOW);
  digitalWrite(m1b,LOW);
  digitalWrite(m2a,LOW);
  digitalWrite(m2b,LOW);
  delay(5);
}
void right ()
{
  Serial.println("right----------------");
  digitalWrite(m1a,LOW);
  digitalWrite(m1b,HIGH);
  digitalWrite(m2a,HIGH);
  digitalWrite(m2b,LOW);
  delay(3500);
  digitalWrite(m1a,LOW);
  digitalWrite(m1b,LOW);
  digitalWrite(m2a,LOW);
  digitalWrite(m2b,LOW);
  delay(5);
}
void stop_motor ()
{
  Serial.println("stop----------------");
    digitalWrite(m1a,LOW);
  digitalWrite(m1b,LOW);
  digitalWrite(m2a,LOW);
  digitalWrite(m2b,LOW);
  delay(50);
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
blu.begin(9600);
SIM900.begin(9600);
lcd.begin(16, 2);
Serial.println("power up");


pinMode(buzzer,OUTPUT);
pinMode(m1a,OUTPUT);
pinMode(m1b,OUTPUT);
pinMode(m2a,OUTPUT);
pinMode(m2b,OUTPUT);
pinMode(metPin,INPUT);
pinMode(ir,INPUT);


 lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("WAR FIELD ROBOT     "); 
  lcd.setCursor(0, 1);//coloumn , row
  lcd.print("                        ");
  delay(2000); 

}

void loop() {
  // put your main code here, to run repeatedly:
 // Serial.println("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");

met = analogRead(metPin);
Serial.println("met = "+String(met));

if (met > 3000)
{
  Serial.println("metal detected");
  stop_motor ();
  beep ();
}
else if (digitalRead(ir)==HIGH)
{
  Serial.println("obstacle detected");
  stop_motor ();
  beep ();  
  right ();
}


  ShowSerialData ();

if((read_msg.indexOf("forward")!=(-1))||(read_msg.indexOf("front")!=(-1))||(read_msg.indexOf("1")!=(-1)))
 {
forward ();
read_msg = "\0";
 }
else if((read_msg.indexOf("backward")!=(-1))||(read_msg.indexOf("back")!=(-1))||(read_msg.indexOf("2")!=(-1)))
 {
backward ();
read_msg = "\0";
 }
else if((read_msg.indexOf("left")!=(-1))||(read_msg.indexOf("l")!=(-1))||(read_msg.indexOf("3")!=(-1)))
 {
left ();
read_msg = "\0";
 }
else if((read_msg.indexOf("right")!=(-1))||(read_msg.indexOf("r")!=(-1))||(read_msg.indexOf("4")!=(-1)))
 {
right ();
read_msg = "\0";
 }
else if((read_msg.indexOf("stop")!=(-1))||(read_msg.indexOf("s")!=(-1))||(read_msg.indexOf("5")!=(-1)))
 {
stop_motor ();
read_msg = "\0";
 }
 //////////////////////////////////////////
 
  ShowSerialData1 ();

if((read_msg1.indexOf("forward")!=(-1))||(read_msg1.indexOf("front")!=(-1))||(read_msg1.indexOf("1")!=(-1)))
 {
forward ();
read_msg1 = "\0";
 }
else if((read_msg1.indexOf("backward")!=(-1))||(read_msg1.indexOf("back")!=(-1))||(read_msg1.indexOf("2")!=(-1)))
 {
backward ();
read_msg1 = "\0";
 }
else if((read_msg1.indexOf("left")!=(-1))||(read_msg1.indexOf("l")!=(-1))||(read_msg1.indexOf("3")!=(-1)))
 {
left ();
read_msg1 = "\0";
 }
else if((read_msg1.indexOf("right")!=(-1))||(read_msg1.indexOf("r")!=(-1))||(read_msg1.indexOf("4")!=(-1)))
 {
right ();
read_msg1 = "\0";
 }
else if((read_msg1.indexOf("stop")!=(-1))||(read_msg1.indexOf("s")!=(-1))||(read_msg1.indexOf("5")!=(-1)))
 {
stop_motor ();
read_msg1 = "\0";
 }

  
}//loop

void ShowSerialData1()
{
  while(blu.available()!=0)
    read_msg1 = blu.readString();
  if (read_msg1 != "\0")
  {
    Serial.println("read_msg1 = "+String(read_msg1));
  }
}
void ShowSerialData()
{
  while(SIM900.available()!=0)
   read_msg = SIM900.readString();
   if (read_msg != "\0")
   {
    Serial.println("read_msg ="+String(read_msg));
   }
}

#include <String.h>
#include <stdio.h>

#define en 2
#define d1 3
#define d2 4
#define d3 5


#define buzzer 11
#define lazer 10
#define ir A0
#define m11 6
#define m12 7
#define m21 8
#define m22 9


String read_msg =  "\0";
char pass[] = "*sendloc#";
int count = 0;

void beep ()
{
  digitalWrite (buzzer,HIGH);
  delay (1000);
  digitalWrite (buzzer, LOW);
  delay (100);
}
void beepp ()
{
  digitalWrite (buzzer,HIGH);
  delay (200);
  digitalWrite (buzzer, LOW);
  delay (50);
  digitalWrite (buzzer,HIGH);
  delay (200);
  digitalWrite (buzzer, LOW);
  delay (50);
  digitalWrite (buzzer,HIGH);
  delay (200);
  digitalWrite (buzzer, LOW);
  delay (50);
  digitalWrite (buzzer,HIGH);
  delay (200);
  digitalWrite (buzzer, LOW);
  delay (50); 
}
void beep1 ()
{
   digitalWrite (buzzer,HIGH);
  delay (500);
  digitalWrite (buzzer, LOW);
  delay (100);
   digitalWrite (buzzer,HIGH);
  delay (500);
  digitalWrite (buzzer, LOW);
  delay (100);
}



void setup() {

 //Serial2.begin(9600);
//Serial1.begin(9600);
Serial.begin (9600);
Serial.println("poewr up");


  pinMode(lazer,INPUT);
  pinMode(ir,INPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(en,INPUT);
  pinMode(d1,INPUT);
  pinMode(d2,INPUT);
  pinMode(d3,INPUT);

  
  pinMode(m11,OUTPUT);
  pinMode(m12,OUTPUT);
  pinMode(m21,OUTPUT);
  pinMode(m22,OUTPUT);

  delay(1000);
}

void loop(){
Serial.println("============================");

int dd1 = digitalRead(en);
Serial.println(dd1);
if (dd1 == 1)
while(1);


//Serial.println("en = "+String(digitalRead(en)));
//Serial.println("d1 = "+String(digitalRead(d1)));
//Serial.println("d2 = "+String(digitalRead(d2)));
//Serial.println("d3 = "+String(digitalRead(d3)));
//Serial.println("--------------------------------------------");
//Serial.println("en = "+String(analogRead(en)));
//Serial.println("d1 = "+String(analogRead(d1)));
//Serial.println("d2 = "+String(analogRead(d2)));
//Serial.println("d3 = "+String(analogRead(d3)));
//Serial.println("******************************************");

delay(500);
/*
if (digitalRead(en)==HIGH)
  {
    if((digitalRead(d1)==HIGH)&&(digitalRead(d2)==LOW)&&(digitalRead(d3)==HIGH))
    {
      Serial.println("dtmf -- BUTTON 5");
      Serial.println("robot--- stop");
stopp ();
 delay(200);   
    while (digitalRead(en)==HIGH);
    }
else  if((digitalRead(d1)==HIGH)&&(digitalRead(d2)==HIGH)&&(digitalRead(d3)==LOW))
    {
      Serial.println("dtmf -- BUTTON 3");
      Serial.println("robot--- left");
left ();
 delay(200);
 while (digitalRead(en)==HIGH);
    }

    else if((digitalRead(d1)==HIGH)&&(digitalRead(d2)==LOW)&&(digitalRead(d3)==LOW)) 
    {
      Serial.println("dtmf -- BUTTON 1");
          Serial.println("robot--- forward");
forward ();
 delay(200);
    while (digitalRead(en)==HIGH);
    }

    else if((digitalRead(d1)==LOW)&&(digitalRead(d2)==HIGH)&&(digitalRead(d3)==LOW)) 
    {
      Serial.println("dtmf -- BUTTON 2");
          Serial.println("robot--- backward");
backward ();
 delay(200);
    while (digitalRead(en)==HIGH);
    }

    else if((digitalRead(d1)==LOW)&&(digitalRead(d2)==LOW)&&(digitalRead(d3)==HIGH)) 
    {
      Serial.println("dtmf -- BUTTON 4");
          Serial.println("robot--- right");
right ();
 delay(200);
    while (digitalRead(en)==HIGH);
    } 
}//en of dtmf
else if (digitalRead(ir)==HIGH)
{
  Serial.println("obstacle alert");
  digitalWrite(lazer,HIGH);
  beep ();
  digitalWrite(lazer,LOW);
  left ();
}
*/
}//loop

void forward () 
{
  Serial.println("FORWARD ");
  digitalWrite(m11,HIGH);
  digitalWrite(m12,LOW);

  digitalWrite(m21,HIGH);
  digitalWrite(m22,LOW);
  
  delay(500);
}
void backward () 
{
  Serial.println("BACKWARD ");
  digitalWrite(m11,LOW);
  digitalWrite(m12,HIGH);

  digitalWrite(m21,LOW);
  digitalWrite(m22,HIGH);
  
  delay(500);
}
void right () 
{
  Serial.println("RIGHT");
 digitalWrite(m11,HIGH);
  digitalWrite(m12,LOW);

  digitalWrite(m21,LOW);
  digitalWrite(m22,HIGH);
  
  delay(500);
}
void left () 
{
  Serial.println("LEFT");
  digitalWrite(m11,LOW);
  digitalWrite(m12,HIGH);

  digitalWrite(m21,HIGH);
  digitalWrite(m22,LOW);
  
  delay(500);
}
void stopp () 
{
  Serial.println("STOP");
  digitalWrite(m11,LOW);
  digitalWrite(m12,LOW);

  digitalWrite(m21,LOW);
  digitalWrite(m22,LOW);
  
  delay(500);
}

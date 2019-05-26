#include <String.h>
#include <stdio.h>

#define buzzer PB1
#define button1 PB11
#define button2 PB10
#define en PB0
#define d1 PA7
#define d2 PA6
#define d3 PA5
#define d4 PA4
#define gled PA3
#define rled PA2


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

void health ()
{
  digitalWrite(gled,HIGH);
  digitalWrite(rled,HIGH);
  delay(500);
  digitalWrite(gled,LOW);
  digitalWrite(rled,LOW);
  delay(500);
  digitalWrite(gled,HIGH);
  digitalWrite(rled,HIGH);
  delay(500);
  digitalWrite(gled,LOW);
  digitalWrite(rled,LOW);
  delay(50);
}

void setup() {

 Serial2.begin(9600);
Serial1.begin(9600);
Serial.begin (9600);
Serial.println("poewr up");

  pinMode(button1,INPUT);
  pinMode(button2,INPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(en,INPUT);
  pinMode(d1,INPUT);
  pinMode(d2,INPUT);
  pinMode(d3,INPUT);
  pinMode(d4,INPUT);
  pinMode(gled,OUTPUT);
  pinMode(rled,OUTPUT);

health ();
 //sendsms("09652490222","KIT STARTED");
  delay(1000);
  //digitalWrite(en,HIGH);
}

void loop(){
Serial.println("*****************************");
if (digitalRead(en)==HIGH)
{
if ((digitalRead(d1) == LOW)&&(digitalRead(d2) == LOW))
{
  Serial.println("RF BUTTON PRESSED");
  digitalWrite(gled,HIGH);
  digitalWrite(rled,LOW);
beep1 ();
}
if ((digitalRead(d1) == LOW)&&(digitalRead(d2) == HIGH))
{
  Serial.println("PANIC BUTTON PRESSED");
  digitalWrite(rled,HIGH);
  digitalWrite(gled,LOW);
 
  beep ();
}
}//EN
else
{
Serial.println("button not pressed........");
digitalWrite(gled,LOW);
  digitalWrite(rled,LOW);
}
}//loop

 void sendsms (String bb , String qq)
  {
    Serial.println("sending sms : "+qq);
    
//     lcd.setCursor(0,0);
  //      lcd.print("sending sms.......... ");
    //     lcd.setCursor(0,1);
     //  lcd.print("                       ");
 
     Serial1.print("AT\r\n");
        Serial1.print('\n');
        ShowSerialData();
        delay(1000);
        Serial1.print("ATE1\r\n");
        ShowSerialData();
        delay(1000);
       Serial1.print("AT&W\r\n");
        Serial1.print('\n');
        ShowSerialData();
        delay(1000);
        Serial1.print("AT+CMGF=1\r\n");
        ShowSerialData();
        delay(1000);
        Serial1.print("AT+CNMI=2,2,0,0,0\r\n");
        ShowSerialData();
        delay(2000);
       // Serial.print("AT+CSMP=17,167,0,0\n");
       // delay(2000); 
        Serial1.print("AT+CMGS=\""+bb+"\"\r");
        ShowSerialData();
       // Serial.print('"');
      //Serial.print("9014449822");
      //Serial.print('"');
      //Serial.print('\r');
        Serial1.print('\n');
        delay(1000);
        Serial1.print(qq);
     Serial1.print('\r');
      Serial1.print('\n');
      
     delay(1000);
       Serial1.print((char)26);
       ShowSerialData();
       //  lcd.setCursor(0,0);
      // lcd.print("****sms sent****");
        // lcd.setCursor(0,1);
      // lcd.print("                       ");
        delay(2000);
        ShowSerialData();
  }
void ShowSerialData() 
{
  read_msg = "\0";
 while (Serial1.available () > 0)
  {
    //Serial.write(Serial1.read ());
read_msg =  (Serial1.readString ());
Serial.println("read_msg = " +read_msg);
  }
 }

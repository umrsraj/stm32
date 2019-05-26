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
#define heart PA0


unsigned hb = 0;

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

 Serial2.begin(9600);
Serial1.begin(9600);
Serial.begin (9600);
Serial.println("poewr up");

  pinMode(button1,INPUT);
  pinMode(button2,INPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(en,OUTPUT);
  pinMode(d1,OUTPUT);
  pinMode(d2,OUTPUT);
  pinMode(d3,OUTPUT);
  pinMode(d4,OUTPUT);
  pinMode(heart,INPUT);

 sendsms("07794038370","KIT STARTED");
  delay(1000);
  digitalWrite(en,HIGH);
}

void loop(){
Serial.println("============================");

 
if (digitalRead(button1) == LOW)
{
  Serial.println("PANIC BUTTON PRESSED");

  digitalWrite(en,LOW);
  
  digitalWrite(d1,LOW);
  digitalWrite(d2,HIGH);
  digitalWrite(d3,HIGH);
  digitalWrite(d4,HIGH);
  delay(2000);
  beep ();
  sendsms ("07794038370","IAM IN EMERGENCY\nPLEASE HELP ME AT \n LAT:17.322637\nLNG:78.535387\n");
  delay(500);
  digitalWrite(en,HIGH);
}
else if (digitalRead(button2) == LOW)
{
  Serial.println("RF BUTTON PRESSED");
  digitalWrite(en,LOW);
  
  digitalWrite(d1,LOW);
  digitalWrite(d2,LOW);
  digitalWrite(d3,HIGH);
  digitalWrite(d4,HIGH);
  delay(2000);
  beep1 ();
  sendsms ("07794038370","CONNECTIVITY TERMINATED WITH GAURDIAN \n AT \n LAT:17.322637\nLNG:78.535387\n\nPLEASE HELP ME ");
  delay(500);
  digitalWrite(en,HIGH);
}
else if (digitalRead(heart)==HIGH)
{
  Serial.println("heart reading");
//    lcd.clear();
//       lcd.setCursor(0,0);
//      lcd.print(" PLZ PUT YOUR  ");
//        lcd.setCursor(0,1);
//      lcd.print("FINGER PROPERLY");
//      delay(1800);
//      lcd.clear();
//      lcd.setCursor(0,0);
//      lcd.print("CALCULATING.....");
//    delay(2000);

  hb = pulseIn(heart);
 Serial.print("hb is = "); Serial.println(hb);

  if ((hb>95)||(hb<70))
  {
Serial.println("****** heart alert *********");
//    lcd.clear();
//  lcd.print("HEART BEAT ALERT");
//    lcd.setCursor(0,1);
//    lcd.print("HB = ");
//    lcd.setCursor(6,1);
//    lcd.print(hb);
beep ();
  sendsms ("07794038370","HEART BEAT ALERT\nHEART BEAT:"+String(hb)+"PLEASE HELP ME AT \n LAT:17.322637\nLNG:78.535387");
delay(500);
}
  else
  {
//  hbvalue = "\0";   
//  lcd.clear();
//  lcd.print("HEART BEAT NORMAL");
//    lcd.setCursor(0,1);
//    lcd.print("H BEAT = ");
//    lcd.setCursor(10,1);
//    lcd.print(hb);
  delay(2000);
  
  } 
}
else
{
  /*
ShowSerialData();
if (read_msg.indexOf("*sendloc#")!=(-1))
{
  Serial.println("requist for location detected..........");
sendsms ("07794038370","IAM AT LOCATION\nLAT:17.322637\nLNG:78.535387\n");
  delay(1000);
}
*/
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
       // Serial1.print("ATE1\r\n");
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

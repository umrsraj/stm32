#include<stdlib.h>
#include <String.h>
#include <LiquidCrystal.h> // include the LCD library

LiquidCrystal lcd(PB12, PB13, PB14, PB15, PA8, PA9); //Initialize the LCD// rs,e,d4,d5.d6,d7

#define button1 PC13
#define button2 PC14
#define button3 PC15
#define button4 PA0
#define vib PA1
#define m11 PA4
#define m12 PA5


unsigned int i = 0;
int count = 0;   
char input[20];
char pass[5] = "\0";
char pass1[5] = "1234";
char pass2[5] = "4321";

unsigned int pin = 0;



void sms (String mn);

void sms1 (String mn);


#define SIM900 Serial2

void openm ()
{
  Serial.println("motor---open");
  digitalWrite(m11,HIGH);
  digitalWrite(m12,LOW);
  delay(10);
}
void closem ()
{
  Serial.println("motor---close");
  digitalWrite(m11,LOW);
  digitalWrite(m12,HIGH);
  delay(10);
}
void stopm ()
{
  Serial.println("motor---stop");
  digitalWrite(m11,LOW);
  digitalWrite(m12,LOW);
  delay(10);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
Serial1.begin(9600);
SIM900.begin(9600);
lcd.begin(16, 2);
Serial.println("power up");
pinMode(button1,INPUT);
pinMode(button2,INPUT);
pinMode(button3,INPUT);
pinMode(button4,INPUT);
pinMode(vib,INPUT);
pinMode(m11,OUTPUT);
pinMode(m12,OUTPUT);

 lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("EXAM PAPER                  "); 
  lcd.setCursor(0, 1);//coloumn , row
  lcd.print("PROTECTION SYSTEM         ");
  delay(2500); 


}

void loop() {
  //---------------------------------------

 lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("please show card    "); 
  lcd.setCursor(0, 1);
  lcd.print("");
  delay(20); 

 while (Serial1.available () )
 {
 count =0;
 while(Serial1.available() && count < 12)  
  {
    
   input[count] = (char(Serial1.read ()));
   count++;
   delay(5);
//Serial.println(input);   
  }
   Serial.print("input = ");  Serial.println(input);
//delay(500);
Serial.println(input[10]);

if (input[10]=='C')
{
  Serial.println("card matched");
   lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("CARD MATCHED       "); 
  lcd.setCursor(0, 1);
  lcd.print("PLEASE ENTER PSWD      ");
  delay(2500);

//////////////////////////////////

i = 0;
lcd.clear ();
  lcd.setCursor(0,0);
  lcd.print("    PASSWORD    ");
while(i<4)
{

  if (digitalRead(button1) == HIGH)
  {
    pass[i]='1';
    lcd.setCursor(i,1);
    lcd.print(pass[i]);
    i++;
    delay(500);
    while(digitalRead(button1)==HIGH);
  }
  else if (digitalRead(button2) == HIGH)
  {
    pass[i]='2';
    lcd.setCursor(i,1);
    lcd.print(pass[i]);
    i++;
    delay(500);
    while(digitalRead(button2)==HIGH);
  }
   else if (digitalRead(button3) == HIGH)
  {
    pass[i]='3';
    lcd.setCursor(i,1);
    lcd.print(pass[i]);
    i++;
    delay(500);
    while(digitalRead(button3)==HIGH);
  }
  else if (digitalRead(button4) == HIGH)
  {
    pass[i]='4';
    lcd.setCursor(i,1);
    lcd.print('4');
    i++;
    delay(500);
    while(digitalRead(button4)==HIGH);
  } 
 
}//PSWD WHILE
pass[4] = '\0';
Serial.print(F("enterred password = ")); Serial.println(pass);
i = 0;

   if(strcmp(pass,pass1)==0)
{
   lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("PASSWORD MATCHED"); 
  lcd.setCursor(0, 1);
  lcd.print("................");
  delay(2500);
  
  lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("BOX OPENING......."); 
  lcd.setCursor(0, 1);
  lcd.print("                  ");
  delay(200);
  openm ();
  delay(2000);
  stopm();
  lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("BOX - OPEN         ");
  lcd.setCursor(0, 1);
  lcd.print("                  ");
  delay(200); 
  while (1);
}
else
{
  Serial.println("wrong password");
  lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("WRONG PASSWORD "); 
  lcd.setCursor(0, 1);
  lcd.print("                  ");
  delay(2000);
  sms1 ("08790067437","WRONG PASSWORD\nPLEASE CHECK");
}

}//CARD-1
else 
{
 lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("INVALID CARD      "); 
  lcd.setCursor(0, 1);
  lcd.print("PLEASE CHECK            ");
  delay(2000);   
}

 }//whiel serial1 available

if (digitalRead(vib)==HIGH)
{
  Serial.println("vibration alert");
   lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("VIBRATION ALERT"); 
  lcd.setCursor(0, 1);
  lcd.print("PLEASE CHECK.........");
  delay(2000);
  sms1 ("08790067437","VIBRATION ALERT\nPLEASE CHECK");
}
 
  
}//loop
void sms (String mn)
{
  String UU = "9502570839";
  lcd.clear();
lcd.setCursor(0,0);
        lcd.print("sending sms.......... ");
 SIM900.print("AT\r\n");
        SIM900.print('\n');
        ShowSerialData();
        delay(3000);
        SIM900.print("ATE1\r\n");
        ShowSerialData();
        delay(3000);
       SIM900.print("AT&W\r\n");
        SIM900.print('\n');
        ShowSerialData();
        delay(3000);
        SIM900.print("AT+CMGF=1\r\n");
        ShowSerialData();
        delay(3000);
        SIM900.print("AT+CNMI=2,2,0,0,0\r\n");
        ShowSerialData();
        delay(2000);
       // Serial.print("AT+CSMP=17,167,0,0\n");
        delay(2000); 
        SIM900.print("AT+CMGS=\""+UU+"\"\r");
        ShowSerialData();
       // Serial.print('"');
      //Serial.print("9014449822");
      //Serial.print('"');
      //Serial.print('\r');
        SIM900.print('\n');
       delay(3000);
       SIM900.println(mn);
     
       SIM900.println();
      
     SIM900.print('\r');
      SIM900.print('\n');
      
     delay(3000);
       SIM900.print((char)26);
       ShowSerialData();
       lcd.setCursor(0,0);
        lcd.print("****sms sent****");
        delay(5000);
  
}
void sms1 (String bb, String qq)
{
    Serial.println("sending sms : "+qq);
    
     lcd.setCursor(0,0);
        lcd.print("sending sms.......... ");
         lcd.setCursor(0,1);
       lcd.print("                       ");
 
     SIM900.print("AT\r\n");
        SIM900.print('\n');
        ShowSerialData();
        delay(1000);
       // SIM900.print("ATE1\r\n");
        ShowSerialData();
        delay(1000);
       SIM900.print("AT&W\r\n");
        SIM900.print('\n');
        ShowSerialData();
        delay(1000);
        SIM900.print("AT+CMGF=1\r\n");
        ShowSerialData();
        delay(1000);
        SIM900.print("AT+CNMI=2,2,0,0,0\r\n");
        ShowSerialData();
        delay(2000);
       // Serial.print("AT+CSMP=17,167,0,0\n");
       // delay(2000); 
        SIM900.print("AT+CMGS=\""+bb+"\"\r");
        ShowSerialData();
       // Serial.print('"');
      //Serial.print("9014449822");
      //Serial.print('"');
      //Serial.print('\r');
        SIM900.print('\n');
        delay(1000);
        SIM900.print(qq);
     SIM900.print('\r');
      SIM900.print('\n');
      
     delay(1000);
       SIM900.print((char)26);
       ShowSerialData();
        lcd.setCursor(0,0);
       lcd.print("****sms sent****");
       lcd.setCursor(0,1);
      lcd.print("                       ");
        delay(2000);
        ShowSerialData();

 
}
void ShowSerialData()
{
  while(SIM900.available()!=0)
    Serial.write(char (SIM900.read()));
}

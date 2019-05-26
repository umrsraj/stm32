#include<String.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(PB12, PB13, PB14, PB15, PA8, PA9); //Initialize the LCD// rs,e,d4,d5.d6,d7
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define gasPin PA1
#define humPin PA4
#define ldrPin PC13
#define relay PC14
#define buzzer PC15

String A = "GET /update?api_key=XDR4H783C68DNKC0&field4=";
String Z = " HTTP/1.1";
String iot = "\0";

int flag = 0;

const int tempPin = PA0;
int temp; 
int d=0;
int hum,gas;
String H="\0";
String G="\0";
String L="\0";
int light = 0;

void beep ()
{
  digitalWrite(buzzer,HIGH);
  delay(1000);
  digitalWrite(buzzer,LOW);
  delay(100);
}

void setup() 
{ 
  
pinMode(gasPin,INPUT); 
pinMode(tempPin,INPUT);
pinMode(ldrPin,INPUT);
  pinMode(humPin,INPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(relay,OUTPUT);  
  
Serial.begin(9600); 
Serial.println("power up");
Serial2.begin(9600);
lcd.begin(16,2);

lcd.clear();

 lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("CYBER SECURITY S/M"); 
  lcd.setCursor(0, 1);//coloumn , row
  lcd.print("..................");
  delay(2000); 

  Serial2.println("AT");
delay(2000);
 ShowSerialData();
 Serial2.println("AT+CWJAP=\"project12\",\"project123456\"");
delay(2000);
 ShowSerialData();
 Serial2.println("AT+CWJAP?");
delay(2000);
  
}//void setup 

void loop() 
{ 
H = "0";
G = "0";
  //analogReadResolution(10);
  
d = analogRead(PA0); 
float V=d*(5/(4095.00));
float temp=V*100;
temp = temp-20;
Serial.print("TEMPERATURE:"); 
Serial.println(temp);

gas = analogRead(gasPin);
hum = analogRead(humPin);

gas = map(gas,0,4095,0,1023);
hum = map(hum,0,4095,0,1023);

Serial.println("gas="+String(gas));
Serial.println("hum="+String(hum));

if (digitalRead(ldrPin)==HIGH)
{
  L = "0";
  light = 0;
  Serial.println("light off");
  digitalWrite(relay,LOW);
  delay(200);
}
else if (digitalRead(ldrPin)==LOW)
{
 
  L = "100";
  light = 1;
  Serial.println("light on");
  delay(100);
  digitalWrite(relay,HIGH);
  delay(200);
}

if(temp>55) 
{ 
  flag = 0;
 Serial.println("temperature alert");
  lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("TEMPERATURE ALERT"); 
  lcd.setCursor(0, 1);//coloumn , row
  lcd.print("T: "+String(temp));
  beep ();
  delay(2000); 
} 
else if (gas > 900)
{
  flag = 0;
  G = "100";
  Serial.println("temperature alert");
  lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("GAS ALERT    "); 
  lcd.setCursor(0, 1);//coloumn , row
  lcd.print("PLEASE CHECK     ");
  beep ();
  delay(2000);  
}
else if (hum < 950)
{
  flag = 0;
  H = "100";
   Serial.println("humidity alert");
  lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("HUMIDITY ALERT    "); 
  lcd.setCursor(0, 1);//coloumn , row
  lcd.print("PLEASE CHECK     ");
  beep ();
  delay(2000);   
}
else
{
   lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("T: "+String(temp)); 
  lcd.setCursor(8, 0); 
  lcd.print("L: "+String(light)); 
  lcd.setCursor(0, 1);
  lcd.print("G: Normal");
  lcd.setCursor(8, 1);
  lcd.print("H: Normal"); 
  delay(200);
}
if(flag < 2)
{
  flag ++;
iot = A + String(temp) + "&field5=" + G + "&field6=" + H + "&field7=" + L ;
thingspeak();
}
} //loop

void ShowSerialData() 
{
 while (Serial2.available () > 0)
  {
    Serial.write(Serial2.read ());
   //Serial2.println(char(Serial2.read ()));
  }
 }
void thingspeak () {


String postStr = iot  ;

Serial.println("iot="+String(iot));
/*******     Uploading to ThingSpeak Cloud   ********/
/*******     Sending AT Commands to ESP8266  ********/

  lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("SENDGING TO"); 
  lcd.setCursor(0, 1);//coloumn , row
  lcd.print("SERVER");
 
Serial2.println("AT");
delay(2000);
 ShowSerialData();

Serial2.println("AT+CIPMUX=0");
delay(2000);
 ShowSerialData();
Serial2.print("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n");
delay(3000);
 ShowSerialData();
String ciplength = "AT+CIPSEND="+String(postStr.length()+5)+"\r\n";   
Serial2.print(ciplength);
delay(3000);
 ShowSerialData();
Serial2.print(postStr);
Serial2.print("\r\n");
delay(5000);
 ShowSerialData();
delay(2000);
 ShowSerialData();

Serial2.print("AT+CIPCLOSE\r\n");
delay(3000);
 ShowSerialData();
 delay(1000);
 Serial2.print("AT+RST\r\n");
 delay(500);
 ShowSerialData();
 Serial.println("update ended");
 
}

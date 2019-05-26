// https://thingspeak.com/channels/689629 -- PUBLIC VIEW PAGE

#include "WiFiEsp.h"
#include<String.h>

/*
// Emulate Serial1 on pins 6/7 if not present
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(12, 13); // RX, TX
#endif
*/

#include <LiquidCrystal.h>
#include <String.h>
#define bt1 PA11
#define bt2 PA12
#define bt3 PA15
#define bt4 PB3

char ssid[] = "project12";            // your network SSID (name)
char pass[] = "project123456";        // your network password
//int status = WL_IDLE_STATUS;     // the Wifi radio's status

char server[] = "api.thingspeak.com";
String A = "GET /update?api_key=WXGBY1HU6V57QD3F&field1=";
String Z = " HTTP/1.1";
String iot = "\0";

//WiFiEspClient client;


 
LiquidCrystal lcd(PA6, PA7, PB0, PB1, PB10, PB11); //Initialize the LCD

 
long duration = 0;
unsigned int distance = 0;

const int trigPin = PA5;  //D6
const int echoPin = PA4;  //D7


#define gled PA0
#define rled PA1

void setup(void) { 
  Serial.begin(9600);
Serial2.begin(9600);
Serial1.begin(9600);

Serial.println("power up");
lcd.begin(16,2);

pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
pinMode(rled, OUTPUT);
pinMode(gled, OUTPUT);

pinMode(bt1,INPUT);
pinMode(bt2,INPUT);
pinMode(bt3,INPUT);

lcd.clear();
lcdstring(0,0,"   WELCOME TO   ");
lcdstring(0,1,"ADVANCED AIRCRAFT");
delay(2000);
lcd.clear();
lcdstring(0,0," ANTI-COLLISION ");
lcdstring(0,1,"     SYSTEM     ");
delay(1500);

delay(500);
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
}
 
void loop() {
  
Serial.println("loop Started");

digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance= duration*0.034/2;
Serial.print("Distance: ");
Serial.println(distance);
delay(100);

lcd.clear();
lcdstring(0,0,"DISTANCE = ");
lcdstring(11,0,String(distance));
delay(200);

if (distance <30)
{
  
digitalWrite(gled,LOW);
digitalWrite(rled,HIGH);
delay(50);
 // lcd.clear();
  lcdstring(0,1,"AIRCRAFT DETECTED");
  //lcdstring(0,1,"sending to server");
  delay(1500);
  Serial2.print("MISSILE ALERT AT:" + String(distance) + "\r\n");
delay(400);
  //send_data ();
}
else if (digitalRead(bt1)==HIGH)
{
  Serial.println("button 1 pressed");
  
lcdstring(0,0,"EMERGENCY ALERT");
lcdstring(0,1,"................");
delay(100);
Serial2.print("EMERGENCY ALERT\r\n");
delay(400);
}
else if (digitalRead(bt2)==HIGH)
{
  Serial.println("button 2 pressed");
  
lcdstring(0,0,"  LEFT MOVE     ");
lcdstring(0,1,"................");
delay(2000);
}
else if (digitalRead(bt3)==HIGH)
{
  Serial.println("button 3 pressed");
  
lcdstring(0,0,"  RIGHT MOVE     ");
lcdstring(0,1,"................");
delay(2000);
}
else if (digitalRead(bt4)==HIGH)
{
  Serial.println("button 4 pressed");
  
lcdstring(0,0,"   UP MOVE     ");
lcdstring(0,1,"................");
delay(2000);
}
else 
{
  
digitalWrite(rled,LOW);
digitalWrite(gled,HIGH);
delay(50);
}

}
/*
void send_data () {

lcd.clear();
lcdstring(0,0,"AIRCRAFT DETECTED");
lcdstring(0,1,"sending to server");
delay(100);

iot = link + String(distance);

 
 if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
   HTTPClient http; //Declare an object of class HTTPClient
   // http.begin("http://orangewebtools.com/Irrigation/moisture.php?a=32"); //Specify request destination

 Serial.println(iot);
   http.begin(iot);
    http.begin("\n");
    int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
  } else {
    Serial.println("Error in WiFi connection");   
  }
  lcd.clear();
lcdstring(0,0,"  DATA SENDING  ");
lcdstring(0,1,"  --COMPLETED--  ");
delay(1);
  delay(3000); //Send a request every 30 seconds

}
*/
void lcdstring (unsigned int a, unsigned int b, String data)
{
  // lcd.clear();
  lcd.setCursor(a, b);
  lcd.print(data);
}

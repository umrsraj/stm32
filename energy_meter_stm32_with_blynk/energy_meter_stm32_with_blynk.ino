
/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
#include <LiquidCrystal.h>
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).

//char auth[] = "822b2c465d2948ff933e7cf5f494f309";

char auth[] = "dfeb07158a94413192f6233c23df1816";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "project12";
char pass[] = "project123456";

unsigned int flag= 0;

// Hardware Serial on Mega, Leonardo, Micro...
#define EspSerial Serial2

// or Software Serial on Uno, Nano...
//#include <SoftwareSerial.h>
//SoftwareSerial EspSerial(12, 13); // RX, TX
 LiquidCrystal lcd(PA6, PA7, PB0, PB1, PB10, PB11);

// Your ESP8266 baud rate:
#define ESP8266_BAUD 9600

#define buzzer PB12

#define relay PB13


volatile int buttonState;
volatile int units = 0;
volatile int units1 = 0;
volatile int cost = 0;
volatile int cost1 = 0;
volatile int total_cost = 0;
volatile int total_units = 0;
int flag2 = 0;

ESP8266 wifi(&EspSerial);

void beep ()
{
  digitalWrite(buzzer,HIGH);
  delay(1000);
  digitalWrite(buzzer,LOW);
  delay(100);
}
WidgetLCD lcd1(V0);
BLYNK_WRITE(V1)
{
   buttonState = param.asInt();
  Serial.print(F("buttonState = ")); Serial.println(buttonState);
  if (buttonState == 1)
  {
    flag2 = 0;
  }
}

void setup()
{
  // Debug console
  Serial.begin(9600);

   Serial.println("power up");
   lcd.begin(16,2);

   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("SMART SOPHISTICATED");
     lcd.setCursor(0,1);
   lcd.print("POWER METER-IOT");
   delay(2000);

   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print(" connecting  to ");
     lcd.setCursor(0,1);
   lcd.print("****network****");
   delay(200);
   
   
  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  Blynk.begin(auth, wifi, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, wifi, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, wifi, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Setup notification button on pin 2
  pinMode(PA0, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(relay, OUTPUT);

  attachInterrupt(PA0,pinisr , FALLING);

  lcd1.clear();
lcd1.print(0,0,"SMART SOPHISTICATED");
lcd1.print(0,1,"POWER METER-IOT");
delay(1000);

   Blynk.notify("KIT STARTED!!!!");

   lcd1.clear();
   lcd.clear();

digitalWrite(relay,HIGH);
delay(2000);
units = 0;
}

void loop()
{
  Blynk.run();

  Serial.print("buttonState = ");Serial.println(buttonState);
  
if (buttonState == 1)
{
  if(flag2 == 0)
  {
    flag2 = 1;
    units = 0;
  Blynk.notify("load turned off\n  please check....");
  }
 digitalWrite(relay,LOW);
delay(300);

lcd1.print(0,1,"  LOAD >>> OFF  ");
 delay(100);
lcd.setCursor(0,1);
lcd.print("  LOAD >>> OFF  ");
 delay(300);
}
else if (buttonState == 0)
{
  delay(200);
   digitalWrite(relay,HIGH);
 delay(300);
}
  
lcd1.clear();
lcd1.print(0,0,"U: ");
lcd1.print(3,0,total_units);
lcd1.print(8,0,"C: ");
lcd1.print(11,0,total_cost);

delay(100);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("U: ");
lcd.setCursor(3,0);
lcd.print(total_units);
lcd.setCursor(8,0);
lcd.print("C: ");
lcd.setCursor(12,0);
lcd.print(total_cost);

delay(100);

if (total_units > 8)
{
   Blynk.notify("PLEASE RECHARGE\nYOUR BILL:"+String(total_cost));
   delay(200);
}

}

void pinisr ()
{
  Serial.println("interrup occured");

   units++;
  
  Serial.print(F("units = ")); Serial.println(units);
  cost = units * 5;

total_cost = cost;
Serial.print(F("total_cost = ")); Serial.println(total_cost);
total_units = units;
Serial.print(F("total_units = ")); Serial.println(total_units);
delay(1000);
}


#include<stdlib.h>
#include <String.h>
#include <TinyGPS++.h>
#include <LiquidCrystal.h> // include the LCD library

LiquidCrystal lcd(PB12, PB13, PB14, PB15, PA8, PA9); //Initialize the LCD// rs,e,d4,d5.d6,d7

#define lv1Pin PC13
#define lv2Pin PC14
#define lv3Pin PC15
#define heart PA4
#define temp PA0
#define gasPin PA1
#define buzzer PA5

unsigned int gas,lv1,lv2,lv3;

unsigned int flag = 0;
String hbvalue = "N";

//AURORA COLLEGE

String otp1[11]={
      "17.305938","17.305991","17.304283",
      "17.302942","17.305938","17.305212",
      "17.303423","17.305665","17.305938"
      "17.305736", "17.305586"  };
      
String otp2[11]={
      "78.457924","78.457912","78.457123",
      "78.4572176","78.457924","78.45793"
      "78.4579322","78.457294","78.457924",
      "78.457291" , "78.457736"  };




String g1 = "\0";
String otp[11] = {"62","72","71","75","97","79","92","79","95","83","99"} ;
unsigned int no = 0;
unsigned hb = 0;
String g = "N";
String lv = "0";
String h = "N";


void beep()
{
   digitalWrite(buzzer, HIGH); 
   delay(1000);
    digitalWrite(buzzer, LOW); 
    delay(100);
}


float temp1=0.0;
unsigned temp2 = 0;
unsigned int i = 0;
volatile int count = 0;
char pass[5] = "\0";
char pass1[5] = "1234";
char pass2[5] = "4321";

unsigned int pin = 0;



void sms (String mn);

void sms1 (String mn);

int card1_flag = 0;
int card2_flag = 0;

String data = "\0";
int amount  = 1000;
int amount1  = 1000;

//................................
static const uint32_t GPSBaud = 9600;

float sped = 0.0;
double a,b,c,d;

TinyGPSPlus gps;
#define ss SIM900
#define SIM900 Serial2
//=======================================================
/*
void displayInfo()
{
  Serial.print(F("Location: "));
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Date/Time: "));
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F(" "));
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(gps.time.centisecond());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.println();
}
*/
/*
static void printFloat(float val, bool valid, int len, int prec)
{
  if (!valid)
  {
    while (len-- > 1)
      Serial.print('*');
    Serial.print(' ');
  }
  else
  {
    Serial.print(val, prec);
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1); // . and -
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i=flen; i<len; ++i)
      Serial.print(' ');
  }
  smartDelay(0);
}

static void printInt(unsigned long val, bool valid, int len)
{
  char sz[32] = "*****************";
  if (valid)
    sprintf(sz, "%ld", val);
  sz[len] = 0;
  for (int i = strlen(sz); i < len; ++i)
    sz[i] = ' ';
  if (len > 0)
    sz[len - 1] = ' ';
  Serial.print(sz);
  smartDelay(0);
}
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}
*/

//=======================================================

//................................x



//////////////////////////////////////////////////

void printDec(byte *buffer, byte bufferSize) {
  Serial.println("......");
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);
    data += String(buffer[i] < 0x10 ? " 0" : " ");
    data += String(buffer[i], DEC);
  }
}

//////////////////////////////////////////////////



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  ss.begin(GPSBaud);
SIM900.begin(9600);
lcd.begin(16, 2);
Serial.println("power up");

pinMode(gasPin,INPUT);
pinMode(lv1Pin,INPUT);
pinMode(lv2Pin,INPUT);
pinMode(lv3Pin,INPUT);
pinMode(buzzer,OUTPUT);
pinMode(temp,INPUT);
pinMode(heart,INPUT);

  lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("HEALTH            ");
    lcd.setCursor(0,1);
    lcd.print("MONITORING S/M     ");
  delay(3000);


}

void loop() {
  // put your main code here, to run repeatedly:

  
  temp2 = analogRead(temp); //read data from analog pin A1. 
float V=temp2*(5/(4095.00)); //conversion of analog voltage to digital voltage. 
  temp1=V*100; //temperature in centigrade scale. 
temp1 = temp1-25;
Serial.print("temperature is = "); Serial.println(temp1);
delay(50);

  
 no = random(11);
 hbvalue = "N";
  

  
Serial.print("temperature is = "); Serial.println(temp1);
delay(50);
Serial.print("heart = "); Serial.println(digitalRead(heart));

gas = analogRead(gasPin);
lv1 = digitalRead(lv1Pin);
lv2 = digitalRead(lv2Pin);
lv3 = digitalRead(lv3Pin);
delay(50);
Serial.print(F("gas = ")); Serial.println(gas);
Serial.print(F("lv1 = ")); Serial.println(lv1);
Serial.print(F("lv2 = ")); Serial.println(lv2);
Serial.print(F("lv3 = ")); Serial.println(lv3);


if ((lv1 == 0) && (lv2 == 0) && (lv3 == 0))
{
  flag = 1;
lv = '3';
}
else if ((lv1 == 0) && (lv2 == 0) && (lv3 == 1))
{
  flag = 1;
lv = '2';
}
else if ((lv1 == 0) && (lv2 == 1) && (lv3 == 1))
{
  flag = 1;
lv = '1';
}
else if ((lv1 == 1) && (lv2 == 1) && (lv3  == 1))
{
  flag = 1;
lv = '0';
lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(" CELINE - EMPTY ");
    lcd.setCursor(0,1);
    lcd.print("***PLZ CHECK****");
    beep ();
  delay(1000);
  sms1("08125702458","CELINE EMPTY\nPLEASE CHECK\nAT\nLAT:"+otp1[no]+"\nLNG:"+otp2[no]);
}

if(gas > 2600)
{
  
flag = 1;
g1 = "EMPTY";
Serial.println(F("gas alert........"));
lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("OXYGEN ALERT       ");
    lcd.setCursor(0,1);
    lcd.print("***PLZ CHECK****");
    beep ();
    g = 'N';
  Serial.print("G = "); Serial.println(g);
  delay(1000);
  
  sms1("08125702458","OXIGEN ALERT\nPLEASE CHECK\nAT\nLAT:"+otp1[no]+"\nLNG:"+otp2[no]);
}
else if(temp1>55)
{
flag = 1;

lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("TEMPERATURE ALERT");
    lcd.setCursor(0,1);
    lcd.print("***PLZ CHECK****");
    beep ();
  delay(1000);
  sms1("08125702458","TEMPERATURE ALERT\nPLEASE CHECK\nAT\nLAT:"+otp1[no]+"\nLNG:"+otp2[no]);
}

else if (!(digitalRead(heart)))
{
  
flag = 1;
  lcd.clear();
     lcd.setCursor(0,0);
    lcd.print(" PLZ PUT YOUR  ");
      lcd.setCursor(0,1);
    lcd.print("    FINGER     ");
    delay(1800);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("CALCULATING.....");
  delay(2000);

  hb = otp[no].toInt();
 Serial.print("otp is = "); Serial.println(hb);

hbvalue = String(hb);
 
 delay(500);
 
 if ((hb>95)||(hb<70))
  {
  lcd.clear();
  lcd.print("HEART BEAT ALERT");
    lcd.setCursor(0,1);
    lcd.print("HB = ");
    lcd.setCursor(6,1);
    lcd.print(hb);
beep ();
delay(1000);

  sms1("08125702458","HEART BEAT ALERT\nPLEASE CHECK\nAT\nLAT:"+otp1[no]+"\nLNG:"+otp2[no]);
  }
  else
  {
   
  lcd.clear();
  lcd.print("HEART BEAT NORMAL");
    lcd.setCursor(0,1);
    lcd.print("H BEAT = ");
    lcd.setCursor(10,1);
    lcd.print(hb);
  delay(1500);
  
  }
}
//Serial.println("last F = "); Serial.println(f);
//if ((f == 'F')&&(temp1 <= 65)){
  lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("T= "+String(temp1)+" HB: 0");
    lcd.setCursor(0,1);
    lcd.print("LV: "+ lv );
    lcd.setCursor(8,1);
    lcd.print("O:Normal" );
delay(300);

  
  //-----------------------------------
 /*
  while (ss.available() > 0)
    if (gps.encode(ss.read()))
      //displayInfo();
   */
      /*
Serial.print("button1 = ");
Serial.println(digitalRead(button1));
Serial.print("button2 = ");
Serial.println(digitalRead(button2));
Serial.print("button3 = ");
Serial.println(digitalRead(button3));
Serial.print("button4 = ");
Serial.println(digitalRead(button4));
Serial.println("i = " +String(i));
Serial.println("======================================================");
  */
      
      /*
if (gps.speed.isValid())
{
 sped = gps.speed.kmph();
  Serial.print("speed = "); Serial.println(sped);
}
*/
/*
//Serial.println("loop started");
  //---------------------------------------
 lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("please show card    "); 
  lcd.setCursor(0, 1);
  lcd.print("");
  delay(20); 


  if ( ! rfid.PICC_IsNewCardPresent())
    return;

  // Verify if the NUID has been readed
  if ( ! rfid.PICC_ReadCardSerial())
    return;
    
  Serial.println();
  Serial.print(F("In dec: "));
  printDec(rfid.uid.uidByte, rfid.uid.size);
  Serial.println();

  
  if (data.indexOf("128 48 220 164") != (-1))
  {
     lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print(" CARD-1 MATCHED "); 
  lcd.setCursor(0, 1);
  lcd.print("");
  delay(2000);
  
 lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("PLEASE ENTER"); 
  lcd.setCursor(0, 1);
  lcd.print(" PASSWORD ");
  delay(2000);
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
    delay(100);
    while(digitalRead(button1)==HIGH);
  }
  else if (digitalRead(button2) == HIGH)
  {
    pass[i]='2';
    lcd.setCursor(i,1);
    lcd.print(pass[i]);
    i++;
    delay(100);
    while(digitalRead(button2)==HIGH);
  }
   else if (digitalRead(button3) == HIGH)
  {
    pass[i]='3';
    lcd.setCursor(i,1);
    lcd.print(pass[i]);
    i++;
    delay(100);
    while(digitalRead(button3)==HIGH);
  }
  else if (digitalRead(button4) == HIGH)
  {
    pass[i]='4';
    lcd.setCursor(i,1);
    lcd.print('4');
    i++;
    delay(100);
    while(digitalRead(button4)==HIGH);
  } 
 
}
pass[4] = '\0';
Serial.print(F("enterred password = ")); Serial.println(pass);
i = 0;

   if(strcmp(pass,pass1)==0)
{
   lcd.clear(); 
  434   lcd.setCursor(0, 0); 
  lcd.print("PASSWORD MATCHED"); 
  lcd.setCursor(0, 1);
  lcd.print("................");
  delay(2000);
//'''''''''''''''''''''''''''''''''''''''''''''''''''

    Serial.println("card matched");
    data = "\0";
    if (card1_flag == 0)
    {
  
//      if (gps.location.isValid())
//      {
        card1_flag = 1;
         a = gps.location.lat();
         b = gps.location.lng();
        Serial.println("a = " + String(a, 6));
        Serial.println("b = " + String(b, 6));
               lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("PERSON-1 JOURNEY"); 
  lcd.setCursor(0, 1);
  lcd.print("   STARTED AT   ");
  delay(2000);
         lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("LAT:"+String(a,6)); 
  lcd.setCursor(0, 1);
  lcd.print("LNG:"+String(b,6));
  delay(2000);
        
   //     sms ("PERSON-1 STARTED JOURNEY \nAT\nLAT:"+String(a,6)+"\nLONG:"+String(b,6));
     sms1 ("08639268629","PERSON-1 STARTED JOURNEY \nAT\nLAT:"+String(c,6)+"\nLONG:"+String(d,6));   
 Serial.println("sms sendtttttttttttttttttttttttttt");
 
 /*     }
      else
      {
        Serial.println("gps not working.........");
        
         lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("INVALID LOCATION"); 
  lcd.setCursor(0, 1);
  lcd.print("PLEASE CHECK......");
  delay(2000);
        
      }
      */
//    }//card1_flag== 0
//    else
//    {
//  //    if (gps.location.isValid())
//  //    {
//        card1_flag = 0;
        /*
        float c = gps.location.lat();
        float d = gps.location.lng();
        Serial.println("c = " + String(c, 6));
        Serial.println("d = " + String(d, 6));
        */
        /*
        unsigned long distance = 
        
        (unsigned long)TinyGPSPlus::distanceBetween(
      gps.location.lat(),
      gps.location.lng(),
      a,
      b) ; 
      //b) / 1000;
  Serial.print("dist = "); Serial.println(distance);
Serial.println("");
amount = amount - (distance *5);

         lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("PERSON-1 JOURNEY"); 
  lcd.setCursor(0, 1);
  lcd.print("    ENDED AT    ");
  delay(2000);

      lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("LAT:");
  lcd.setCursor(4, 0); 
  lcd.print(gps.location.lat(),6); 
  lcd.setCursor(0, 1);
  lcd.print("LNG:"); 
  lcd.setCursor(4, 1);
  lcd.print(gps.location.lng(),6);
  delay(2000);

         lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("Trav Dist:"+String(distance)); 
  lcd.setCursor(0, 1);
  lcd.print("Rem Bal:"+String(amount));
  delay(2000);

sms1 ("08639268629","PERSON-1 JOURNEY ENDED  \nAT\nLAT:"
+String(gps.location.lat(),6)+"\nLONG:"+String(gps.location.lng(),6)
+"\nAND Travelled Distance of "+String(distance)+"m"
+"\nRemaing Bal:"+String(amount));

    /*            
      }
      else
      {
        Serial.println("gps not working.........");
        
         lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("INVALID LOCATION"); 
  lcd.setCursor(0, 1);
  lcd.print("PLEASE CHECK......");
  delay(2000);
      }
*/
/*
    }// card1_flag == 1
    data = "\0";
//'''''''''''''''''''''''''''''''''''''''''''''''''''


}
else
{
  lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print(" WRONG PASSWORD "); 
  lcd.setCursor(0, 1);
  lcd.print("................");
  delay(2000);
}

//////////////////////////////////////////////
   

  }//1st card
  else if (data.indexOf("29 177 111 133") != (-1))
  {
     lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print(" CARD-2 MATCHED "); 
  lcd.setCursor(0, 1);
  lcd.print("");
  delay(2000);
    
 lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("PLEASE ENTER"); 
  lcd.setCursor(0, 1);
  lcd.print(" PASSWORD ");
  delay(2000);
//////////////////////////////////

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
    delay(100);
    while(digitalRead(button1)==HIGH);
  }
  else if (digitalRead(button2) == HIGH)
  {
    pass[i]='2';
    lcd.setCursor(i,1);
    lcd.print(pass[i]);
    i++;
    delay(100);
    while(digitalRead(button2)==HIGH);
  }
   else if (digitalRead(button3) == HIGH)
  {
    pass[i]='3';
    lcd.setCursor(i,1);
    lcd.print(pass[i]);
    i++;
    delay(100);
    while(digitalRead(button3)==HIGH);
  }
  else if (digitalRead(button4) == HIGH)
  {
    pass[i]='4';
    lcd.setCursor(i,1);
    lcd.print('4');
    i++;
    delay(100);
    while(digitalRead(button4)==HIGH);
    delay(600);
  } 
 
}
pass[4] = '\0';
Serial.print(F("enterred password = ")); Serial.println(pass);
i = 0;

   if(strcmp(pass,pass2)==0)
{
   lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("PASSWORD MATCHED"); 
  lcd.setCursor(0, 1);
  lcd.print("................");
  delay(2000);
//'''''''''''''''''''''''''''''''''''''''''''''''''''

    Serial.println("card-2 matched");
    data = "\0";
    if (card2_flag == 0)
    {
  
  //    if (gps.location.isValid())
   //   {
        card2_flag = 1;
         c = gps.location.lat();
         d = gps.location.lng();
        Serial.println("c = " + String(c, 6));
        Serial.println("d = " + String(d, 6));
               lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("PERSON-2 JOURNEY"); 
  lcd.setCursor(0, 1);
  lcd.print("   STARTED AT   ");
  delay(2000);
         lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("LAT:"+String(c,6)); 
  lcd.setCursor(0, 1);
  lcd.print("LNG:"+String(d,6));
  delay(2000);
        
        sms1 ("09550843384","PERSON-2 STARTED JOURNEY \nAT\nLAT:"+String(c,6)+"\nLONG:"+String(d,6));
    /*    
      }
      else
      {
        Serial.println("gps not working.........");
        
         lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("INVALID LOCATION"); 
  lcd.setCursor(0, 1);
  lcd.print("PLEASE CHECK......");
  delay(2000);
        
      }
     
    }//card2_flag== 0
    else
    {
    //  if (gps.location.isValid())
    //  {
        card2_flag = 0;
        /*
        float c = gps.location.lat();
        float d = gps.location.lng();
        Serial.println("c = " + String(c, 6));
        Serial.println("d = " + String(d, 6));
        */
        /*
        unsigned long distance1 = 
        
        (unsigned long)TinyGPSPlus::distanceBetween(
      gps.location.lat(),
      gps.location.lng(),
      c,
      d) ; 
      //b) / 1000;
  Serial.print("dist1 = "); Serial.println(distance1);
Serial.println("");
amount1 = amount1 - (distance1 *5);

         lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("PERSON-2 JOURNEY"); 
  lcd.setCursor(0, 1);
  lcd.print("    ENDED AT    ");
  delay(2000);

      lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("LAT:");
  lcd.setCursor(4, 0); 
  lcd.print(gps.location.lat(),6); 
  lcd.setCursor(0, 1);
  lcd.print("LNG:"); 
  lcd.setCursor(4, 1);
  lcd.print(gps.location.lng(),6);
  delay(2000);

         lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("Trav Dist:"+String(distance1)); 
  lcd.setCursor(0, 1);
  lcd.print("Rem Bal:"+String(amount1));
  delay(2000);


sms1 ("09550843384","PERSON-2 JOURNEY ENDED  \nAT\nLAT:"
+String(gps.location.lat(),6)+"\nLONG:"+String(gps.location.lng(),6)
+"\nAND Travelled Distance of "+String(distance1)+"m"
+"\nRemaing Bal:"+String(amount1));

 */


   /*              
      }
  
   else
      {
        Serial.println("gps not working.........");
        
         lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("INVALID LOCATION"); 
  lcd.setCursor(0, 1);
  lcd.print("PLEASE CHECK......");
  delay(2000);
      }
    */
    /*
    }// card1_flag == 1
}
else
{
  lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print(" WRONG PASSWORD "); 
  lcd.setCursor(0, 1);
  lcd.print("................");
  delay(2000);
}

////////////////////////////////////////////// 
    data = "\0";

  }//2nd card
  else
  {
    Serial.println("card not matched");
    delay(2000);
  }

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    //while(true);
  }  
  */
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
  /*
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
        Serial.print("AT+CSMP=17,167,0,0\n");
        delay(2000); 
        SIM900.print("AT+CMGS=\"08639268629\"\r");
        ShowSerialData();
       // Serial.print('"');
      //Serial.print("9014449822");
      //Serial.print('"');
      //Serial.print('\r');
        SIM900.print('\n');
        delay(1000);
        SIM900.print(mn);
       // SIM900.print("EMPTY \n");
     SIM900.print('\r');
      SIM900.print('\n');
      
     delay(3000);
       SIM900.print((char)26);
       ShowSerialData();
       lcd.setCursor(0,0);
        lcd.print("****sms sent****");
        delay(5000);
 */ 
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

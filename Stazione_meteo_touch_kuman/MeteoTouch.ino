#include "BMP280.h"
#include "Wire.h"
#include "DHT.h"
#include <DS3231.h>

#define DHTPIN 53
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE); 
BMP280 bmp;
DS3231  rtc(SDA, SCL);

#include <Adafruit_GFX.h>    
#include <Adafruit_TFTLCD.h>
#include <TouchScreen.h>

#define LCD_CS A3
#define LCD_CD A2 
#define LCD_WR A1 
#define LCD_RD A0 

#define LCD_RESET A4

#define YP A2
#define XM A3
#define YM 8
#define XP 9

#define TS_MINX 130
#define TS_MAXX 905
#define TS_MINY 75
#define TS_MAXY 930

#define MINPRESSURE 10
#define MAXPRESSURE 1000

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define GRAY    0x8410

#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;

Time  tempo;

double Temp, Pres, t, h, TempMed, t1, t2, t3, t4, p1, p2, p3, p4, h1, h2, h3, h4;
boolean buttonEnabled01 = true;
boolean buttonEnabled02 = true;
boolean buttonEnabled03 = true;
bool h12;
bool PM;

void setup()
{
  bmp.begin();
  dht.begin();
  bmp.setOversampling(4);
  rtc.begin();

  //rtc.setDOW(MONDAY);     // Imposta il giorno della settimana
  //rtc.setTime(18, 41, 00);     // Impostail l'orario 12:00:00 (formato 24 ore)
  //rtc.setDate(21, 10, 2019);   // Imposta la data nel formato dd, mm, aaaa
  
  Serial.begin(9600);

  tft.reset();

  uint16_t identifier = 0x9486;
  Serial.print("TFT Display: ");
  Serial.println(identifier);
  tft.begin(identifier);
  tft.setRotation(1);
  tft.fillScreen(BLACK);
  
  tft.fillRect(0,100, 480, 5, WHITE);
  tft.fillRect(0,0, 480, 100, BLUE);

  tft.setCursor(10, 5);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.println("Stazione Meteo");
  
  tft.setCursor(10, 30);
  tft.setTextColor(WHITE);
  tft.setTextSize(7);
  tft.println("STUDIO");


}

void loop()
{

TSPoint p = ts.getPoint();
if (p.z > ts.pressureThreshhold){

p.x = map (p.x , TS_MINX, TS_MAXX, 0, 480 );
p.y = map (p.y , TS_MINY, TS_MAXY, 0, 320 );

  Serial.print ("x= ");
  Serial.println(p.x);
  Serial.print ("y= ");
  Serial.println(p.y);
    delay(500);

  if(p.x>320 && p.x<480 && p.y>150 && p.y<250 && buttonEnabled01) 
   
     {
    
        
     pinMode(XM, OUTPUT);
     pinMode(YP, OUTPUT);
      tft.fillRect(0,105, 480, 220, BLACK);
       tempday();
       delay (5000);
       tft.fillRect(0,105, 480, 220, BLACK);
       Home();
                }
   if(p.x>10 && p.x<160 && p.y>150 && p.y<250 && buttonEnabled02) 
   
         {
            
            pinMode(XM, OUTPUT);
            pinMode(YP, OUTPUT);
              tft.fillRect(0,105, 480, 220, BLACK);
              humday();
              delay (5000);
              tft.fillRect(0,105, 480, 220, BLACK);
              Home();
                       }
      
    if(p.x>10 && p.x<270 && p.y>250 && p.y<320 && buttonEnabled03) 
   
                  {
           
                    pinMode(XM, OUTPUT);
                    pinMode(YP, OUTPUT);
                      tft.fillRect(0,105, 480, 220, BLACK);
                      presday();
                      delay (5000);
                      tft.fillRect(0,105, 480, 220, BLACK);
                      Home();
                              }     
      }

  if (p.z == 0) {
        pinMode(XM, OUTPUT);
        pinMode(YP, OUTPUT);
        Home();
        } 
        
 }

void Home(){

    Data();
    drop();
  
  tempo = rtc.getTime();
  
  for (int n=100; n<315; n++){
    tft.fillRect(280,n, 5, 5, WHITE);
  }
  
  tft.fillRect(0,210, 280, 5, WHITE);
  
if (tempo.hour == 0 && tempo.min == 0 && tempo.sec > 0 && tempo.sec < 4){
  tft.fillRect(300,5, 480, 25, BLUE);
  tft.setCursor(300, 5);
  tft.setTextColor(WHITE, BLUE);
  tft.setTextSize(3);
  tft.println(rtc.getDOWStr());
  }

  else {
  
  tft.setCursor(300, 5);
  tft.setTextColor(WHITE, BLUE);
  tft.setTextSize(3);
  tft.println(rtc.getDOWStr());
    }
  
  tft.setCursor(300, 37);
  tft.setTextColor(WHITE, BLUE);
  tft.setTextSize(3);
  tft.print(rtc.getTimeStr());
    
  tft.setCursor(300, 72);
  tft.setTextColor(YELLOW, BLUE);
  tft.setTextSize(3);
  tft.print(rtc.getDateStr());

// Pressione
  tft.setCursor(10,220);
  tft.setTextColor(YELLOW);
  tft.setTextSize(3);
  tft.println("Pressione");
  tft.setCursor(10,270);
  tft.setTextColor(WHITE, BLACK);
  tft.setTextSize(5);
  tft.println(Pres);
  tft.setCursor(230,290);
  tft.setTextColor(CYAN);
  tft.setTextSize(2);
  tft.println("mBar");

// Umidità
  tft.setCursor(10,110);
  tft.setTextColor(YELLOW);
  tft.setTextSize(3);
  tft.println("Umidita'");
  tft.setCursor(10,160);
  tft.setTextColor(WHITE, BLACK);
  tft.setTextSize(5);
  tft.println(h);
  tft.setCursor(200,180);
  tft.setTextColor(CYAN);
  tft.setTextSize(2);
  tft.println("%");

// Temperatura
  tft.setCursor(350,110);
  tft.setTextColor(YELLOW);
  tft.setTextSize(3);
  tft.println("Temp.");
  tft.setCursor(320,160);
  tft.setTextColor(WHITE, BLACK);
  tft.setTextSize(5);
  tft.println(TempMed);
  tft.setCursor(345,200);
  tft.setTextColor(CYAN);
  tft.setTextSize(2);
  tft.println("Celsius");
  
if (TempMed < 10){
      termo00();
  }
  else if (TempMed >= 10 && TempMed < 27 ) {
        termo01();
    }
    else {
            termo02();
    }
  
  }

void Data(){
    
    
  
  h = dht.readHumidity();
  t = dht.readTemperature();
  
  char misurazione = bmp.startMeasurment();
  misurazione = bmp.getTemperatureAndPressure(Temp,Pres);

  TempMed = (t + Temp)/2;

  
 Serial.print("Temperatura BMP= ");
 Serial.print(Temp); 
 Serial.print(" C\t");
 Serial.print("Pressione = ");
 Serial.print(Pres); 
 Serial.println(" mBar");
        
 Serial.print("Temperatura DHT22: ");
 Serial.print(t);
 Serial.print("C, Umidità: ");
 Serial.print(h);
 Serial.println("%");

 Serial.print ("Temperatura Media: ");
 Serial.println(TempMed);


memo();
 

}

void tempday(){

  for (int n=100; n<315; n++){
    tft.fillRect(240,n, 5, 5, WHITE);
  }
  
  tft.fillRect(0,210, 480, 5, WHITE);

//t1
  tft.setCursor(10,110);
  tft.setTextColor(YELLOW);
  tft.setTextSize(2);
  tft.println("Ore 00.00");
  tft.setCursor(10,150);
  tft.setTextColor(WHITE, BLACK);
  tft.setTextSize(5);
  tft.println(t1);
  tft.setCursor(200,165);
  tft.setTextColor(CYAN);
  tft.setTextSize(3);
  tft.println(" C");

//t2
  tft.setCursor(260,110);
  tft.setTextColor(YELLOW);
  tft.setTextSize(2);
  tft.println("Ore 06.00");
  tft.setCursor(260,150);
  tft.setTextColor(WHITE, BLACK);
  tft.setTextSize(5);
  tft.println(t2);
  tft.setCursor(440,165);
  tft.setTextColor(CYAN);
  tft.setTextSize(3);
  tft.println(" C");

//t3
  tft.setCursor(10,220);
  tft.setTextColor(YELLOW);
  tft.setTextSize(2);
  tft.println("Ore 12.00");
  tft.setCursor(10,260);
  tft.setTextColor(WHITE, BLACK);
  tft.setTextSize(5);
  tft.println(t3);
  tft.setCursor(200,275);
  tft.setTextColor(CYAN);
  tft.setTextSize(3);
  tft.println(" C");

//t4
  tft.setCursor(260,220);
  tft.setTextColor(YELLOW);
  tft.setTextSize(2);
  tft.println("Ore 18.00");
  tft.setCursor(260,260);
  tft.setTextColor(WHITE, BLACK);
  tft.setTextSize(5);
  tft.println(t4);
  tft.setCursor(440,275);
  tft.setTextColor(CYAN);
  tft.setTextSize(3);
  tft.println(" C");
  
}

void presday(){
for (int n=100; n<315; n++){
    tft.fillRect(240,n, 5, 5, WHITE);
  }
  
  tft.fillRect(0,210, 480, 5, WHITE);

//p1
  tft.setCursor(10,110);
  tft.setTextColor(YELLOW);
  tft.setTextSize(2);
  tft.println("Ore 00.00");
  tft.setCursor(10,150);
  tft.setTextColor(WHITE, BLACK);
  tft.setTextSize(5);
  tft.println(p1);
  tft.setCursor(180,190);
  tft.setTextColor(CYAN);
  tft.setTextSize(2);
  tft.println("mBar");

//p2
  tft.setCursor(260,110);
  tft.setTextColor(YELLOW);
  tft.setTextSize(2);
  tft.println("Ore 06.00");
  tft.setCursor(260,150);
  tft.setTextColor(WHITE, BLACK);
  tft.setTextSize(5);
  tft.println(p2);
  tft.setCursor(420,190);
  tft.setTextColor(CYAN);
  tft.setTextSize(2);
  tft.println("mBar");

//p3
  tft.setCursor(10,220);
  tft.setTextColor(YELLOW);
  tft.setTextSize(2);
  tft.println("Ore 12.00");
  tft.setCursor(10,260);
  tft.setTextColor(WHITE, BLACK);
  tft.setTextSize(5);
  tft.println(p3);
  tft.setCursor(180,300);
  tft.setTextColor(CYAN);
  tft.setTextSize(2);
  tft.println("mBar");

//p4
  tft.setCursor(260,220);
  tft.setTextColor(YELLOW);
  tft.setTextSize(2);
  tft.println("Ore 18.00");
  tft.setCursor(260,260);
  tft.setTextColor(WHITE, BLACK);
  tft.setTextSize(5);
  tft.println(p4);
  tft.setCursor(420,300);
  tft.setTextColor(CYAN);
  tft.setTextSize(2);
  tft.println("mBar");
  
}

void humday(){
for (int n=100; n<315; n++){
    tft.fillRect(240,n, 5, 5, WHITE);
  }
  
  tft.fillRect(0,210, 480, 5, WHITE);

//h1
  tft.setCursor(10,110);
  tft.setTextColor(YELLOW);
  tft.setTextSize(2);
  tft.println("Ore 00.00");
  tft.setCursor(10,150);
  tft.setTextColor(WHITE, BLACK);
  tft.setTextSize(5);
  tft.println(h1);
  tft.setCursor(200,165);
  tft.setTextColor(CYAN);
  tft.setTextSize(3);
  tft.println(" %");

//h2
  tft.setCursor(260,110);
  tft.setTextColor(YELLOW);
  tft.setTextSize(2);
  tft.println("Ore 06.00");
  tft.setCursor(260,150);
  tft.setTextColor(WHITE, BLACK);
  tft.setTextSize(5);
  tft.println(h2);
  tft.setCursor(440,165);
  tft.setTextColor(CYAN);
  tft.setTextSize(3);
  tft.println(" %");

//h3
  tft.setCursor(10,220);
  tft.setTextColor(YELLOW);
  tft.setTextSize(2);
  tft.println("Ore 12.00");
  tft.setCursor(10,260);
  tft.setTextColor(WHITE, BLACK);
  tft.setTextSize(5);
  tft.println(h3);
  tft.setCursor(200,275);
  tft.setTextColor(CYAN);
  tft.setTextSize(3);
  tft.println(" %");

//h4
  tft.setCursor(260,220);
  tft.setTextColor(YELLOW);
  tft.setTextSize(2);
  tft.println("Ore 18.00");
  tft.setCursor(260,260);
  tft.setTextColor(WHITE, BLACK);
  tft.setTextSize(5);
  tft.println(h4);
  tft.setCursor(440,275);
  tft.setTextColor(CYAN);
  tft.setTextSize(3);
  tft.println(" %");
}

void memo(){

//Memorizza Temperatura ogni 6 ore
if (tempo.hour == 0 && tempo.min == 0 && tempo.sec > 0 && tempo.sec < 4){
  t1 = TempMed;
}

if (tempo.hour == 6 && tempo.min == 0 && tempo.sec > 0 && tempo.sec < 4){
  t2 = TempMed;
}

if (tempo.hour == 12 && tempo.min == 0 && tempo.sec > 0 && tempo.sec < 4){
  t3 = TempMed;
}

if (tempo.hour == 18 && tempo.min == 0 && tempo.sec > 0 && tempo.sec < 4){
  t4 = TempMed;
}


//Memorizza Pressione ogni 6 ore
if (tempo.hour == 0 && tempo.min == 0 && tempo.sec > 0 && tempo.sec < 4){
  p1 = Pres;
}

if (tempo.hour == 6 && tempo.min == 0 && tempo.sec > 0 && tempo.sec < 4){
  p2 = Pres;
}

if (tempo.hour == 12 && tempo.min == 0 && tempo.sec > 0 && tempo.sec < 4){
  p3 = Pres;
}

if (tempo.hour == 18 && tempo.min == 0 && tempo.sec > 0 && tempo.sec < 4){
  p4 = Pres;
}

//Memorizza Umidità ogni 6 ore
if (tempo.hour == 0 && tempo.min == 0 && tempo.sec > 0 && tempo.sec < 4){
  h1 = h;
}

if (tempo.hour == 6 && tempo.min == 0 && tempo.sec > 0 && tempo.sec < 4){
  h2 = h;
}

if (tempo.hour == 12 && tempo.min == 0 && tempo.sec > 0 && tempo.sec < 4){
  h3 = h;
}

if (tempo.hour == 18 && tempo.min == 0 && tempo.sec > 0 && tempo.sec < 4){
  h4 = h;
}

}

void drop(){
  
tft.fillRect(245,120, 5, 5, CYAN);
tft.fillRect(245,125, 5, 5, CYAN);
tft.fillRect(245,130, 5, 5, CYAN);
tft.fillRect(250,130, 5, 5, CYAN);
tft.fillRect(240,130, 5, 5, CYAN);
tft.fillRect(245,135, 5, 5, CYAN);
tft.fillRect(250,135, 5, 5, CYAN);
tft.fillRect(240,135, 5, 5, CYAN);
tft.fillRect(245,140, 5, 5, CYAN);
tft.fillRect(250,140, 5, 5, CYAN);
tft.fillRect(240,140, 5, 5, CYAN);
tft.fillRect(255,140, 5, 5, CYAN);
tft.fillRect(235,140, 5, 5, CYAN);
tft.fillRect(245,145, 5, 5, CYAN);
tft.fillRect(250,145, 5, 5, CYAN);
tft.fillRect(240,145, 5, 5, WHITE);
tft.fillRect(255,145, 5, 5, CYAN);
tft.fillRect(235,145, 5, 5, CYAN);
tft.fillRect(245,150, 5, 5, CYAN);
tft.fillRect(250,150, 5, 5, CYAN);
tft.fillRect(240,150, 5, 5, WHITE);
tft.fillRect(255,150, 5, 5, CYAN);
tft.fillRect(235,150, 5, 5, CYAN);
tft.fillRect(245,155, 5, 5, WHITE);
tft.fillRect(250,155, 5, 5, CYAN);
tft.fillRect(240,155, 5, 5, CYAN);
}

void termo00(){

tft.fillRect(380,225, 5, 5, WHITE);
tft.fillRect(385,225, 5, 5, WHITE);
tft.fillRect(375,230, 5, 5, WHITE);
tft.fillRect(390,230, 5, 5, WHITE);
tft.fillRect(375,235, 5, 5, WHITE);
tft.fillRect(390,235, 5, 5, WHITE);
tft.fillRect(375,240, 5, 5, WHITE);
tft.fillRect(390,240, 5, 5, WHITE);
tft.fillRect(375,245, 5, 5, WHITE);
tft.fillRect(390,245, 5, 5, WHITE);
tft.fillRect(385,245, 5, 5, WHITE);
tft.fillRect(375,250, 5, 5, WHITE);
tft.fillRect(390,250, 5, 5, WHITE);
tft.fillRect(375,255, 5, 5, WHITE);
tft.fillRect(390,255, 5, 5, WHITE);
tft.fillRect(375,260, 5, 5, WHITE);
tft.fillRect(390,260, 5, 5, WHITE);
tft.fillRect(385,260, 5, 5, WHITE);
tft.fillRect(375,265, 5, 5, WHITE);
tft.fillRect(390,265, 5, 5, WHITE);
tft.fillRect(375,270, 5, 5, WHITE);
tft.fillRect(390,270, 5, 5, WHITE);
tft.fillRect(375,275, 5, 5, WHITE);
tft.fillRect(390,275, 5, 5, WHITE);
tft.fillRect(385,275, 5, 5, WHITE);
tft.fillRect(370,280, 5, 5, WHITE);
tft.fillRect(395,280, 5, 5, WHITE);
tft.fillRect(365,285, 5, 5, WHITE);
tft.fillRect(400,285, 5, 5, WHITE);
tft.fillRect(365,290, 5, 5, WHITE);
tft.fillRect(400,290, 5, 5, WHITE);
tft.fillRect(365,295, 5, 5, WHITE);
tft.fillRect(400,295, 5, 5, WHITE);
tft.fillRect(370,300, 5, 5, WHITE);
tft.fillRect(395,300, 5, 5, WHITE);
tft.fillRect(375,305, 5, 5, WHITE);
tft.fillRect(390,305, 5, 5, WHITE);
tft.fillRect(380,305, 5, 5, WHITE);
tft.fillRect(385,305, 5, 5, WHITE);

tft.fillRect(380,255, 10, 5, BLACK);
tft.fillRect(380,260, 5, 5, BLACK);
tft.fillRect(380,265, 10, 5, BLACK);
tft.fillRect(380,270, 10, 5, BLACK);
tft.fillRect(380,275, 5, 5, RED);
tft.fillRect(375,280, 20, 5, RED);
tft.fillRect(370,285, 30, 15, RED);
tft.fillRect(375,300, 20, 5, RED);
}

void termo01(){

tft.fillRect(380,225, 5, 5, WHITE);
tft.fillRect(385,225, 5, 5, WHITE);
tft.fillRect(375,230, 5, 5, WHITE);
tft.fillRect(390,230, 5, 5, WHITE);
tft.fillRect(375,235, 5, 5, WHITE);
tft.fillRect(390,235, 5, 5, WHITE);
tft.fillRect(375,240, 5, 5, WHITE);
tft.fillRect(390,240, 5, 5, WHITE);
tft.fillRect(375,245, 5, 5, WHITE);
tft.fillRect(390,245, 5, 5, WHITE);
tft.fillRect(385,245, 5, 5, WHITE);
tft.fillRect(375,250, 5, 5, WHITE);
tft.fillRect(390,250, 5, 5, WHITE);
tft.fillRect(375,255, 5, 5, WHITE);
tft.fillRect(390,255, 5, 5, WHITE);
tft.fillRect(375,260, 5, 5, WHITE);
tft.fillRect(390,260, 5, 5, WHITE);
tft.fillRect(385,260, 5, 5, WHITE);
tft.fillRect(375,265, 5, 5, WHITE);
tft.fillRect(390,265, 5, 5, WHITE);
tft.fillRect(375,270, 5, 5, WHITE);
tft.fillRect(390,270, 5, 5, WHITE);
tft.fillRect(375,275, 5, 5, WHITE);
tft.fillRect(390,275, 5, 5, WHITE);
tft.fillRect(385,275, 5, 5, WHITE);
tft.fillRect(370,280, 5, 5, WHITE);
tft.fillRect(395,280, 5, 5, WHITE);
tft.fillRect(365,285, 5, 5, WHITE);
tft.fillRect(400,285, 5, 5, WHITE);
tft.fillRect(365,290, 5, 5, WHITE);
tft.fillRect(400,290, 5, 5, WHITE);
tft.fillRect(365,295, 5, 5, WHITE);
tft.fillRect(400,295, 5, 5, WHITE);
tft.fillRect(370,300, 5, 5, WHITE);
tft.fillRect(395,300, 5, 5, WHITE);
tft.fillRect(375,305, 5, 5, WHITE);
tft.fillRect(390,305, 5, 5, WHITE);
tft.fillRect(380,305, 5, 5, WHITE);
tft.fillRect(385,305, 5, 5, WHITE);

tft.fillRect(380,235, 10, 10, BLACK);
tft.fillRect(380,245, 5, 5, BLACK);
tft.fillRect(380,250, 10, 5, BLACK);
tft.fillRect(380,255, 10, 5, RED);
tft.fillRect(380,260, 5, 5, RED);
tft.fillRect(380,265, 10, 5, RED);
tft.fillRect(380,270, 10, 5, RED);
tft.fillRect(380,275, 5, 5, RED);
tft.fillRect(375,280, 20, 5, RED);
tft.fillRect(370,285, 30, 15, RED);
tft.fillRect(375,300, 20, 5, RED);
}

void termo02(){

tft.fillRect(380,225, 5, 5, WHITE);
tft.fillRect(385,225, 5, 5, WHITE);
tft.fillRect(375,230, 5, 5, WHITE);
tft.fillRect(390,230, 5, 5, WHITE);
tft.fillRect(375,235, 5, 5, WHITE);
tft.fillRect(390,235, 5, 5, WHITE);
tft.fillRect(375,240, 5, 5, WHITE);
tft.fillRect(390,240, 5, 5, WHITE);
tft.fillRect(375,245, 5, 5, WHITE);
tft.fillRect(390,245, 5, 5, WHITE);
tft.fillRect(385,245, 5, 5, WHITE);
tft.fillRect(375,250, 5, 5, WHITE);
tft.fillRect(390,250, 5, 5, WHITE);
tft.fillRect(375,255, 5, 5, WHITE);
tft.fillRect(390,255, 5, 5, WHITE);
tft.fillRect(375,260, 5, 5, WHITE);
tft.fillRect(390,260, 5, 5, WHITE);
tft.fillRect(385,260, 5, 5, WHITE);
tft.fillRect(375,265, 5, 5, WHITE);
tft.fillRect(390,265, 5, 5, WHITE);
tft.fillRect(375,270, 5, 5, WHITE);
tft.fillRect(390,270, 5, 5, WHITE);
tft.fillRect(375,275, 5, 5, WHITE);
tft.fillRect(390,275, 5, 5, WHITE);
tft.fillRect(385,275, 5, 5, WHITE);
tft.fillRect(370,280, 5, 5, WHITE);
tft.fillRect(395,280, 5, 5, WHITE);
tft.fillRect(365,285, 5, 5, WHITE);
tft.fillRect(400,285, 5, 5, WHITE);
tft.fillRect(365,290, 5, 5, WHITE);
tft.fillRect(400,290, 5, 5, WHITE);
tft.fillRect(365,295, 5, 5, WHITE);
tft.fillRect(400,295, 5, 5, WHITE);
tft.fillRect(370,300, 5, 5, WHITE);
tft.fillRect(395,300, 5, 5, WHITE);
tft.fillRect(375,305, 5, 5, WHITE);
tft.fillRect(390,305, 5, 5, WHITE);
tft.fillRect(380,305, 5, 5, WHITE);
tft.fillRect(385,305, 5, 5, WHITE);

tft.fillRect(380,235, 10, 10, RED);
tft.fillRect(380,245, 5, 5, RED);
tft.fillRect(380,250, 10, 5, RED);
tft.fillRect(380,255, 10, 5, RED);
tft.fillRect(380,260, 5, 5, RED);
tft.fillRect(380,265, 10, 5, RED);
tft.fillRect(380,270, 10, 5, RED);
tft.fillRect(380,275, 5, 5, RED);
tft.fillRect(375,280, 20, 5, RED);
tft.fillRect(370,285, 30, 15, RED);
tft.fillRect(375,300, 20, 5, RED);
}

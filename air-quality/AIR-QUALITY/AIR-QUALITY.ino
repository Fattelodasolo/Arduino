#include <Adafruit_ILI9341.h>
#include "Adafruit_GFX.h"
#include <URTouch.h>
#include <SPI.h>
#include "Adafruit_CCS811.h"

#define TFT_DC 9
#define TFT_CS 10
#define TFT_CLK 13
#define TFT_MISO 12
#define TFT_MOSI 11
#define TFT_RST 8

#define SCK_PIN 3              
#define CS_PIN  4               
#define MOSI_PIN 5              
#define MISO_PIN 6
#define TIRQ_PIN  7

URTouch ts(SCK_PIN, CS_PIN, MOSI_PIN, MISO_PIN, TIRQ_PIN);

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

Adafruit_CCS811 ccs;

bool state1 = 0;
bool touch1 = 0;
bool state2 = 0;
bool touch2 = 0;
bool buzzer = 0;

unsigned long tempo;
unsigned long tempoattesa = 1000;

const unsigned char windicon[] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x01, 0xfe, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x03, 0x87, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x07, 0x0f, 0xc0, 0x00, 
0x00, 0x00, 0x00, 0x07, 0x1f, 0xe0, 0x00, 
0x03, 0xff, 0xff, 0xfe, 0x1c, 0xf0, 0x00, 
0x03, 0xff, 0xff, 0xfc, 0x38, 0x70, 0x00, 
0x03, 0xff, 0xff, 0xf0, 0x30, 0x30, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x10, 0x30, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 
0x00, 0x1f, 0xff, 0xff, 0xff, 0xe0, 0x00, 
0x00, 0x1f, 0xff, 0xff, 0xff, 0xc0, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x7f, 0xff, 0xff, 0x00, 0x00, 0x00, 
0x00, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 
0x00, 0x7f, 0xff, 0xff, 0xc0, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x60, 0x60, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x70, 0x60, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x70, 0xe0, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x3f, 0xc0, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x1f, 0x80, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 
};

const unsigned char lighticon[] PROGMEM = {
0xff, 0xff, 0xff, 0xf7, 0xff, 0xff, 0xff, 0xc0, 
0xff, 0xff, 0xff, 0xf3, 0xff, 0xff, 0xff, 0xc0, 
0xff, 0xff, 0xff, 0xf3, 0xff, 0xff, 0xff, 0xc0, 
0xff, 0xff, 0xff, 0xf3, 0xff, 0xff, 0xff, 0xc0, 
0xff, 0xff, 0xff, 0xfb, 0xff, 0xff, 0xff, 0xc0, 
0xff, 0xff, 0x9f, 0xff, 0xfe, 0x7f, 0xff, 0xc0, 
0xff, 0xff, 0x9f, 0xff, 0xfc, 0x7f, 0xff, 0xc0, 
0xff, 0xff, 0xc7, 0xe9, 0xf9, 0xff, 0xff, 0xc0, 
0xff, 0xff, 0xff, 0x00, 0x3d, 0xff, 0xff, 0xc0, 
0xff, 0xff, 0xfe, 0x00, 0x1f, 0xff, 0xff, 0xc0, 
0xff, 0xff, 0xfc, 0x00, 0x0f, 0xff, 0xff, 0xc0, 
0xff, 0xff, 0xf8, 0x00, 0x07, 0xff, 0xff, 0xc0, 
0xff, 0xff, 0xf0, 0x00, 0x07, 0xff, 0xff, 0xc0, 
0xff, 0xff, 0xf0, 0x00, 0x03, 0xff, 0xff, 0xc0, 
0xff, 0xff, 0xf0, 0x00, 0x03, 0xff, 0xff, 0xc0, 
0xff, 0xff, 0xe0, 0x00, 0x03, 0xff, 0xff, 0xc0, 
0xff, 0xf0, 0x70, 0x00, 0x01, 0x83, 0xff, 0xc0, 
0xff, 0xf4, 0xe0, 0x00, 0x03, 0xc7, 0xff, 0xc0, 
0xff, 0xff, 0xf0, 0x00, 0x01, 0xff, 0xff, 0xc0, 
0xff, 0xff, 0xf0, 0x00, 0x03, 0xff, 0xff, 0xc0, 
0xff, 0xff, 0xf0, 0x00, 0x03, 0xff, 0xff, 0xc0, 
0xff, 0xff, 0xf0, 0x00, 0x07, 0xff, 0xff, 0xc0, 
0xff, 0xff, 0xf8, 0x00, 0x0f, 0xff, 0xff, 0xc0, 
0xff, 0xff, 0xfc, 0x00, 0x0f, 0xff, 0xff, 0xc0, 
0xff, 0xff, 0xff, 0x00, 0x3f, 0xff, 0xff, 0xc0, 
0xff, 0xff, 0xef, 0x80, 0x7b, 0xff, 0xff, 0xc0, 
0xff, 0xff, 0xc7, 0xfb, 0xf8, 0xff, 0xff, 0xc0, 
0xff, 0xff, 0x9f, 0xff, 0xfc, 0x7f, 0xff, 0xc0, 
0xff, 0xff, 0x9f, 0xff, 0xff, 0x7f, 0xff, 0xc0, 
0xff, 0xff, 0xff, 0xf3, 0xff, 0xff, 0xff, 0xc0, 
0xff, 0xff, 0xff, 0xf3, 0xff, 0xff, 0xff, 0xc0, 
0xff, 0xff, 0xff, 0xf3, 0xff, 0xff, 0xff, 0xc0, 
0xff, 0xff, 0xff, 0xf7, 0xff, 0xff, 0xff, 0xc0, 
0xff, 0xff, 0xff, 0xf3, 0xff, 0xff, 0xff, 0xc0
};

const float S_analog = 1023.0;

int x, y, co, nh3, co2, tvoc;
float  no2;

void setup() {
  pinMode(2, OUTPUT);
  pinMode(17, OUTPUT);

  Serial.begin(9600); 
  ccs.begin();
    while(!ccs.available()){
      Serial.print(".");
      delay (1000);
    }

  ts.InitTouch();
  ts.setPrecision(PREC_MEDIUM);
  Serial.println("\nTouch inizializzato!");
  delay(500);

  digitalWrite(2, HIGH);
    
  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(ILI9341_BLACK);
  homepage();
   
}

void loop() {

  if (ts.dataAvailable()) {
    ts.read();
      x=ts.getX();
      y=ts.getY();
    Serial.print("x = ");
    Serial.print(x);
    Serial.print("\ty = ");
    Serial.println(y);
    
  
    if (x > 12 && x < 64 && y > 10 && y < 36) {
        state1 = 0;
        touch1 = !touch1;      
        }
     
    if (x > 285 && x < 316 && y > 14 && y < 40) {
        state2 = 0;
        touch2 = !touch2;      
        }
    }
  // NPN
  if (state1 == 0 && touch1 == 1) {
    /*tft.fillRect(7, 7, 58, 34,ILI9341_RED);
    tft.setCursor(17, 20);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(1);
    tft.println("Display");*/
    state1 = 1;
    digitalWrite(2, LOW);
    delay(200);
  }

  if (state1 == 0 && touch1 == 0) {
    /*tft.fillRect(7, 7, 58, 34,ILI9341_BLUE);
    tft.setCursor(17, 20);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(1);
    tft.println("Display");*/
    state1 = 1;
    digitalWrite(2, HIGH);
    delay(200);
  }
// Buzzer
  if (state2 == 0 && touch2 == 1) {
    tft.fillCircle(294, 25, 17, ILI9341_RED);
    tft.setCursor(290, 17);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(2);
    tft.println("A");
    state2 = 1;
    buzzer = 1;
    delay(200);
  }

  if (state2 == 0 && touch2 == 0) {
    tft.fillCircle(294, 25, 17, ILI9341_GREEN);
    tft.setCursor(290, 17);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(2);
    tft.println("A");
    state2 = 1;
    buzzer = 0;
    delay(200);
  }
  
  dati();
}


void homepage(){
  
  tft.setCursor(85, 18);
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_CYAN);
  tft.println("AIR-QUALITY");

  tft.drawBitmap(215, 6, windicon, 50, 38,ILI9341_CYAN);
  tft.drawBitmap(7, 7, lighticon, 58, 34,ILI9341_LIGHTGREY);
  
  tft.drawRoundRect(0, 0, 320, 240, 7, ILI9341_WHITE);
  tft.drawCircle(294, 25, 18, ILI9341_WHITE);
  tft.drawRect (6, 6, 60, 36,ILI9341_WHITE);
  
  tft.drawRect(5, 50, 310, 10, ILI9341_WHITE);
  tft.setCursor(5, 68);
  tft.setTextSize(1);
  tft.setTextColor(ILI9341_YELLOW);
  tft.println("Anidride Carbonica:");
  
  tft.drawRect(5, 90, 310, 10, ILI9341_WHITE);
  tft.setCursor(5, 108);
  tft.setTextSize(1);
  tft.setTextColor(ILI9341_YELLOW);
  tft.println("Monossido di Carbonio:");
  
  tft.drawRect(5, 130, 310, 10, ILI9341_WHITE);
  tft.setCursor(5, 148);
  tft.setTextSize(1);
  tft.setTextColor(ILI9341_YELLOW);
  tft.println("Ammoniaca:");
  
  tft.drawRect(5, 170, 310, 10, ILI9341_WHITE);
  tft.setCursor(5, 188);
  tft.setTextSize(1);
  tft.setTextColor(ILI9341_YELLOW);
  tft.println("Diossido di Azoto:");
  
  tft.drawRect(5, 210, 310, 10, ILI9341_WHITE);  
  tft.setCursor(5, 228);
  tft.setTextSize(1);
  tft.setTextColor(ILI9341_YELLOW);
  tft.println("TVOC:");
}


void dati(){
if (millis() > tempo)  {
  ccs.readData();

  co2 = ccs.geteCO2();
  tvoc = ccs.getTVOC();
  
  co = map (analogRead(A0), 0, S_analog, 1, 1000);            // Calcolo Monossido di Carbonio
  nh3 = map (analogRead(A1), 0, S_analog, 1, 500);            // Calcolo Ammoniaca
  no2 = (map (analogRead(A2), 0, S_analog, 5, 1000)) / 100.0 ;  // Calcolo Diossido di Azoto

  alarm();
  
  
  Serial.print("CO2: ");
  Serial.print(co2);
  Serial.print(" ppm \tTVOC: ");
  Serial.print(tvoc);
  Serial.println(" ppb");
  Serial.print("CO: ");
  Serial.print(co);
  Serial.print(" ppm\t");
  Serial.print("NH3: ");
  Serial.print(nh3);
  Serial.print("ppm\t");
  Serial.print("NO2: ");
  Serial.print(no2);
  Serial.println("ppm");

  //CO2 Display
  tft.setCursor(125, 68);
  tft.setTextSize(1);
  tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
  tft.print(co2);
  tft.print("  "); 
  tft.print("ppm"); tft.println("   "); 
  
  //CO Display
  tft.setCursor(145, 108);
  tft.setTextSize(1);
  tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
  tft.print(co);
  tft.print("  "); 
  tft.print("ppm"); tft.println("   "); 
  
  //NH3 Display
  tft.setCursor(75, 148);
  tft.setTextSize(1);
  tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
  tft.print(nh3);
  tft.print("  "); 
  tft.print("ppm"); tft.println("   "); 
  
  //NO2 Display
  tft.setCursor(120, 188);
  tft.setTextSize(1);
  tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
  tft.print(no2);
  tft.print("  "); 
  tft.print("ppm"); tft.println("   "); 

  //TVOC Display
  tft.setCursor(40, 228);
  tft.setTextSize(1);
  tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
  tft.print(tvoc);
  tft.print("  "); 
  tft.print("ppb"); tft.println("   ");

  //Grafici
  int g_co2 = map (co2, 400, 8192, 25, 309);
  int g_co = map (co, 1, 1000, 25, 309);
  int g_nh3 = map (nh3, 1, 500, 25, 309);
  int g_no2 = map (no2, 0, 10, 25, 309);
  int g_tvoc = map (tvoc, 0 , 1187, 25, 309);


// CO2 Grafico
  if (co2 < 1400){
    tft.fillRect(6, 51, g_co2, 8, ILI9341_GREEN);
    tft.fillRect(g_co2, 51, 309-g_co2, 8, ILI9341_BLACK);
  }
  else if (co2 >= 1400 && co2 < 2000){
    tft.fillRect(6, 51, g_co2, 8,ILI9341_YELLOW);
    tft.fillRect(g_co2, 51, 309-g_co2, 8, ILI9341_BLACK);
  }
  else if (co2 >= 2000 && co2 <8192){
    tft.fillRect(6, 51, g_co2, 8, ILI9341_RED);
    tft.fillRect(g_co2, 51, 309-g_co2, 8, ILI9341_BLACK);
    }

// CO Grafico
  if (co < 9){
    tft.fillRect(6, 91, g_co, 8, ILI9341_GREEN);
    tft.fillRect(g_co, 91, 309-g_co, 8, ILI9341_BLACK);
  }
  else if (co >= 9 && co < 25){
    tft.fillRect(6, 91, g_co, 8,ILI9341_YELLOW);
    tft.fillRect(g_co, 91, 309-g_co, 8, ILI9341_BLACK);
  }
  else if (co >= 25 && co < 1000){
    tft.fillRect(6, 91, g_co, 8, ILI9341_RED);
    tft.fillRect(g_co, 91, 309-g_co, 8, ILI9341_BLACK);
    }

// NH3 Grafico
  if (nh3 < 25){
    tft.fillRect(6, 131, g_nh3, 8, ILI9341_GREEN);
    tft.fillRect(g_nh3, 131, 309-g_nh3, 8, ILI9341_BLACK);
  }
  else if (nh3 >= 25 && nh3 < 400){
    tft.fillRect(6, 131, g_co2, 8,ILI9341_YELLOW);
    tft.fillRect(g_nh3, 51, 309-g_nh3, 8, ILI9341_BLACK);
  }
  else if (nh3 >= 400 && nh3 <500){
    tft.fillRect(6, 131, g_nh3, 8, ILI9341_RED);
    tft.fillRect(g_nh3, 131, 309-g_nh3, 8, ILI9341_BLACK);
    }

// NO2 Grafico
  if (no2 < 4){
    tft.fillRect(6, 171, g_no2, 8, ILI9341_GREEN);
    tft.fillRect(g_no2, 171, 309-g_no2, 8, ILI9341_BLACK);
  }
  else if (no2 >= 4 && no2 < 5){
    tft.fillRect(6, 171, g_no2, 8,ILI9341_YELLOW);
    tft.fillRect(g_no2, 51, 309-g_no2, 8, ILI9341_BLACK);
  }
  else if (no2 >= 5 && no2 <10){
    tft.fillRect(6, 131, g_no2, 8, ILI9341_RED);
    tft.fillRect(g_no2, 131, 309-g_no2, 8, ILI9341_BLACK);
    }

// TVOC Grafico
    if (tvoc < 80){
    tft.fillRect(6, 211, g_tvoc, 8, ILI9341_GREEN);
    tft.fillRect(g_tvoc, 211, 309-g_tvoc, 8, ILI9341_BLACK);
  }
  else if (tvoc >= 80 && co2 < 101){
    tft.fillRect(6, 211, g_tvoc, 8,ILI9341_YELLOW);
    tft.fillRect(g_tvoc, 211, 309-g_tvoc, 8, ILI9341_BLACK);
  }
  else if (tvoc >= 101 && co2 <1187){
    tft.fillRect(6, 211, g_tvoc, 8, ILI9341_RED);
    tft.fillRect(g_tvoc, 211, 309-g_tvoc, 8, ILI9341_BLACK);
    }
tempo = millis() + tempoattesa;
  }
}

void alarm(){
  if (co2 >= 1400){
    if (buzzer == 0){
    buzzer_on();
    }
  }

  if (co >= 9){
    if (buzzer == 0){
    buzzer_on();
    }
  }

  if (no2 >= 4){
    if (buzzer == 0){
     buzzer_on();
    }
  }

  if (nh3 >= 25){
    if (buzzer == 0){
     buzzer_on();
    }
  }
  
  if (tvoc >= 80){
    if (buzzer == 0){
     buzzer_on();
    }
  }
}

void buzzer_on(){
 
  digitalWrite(17, HIGH);
  delay(100);
  digitalWrite(17, LOW);
  delay(100);   
}

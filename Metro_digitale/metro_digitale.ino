#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

#define TFT_CS        10
#define TFT_RST        9 
#define TFT_DC         8

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define ECHO_PIN 3
#define TRIG_PIN 4

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

float distanceCm;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  tft.initR(INITR_BLACKTAB);
  tft.setRotation(1);
  tft.fillScreen(ST77XX_BLACK);
 
  Serial.begin(9600);
}

void loop() {

digitalWrite(TRIG_PIN, LOW); 
  delayMicroseconds(2); 
  digitalWrite(TRIG_PIN, HIGH); 
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  unsigned long impulso = pulseIn(ECHO_PIN,HIGH); 
  distanceCm = impulso / 2.0 * 0.0343;

  float distanceinch = distanceCm*0.393701;


          
  Serial.print("Distanza in cm: ");
  Serial.println(distanceCm);   
  Serial.print("Distanza in pillici: ");
  Serial.println(distanceinch);    

  if (distanceCm <400){
  tft.setCursor(40,5);
  tft.setTextColor(CYAN);
  tft.setTextSize(1);
  tft.println("Centimetri");
  tft.setCursor(10,30);
  tft.setTextColor(WHITE, BLACK);
  tft.setTextSize(4);
  tft.print(distanceCm);
  tft.print("  ");

  tft.setCursor(40,73);
  tft.setTextColor(YELLOW);
  tft.setTextSize(1);
  tft.println("Inch");
  tft.setCursor(10,97);
  tft.setTextColor(WHITE, BLACK);
  tft.setTextSize(4);
  tft.print(distanceinch);
  tft.print("  ");
    
  }
  else {

  tft.fillScreen(ST77XX_BLACK);
    
  tft.setCursor(10,50);
  tft.setTextColor(RED);
  tft.setTextSize(5);
  tft.println("Error");
  
  delay (1000);

  tft.fillScreen(ST77XX_BLACK);
    }
  
  delay(100);
}

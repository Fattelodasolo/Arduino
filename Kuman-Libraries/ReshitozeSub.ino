#include <Adafruit_GFX.h>    
#include <Adafruit_TFTLCD.h>
#define LCD_CS A3
#define LCD_CD A2 
#define LCD_WR A1 
#define LCD_RD A0 

#define LCD_RESET A4

#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;

void setup(void) {
  Serial.begin(9600);
  Serial.println(F("TFT LCD test"));

  tft.reset();

  uint16_t identifier = tft.readID();
  if(identifier == 0x9325) {
    Serial.println(F("Found ILI9325 LCD driver"));
  } else if(identifier == 0x9328) {
    Serial.println(F("Found ILI9328 LCD driver"));
  } else if(identifier == 0x4535) {
    Serial.println(F("Found LGDP4535 LCD driver"));
  }else if(identifier == 0x7575) {
    Serial.println(F("Found HX8347G LCD driver"));
  } else if(identifier == 0x9341) {
    Serial.println(F("Found ILI9341 LCD driver"));
  }else if(identifier == 0x7783) {
    Serial.println(F("Found ST7781 LCD driver"));
  }else if(identifier == 0x8230) {
    Serial.println(F("Found UC8230 LCD driver"));  
  }
  else if(identifier == 0x8357) {
    Serial.println(F("Found HX8357D LCD driver"));
  } else if(identifier==0x0101)
  {     
      identifier=0x9341;
       Serial.println(F("Found 0x9341 LCD driver"));
  }else if(identifier==0x9481)
  {     
       Serial.println(F("Found 0x9481 LCD driver"));
  }
  else if(identifier==0x9486)
  {     
       Serial.println(F("Found 0x9486 LCD driver"));
  }
  else {
    Serial.print(F("Unknown LCD driver chip: "));
    Serial.println(identifier, HEX);
    Serial.println(F("If using the Adafruit 2.8\" TFT Arduino shield, the line:"));
    Serial.println(F("  #define USE_ADAFRUIT_SHIELD_PINOUT"));
    Serial.println(F("should appear in the library header (Adafruit_TFT.h)."));
    Serial.println(F("If using the breakout board, it should NOT be #defined!"));
    Serial.println(F("Also if using the breakout, double-check that all wiring"));
    Serial.println(F("matches the tutorial."));
    identifier=0x9486;
    
  }
  
  tft.begin(identifier);
  tft.setRotation(1);
  tft.fillScreen(BLACK);
  tft.setCursor(30, 40);
  tft.setTextColor(RED);
  tft.setTextSize(8);
  tft.println("RESHITOZE");
   
   Serial.print("TFT size is "); 
   Serial.print(tft.width()); 
   Serial.print("x"); 
   Serial.println(tft.height());

}

void loop(void) {
  unsigned long start = micros();
  tft.fillRect(80,200, 320, 70, RED);
  tft.setCursor(80,210);
  tft.setTextColor(WHITE);
  tft.setTextSize(6);
  tft.println("ISCRIVITI");
  delay(1000);
  
  tft.fillRect(80,200, 320, 70, RED);
  tft.setCursor(80,210);
  tft.setTextColor(RED);
  tft.setTextSize(6);
  tft.println("ISCRIVITI");
  delay(1000);
}

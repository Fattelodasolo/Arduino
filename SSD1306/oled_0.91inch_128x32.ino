#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0); 

 void setup(void) {
   u8g2.begin();
}

  void loop(void) {
   u8g2.clearBuffer();
   u8g2.setFont(u8g2_font_logisoso28_tr);
   u8g2.drawStr(0,29,"Iscriviti");
   u8g2.sendBuffer();
   delay(3000);

   u8g2.clearBuffer();
   u8g2.setFont(u8g2_font_logisoso28_tr);
   u8g2.drawStr(30,29,"al");
   u8g2.sendBuffer();
   delay(800);

   u8g2.clearBuffer();
   u8g2.setFont(u8g2_font_logisoso28_tr);
   u8g2.drawStr(10,29,"canale");
   u8g2.sendBuffer();
   delay(800);

   u8g2.clearBuffer();
   u8g2.setFont(u8g2_font_logisoso24_tr);
   u8g2.drawStr(0,29,"Reshitoze");
   u8g2.sendBuffer();
   delay(2000);

   
}

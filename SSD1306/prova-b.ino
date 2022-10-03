#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>


U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0); 
  
void setup() {
  u8g2.begin();

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_logisoso16_tr);
  u8g2.drawStr(0,15,"Avvio");
  u8g2.sendBuffer();

  delay(1000);

  u8g2.setFont(u8g2_font_logisoso20_tr);
  u8g2.drawStr(0,40,"Tutto OK");
  u8g2.sendBuffer();

}

void loop() {
 
}

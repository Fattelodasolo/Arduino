#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET 18
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  display.display();
  display.clearDisplay();
}

void loop() {
int sensor = analogRead(A1);

 float t = sensor * 0.48875;
 
  Serial.print("Temp = ");
  Serial.print(t);
  Serial.println("°C");

  
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("LM35");

  display.setTextSize(3);
  display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
  display.setCursor(0, 25);
  display.print(t);
  display.println(" C");

  display.display();

  delay(1000);
  
  

}

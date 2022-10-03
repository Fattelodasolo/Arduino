#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

int analog_value;
float halleffect;

void setup() {

Serial.begin(9600);
  lcd.begin(16,2);

}

void loop() {
 analog_value = analogRead (A0);
 halleffect = analog_value * (5.0 / 1023);

Serial.print(analog_value);
Serial.print("\t");
Serial.println(halleffect);


  lcd.setCursor(0, 0);
  lcd.print("Effetto Hall: ");
  
  lcd.setCursor(0,1);
  lcd.print("V: ");
  lcd.print(halleffect);
  lcd.print("  ");

  delay (500);

}

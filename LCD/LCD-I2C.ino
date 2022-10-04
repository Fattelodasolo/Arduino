// Sensore DHT11
#include "DHT.h"
#define DHTPIN 12       // Definisco il PIN digitale a cui è collegato il sensore
#define DHTTYPE DHT11   // Specifico che uso il DHT11

DHT dht(DHTPIN, DHTTYPE);

//I2C LCD:
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Display LCD I2C
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); // porta del display YwRobot Arduino LCM1602 IIC V1

// Se non funziona prova una di queste levando i commenti
//LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); // porta del display LCM1602 IIC A0 A1 A2 v3
//LiquidCrystal_I2C lcd(0x20, 4, 5, 6, 0, 1, 2, 3, 7, NEGATIVE); // porta del display Arduino-IIC-LCD GY-LCD-V1
//LiquidCrystal_I2C lcd(0x20, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); // porta del display LCM1602 IIC A0 A1 A2 v2

void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);
  Serial.println("Avvio sistema");

  dht.begin();

}

void loop() {
  
  int h = dht.readHumidity();     // Legge temperatura
  int t = dht.readTemperature();  // Legge umidità

// imposta il cursore partendo da (0,0)
  lcd.setCursor(0, 0);
  lcd.print("Temperatura: ");
  lcd.print(t);
  lcd.print("C");

// imposta il cursore partendo da (16,1)
  lcd.setCursor(0,1);
  lcd.print("Umidita': ");
  lcd.print(h);
  lcd.print("%");
  delay (5000); // attendo 5 secondi
  lcd.clear();          // Pulisce display LCD

// Imposta il cursore per far apparire una scritta personalizzata
  lcd.setCursor(0, 0);
  lcd.print("RESHITOZE");
  lcd.setCursor(0,1);
  lcd.print("YOUTUBE");
  delay (5000);         // attendo 5 secondi
  lcd.clear();          // Pulisce display LCD

// Stampa al monitor seriale i valori    
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.print("C, Umidità: ");
  Serial.print(h);
  Serial.println("%");

  

}


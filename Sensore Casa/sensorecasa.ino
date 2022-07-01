/* 
Programma realizzato da Letterio Bavastrelli e rilasciato con GNU GPL V.3
Copyright (C) 2017  Letterio Bavastrelli

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/gpl-3.0.html>.

Contact me: reshitoze@gmail.com

Visit my YT Channel: https://www.youtube.com/Reshitoze
*/

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

// definisco i BIT per far apparire il cuore
byte Cuore[8] = {
        B00000,
        B01010,
        B11111,
        B11111,
        B11111,
        B01110,
        B00100,
        B00000
};

void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.createChar(0, Cuore); 
  Serial.println("Inizializzazione sensore DHT11 con DISPLAY LCD per appartamento");

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
  lcd.clear();  // Pulisce display LCD


// Imposta il cursore per far apparire una scritta personalizzata
  lcd.setCursor(0, 0);
  lcd.print("  Sensore casa");
  lcd.setCursor(0,1);
  lcd.write(byte(0));   // cuore
  lcd.write(byte(0));   // cuore
  lcd.print(" Annamaria ");
  lcd.write(byte(0));   // cuore
  lcd.write(byte(0));   // cuore
  delay (5000);         // attendo 5 secondi
  lcd.clear();          // Pulisce display LCD
  
// Stampa al monitor seriale i valori    
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.print("C, Umidità: ");
  Serial.print(h);
  Serial.println("%");

  

}


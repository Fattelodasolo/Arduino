//   Programma realizzato da Letterio Bavastrelli e rilasciato con GNU GPL V.3
//   Serra autonoma con sensore di temperatura e umidità (DHT11), igrometro, fotoresistore, display LCD 20x4, sensore livello acqua e relè.
//   Copyright (C) 2017  Letterio Bavastrelli

//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.

//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.

//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <https://www.gnu.org/licenses/gpl-3.0.html>.

// Contact me: letteriobavastrelli@gmail.com

// Visit my YT Channel: https://www.youtube.com/Reshitoze

const int valore_limite = 990; //Valore dell'igrometro al quale il relay sarà ON

//DHT11 Sensor:
#include "DHT.h"
#define DHTPIN 12     // Sensore collegato al PIN 12
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);


//I2C LCD:
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD I2C address
LiquidCrystal_I2C lcd(0x63, 20, 4);

void setup()
{
// PIN 9 al Relè - IN1
Serial.begin(9600);
  pinMode(9, OUTPUT);

// PIN 10 al relè - IN2
  pinMode(10, OUTPUT);

// PIN 11 al relè - IN3
  pinMode(11, OUTPUT);

//PIN 13 al LED
  pinMode (13, OUTPUT);

//I2C LCD
Serial.begin(9600);
  lcd.init();
  lcd.backlight(); 
  Serial.println("Serra Autonoma di Reshitoze");
  
// Avvio sensore DHT11  
  dht.begin();
}


void loop()
{

// Fotoresistore
int Lumen = analogRead (A0); // Lumen come intero della lettura del pin A0
Serial.print("Sensore crepuscolare: ");
Serial.println(Lumen, DEC); // Stampa un valore decimale del fotoresistore
  
if (Lumen > 750)
  digitalWrite (11, HIGH); // Se il valore di Lumen è superiore a 750 attiva relè
else
  digitalWrite (11, LOW); // altrimenti spegne relè


//Livello Acqua
int water = analogRead(A1);
Serial.print ("Sensore acqua: ");
Serial.println(water, DEC);  // Stampa il valore decimale del sensore di livello acqua
  
  if (water >= 100) {
    
    lcd.setCursor(0,3);  // Indica posizione del cursore su LCD
    lcd.print("Acqua: OK"); // Stampa su LCD il testo
    lcd.print("");
    lcd.print("");
  }
  else    
    {
    lcd.setCursor(0,3);  // Indica posizione del cursore su LCD
    lcd.print("Acqua: BASSA"); // Stampa su LCD il testo
    alarm();
    flash();
    }

// Igrometro
int igro = analogRead(A3); // Legge il valore analogico
int umdtrr = 0; // Variabile umidità suolo
umdtrr = map (igro, 100, 990, 100, 0); // converto il valore analogico in percentuale
Serial.print("Umidità del terreno: ");
Serial.print(umdtrr);
Serial.println ("%"); //Stampa a schermo il valore

if (igro <= valore_limite)
  digitalWrite(9,LOW); // Attiva Relè 1
else
  digitalWrite(9,HIGH); // Spegni Relè 1


// Lettura umidità e temperatura del sensore DHT11
int h = dht.readHumidity();
int t = dht.readTemperature();

// Misura la temperatura e se maggiore di 40 gradi attiva relè per accendere la ventola
if (t >= 40 )
   digitalWrite (10, HIGH); // Attiva Relè 2
else
   digitalWrite (10, LOW); // Spegni Relè 2

  Serial.print("Temp: ");
  Serial.print(t);
  Serial.print("C, Umid: ");
  Serial.print(h);
  Serial.println("%");


// impostare cursore sulla prima riga:
lcd.setCursor(0, 0);
lcd.print("Temperatura: ");
lcd.print(t);
lcd.print("C");
  
// imposta cursore sulla seconda riga:
lcd.setCursor(0,1);
lcd.print("Umidita': ");
lcd.print(h);
lcd.print("%");

// imposta il cursore sulla terza riga:
lcd.setCursor(0,2);
lcd.print("Umidita' terra: ");
lcd.print(umdtrr);
lcd.print("%");

delay(2000);

}

void alarm(){
  tone(3,850,700);  // Imposta tono acustico su PIN 3
  delay(150);       // Aspetta per 0,15 secondi
  tone(3,850,700);  // Imposta tono acustico su PIN 3
  delay(150);       // Aspetta per 0,15 secondi
}

void flash() {
  digitalWrite(13, HIGH);   // Imposta il LED su ON
  delay(1000);               // Aspetta per 1 secondo
  digitalWrite(13, LOW);    // Impostiamo il LED su OFF
  delay(1000);               // Aspetta per 1 secondo
}

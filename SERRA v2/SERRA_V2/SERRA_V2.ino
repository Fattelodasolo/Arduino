/*Programma realizzato da Letterio Bavastrelli e rilasciato con GNU GPL V.3
Serra autonoma con sensore di temperatura e umidità (DHT11), igrometro, fotoresistore, display NEXTION TFT da 3,5", sensore livello acqua e relè.
Copyright (C) 2020  Letterio Bavastrelli

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

Visit my YT Channel: https://www.youtube.com/Reshitoze
Visit my WebSite: https://www.fattelodasolo.it
*/

#include "Nextion.h"
#include "DHT.h"
#define DHTPIN 12     // Sensore collegato al PIN 12
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

NexSlider slider00 = NexSlider (1, 3, "flame");
NexSlider slider01 = NexSlider (1, 4, "water");
NexSlider slider02 = NexSlider (1, 5, "light");

NexNumber flame_slider = NexNumber (1, 9, "temp01");
NexNumber water_slider = NexNumber (1, 10, "umid01");
NexNumber light_slider = NexNumber (1, 11, "luce");

NexDSButton button00 = NexDSButton(2, 6, "fan");
NexDSButton button01 = NexDSButton(2, 7, "lamp");

NexTouch *nex_listen_list[] = {
  &button00,
  &button01,
  &slider00,
  &slider01,
  &slider02,
  NULL
  };

char buffer[100] = {0};

int t, h, Lumen, lumin, water, igro, umdtrr, caldo_limite, igro_limite, luce_limite;
long caldo, acqua, luce;
String data = ""; 


void setup()
{
Serial.begin(9600);

dht.begin();

nexInit();

  button00.attachPop(fan, &button00);
  button01.attachPop(lamp, &button01);
  slider00.attachPop(SliderCaldo, &slider00);
  slider01.attachPop(SliderAcqua, &slider01);
  slider02.attachPop(SliderLuce, &slider02);
  

  pinMode(3, OUTPUT); // PIN 3 al BUZZER
  pinMode(9, OUTPUT); // PIN 9 al Relè - IN1
  pinMode(10, OUTPUT);// PIN 10 al relè - IN2
  pinMode(11, OUTPUT);// PIN 11 al relè - IN3
  pinMode (13, OUTPUT);//PIN 13 al LED

}


void loop(){
  Dati();
  nexLoop(nex_listen_list);  
  
    Serial.print("temp.val=");
    Serial.print(t);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
    
    Serial.print("umid.val=");
    Serial.print(h);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);

    Serial.print("suolo.val=");
    Serial.print(umdtrr);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);

    
    if (water >= 100) {
    
      data = "acqua.txt=\"" + String("OK") + "\"";
    
        Serial.print(data);
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
    }
    else    
    {
      alarm();
      flash();
      data = "acqua.txt=\"" + String("Basso") + "\"";
    
        Serial.print(data);
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
    }
    
  delay (100);
}

void Dati(){

// Fotoresistore
Lumen = analogRead (A0);
  lumin = map ( Lumen, 1023, 0, 0, 100);

water = analogRead(A1);

// Igrometro
igro = analogRead(A3); // Legge il valore analogico
  umdtrr = map (igro, 1023, 0, 0, 100);
  
// Lettura umidità e temperatura del sensore DHT11
h = dht.readHumidity();
t = dht.readTemperature();

}

void SliderCaldo(void *ptr){
  long caldo = 0;
  slider00.getValue(&caldo);
  flame_slider.setValue(caldo);

  caldo_limite = (int)caldo;

   if (t >= 30 || t >= caldo_limite ){
    digitalWrite (10, HIGH); // Attiva Relè 2
  }
  else{
   digitalWrite (10, LOW); // Spegni Relè 2
   }
  
}

void SliderAcqua(void *ptr){

  slider01.getValue(&acqua);
  water_slider.setValue(acqua);

  igro_limite = (int)acqua;

  if (umdtrr <= 15 || umdtrr <= igro_limite) {
    digitalWrite(9, LOW); // Attiva Relè 1
  }
  else {
    digitalWrite(9, HIGH); // Spegni Relè 1
  }
  
}

void SliderLuce(void *ptr){

  slider02.getValue(&luce);
  light_slider.setValue(luce);

  luce_limite = (int)luce;

  if (lumin <= 40 || lumin <= luce_limite){
    digitalWrite (11, LOW);
  }
  else {
    digitalWrite (11, HIGH);
  }
  
}

void fan(void *ptr)
{
    uint32_t dual_state;
    NexDSButton *btn = (NexDSButton *)ptr;
    dbSerialPrint("ptr=");
    dbSerialPrint((uint32_t)ptr); 
    memset(buffer, 0, sizeof(buffer));

    
    button00.getValue(&dual_state);
    if(dual_state){
        digitalWrite(10, HIGH);
    }
    else {
       digitalWrite(10, LOW);
    }
}

void lamp(void *ptr)
{
    uint32_t dual_state;
    NexDSButton *btn = (NexDSButton *)ptr;

    dbSerialPrint("ptr=");
    dbSerialPrint((uint32_t)ptr); 
    memset(buffer, 0, sizeof(buffer));

    
    button01.getValue(&dual_state);
    if(dual_state){
        digitalWrite(11, HIGH);
    }
    else {
       digitalWrite(11, LOW);
    }
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

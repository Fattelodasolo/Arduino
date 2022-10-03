#include "DHT.h"           // libreria DHT11
#define DHTPIN 12          // sensore collegato al pin 12
#define DHTTYPE DHT11      // tipo sensore 
DHT dht(DHTPIN, DHTTYPE);  // creo oggetto dht

int t, h;           // variabili intere per umidità e temperatura
void setup() {

Serial.begin(9600);
Serial.println ("Stazione meteo con Nextion");
dht.begin();             // avvio sensore

}

void loop() {

t = dht.readTemperature();           // rilevo temperatura
h = dht.readHumidity();              // rilevo umidità

// invio tramite seriale i valori interi al display
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
 
 delay (500);

}

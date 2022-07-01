#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11 

DHT dht(DHTPIN, DHTTYPE);

String terminal;

void setup() {
  Serial.begin(9600);
  
  dht.begin();
}

void loop() {
  int h = dht.readHumidity();
  int t = dht.readTemperature();

  
  terminal = "Meteo: " + String (t) + "°C " + String (h) + "%" ; 
  
  Serial.println (terminal);

  delay(2000);

}

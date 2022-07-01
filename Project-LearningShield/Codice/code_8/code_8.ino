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

  int sensor1 = analogRead(A0);
  int luce = map (sensor1, 0, 1023, 100, 0);

  int sensor2 = analogRead(A1);
  float t1 = sensor2 * 0.48875;
  
  int h = dht.readHumidity();
  int t2 = dht.readTemperature();

  float tmed = (t1 + t2) / 2;

  
  terminal = "Meteo: "; 
  terminal += "Temperatura " + String (tmed) + "°C ";
  terminal += "Umidità " + String (h) + "% ";
  terminal += "Luce " + String (luce) + "%";
  
  Serial.println (terminal);

  delay(2000);

}

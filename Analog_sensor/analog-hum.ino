#include "DHT.h"
#define DHTPIN 12
#define DHTTYPE DHT11
#define PIN_OUT 3

DHT dht(DHTPIN, DHTTYPE);


int h, v;

void setup() {
  pinMode (PIN_OUT, OUTPUT);
  dht.begin();
  Serial.begin(9600);

}

void loop() {
  
h = dht.readHumidity();
v = map (h, 0, 100, 0, 255);
analogWrite (PIN_OUT, v);

    Serial.print ("Valore Umidità: ");
    Serial.println(h);

    Serial.print ("Valore PWM: ");
    Serial.println(v);
  
  delay(100);
}

#include <BME280I2C.h>
#include <Wire.h>

BME280I2C bme;

void setup() {
  
Serial.begin(9600);
Wire.begin();
bme.begin();
}

void loop() {

float temp, hum, pres;

bme.read(pres, temp, hum);


Serial.print("Temperatura: ");
Serial.print(temp);
Serial.println ("°C");

Serial.print("Umidità: ");
Serial.print (hum);
Serial.println(" %");

Serial.print("Pressione: ");
Serial.print (pres);
Serial.println (" Pa");

Serial.println (" ");

delay (3000);

}

#include <BME280I2C.h>
#include <Wire.h>
#include "Adafruit_CCS811.h"
#include <EEPROM.h>

Adafruit_CCS811 ccs;
BME280I2C bme;

int co2, tvoc, tmax, umax, pmax, p;
int tmin = 50;
int umin = 101;
int pmin = 1100;
float temp, hum, pres;
String data = "";

void setup() {
  Serial.begin(9600);
 
  Wire.begin();
  bme.begin();
  ccs.begin();
  while(!ccs.available()){
    Serial.print(".");
    delay (1000);
  }

}

void loop() {
  
  ccs.readData();
  bme.read(pres, temp, hum);
  
  co2 = ccs.geteCO2();
  tvoc = ccs.getTVOC();

  p = pres/100;               //Converto i Pascal in milliBar e trasfoprmo i float in interi
  
//Memorizzo minimo e massimo di temperatura
  if (temp > tmax) {
  tmax = temp;
  EEPROM.write(0, temp);
  }

  if (temp < tmin) {
  tmin = temp;
  EEPROM.write(1, temp);
  }

//Memorizzo minimo e massimo di umidità
  if (hum > umax) {
  umax = hum;
  EEPROM.write(2, hum);
  }

  if (hum < umin) {
  umin = hum;
  EEPROM.write(3, umin);
  }

//Memorizzo minimo e massimo di pressione
if (p > pmax) {
  pmax = p;
  EEPROM.write(4, p);
  }

  if (p < pmin) {
  pmin = p;
  EEPROM.write(5, p);
  }


// Invio i dati alla Page 0 del Nextion  
  data = "temp.txt=\"" + String(temp) + "\"";
    Serial.print(data);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);

  data = "umid.txt=\"" + String(hum) + "\"";
    Serial.print(data);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);

  data = "pres.txt=\"" + String(pres/100.00) + "\"";
    Serial.print(data);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);

  data = "co2.txt=\"" + String(co2) + "\"";
    Serial.print(data);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);

  data = "tvoc.txt=\"" + String(tvoc) + "\"";
    Serial.print(data);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);

// Invio i dati alla Page 1 del Nextion
  data = "temp2.txt=\"" + String(tmax) + "\"";
    Serial.print(data);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);

  data = "temp1.txt=\"" + String(tmin) + "\"";
    Serial.print(data);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
    
// Invio i dati alla Page 2 del Nextion
  data = "umi1.txt=\"" + String(umin) + "\"";
    Serial.print(data);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);

  data = "umi2.txt=\"" + String(umax) + "\"";
    Serial.print(data);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);

// Invio i dati alla Page 3 del Nextion
  data = "p1.txt=\"" + String(pmin) + "\"";
    Serial.print(data);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);

  data = "p2.txt=\"" + String(pmax) + "\"";
    Serial.print(data);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
    
  delay(500);
}

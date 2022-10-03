#include "Adafruit_CCS811.h"

Adafruit_CCS811 ccs;

void setup() {
  Serial.begin(9600);
  Serial.println("Avvio CCS811");

  ccs.begin();
  while(!ccs.available()){
    Serial.print(".");
    delay (1000);
  }

  Serial.println("CCS811 Pronto!");

}

void loop() {
  
  ccs.readData();

  int co2 = ccs.geteCO2();
  int tvoc = ccs.getTVOC();
  
      Serial.print("CO2: ");
      Serial.print(co2);
      Serial.print(" ppm \tTVOC: ");
      Serial.print(tvoc);
      Serial.println(" ppb");
  delay(500);
}

#include <OneWire.h>                      // Libreria OneWire
#include <DallasTemperature.h>            // Libreria Sensore
#define ONE_WIRE_BUS 2                    // Sensore collegato al pin 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

float t;                                  // variabile per la temperatura
String data = "";                         // stringa vuota

void setup() {

Serial.begin(9600);
Serial.println ("Stazione meteo con Nextion");
sensors.begin();                         // avvio sensore

}

void loop() {

sensors.requestTemperatures();           // richiesta al sensore
t = sensors.getTempCByIndex(0);          // rilevo temperatura

// trasformo la temperatura in string e la trasmetto al display tramite seriale alla casella temp.txt
  data = "temp.txt=\"" + String(t) + "\"";
    Serial.print(data);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);

 
 delay (500);

}

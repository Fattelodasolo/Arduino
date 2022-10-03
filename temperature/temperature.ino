#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include "DHT.h"
#include "BMP280.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SHT3x.h>
#include "Adafruit_MCP9808.h"

#define DHTPIN 5
#define DHTTYPE DHT22
#define ONE_WIRE_BUS 4

DHT dht22(DHTPIN, DHTTYPE);

BMP280 bmp;
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
SHT3x Sensor;
Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();
 
const int CS_PIN = 10; 
String dataString ="";
File SDData;

float t22, t_dallas, sht_t, c;
double Temp, Pres;

int tempo = 9e5;

void setup() {
  pinMode(CS_PIN, OUTPUT);
  Serial.begin(9600);
  Wire.begin();
  bmp.begin();
  sensors.begin();
  Sensor.Begin();
  tempsensor.begin(0x18);
  tempsensor.setResolution(3);

  bmp.setOversampling(4);

if (!SD.begin(CS_PIN)) {
Serial.println("SD CARD non presente");
while (1);
}
Serial.println("SD Card inizializzata");
}

void loop() {
  
  Sensor.UpdateData();
  tempsensor.wake();
  char result = bmp.startMeasurment();
 

  bmp.getTemperatureAndPressure(Temp,Pres);

  sensors.requestTemperatures();

  t_dallas = sensors.getTempCByIndex(0);

  t22 = dht22.readTemperature();


  sht_t = Sensor.GetTemperature();

  c = tempsensor.readTempC();


  Serial.print("DHT22: ");
  Serial.print(t22);
  Serial.print("\tBMP280: ");
  Serial.print(Temp);
  Serial.print("\tDallas: ");
  Serial.print(t_dallas);
  Serial.print("\tSHT31: ");
  Serial.print(sht_t);
  Serial.print("\tMPC9808: ");
  Serial.println(c);

  MemoryCard();

  delay(tempo);

 }


void MemoryCard(){
dataString = String(t22) + ";" + String(Temp) + ";" + String(t_dallas) + ";" + String(sht_t) + ";" + String(c);                                                           
SDData = SD.open("dati.csv", FILE_WRITE); 
if (SDData){
SDData.println(dataString);
SDData.close();
}
else{
Serial.println("Errore di scrittura sul file!");
}


 }

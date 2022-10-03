#include <SHT3x.h>
SHT3x Sensor;
void setup() {
  
  Serial.begin(9600);
  Sensor.Begin();
}

void loop() {
  Sensor.UpdateData();
  
  Serial.print(Sensor.GetTemperature()); //Celsius
  Serial.print("C");
  Serial.print(" | ");
  
  Serial.print(Sensor.GetRelHumidity());
  Serial.print("%");
  Serial.print(" | ");

  Serial.print(Sensor.GetAbsHumidity()); //Torr
  Serial.print(" Torr");
  Serial.print(" | ");

  Serial.print(Sensor.GetAbsHumidity(SHT3x::psi)); //Libbre per pollice quadro
  Serial.print(" psi");
  Serial.print(" | ");

  Serial.print(Sensor.GetAbsHumidity(SHT3x::Pa)); //Pascal
  Serial.print(" Pa");

   Serial.print(" Tolleranza: ±");
  Serial.print(Sensor.GetAbsHumTolerance(SHT3x::mH2O));
  Serial.print(" mH2O");
  

  Serial.println();
  delay(500);
}

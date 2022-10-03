#include <SHT3x.h>
SHT3x Sensor;
void setup() {
  
  Serial.begin(9600);
  Sensor.Begin();
}

void loop() {
  Sensor.UpdateData();
  
  Serial.print(Sensor.GetTemperature()); //Celsius di default
  Serial.print("C");
  Serial.print(" | ");
  
  Serial.print(Sensor.GetTemperature(SHT3x::Cel)); //Celsius
  Serial.print("C");
  Serial.print(" | ");

  Serial.print(Sensor.GetTemperature(SHT3x::Far)); //Fahrenheit
  Serial.print("F");
  Serial.print(" | ");

  Serial.print(Sensor.GetTemperature(SHT3x::Kel)); //Kelvin
  Serial.print("K");
  

  Serial.println();
  delay(500);
}

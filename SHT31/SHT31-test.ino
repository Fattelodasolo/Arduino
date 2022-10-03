#include <SHT3x.h>
SHT3x Sensor;
void setup() {
  
  Serial.begin(9600);
  Sensor.Begin();
}

void loop() {

  Sensor.UpdateData();
  Serial.print("Temperatura: ");
  Serial.print(Sensor.GetTemperature());
  Serial.println("C");
  Serial.print("Umidità: ");
  Serial.print(Sensor.GetRelHumidity());
  Serial.println("%");

  delay(500);
}

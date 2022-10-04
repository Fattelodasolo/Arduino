#include "BMP280.h"
#include "Wire.h"
BMP280 bmp;
void setup()
{
  Serial.begin(9600);
  if(!bmp.begin()){
    Serial.println("BMP non funziona!!!!!");
    while(1);
  }
  else Serial.println("BMP avviato");
  
  bmp.setOversampling(4);
  
}
void loop()
{
  double T,P;
  char result = bmp.startMeasurment();
 
  if(result!=0){
    delay(result);
    result = bmp.getTemperatureAndPressure(T,P);
    
        Serial.print("T = \t");Serial.print(T,2); Serial.print(" degC\t");
        Serial.print("P = \t");Serial.print(P,2); Serial.println(" mBar");
       
      }
 
 
  else {
    Serial.println("Error.");
  }
  
  delay(3000);
}

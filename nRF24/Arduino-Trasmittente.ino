#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 myRF24 (7, 8);
byte address[6] = "00001";

void setup(){
  
  Serial.begin(9600);
  
  myRF24.begin();
  myRF24.openWritingPipe(address);
  myRF24.setPALevel(RF24_PA_MIN);
  myRF24.stopListening();
  }

void loop(){
  char  text[5] = "Prova";
  
  myRF24.write(&text, sizeof(text)); 

  Serial.println(text);
  delay(1000);

}

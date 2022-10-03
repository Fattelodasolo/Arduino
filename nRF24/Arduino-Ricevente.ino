#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 myRF24 (7, 8);
byte address[6] = "00001"; 
 
void setup(){
  
  Serial.begin(9600);
  delay(1000);

  myRF24.begin();
  myRF24.openReadingPipe(0, address);
  myRF24.setPALevel(RF24_PA_MIN);
  myRF24.startListening();
}


void loop(){
  
  if ( myRF24.available()) {
    char  text[5] = "";
    myRF24.read( &text, sizeof(text));
    Serial.println(text);
    }
     
  }

#include <UTFT.h>                         // Libreria UTFT Display TFT ILI9486
#include <Wire.h>
#include <ADXL345.h>                      // Libreria accelerometro ADXL345
#include <SD.h>                           // Libreria SD Card
#include <SPI.h>

ADXL345 accel(ADXL345_ALT);               // Indirizzo Alternativo con SD0 in LOW

extern uint8_t SmallFont[];
UTFT myGLCD(CTE40,38,39,40,41);           // Identifica il tipo di display TFT

const int CS_PIN = 53;                    // Pin CS di Arduino Mega
float x,y,z;

String dataString ="";                    // Variabile stringa per caricare i dati
File SDData;

void setup()
{
  pinMode(CS_PIN, OUTPUT);
  Serial.begin(9600);
  Wire.begin();

  byte deviceID = accel.readDeviceID();
  if (deviceID != 0) {
    Serial.print("0x");
    Serial.print(deviceID, HEX);
    Serial.println("");
  } else {
    Serial.println("read device id: failed");
    while(1) {
      delay(100);
    }
    }

    if (!accel.writeRate(ADXL345_RATE_200HZ)) {
    Serial.println("write rate: failed");
    while(1) {
      delay(100);
    }
  }


  if (!accel.writeRange(ADXL345_RANGE_16G)) {
    Serial.println("write range: failed");
    while(1) {
      delay(100);
    }
  }

  if (!accel.start()) {
    Serial.println("start: failed");
    while(1) {
      delay(100);
    }
  }
  myGLCD.InitLCD();
  myGLCD.setFont(SmallFont);

  myGLCD.clrScr();
  
if (!SD.begin(CS_PIN)) {
Serial.println("SD CARD non presente");
while (1);
}
Serial.println("SD Card inizializzata");
}


void loop() {
  myGLCD.setColor(255,255,0);               // Imposto colore del testo
  myGLCD.print("Asse X", 5, 15);            // Scrivo i titoli
  myGLCD.print("Asse Y", 5, 125);
  myGLCD.print("Asse Z", 5, 245);

  assi_xyz();
  myGLCD.clrScr();                          // Pulisco il display
  }


void assi_xyz(){
for (int i=1; i<480; i++){                  // In un grafico lineare "i" è la varibile del tempo che scorre
  accel.update();                           // il codice stampa un valore "x" rilevato nell'istante in cui "i" ha un valore
  x= accel.getX();
    Serial.print ("X: ");
    Serial.println(accel.getX());
  if (x==0 || x > 0.01 && x < 0.09){
    x = 1;
  myGLCD.setColor(0, 0, 255);
  myGLCD.setBackColor(0, 0, 0);
  myGLCD.drawLine(i,x*10+50, i, 50);        // disegna la linea di x. Moltiplichiamo per 10 solo per rendere più visibile il risultato
    }
  else{
  myGLCD.setColor(0, 0, 255);
  myGLCD.setBackColor(0, 0, 0);
  myGLCD.drawLine(i,x*10+50, i, 50);
  }
  

  y= accel.getY();
    Serial.print ("Y: ");
    Serial.println(accel.getY());
      if (y==0 || y > 0.01 && y < 0.09){
    y = 1;
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(0, 0, 0);
  myGLCD.drawLine(i,y*10+160, i, 160);
    }
  else{
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(0, 0, 0);
  myGLCD.drawLine(i,y*10+160, i, 160);
  }


z= accel.getZ();
    Serial.print ("Z: ");
    Serial.println(accel.getZ());
   if (z==0 || z > 0.01 && z < 0.09){
    z = 1;
  myGLCD.setColor(255, 0, 0);
  myGLCD.setBackColor(0, 0, 0);
  myGLCD.drawLine(i,z*10+280, i, 280);
    }
  else{
  myGLCD.setColor(255, 0, 0);
  myGLCD.setBackColor(0, 0, 0);
  myGLCD.drawLine(i,z*10+280, i, 280);
  }

  MemoryCard();
  
  delay (25); 
}

}


void MemoryCard(){
dataString = String(x) + ";" + String(y) + ";" + String(z); // Crea una stringa contenente i valori X,Y e Z.
                                                            // con ; crea nuove colonne nel file CSV
SDData = SD.open("dati.csv", FILE_WRITE);                   // Crea il file CSV
if (SDData){
SDData.println(dataString);                                 // Scrive le stringhe nel file
SDData.close();                                             // Chiude il file
}
else{
Serial.println("Errore di scrittura sul file!");
}  
  }

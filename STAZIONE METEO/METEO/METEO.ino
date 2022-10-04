/* Programma realizzato da Letterio Bavastrelli e rilasciato con GNU GPL V.3
Stazione Meteo con connessione Ethernet che inoltra i dati su un sito web.
Copyright (C) 2018  Letterio Bavastrelli

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/gpl-3.0.html>.

Visit my YT Channel: https://www.youtube.com/Reshitoze */


#include <SPI.h>
#include <Ethernet.h>

//BMP280 Sensor:
#include <Wire.h>
// #include <SPI.h>                                                   // Ho già incluso, ma se non uso la Shield Ethernet, levo i commenti
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#define BMP_SCK 13
#define BMP_MISO 12
#define BMP_MOSI 11 
#define BMP_CS 10

//DHT22 Sensor:
#include "DHT.h"
#define DHTPIN 9                                                      // Sensore collegato al PIN 9
#define DHTTYPE DHT22                                                 // DHT22
DHT dht(DHTPIN, DHTTYPE);


// Connessione Ethernet
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };                  // MAC della Shied Ethernet
IPAddress ip(192, 168, 1, 251);                                       // Indirizzo IP del dispositivo sulla rete
IPAddress gateway(192,168,1,1);                                       // IP del Gateway
IPAddress subnet (255,255,255,0);                                     // SubNet Mask
char server[] = "www.miosito.it";            // Sito Altervista

EthernetClient client;

Adafruit_BMP280 bmp;                                                  // Sensore BMP280
//Adafruit_BMP280 bmp(BMP_CS);
//Adafruit_BMP280 bmp(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK);

// Dichiaro costanti i PIN del sensore Ultrasuoni
  const int TRIG_PIN = 5;
  const int ECHO_PIN = 6;


// Dichiaro variabili e costanti Anemometro
  const float raggio = 0.06;                                          // Raggio dell'anemometro in metri (dal centro all'estremità della pala)
  int TimePulse = 0;                                                  // Variabile con cui si registrano i millisecondi dal primo impulso
  int Time = 0;                                                       // Tempo trascorso dal primo impulso
  int WindTime = 2000;                                                // Due secondi il tempo da considerare per escludere a priori brevi folate di vento dal conteggio
  int Anemometro_OFF = 0;                                             // Contatto dell'anemometro in OFF
  int Anemometro_ON = 0;                                              // Contatto anemometro in ON
  int Frequenza = 0;                                                  // Variabile della frequenza degli impulso


// Dichiaro variabili sensori
  int p, rain, Lumen, Crepuscolo, LivMono;
  float t, h, TemperaturaMed, LivTemp, LivPioggia, snow, tempo, CmMs, wind, LivNeve, temp;


  unsigned long lastConnectionTime = 0; 
  boolean lastConnected = false;    
  const unsigned long postingInterval = 10L*1000L;                    // La "L" si utilizza per i numeri lunghi


// Stringa con cui convertire le variabili
  String datiWEB = "";


void setup() {

  Serial.begin(9600);                                                       // Initializza la porta seriale
  pinMode(2, INPUT);                                                        // Pin a cui è collegato l'anemometro
  while (!Serial) {
    ;
  }

// Avvia connessione Ethernet:
   Serial.println ("Avvio Ethernet-Shield");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Tentativo di connessione con DHCP fallito");            // Proviamo con l'indirizzo IP Statico
    Ethernet.begin(mac, ip, gateway, subnet);                               // Avvio la shield
  }


// Avvio BMP280
  Serial.println(F("Avvio del sensore BMP280"));

// Avvio sensore DHT22  
  dht.begin();
  Serial.println ("Avvio del sensore DHT22");

// Sensore Ultrasuoni
    pinMode(TRIG_PIN, OUTPUT);                                             // Dichiaro come output il pin trig
    pinMode(ECHO_PIN, INPUT);                                              // Dichiaro come input il pin echo
    Serial.println ("Avvio del sensore HC-SR04");
  
}

void loop() {

    while(client.available())
{
      char c = client.read();
        Serial.print(c);
}
 
    if (!client.connected() && lastConnected)
{
        Serial.println();
        Serial.println("Disconnesso.");
      client.stop();
}

    if(!client.connected() && (millis() - lastConnectionTime > postingInterval)) {
          Sensori();                                                                          // I sensori prelevano i dati e li caricano sul sito
  }
  
          lastConnected = client.connected();


}











void Sensori() {

// Fotoresistore
    Lumen = analogRead (A0);                                   // Lumen come intero della lettura del pin A0
    Crepuscolo =  map (Lumen, 0, 1023, 0, 100);
      Serial.print("Sensore crepuscolare: ");
      Serial.print(Crepuscolo);
      Serial.println("%");                                     // Stampa un valore percentuale del fotoresistore


// Livello Pioggia
   rain = analogRead (A1);
   LivPioggia = map (rain, 970, 0, 0, 100);
      Serial.print ("Sensore Pioggia: ");
      Serial.print (LivPioggia);  
      Serial.println ("%");                                    // Stampa il valore percentuale del sensore di livello pioggia


// Livello di Monossido di Carbonio MQ-7
  int sensor_monossido = analogRead(A2);                      // Rileva la presenza di monossido di carbonio nell'aria
  LivMono = map (sensor_monossido, 0, 1023, 20, 2000);        // effettuo la mappatura per ottenere valori in scala
      Serial.print ("Monossido di Carbonio: ");
      Serial.print (LivMono);  
      Serial.println ("ppm");                                 // Stampa il valore in ppm (parti per milione) del sensore MQ-7


// Lettura umidità e temperatura del sensore DHT22
    h = dht.readHumidity();                                   // Temperatura rilevata dal DHT22
    t = dht.readTemperature();                                // umidità rilevata dal DHT22
      Serial.print("Temp: ");
      Serial.print(t);
      Serial.print("C, Umid: ");
      Serial.print(h);
      Serial.println("%");

//Barometro
   p = bmp.readTemperature();                                 // Temperatura rilevata dal BMP280
      Serial.print(F("Temperatura = "));
      Serial.print(bmp.readTemperature());                    // Stampa il risultato sul monitor
      Serial.println(" C");
    
      Serial.print(F("Pressione = "));                        // Pressione rilevata dal BMP280 in Pascal
      Serial.print(bmp.readPressure());                       // Stampa il risultato sul monitor
      Serial.println(" Pa");

      Serial.print(F("Altitudine = "));
      Serial.print(bmp.readAltitude(99656.30));               // da cambiare in caso di diverso luogo
      Serial.println(" m");
    
      Serial.println();
      

// Ho due sensori che rilevano la temperatura, perciò faccio la media e creo una variabile
  LivTemp = (dht.readTemperature() + bmp.readTemperature());
  TemperaturaMed = (LivTemp / 2.0);


// Altezza della neve
  CmMs = 0.0331 + ( 0.000062 * TemperaturaMed);               // Calcolo i cm/ms (centimetro al millisecondo) del suono in base alla temperatura
    digitalWrite(TRIG_PIN, LOW); 
      delayMicroseconds(2); 
    digitalWrite(TRIG_PIN, HIGH); 
      delayMicroseconds(10);                                  // Invio un impulso di dieci millisecondi sul pin TRIG, dichiarato sopra
    digitalWrite(TRIG_PIN, LOW);

  tempo = pulseIn(ECHO_PIN,HIGH);                             // riceve sul pin ECO e calcola la durata dell'impulso
  snow = (tempo * CmMs / 2.0);                                // Calcolo l'altezza della neve moltiplicando il tempo per la velocità dell'impulso (cm/ms) e divido per 2, poichè lo spazio che percorre l'impulso è doppio.
  LivNeve = 200.0 - snow;                                     // 200.0 sono i cm di altezza a cui è posto il sensore. Cambiare se è posto ad altezza differente.

    Serial.print("Neve: ");
    Serial.print(LivNeve);
    Serial.println("cm");

// Punto di rugiada - Approssimazione di Magnus-Tetens
  double a = 17.271;
  double b = 237.7;
  temp = (a * TemperaturaMed) / (b + TemperaturaMed) + log( h / 100);
  
    Serial.print("Punto di rugiada: ");
    Serial.print(temp);
    Serial.println("C");



// Velocità del vento con anemometro

    Anemometro_OFF = digitalRead(2);                                                                                // PIN 2 dell'anemometro

    if (Anemometro_OFF != Anemometro_ON)                                                                            // Si usa il "NOT EQUAL TO" per controllare un cambiamento di stato
      {
          Anemometro_ON = Anemometro_OFF;                                                                           // Cambiamento di stato diventa "UGUALE", ovvero si passa da un valore ad un altro
  
            if (Anemometro_OFF == HIGH)                                                                             // Valore ALTO, allora...
               {
                    if (Frequenza == 0)
                          { TimePulse =  millis();} // ...memorizza il primo impulso

                             Frequenza = Frequenza + 1;                                                             // Aumento del valore Frequenza a causa di ogni nuovo passaggio dal contatto      
    
                                  Time = ( millis() - TimePulse);                                                   // Calcolo del tempo trascorso dal primo impulso
    
                                          if (Time >=  WindTime)                                                    // Se il tempo è superiore a quello indicato come tempo minimo, ossia il WindTime, si effettuano i calcoli per calcolare il vento
                                               {

                                                  wind = (3.6*Frequenza*3.14*raggio)/( Time/1000.0);                // Usiamo questa formula per calcolare della velocità espressa in Km/h, dove 3.14 è il PiGreco, 3.6 è il valore per convertire i m/s in Km/h, perchè svolgiamo i calcoli usando metri e secondi.
                                                     Serial.print ("Vento: ");
                                                     Serial.print (wind);
                                                     Serial.println (" Km/h");                                      // Stampa il valore della variabile vento
     
                                                           Frequenza = 0;                                           // Conteggio azzerato per una nuova lettura
                                                           Anemometro_OFF = 0;
                                                           Anemometro_ON = 1;
                                                           Time = 0;
                                                   
                                                               }
                                                                  else 
                                                                      { wind = 0.00;
                                                                        Serial.print ("Vento = "); 
                                                                        Serial.print (0.00); 
                                                                        Serial.println (" Km/h");
                                                                                            }                
    }
  }

                Dati();                                                                                             // Richiama la funziona Dati per inviare i dati sul web
}


void Dati() // Funzione per caricare i dati dei sensori sul web
{

// Inizializzo la Shield dopo 1 secondo:
  delay(1000);
  Serial.println("Connessione al server");

// Invio Temperatura al server
    if (client.connect(server, 80)) {
          Serial.println("Connesso al server");
          
 
//invio la richiesta al server
          datiWEB ="GET /salva-dati.php?temperatura=";                            // File dove vengono salvati i dati.
          datiWEB+=TemperaturaMed;                                                 // Converte in stringa i dati delle variabili e le inoltra al file salvato sul sito...
          datiWEB+="&umidita=";                                                    // ... dove vengono inserite nella tabella del database
          datiWEB+=h;
          datiWEB+="&pressione=";
          datiWEB+=p;
          datiWEB+="&luminosita=";
          datiWEB+=Crepuscolo;
          datiWEB+="&pioggia=";
          datiWEB+=LivPioggia;
          datiWEB+="&neve=";
          datiWEB+=LivNeve;
          datiWEB+="&monossido=";
          datiWEB+=LivMono;
          datiWEB+="&vento=";
          datiWEB+=wind;
          datiWEB+="&rugiada=";
          datiWEB+=temp;
          datiWEB+=" HTTP/1.1";
        client.println(datiWEB);
        client.println("Host: stazionemeteoarduino.altervista.org");
        client.println("User-Agent: arduino-ethernet");
        client.println("Connection: close");
        client.println();
          lastConnectionTime = millis();
            Serial.println(datiWEB);
}
    else
{
//Se fallisce la connessione
            Serial.println("Connessione fallita");
            Serial.println("Non connesso al server");
        client.stop();
}

//esegui la richiesta ogni ora
  delay(3600000);

}
  


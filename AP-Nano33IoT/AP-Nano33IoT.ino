#include <SPI.h>
#include <WiFiNINA.h>

char ssid[] = "NANO_AP";
char pass[] = "fattelodasolo";

int led = 13;
int status = WL_IDLE_STATUS;
WiFiServer server(80);

void setup() {

  Serial.begin(9600);
    while (!Serial);

  pinMode(led, OUTPUT);

  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Il modulo Wi-Fi non risponde.");
    while (true);
  }

  WiFi.config(IPAddress(192, 168, 4, 1));

  status = WiFi.beginAP(ssid, pass);
    if (status != WL_AP_LISTENING) {
      Serial.println("Creazione AP fallita!");
      while (true);
  }

  delay(1000);

  server.begin();
  
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  IPAddress ip = WiFi.localIP();
  Serial.print("IP: ");
  Serial.println(ip);
}

void loop() {
 
  if (status != WiFi.status()) {
    status = WiFi.status();

    if (status == WL_AP_CONNECTED) {
      Serial.println("Dispositivo connesso all'AP");
    } else {
      Serial.println("Dispositivo disconnesso dall'AP");
    }
  }
  
  WiFiClient client = server.available();   // In attesa del client

  if (client) {                             // Se c'è un client,
    Serial.println("new client");           // stampa il messaggio sul Seriale
    String currentLine = "";                // crea una stringa per contenere i dati in entrata dal client
    while (client.connected()) {            // mentre il client è connesso...
      delayMicroseconds(10);                // ... attendo 10 micro secondi
      if (client.available()) {             // se ci sono byte da leggere dal client,
        char c = client.read();             // leggi un byte, poi
        Serial.write(c);                    // stampalo su Seriale
        if (c == '\n') {                    // se il byte è il carattere di nuova riga

          // se la riga corrente è vuota, hai due caratteri di nuova riga di seguito.
          // questa è la fine della richiesta HTTP del client, quindi invia una risposta:
          if (currentLine.length() == 0) {
            
            
            client.println("HTTP/1.1 200 OK"); // Le intestazioni HTTP iniziano sempre con un codice di risposta
            client.println("Content-type:text/html"); // e un Content-type in modo che il client sappia cosa sta arrivando, quindi una riga vuota:
            client.println();

            // il contenuto della risposta HTTP segue l'intestazione:
            client.print("Clicca <a href=\"/H\">QUI</a> per accendere il LED<br>");
            client.print("Clicca <a href=\"/L\">QUI</a> per spegnere il LED<br>");

            // La risposta HTTP termina con un'altra riga vuota:
            client.println();
            // interrompo il ciclo while:
            break;
          }
          else {      // se si ha una nuova riga, pulisco currentLine:
            currentLine = "";
          }
        }
        else if (c != '\r') {    // se si riceve il carattere di Ritorno Carrello,
          currentLine += c;      // lo si aggiunge a currentLine
        }

        // Verificare se la richiesta del client era "GET /H" o "GET /L":
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(led, HIGH);               // accende il LED
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(led, LOW);                // spegne il LED
        }
      }
    }
    // chiude la connessione
    client.stop();
    Serial.println("client disconnesso!");
  }
}

#include <SPI.h>
#include <Ethernet.h>
#include <avr/wdt.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

char server[] = "www.fattelodasolo.it";


IPAddress ip(192, 168, 1, 177);
IPAddress myDns(192, 168, 1, 1);

EthernetClient client;


unsigned long beginMicros, endMicros;
unsigned long byteCount = 0;
bool printWebData = true;  

void setup() {

  Serial.begin(9600);
  while (!Serial) {
    ; }

  
  Serial.println("Avvio connessione");
  
    
    Ethernet.begin(mac, ip, myDns);
    Serial.print("IP assegnato: ");
    Serial.println(Ethernet.localIP());
    
  delay(1000);
  Serial.print("Connessione a ");
  Serial.print(server);
  Serial.println("...");

  
  if (client.connect(server, 80)) {
    Serial.print("connesso a ");
    Serial.println(client.remoteIP());
    client.println("GET / HTTP/1.1");
    client.println("Host: www.fattelodasolo.it");
    client.println("Connessione: chiusa");
    client.println();
  } else {
    
    Serial.println("connessione fallita");
    delay(500);
    Serial.println("Riavvio...");
    delay(1000);
    wdt_enable(WDTO_30MS);
  }
  beginMicros = micros();

  wdt_reset();
}

void loop() {
  int len = client.available();
  if (len > 0) {
    byte buffer[80];
    if (len > 80) len = 80;
    client.read(buffer, len);
    if (printWebData) {
      Serial.write(buffer, len); // show in the serial monitor (slows some boards)
    }
    byteCount = byteCount + len;
  }

  if (!client.connected()) {
    endMicros = micros();
    Serial.println();
    Serial.println("disconnesso.");
    client.stop();
    Serial.print("Received ");
    Serial.print(byteCount);
    Serial.print(" bytes in ");
    float seconds = (float)(endMicros - beginMicros) / 1000000.0;
    Serial.print(seconds, 4);
    float rate = (float)byteCount / seconds / 1000.0;
    Serial.print(", rate = ");
    Serial.print(rate);
    Serial.print(" kbytes/second");
    Serial.println();

    while (true) {
      delay(1);
    }
  }
 
}

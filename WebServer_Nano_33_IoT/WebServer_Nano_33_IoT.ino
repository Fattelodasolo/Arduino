#include <SPI.h>
#include <WiFiNINA.h>

char ssid[] = "nome_rete";
char pass[] = "password";

int status = WL_IDLE_STATUS;

String msg = "Hello World!";

WiFiServer server(80);

void setup() {
  Serial.begin(9600);

if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Il modulo Wi-Fi non risponde");
    while (true);
  }

while (status != WL_CONNECTED) {
    Serial.println("Attendere connessione alla rete");
    status = WiFi.begin(ssid, pass);

    delay(10000);
  }
  server.begin();

  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  IPAddress ip = WiFi.localIP();
  Serial.print("IP: ");
  Serial.println(ip);

  long rssi = WiFi.RSSI();
  Serial.print("Segnale (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void loop() {
WiFiClient client = server.available();
  if (client) {
    Serial.println("Nuovo client");
    
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
if (c == '\n' && currentLineIsBlank) {
          
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println("Refresh: 5");
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");

          client.print("<h1>" + msg + "</h1>");

          client.println("</html>");
          break;
        }
        if (c == '\n') {
          currentLineIsBlank = true;
        } else if (c != '\r') {
          currentLineIsBlank = false;
        }
      }
    }
    delay(1);

    client.stop();
    Serial.println("Client disconnesso");
  }          
}

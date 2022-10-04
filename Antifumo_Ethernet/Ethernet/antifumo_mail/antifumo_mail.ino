//   Programma realizzato da Letterio Bavastrelli e rilasciato con GNU GPL V.3
//   Rilevamento Fumo con inoltro e-mail di avviso via Ethernet su account Virgilio
//   Copyright (C) 2017  Letterio Bavastrelli

//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.

//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.

//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <https://www.gnu.org/licenses/gpl-3.0.html>.

// Contact me: letteriobavastrelli@gmail.com

// Visit my YT Channel: https://www.youtube.com/Reshitoze

#include <SPI.h>
#include <Ethernet.h>
#include <avr/io.h>
#include <avr/wdt.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; // MAC della Shied Ethernet
IPAddress ip(192, 168, 1, 177); // Indirizzo IP del dispositivo sulla rete
IPAddress gateway(192,168,1,1);  // IP del Gateway
IPAddress subnet (255,255,255,0); // SubNet Mask

 // Login data:
 String UserName64 = "UserNameInBase64";
 String Password64 = "PasswordNameInBase64==";
 char server[] = "out.virgilio.it"; // Virgilio Server SMTP

// SMTP server VIRGILIO
String ServerName = "virgilio.it";
 // Mail data:
 String Sender = "mittente@virgilio.it";       // Indirizzo email mittente
 String Recipient = "destinatario@virgilio.it";    // Indirizzo dove recapitare la mail
 String Subject = "Sensore Rilevamento Fumo";         // Oggetto email
 String Body = "Rilevato fumo nel bagno uomini secondo piano. Intervenire!";   // Testo email

int time = 1000;

 int wait = 1000;
 String ServerResponse="";

EthernetClient client;

void setup()
 {
 Serial.begin(9600);  // Avvio il monitor seriale
 while (!Serial) {
    ;
  }
}

void loop()
{

// Sensore rilevamento Fumo 

int fumo = analogRead(A0);
  
  if (fumo < 100) // Se non c'è fumo, allora non inviare email
      ;
  else
    {
    Connection();  
    SMTP_email_command();
    // Se c'è fumo avvia la connessione e la funzione SMTP_email_command()
    }

wdt_reset(); // Resetta la funziona Watchdog
    
delay (5000); // Controlla ogni 5 secondi
}

void Connection(){
  // Avvia connessione Ethernet:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Tentativo di connessione con DHCP fallito");
    // proviamo con l'indirizzo IP Statico
    Ethernet.begin(mac, ip, gateway, subnet); // Avvio la shield
  }


// Inizializzo la Shield dopo 1 secondo:
  delay(1000);
  Serial.println("Connessione...");

if (client.connect(server, 25)) {
    Serial.println("Connesso");
    client.println();
  }
  
  else {
    Serial.println("Connessione fallita");
    wdt_enable(WDTO_30MS); // Ritenta la connessione se fallisce
  }   
// Se ci sono bytes in arrivo dal sever, leggili e stampali
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }
}
void SMTP_email_command(void) // Invio email con SMTP
{
     SendMsg("EHLO " + ServerName);
     SendMsg("AUTH LOGIN ");
     SendMsg(UserName64);
     SendMsg(Password64);
     SendMsg("MAIL From:<" + Sender +">");
     SendMsg("RCPT To:<" + Recipient + ">");
     SendMsg("DATA");
     SendMsg("To: " + Recipient); 
     SendMsg("From: " + Sender);
     SendMsg("Subject: "+ Subject);
     SendMsg("");
     SendMsg(Body); 
     SendMsg("");
     SendMsg(".");
     SendMsg("QUIT");
     client.println();
     client.stop();
}

void GetResponse() {
    if (client.available()) {
         char c = client.read();
         while (client.available()) { // Store command char by char.
           ServerResponse +=c;
           c = client.read();
         }
    Serial.println("<<<" + ServerResponse);
    ServerResponse="";
  }
 }
 
void SendMsg(String m) {
   client.println(m);
   Serial.println(">>>" + m);
   delay(wait);
   GetResponse();
 }

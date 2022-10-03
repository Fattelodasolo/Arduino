#include <DS3231.h>

DS3231  rtc(SDA, SCL);      // creo oggetto rtc per gestire il modulo e lo collego a SDA e SCL

Time tempo;                 // variabile in cui caricare ore, minuri, secondi, anno, giorno e mese

void setup() {
  Serial.begin(9600);

  rtc.begin();              // avvio modulo DS3231

  // Commenta le successiva tre righe dopo aver caricato lo sketch, poi ricaricalo nuovamente
  rtc.setDOW(THURSDAY);      // Imposta il giorno della settimana
  rtc.setTime(11, 9, 0);     // Imposta l'ora in formato 24 ore
  rtc.setDate(7, 1, 2021);   // Imposta data in formato GG/MM/AAAA
  
}
void loop() {

  tempo = rtc.getTime();                // Acquisisco informazioni sull'orario
  
  // Informazioni su Anno, mese e giorno
  Serial.print ("Siamo nell'anno ");
  Serial.print(tempo.year); 
  Serial.print (" DC, nel mese di ");
  Serial.print( rtc.getMonthStr());
  Serial.print("(");
  Serial.print(tempo.mon);
  Serial.print(")");
  Serial.print(", giorno ");
  Serial.println(tempo.date);

  // Giorno della settimana
  Serial.print ("Oggi è ");
  Serial.println(rtc.getDOWStr());

  // Informazioni su ore, minuti e secondi
  Serial.print("Sono le ore ");
  Serial.print(tempo.hour);
  Serial.print(" e ");
  Serial.print(tempo.min);
  Serial.print(" minuti e  ");
  Serial.print(tempo.sec);
  Serial.println (" secondi.");
  Serial.println("");

  delay (5000);
}

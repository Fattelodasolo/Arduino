#include <DS3231.h>

DS3231  rtc(SDA, SCL);      // creo oggetto rtc per gestire il modulo e lo collego a SDA e SCL

void setup() {
  Serial.begin(9600);

  rtc.begin();              // avvio modulo DS3231

  // Commenta le successiva tre righe dopo aver caricato lo sketch, poi ricaricalo nuovamente
  rtc.setDOW(THURSDAY);      // Imposta il giorno della settimana
  rtc.setTime(11, 0, 0);     // Imposta l'ora in formato 24 ore
  rtc.setDate(7, 1, 2021);   // Imposta data in formato GG/MM/AAAA
  
}

void loop() {
  Serial.println(rtc.getDOWStr());      // Giorno della settimana
  Serial.println(rtc.getDateStr());     // Data
  Serial.println(rtc.getTimeStr());     // Orario
  Serial.println("");
  
  delay (1000);

}

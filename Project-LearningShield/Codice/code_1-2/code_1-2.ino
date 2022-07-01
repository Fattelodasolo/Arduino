void setup() {
pinMode(4, OUTPUT); // Impostiamo la direzione del PIN 4 su OUTPUT perchè emetta un segnale
 
pinMode(12, OUTPUT); // Impostiamo la direzione del PIN 12 su OUTPUT perchè emetta un segnale
 
pinMode(13, OUTPUT); // Impostiamo la direzione del PIN 13 su OUTPUT perchè emetta un segnale
}

// la funzione LOOP ripete all'infinito le operazioni
void loop() {
 
digitalWrite(13, HIGH);                    // Accende il LED verde
digitalWrite(12, LOW);                     // Spegne il LED bianco
digitalWrite(4, LOW);                     // Spegne il LED rosso
delay(5000);                               // attesa di 5 secondi
 
digitalWrite(13, LOW);                     // Spegne il LED verde
digitalWrite(12, HIGH);                    // Accende il LED bianco
digitalWrite(4, LOW);                     // Spegne il LED rosso
delay(2000);                               // attesa di 2 secondi
 
digitalWrite(13, LOW);                     // Spegne il LED verde
digitalWrite(12, LOW);                     // Spegne il LED bianco
digitalWrite(4, HIGH);                    // Accende il LED rosso
delay(5000);                               // attesa di 5 secondo
}

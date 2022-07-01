const int limite = 34.00;                // limite del sistema
 
void setup() {
pinMode (3, OUTPUT);                   // direzione del pin buzzer
pinMode (13, OUTPUT);                  // direzione del pin led
Serial.begin (9600);                   // avvio del monitor seriale
}
 
void loop() {
iint sensor = analogRead(A1);         // rilevo il valore da A1

float t = sensor * 0.48875;
Serial.println(t);                  // stampo su monitor seriale
 
if (t > limite) {                   // se il valore luce supera il limite...
 
digitalWrite(13, HIGH);                // accendo il led e faccio suonare il buzzer
tone(3,400,1000);
delay(500);
tone(3,650,1000);
delay(500);
}
else {
 
digitalWrite(13, LOW);                // altrimenti non fa nulla
}
 
}

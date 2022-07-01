void setup() {
 
pinMode (13, OUTPUT); //LED
Serial.begin(9600); // avvio il monitor seriale
}
 
void loop () {
int luce = analogRead (A0); // Variabile luce che legge dal pin analogico A0
 
if (luce > 500){ // se il valore di luce è superiore a 500 accendi LED
digitalWrite (13, HIGH);
}
else{
digitalWrite (13, LOW);
}
 
Serial.println(luce); // stampo il valore di luce
delay (200);
}

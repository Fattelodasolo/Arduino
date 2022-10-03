int r, g, b, p1, p2, p3;

void setup() {
pinMode (9, OUTPUT);
pinMode (10, OUTPUT);
pinMode (11, OUTPUT);

Serial.begin(9600);

}

void loop() {
 p1= analogRead (A0);
 p2= analogRead (A1);
 p3= analogRead (A2);

 r = map (p1, 0, 1023, 0, 255);
 g = map (p2, 0, 1023, 0, 255);
 b = map (p3, 0, 1023, 0, 255);


 analogWrite (11, b);
 analogWrite (10, g);
 analogWrite (9, r);

 Serial.print ("Rosso: ");
 Serial.println (r);
 Serial.print ("Verde: ");
 Serial.println (g);
 Serial.print ("Blu: ");
 Serial.println (b);

 delay (5);
}

#define ECHO_PIN 12
#define TRIG_PIN 13

float distanceCm;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
 
  Serial.begin(9600);
}

void loop() {
  digitalWrite(TRIG_PIN, LOW); 
  delayMicroseconds(2); 
  digitalWrite(TRIG_PIN, HIGH); 
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  unsigned long impulso = pulseIn(ECHO_PIN,HIGH); 
  distanceCm = impulso / 2.0 * 0.0343;              // cm/microsecondi (velocità con 20° C)


  Serial.print("Distanza in cm: ");
  Serial.println(distanceCm);
  

  delay(1000);
}

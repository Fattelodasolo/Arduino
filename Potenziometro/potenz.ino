#include <Servo.h>
Servo motor;

void setup() {
  Serial.begin(9600);
  motor.attach(3);
}

void loop() {
  int potenz = analogRead(A0);
  int pos = map (potenz, 0, 1023, 0, 180);

  motor.write(pos);
    Serial.print("Gradi = ");
    Serial.print(pos);
    Serial.println("°");
 delay (10);   
}

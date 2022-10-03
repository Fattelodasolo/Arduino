const int S_analog = 1023.0;

int co, nh3; 
float no2;
  
void setup() {
  Serial.begin(9600);
}

void loop() {
  co = map (analogRead(A0), 0, S_analog, 1, 1000);            // Calcolo Monossido di Carbonio
  nh3 = map (analogRead(A1), 0, S_analog, 1, 500);            // Calcolo Ammoniaca
  no2 = (map (analogRead(A2), 0, S_analog, 5, 1000)) / 100.0 ;  // Calcolo Diossido di Azoto
  
  Serial.print("CO: ");
  Serial.print(co);
  Serial.print(" ppm\t");
  Serial.print("NH3: ");
  Serial.print(nh3);
  Serial.print("ppm\t");
  Serial.print("NO2: ");
  Serial.print(no2);
  Serial.println("ppm");

  delay(1000);
}

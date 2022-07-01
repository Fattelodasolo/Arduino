#define INT_A 2 // controlla la direzione del motore sinistro sul PIN 2
#define INT_B 4 // controlla la direzione del motore destro sul PIN 4
#define left_A 9 // definisce la velocità del motore sinistro al PIN 9
#define right_B 5 // definisce la velocità del motore destro al PIN 5
int sensore0, sensore1, sensore2;
void setup() {
  pinMode (13, INPUT);

  Serial.begin(9600);
  Serial.println ("Avvio macchina");

}

void loop() {
 sensore0 = digitalRead (13);

  if (sensore0 == 0){
    Stop();
    Serial.println ("Ostacolo rilevato");
    delay(100);
    Back();
    Serial.println ("Retromarcia");
    delay(500);
    Right();
    Serial.println ("Giro a destra");
    delay(500);
    Go();
    Serial.println ("Avanti");
    sensore1 = digitalRead (13);
    
    if (sensore1 == 0) {
      Stop();
      Serial.println ("Ostacolo rilevato");
      delay(100);
      Back();
      Serial.println ("Retromarcia");
      delay(500);
      Left();
      Serial.println ("Giro a sinistra");
      delay(1000);
      Go();
      Serial.println ("Avanti");
      sensore2 = digitalRead (13);
      
      if (sensore2 == 0) {
        Stop();
        Serial.println ("Ostacolo rilevato");
        Back();
        Serial.println ("Retromarcia");
        delay(500);
        Stop();
        delay(100);
        Left();
        Serial.println ("Giro a sinistra");
        delay(1000);
        Go();
      }
      
      else {
        Go();
      }
   
  }
    else {
        Go(); 
        }
  }
 else {
      Go();
      }

}


// funzione per fermarsi
void Stop()
{
digitalWrite (INT_A, LOW);
digitalWrite (INT_B, LOW);
analogWrite (left_A, 0); 
analogWrite (right_B, 0);
}

// funzione per girare a destra
void Right()
{
digitalWrite(INT_A,LOW);
digitalWrite(INT_B,HIGH);
analogWrite(left_A,100);
analogWrite(right_B,100);
}

// funzione per girare a sinistra
void Left()
{
digitalWrite(INT_A,HIGH);
digitalWrite(INT_B,LOW);
analogWrite(left_A,100);
analogWrite(right_B,100);
}

// funzione per retromarcia
void Back()
{
digitalWrite(INT_A,HIGH);
digitalWrite(INT_B,HIGH);
analogWrite(left_A,100);
analogWrite(right_B,100);
}

// funzione per andare avanti
void Go()
{
digitalWrite(INT_A,LOW);
digitalWrite(INT_B,LOW);
analogWrite(left_A,100);
analogWrite(right_B,100);
}

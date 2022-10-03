void setup(void)
{
    Serial.begin(9600);
    
}

void loop(void)
{
    int sensor = analogRead(A0);

    int valore = map (sensor, 0, 1023, 0, 100);
    
    Serial.print("j0.val=");
    Serial.print(valore);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
}

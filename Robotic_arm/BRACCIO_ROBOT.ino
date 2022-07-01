#include <Servo.h>  // add the servo libraries
Servo myservo1;  // create servo object to control a servo
Servo myservo2;
Servo myservo3;
Servo myservo4;
int pos1=80, pos2=60, pos3=130, pos4=0;  // define the variable of 4 servo angle and assign the initial value( that is the boot posture angle value)
char val;

void setup()
{
   // boot posture
  myservo1.write(pos1);  
  delay(1000);
  myservo2.write(pos2);
  myservo3.write(pos3);
  myservo4.write(pos4);
  delay(1500);

  Serial.begin(9600); //  set the baud rate to 9600
}

void loop() 
{
  myservo1.attach(A1);  // set the control pin of servo 1 to A1
  myservo2.attach(A0);  // set the control pin of servo 2 to A0
  myservo3.attach(3);   // set the control pin of servo 3 to D6
  myservo4.attach(9);   // set the control pin of servo 4 to D9

  if(Serial.available())   // if receive the data
  {
    val=Serial.read();    // read the received data
    Serial.println(val);
   
    switch(val)   
    {
      case 'B':  T_left();  break;   // execute the corresponding function when receive the value 
      case 'C':  T_right();  break;
      case 'A':  RF();  break;
      case 'D':  RB();  break;
      case '2':  ZK();  break;
      case '3':  ZB();  break;
      case '1':  LF();  break;
      case '4':  LB();  break;
    }
  }
}
//**************************************************
// turn left
void T_left()
{
    pos1=pos1+1;
    myservo1.write(pos1);
    delay(5);
    if(pos1>180)
    {
      pos1=180;
    }
}
//turn right 
void T_right()
{
    pos1=pos1-1;
    myservo1.write(pos1);
    delay(5);
    if(pos1<1)
    {
      pos1=1;
    }
}
//********************************************
//open the claw
void ZK()
{
      pos4=pos4-2;
      Serial.println(pos4);
      myservo4.write(pos4);
      delay(5);
      if(pos4<2)
      {
        pos4=0;
      }
}
// close the claw
void ZB()
{
    pos4=pos4+8;
      Serial.println(pos4);
      myservo4.write(pos4);
      delay(5);
      if(pos4>108)
      {
        pos4=108;
      }
}

//******************************************
// the upper arm will lift up 
void RF()
{
    pos2=pos2-1;
    myservo2.write(pos2);
    delay(5);
    if(pos2<0)
    {
      pos2=0;
    }
}
// the upper arm will go down 
void RB()
{
    pos2=pos2+1;
    myservo2.write(pos2);
    delay(5);
    if(pos2>180)
    {
      pos2=180;
    }
}

//***************************************
// the lower arm will stretch out 
void LB()
{
  pos3=pos3+1;
    myservo3.write(pos3);
    delay(5);
    if(pos3>180)
    {
      pos3=180;
    }
}
// the lower arm will draw back 
void LF()
{
  pos3=pos3-1;
    myservo3.write(pos3);
    delay(5);
    if(pos3<35)
    {
      pos3=35;
    }
}

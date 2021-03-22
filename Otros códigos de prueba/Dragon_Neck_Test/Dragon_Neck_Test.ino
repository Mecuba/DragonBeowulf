#include<Servo.h> 
Servo neckRot;
Servo neckLift;


void servoMove();
int posRot = 0; // initial position of servo
int posLift = 0;

char valSerial; // initial value of input

void setup() {
  Serial.begin(9600);
  Serial.println("Hola hola");
  neckLift.attach(8);
  neckRot.attach(7);

}

void loop() {
if (Serial.available()>0){
  valSerial = Serial.read();// read the serial value
  servoMove();
 }
}

  //-----------------------------NEOPIXEL EYES-----------------------------------

//-----------------------------SERVO CONTROL-----------------------------------

void servoMove(){
  switch(valSerial)
  {
//neckRot
  case 'q':
    if(posRot<180) posRot += 10; //than position of servo motor increases by 1 ( anti clockwise)
    Serial.println(posRot);
    neckRot.write(posRot);// the servo will move according to position
    delay(15);//delay for the servo to get to the position
    break;

  case 'e':
   if(posRot>0) posRot -= 10; //than position of servo motor decreases by 1 (clockwise)
    Serial.println(posRot);
    neckRot.write(posRot);
    delay(15);
    break;

   case 'w':
    posRot = 90; //the servo gets to its middle position
    Serial.println(posRot);
    neckRot.write(posRot);
    delay(50);
    break;
  
//neckLift
  case 'a':
    if(posLift<180) posLift += 10; //the position of servo motor increases by 1 ( anti clockwise)
    Serial.println(posLift);
    neckLift.write(posLift);// the servo will move according to position
    delay(15);//delay for the servo to get to the position
    break;

  case 'd':
   if(posLift>0) posLift -= 10; //the position of servo motor decreases by 1 (clockwise)
    Serial.println(posLift);
    neckLift.write(posLift);
    delay(15);
    break;

   case 's':
    posLift = 90; //the servo gets to its middle position
    Serial.println(posLift);
    neckLift.write(posLift);
    delay(50);
    break;

 }
}


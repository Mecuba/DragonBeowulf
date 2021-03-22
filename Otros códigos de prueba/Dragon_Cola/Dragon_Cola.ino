#include <Servo.h>
  
  Servo servoMotor;
  Servo servoMotor1; 
  int pos1=180;
  void setup() 
  {
  Serial.begin(9600);
  servoMotor.attach(12);
  servoMotor1.attach(13);
  servoMotor.write(180);
  servoMotor1.write(180);
}
 
void loop() {

for(pos1=180; pos1>0; pos1--)
{

  servoMotor.write(pos1);
  servoMotor1.write(pos1);
  delay(10); 
  }
for(pos1=0; pos1<180; pos1++)
{

  servoMotor.write(pos1);
  servoMotor1.write(pos1);
  delay(10);
  }  
}


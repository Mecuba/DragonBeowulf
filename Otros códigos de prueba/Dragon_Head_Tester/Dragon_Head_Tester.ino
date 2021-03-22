#include<Servo.h> 
Servo eyeRot;
Servo eyeLid;
Servo jaw;

#include <Adafruit_NeoPixel.h>
#define PIN 5
Adafruit_NeoPixel strip = Adafruit_NeoPixel(2, PIN, NEO_GRB + NEO_KHZ800);
void neoEyes();
void servoMove();
uint16_t j=0;
uint32_t Wheel();
int posRot = 110; // initial position of server
int posLid = 110;
int posJaw = 90;
int color = 0;

char valSerial; // initial value of input

void setup() {
  Serial.begin(9600);

  eyeLid.attach(6);
  jaw.attach(3);
  eyeRot.attach(2);
  eyeRot.write(posRot);
  jaw.write(posJaw);
  eyeLid.write(posLid);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

// Input a value 0 to 255 to get a color value.
//The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos ) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void loop() {
if (Serial.available()>0){
  valSerial = Serial.read();// read the serial value
  servoMove();
  neoEyes();
 }
}

  //-----------------------------NEOPIXEL EYES-----------------------------------

void neoEyes(){
uint16_t i;
  
    switch(valSerial)
  {

    case 'i':
    color+=1;
    Serial.print("El color es ");
    Serial.println(color);
    for(j=j; j<color; j++) {
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((256 / strip.numPixels())+ j) & 255));
    }
    strip.show();
    }
    break;

    case 'p':
    Serial.println("OFF");
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i,0);
    }
    strip.show();
    break;

    case 'o':
    color-=1;
    if(color<0) color=0;
    Serial.print("El color es ");
    Serial.println(color);
    for(j=j; j>color; j--) {
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((256 / strip.numPixels())- j) & 255));
    }
    if(color<0) color=0;
    strip.show();
    }
    break;
  }
  delay(1); //Tan rápido que le da fluidez al cambio de color pero tan lento que se ve lo suficiente cada color
}
//-----------------------------SERVO CONTROL-----------------------------------

void servoMove(){
  switch(valSerial)
  {
//eyeRot
  case 'q':
    if(posRot<130) posRot += 10; //than position of servo motor increases by 1 ( anti clockwise)
    Serial.println(posRot);
    eyeRot.write(posRot);// the servo will move according to position
    delay(15);//delay for the servo to get to the position
    break;

  case 'e':
   if(posRot>70) posRot -= 10; //than position of servo motor decreases by 1 (clockwise)
    Serial.println(posRot);
    eyeRot.write(posRot);
    delay(15);
    break;

   case 'w':
    posRot = 110; //the servo gets to its middle position
    Serial.println(posRot);
    eyeRot.write(posRot);
    delay(50);
    break;
  
//eyeLid
   case 'a':
    posLid += 10;
    Serial.println(posLid);
    eyeLid.write(posLid);// the servo will move according to position
    delay(15);//delay for the servo to get to the position
    break;

   case 'd':
    if(posLid>80)posLid -= 10;
    Serial.println(posLid);
    eyeLid.write(posLid);
    delay(15);
    break;

    case 's':
    posLid = 110; //the servo gets to its middle position
    Serial.println(posLid);
    eyeLid.write(posLid);
    delay(50);
    break;

//jaw
    case 'z':
    posJaw = 0; //than position of servo motor increases by 1 ( anti clockwise)
    Serial.println(posJaw);
    jaw.write(posJaw);// the servo will move according to position
    delay(15);//delay for the servo to get to the position
    break;

    case 'x':
    posJaw = 90; //than position of servo motor decreases by 1 (clockwise)
    Serial.println(posJaw);
    jaw.write(posJaw);
    delay(15);
    break;

    case 'c':
    posJaw -= 10; //the servo gets to its middle position
    Serial.println(posJaw);
    jaw.write(posJaw);
    delay(50);
    break;
  }
}


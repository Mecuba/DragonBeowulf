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
boolean abierto=0;
uint32_t Wheel();
int posRot = 110; // initial position of servo
int posLid = 110;
int posJaw = 60;
int color = 0;


void setup() {
  
  eyeLid.attach(6);
  jaw.attach(3);
  eyeRot.attach(2);
  
  eyeRot.write(posRot);
  jaw.write(posJaw);
  eyeLid.write(posLid);

//  jaw.write(180);
//  delay(1000);
//  jaw.write(0);
//  delay(1000);
//  jaw.write(posJaw);
//  delay(1000);
  
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

//transition r - g - b - back to r.
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
  servoLidDemo();
  neoEyesDemo();
  servoRotDemo();
}

  //-----------------------------NEOPIXEL EYES-----------------------------------

void neoEyesDemo(){
uint16_t i;
    if (abierto=0){
    color+=39;
    for(j=j; j<color; j++) {
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((256 / strip.numPixels())+ j) & 255));
    }
    strip.show();
    }
  }
}
//-----------------------------SERVO CONTROL-----------------------------------

void servoLidDemo(){
  if (abierto==0) posLid--;
  if (posLid==80) abierto=1;
  
  if (abierto==1) posLid++;
  if(posLid==110) abierto=0;

  eyeLid.write(posLid);
  delay(100);
}

void servoRotDemo(){
  if (abierto==1){
  for(posRot=60;posRot<130;posRot++){
  eyeRot.write(posRot);
  delay(100);
  }
  for(posRot=130;posRot>60;posRot--){
  eyeRot.write(posRot);
  delay(100);
  }
  for(posRot=60;posRot<110;posRot++){
  eyeRot.write(posRot);
  delay(100);
  }
 }
}


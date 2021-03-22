#include<Servo.h> 
Servo eyeRot;
Servo eyeLid;
Servo jaw;
Servo neckRot;
Servo neckLift;
Servo respira;
Servo cola1;
Servo cola2;
Servo alas;
Servo gas;

#include <Adafruit_NeoPixel.h>
#define PIN 5
Adafruit_NeoPixel strip = Adafruit_NeoPixel(2, PIN, NEO_GRB + NEO_KHZ800);

#define ignitePin A3

//Useful variables
boolean irovenir = 1;
boolean respir = 1;
uint16_t j = 0;
uint32_t Wheel();

int posRot = 110; // initial positions of servos
int posLid = 110;
int posJaw = 70;
int posGas = 70;
int color = 0;
int posNeckRot = 0;
int posLift = 0;
int posResp = 10;
int posCola= 90;
int posAla=50;

char valSerial; // initial value of input

void setup() {
  Serial.begin(9600);
  Serial.println("Hola hola");
  
  eyeRot.attach(2);
  jaw.attach(3);
  //4 es del Módulo SD
  eyeLid.attach(6);
  neckRot.attach(7);
  neckLift.attach(8);
  //9 es del Módulo SD
  alas.attach(10);
  //11 es del Modulo SD
  //12 es del Modulo SD
  //13 es del Modulo SD
  cola1.attach(A0);
  respira.attach(A1);
  cola2.attach(A2);
  pinMode(ignitePin,OUTPUT);//A3
  gas.attach(A4);
  
  eyeRot.write(posRot);
  jaw.write(posGas);
  eyeLid.write(posLid);
  respira.write(posResp);
  cola1.write(posCola);
  cola2.write(posCola);
  neckRot.write(posNeckRot);
  neckLift.write(posLift);
  gas.write(posGas);
  alas.write(posAla);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

// Input a value 0 to 255 to get a color value. The colours are a transition r - g - b - back to r.
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
  valSerial = Serial.read();// Read the serial input
  servoMove();
  neoEyes();
 }
  coletea();
  respiracion();
  delay(9);
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
//-----------------------------SERVO HEAD CONTROL-----------------------------------

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
    Serial.println("eyeRot");
    Serial.println(posRot);
    eyeRot.write(posRot);
    delay(50);
    break;
  
//eyeLid
   case 'a':
    if(posLid<130)posLid += 10;
    Serial.println(posLid);
    eyeLid.write(posLid);
    delay(15);
    break;

   case 'd':
    if(posLid>80)posLid -= 10;
    Serial.println(posLid);
    eyeLid.write(posLid);
    delay(15);
    break;

    case 's':
    posLid = 110;
    Serial.println("eyeLid");
    Serial.println(posLid);
    eyeLid.write(posLid);
    delay(50);
    break;

//jaw
    case 'z':
    posJaw += 10;
    Serial.println(posJaw);
    alas.write(posJaw);
    delay(15);
    break;

    case 'x':
    posJaw = 70;
    Serial.println("Jaw");
    Serial.println(posJaw);
    alas.write(posJaw);
    delay(15);
    break;

    case 'c':
    posJaw -= 10;
    Serial.println(posJaw);
    alas.write(posJaw);
    delay(15);
    break;
//-----------------------------SERVO NECK CONTROL-----------------------------------
//neckRot
  case 'j':
    if(posNeckRot<180) posNeckRot += 10;
    Serial.println(posNeckRot);
    neckRot.write(posNeckRot);
    delay(15);
    break;

  case 'l':
   if(posNeckRot>0) posNeckRot -= 10;
    Serial.println(posNeckRot);
    neckRot.write(posNeckRot);
    delay(15);
    break;

   case 'k':
    posNeckRot = 90;
    Serial.println("neckRot");
    Serial.println(posNeckRot);
    neckRot.write(posNeckRot);
    delay(50);
    break;
  
//neckLift
  case 'b':
    if(posLift<180) posLift += 10;
    Serial.println(posLift);
    neckLift.write(posLift);
    delay(15);
    break;

  case 'm':
   if(posLift>0) posLift -= 10;
    Serial.println(posLift);
    neckLift.write(posLift);
    delay(15);
    break;

   case 'n':
    posLift = 20;
    Serial.println("neckLift");
    Serial.println(posLift);
    neckLift.write(posLift);
    delay(50);
    break;

   case 'f':
    Serial.println("Ignite");
    abrirAlas();
    for(posNeckRot=0;posNeckRot<160;posNeckRot++){
    neckRot.write(posNeckRot);
    delay(8);
    }
    for(posLift=0;posLift<60;posLift++){
    neckLift.write(posLift);
    delay(8);
    }
    digitalWrite(ignitePin,HIGH);
    delay(2000);
    //gas.write(40);
    delay(1000);
    //gas.write(70);
    Serial.println("Ignite OFF");
    digitalWrite(ignitePin,LOW);
    for(;posNeckRot>90;posNeckRot--){
    neckRot.write(posNeckRot);
    delay(8);
    }
    for(;posLift>0;posLift--){
    neckLift.write(posLift);
    delay(8);
    }
    plegarAlas();
    break;

   case 't':
    Serial.println("Gas");
    gas.write(40);
    delay(1000);
    Serial.println("Gas OFF");
    gas.write(70);
    break;
//-----------------------------SERVO BREATHING CONTROL-----------------------------------
//Estirar cuello
  case 'y':
    if(posNeckRot==0 && posLift==60){
    Serial.println("Estirando el cuello");
    Serial.println("Paso 1");
    neckRot.write(170);
    neckLift.write(0);
    delay(1000);
    Serial.println("Paso 2");
    neckRot.write(90);
    neckLift.write(20);
    delay(1000);
    Serial.println("Paso 3");
    neckRot.write(180);
    neckLift.write(20);
    delay(1000);
    Serial.println("Paso 4");
    neckRot.write(180);
    neckLift.write(100);
    delay(1000);
    Serial.println("Paso 5");
    neckRot.write(180);
    neckLift.write(20);
    delay(1000);
    Serial.println("Paso 6");
    neckRot.write(180);
    neckLift.write(100);
    delay(1000);
    Serial.println("Paso 7");
    neckRot.write(180);
    neckLift.write(20);
    delay(1000);
    Serial.println("Paso 8");
    neckRot.write(180);
    neckLift.write(100);
    delay(1000);
    Serial.println("Paso 9");
    neckRot.write(180);
    neckLift.write(20);
    delay(1000);
    Serial.println("Paso 10");
    neckRot.write(180);
    neckLift.write(100);
    delay(1000);
    break;
    
   case 'u':
   neckRot.write(0);
   delay(1500);
   neckLift.write(20);
    }
  }
}
//-----------------------------AUTOMATIC FUNCTIONS-----------------------------------
//Cola
void coletea(){
  if (irovenir==0) posCola--;
  if (irovenir==1) posCola++;
  
  if (posCola==180) irovenir=0;
  if(posCola==0) irovenir=1;

  cola1.write(posCola);
  cola2.write(posCola);
}
//Respira
void respiracion(){
  if (respir==0) posResp--;
  if (respir==1) posResp++;
  
  if (posResp==180) respir=0;
  if(posResp==10) respir=1;

  respira.write(posResp);
}
void abrirAlas(){
  posAla=180;
  alas.write(posAla);
}
void plegarAlas(){
  for(posAla=180;posAla>50;posAla--){
  alas.write(posAla);
  delay(20);
  }
}


/*
 * Código para el funcionamiento autónomo 
 * del Dragón Beowulf para el Cocotrón 2018. 
 * Por Cardansan, 25/10/18.
*/

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
boolean intrusion=false;
boolean alejarse=false;
boolean blinkState=false;
boolean irovenir = 1;
boolean respir = 1;
boolean paso21=false;
boolean paso32=false;
float prevDistancia;
int counter=0;
int counter2=0;

unsigned long int colaTime;
unsigned long int respiraTime;
unsigned long int blinkTime;
unsigned long int ultraTime;
unsigned long int tiempo;
uint16_t j = 0;
uint32_t Wheel();

//Variables para colorLoop()
boolean colorLoopState=false;
int color1, color2;
int colorCambio;
boolean colorSubiendo=true;
boolean colorLoopInicio=true;
unsigned long int colorLoopTime;

int color = 0;
int posRot = 110; // initial positions of servos
int posLid = 110;
int posJaw = 0;
int posNeckRot = 0;
int posLift = 0;
int posResp = 10;
int posCola= 90;
int posAlas= 90;
int posGas;//--------------¡¡¡Poner valor!!!------------------

   // defines pins numbers
    const int trigPin = 11;
    const int echoPin = 12;
    // defines variables
    long duration;
    float distancia;
    int distancia_int;
    int distancia_red;
    int distancia_met_red;
    float distancia_ant;
    float distancia_met;
    int distancia_met_int;
    int uno;
    int dos = 1;
    
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
  jaw.write(posJaw);
  eyeLid.write(posLid);
  respira.write(posResp);
  cola1.write(posCola);
  cola2.write(posCola);
  neckRot.write(posNeckRot);
  neckLift.write(posLift);
  
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPin, INPUT); // Sets the echoPin as an Input
    
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  eyeClose();
  plegarAlas();

  //Variables para funciones autónomas
  colaTime=millis();
  respiraTime=(millis()-10);
  colorLoopTime=millis();
  ultraTime=millis();
  tiempo=millis();

  eyeOpen();
  neoON(1);
  delay(2000);
  eyeClose();
  colorLoopON(75,110);

}


/*
                _     _   _                    ____  
               (_)   | | | |                  / /\ \ 
    __   _____  _  __| | | | ___   ___  _ __ | |  | |
    \ \ / / _ \| |/ _` | | |/ _ \ / _ \| '_ \| |  | |
     \ V / (_) | | (_| | | | (_) | (_) | |_) | |  | |
      \_/ \___/|_|\__,_| |_|\___/ \___/| .__/| |  | |
                                       | |    \_\/_/ 
                                       |_|           
 */
void loop() {
  scanUltrasonico();
  if(intrusion==true) despertar();
  if(alejarse==true) dormir();
  if(colorLoopState==true){
  actualColorLoop();
  }
  coletea();
  respiracion();
  if(blinkState==true) parpadea();
}

  //-----------------------------NEOPIXEL EYES-----------------------------------
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

void neoOFF(){
    for(int i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i,0);
    }
    strip.show();
}

void neoON(int col){ //¿En qué color quieres encenderlo? Puede ser el mismo color que antes con la variable "color".
    for(int i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(col));
    }
    strip.show();
}
void neoTransition(int goal){ //Transcisión Gradual hasta el color indicado
  int col=color;
  boolean finished=false;
  for(;finished==false;){
    if(color<goal) col++;
    else if(color>goal) col--;
    else if(color==goal) finished=true;
    neoON(col);
    delay(1);
  }
}
//Sección dedicada para colorLoop() y sus funciones auxiliares°°°°
void colorLoopON(int col1,int col2){
  color1=col1;
  color2=col2;
  colorCambio=col1;
  neoON(colorCambio);
  colorLoopState=true;
}
void colorLoopOFF(){
  colorLoopState=false;
}
void actualColorLoop(){
if(millis()>(colorLoopTime+50)){
  colorLoopTime=millis();
  if(colorSubiendo==true){
    colorCambio++;
  }
  else{
    colorCambio--;
  }
  
  neoON(colorCambio);
  
  if(colorCambio==color2){
    colorSubiendo=false;
  }
  else if(colorCambio==color1){
    colorSubiendo=true;
  }
  else{
    return;
  }
}
}
//Fin sección dedicada para colorLoop() y sus funciones auxiliares°°°

//-----------------------------SERVO CONTROL-----------------------------------
//MANDÍBULA
void jawOpen(){
  jaw.write(0);
  delay(15);
}
void jawClose(){
  jaw.write(180);
  delay(15);
}
//EYE ROT
void verFrente(){
  eyeRot.write(100);
  delay(15);
}
void verCostado(){
  eyeRot.write(70);
  delay(15);
}

//PÁRPADO
void pestanea(){ //Termina y comienza con los ojos abiertos.

  for(int i=80;i<130;i++){ //De abierto a cerrado
    eyeLid.write(i);
    delay(5);
  }
  neoOFF();
  delay(200);
  
  for(int i=130;i>80;i--){ //De cerrado a abierto
    eyeLid.write(i);
    delay(5);
    if(i<100)neoON(color);
  }
}
void eyeClose(){
  eyeLid.write(130);
  neoOFF();
  delay(15);
}
void eyeOpen(){
  eyeLid.write(80);
  neoON(color);
  delay(15);
}

void blinkStateON(){
  blinkState=true;
  blinkTime=millis();
}
void parpadea(){
  if(millis()>(blinkTime+1300)){
    pestanea();
    blinkTime=millis();
  }
}

//-----------------------------AUTOMATIC FUNCTIONS-----------------------------------
//Cola
void coletea(){
 if(millis()>(colaTime+8)){
  if (irovenir==0) posCola--;
  if (irovenir==1) posCola++;
  
  if (posCola==180) irovenir=0;
  if(posCola==0) irovenir=1;

  cola1.write(posCola);
  cola2.write(posCola);
  
  colaTime=millis();
 }
}
//Respira
void respiracion(){
 if(millis()>(respiraTime+9)){
  
  if (respir==0) posResp--;
  if (respir==1) posResp++;
  
  if (posResp==180) respir=0;
  if(posResp==10) respir=1;

  respira.write(posResp);
  Serial.println("Respira!");
  Serial.println(posResp);
  respiraTime=millis();
  Serial.println("respTime");
  Serial.println(respiraTime);
 }
}
//----------------OTHER FUNCTIONS-----------------------
int scanUltrasonico(){
  if(millis()>(ultraTime+500)){
  
    distancia_ant = distancia;
    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    distancia= duration*0.034/2;
    distancia_met = distancia/100;
    distancia_int = (int)distancia;
    distancia_met_int = (int)distancia_met;
    distancia_met_red = round(distancia_met);
    //
    if(abs((distancia_met-distancia_met_red))<=.1){
      distancia = distancia_ant;
    }else{
        distancia = distancia;
      }
    //
    if(abs(distancia-distancia_ant)>=150){
      distancia = distancia_ant;
    }else{
      distancia = distancia;
    }
    //
    distancia_met = distancia/100;
    distancia_int = (int)distancia;
    distancia_met_int = (int)distancia_met;
    distancia_met_red = round(distancia_met);
    uno = distancia_met_int;
    if(uno<dos){
      Serial.print("1 metro mas cerca");
    }else{
      if(uno == dos){
        Serial.print("Se mantiene igual");
      }else{
        Serial.print("Se aleja");
      }
    }
    dos = uno;
    // Prints the distance on the Serial Monitor
    Serial.print("\nDistance: ");
    Serial.println(distancia);
    Serial.println("\nenteros");
    Serial.println(distancia_int);
    Serial.print("\ndistancia en metros: ");
    Serial.println(distancia_met);
    Serial.print("\ndistancia en metros enteros: ");
    Serial.println(distancia_met_int);
    if(distancia_met<=1) {
      counter++;
      if(counter==3){
      alejarse=false;
      intrusion=true;
      counter=0;
      }
    }
      
    else if(distancia_met<3 && distancia_met>1 && intrusion==true){
      counter2++;
      if(counter2==3){
       intrusion=false;
       alejarse=true;
      }

    }
    else{
      intrusion=false;
      alejarse=false;
      counter=0;
      counter2;
    }
  }
}
void estirarCuello(){
  neckLift.write(110);
}
void doblarCuello(){
  neckLift.write(60);
  delay(100);
  neckLift.write(0);
  delay(15);
}
void abrirAlas(){
  alas.write(130);
}
void plegarAlas(){
  alas.write(0);
}
void rugido(){
  
}
void despertar(){
  if(millis>tiempo+10000){
  Serial.println("DESPERTE---------------------------------------------------");
  delay(60000);
  eyeOpen();
  neoON(255);
  jawOpen();
  verCostado();
  abrirAlas();
  rugido();
  doblarCuello();
  colorLoopON(90,110);
  blinkStateON();
  tiempo=millis();
  }
}
void dormir(){
  Serial.println("a dormirrr------------------------------------------------");
  plegarAlas();
  eyeClose();
  blinkState=false;
  colorLoopOFF();
}


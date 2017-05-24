#include "Arduino.h"
#define RED 5
#define GREEN 6
#define BLUE 3
#define WHITE 9

// music note frequency table
int nc2 = 65;
int nc2s = 69;
int nd2 = 73;
int nd2s = 78;
int ne2 = 82;
int nf2 = 87;
int nf2s = 93;
int ng2 = 98;
int ng2s = 104;
int na2 = 110;
int na2s = 117;
int nb2 = 123;
int nc3 = 131;
int nc3s = 139;
int nd3 = 147;
int nd3s = 156;
int ne3 = 165;
int nf3 = 175;
int nf3s = 185;
int ng3 = 196;
int ng3s = 208;
int na3 = 220;
int na3s = 233;
int nb3 = 247;
int nc4 = 262;
int nc4s = 277;
int nd4 = 294;
int nd4s = 311;
int ne4 = 330;
int nf4 = 349;
int nf4s = 370;
int ng4 = 392;
int ng4s = 415;
int na4 = 440;
int na4s = 466;
int nb4 = 494;
int nc5 = 523;
int nc5s = 554;
int nd5 = 587;
int nd5s = 622;
int ne5 = 659;
int nf5 = 698;
int nf5s = 740;
int ng5 = 784;
int ng5s = 831;
int na5 = 880;
int na5s = 932;
int nb5 = 988;

double speed = 0.55;
//int marioCounter = 0;
int rainbowCounter = 0;
int marioCounter2 = 0;

// mario like climbing music
int lineTwoNotes[8] = {ng2, nc3, ne3, ng3, nc4, ne4, ng4, ne4};
int lineTwoTimes[8] = {250, 250, 250, 250, 250, 250, 700, 500};

int lineThreeNotes[8] = {ng2s, nc3, nd3s, ng3s, nc4, nd4s, ng4s, nd4s};
int lineThreeTimes[8] = {250, 250, 250, 250, 250, 250, 700, 500};

int lineFourNotes[11] = {na2s, nd3, nf3, na3s, nd4, nf4, na4s, na4s, na4s, na4s, nc5};
int lineFourTimes[11] = {250, 250, 250, 250, 250, 250, 650, 250, 250, 250, 1500};

#define FADESPEED 2     // make this higher to slow down flashing lights
#include <BobaBlox.h>  // music playing library

// code to run 5v digital neopixel targetting ring  upto 24 pixels
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip = Adafruit_NeoPixel(24, 10 , NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel light = Adafruit_NeoPixel(1, 7, NEO_GRB + NEO_KHZ800);


// setup for I2C communication
#include <Wire.h>
String comdata = "";
int lastLength = 0;

// libraries and dsetup of any digital neopixel rings or pixels
// nneded if arduino is controling aiming ring
//#include <Adafruit_NeoPixel.h>
//Adafruit_NeoPixel pixel = Adafruit_NeoPixel(16, 6, NEO_GRB + NEO_KHZ800);

// Ultrasonic sensor libraries and PINsetup
//#include <NewPing.h>
//#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
//#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
//#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
//NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

int c = 0;
int A1c = 110;
int B1c = 124;
int C1c = 139;
int D1c = 147;
int E2c = 165;
int F2c = 185;
int G2c = 196;
int A2c = 220;
int B2c = 247;
int C2c = 277;
int D2c = 294;

Speaker mySpeaker(8);

void setup() {
  light.begin();
  strip.begin();
  //  Serial.print("setup");  //commented out because it goes weird btw --- serial print does not seem to work with I2C
  light.setPixelColor(0, light.Color(255, 255, 255));
  light.show();
  //ANALOG pixel STUFF BEGIN
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(WHITE, OUTPUT);
  //ANOLOG pixel SETUP STUFF END
  playOdeToJoy();

  //  pixel.begin();
  Wire.begin(8);                // join i2c bus with address
  Wire.onReceive(receiveEvent); // register event to recieve instructions from Roborio
  //  Wire.onRequest(requestEvent); // register event to send back data to Roborio
  Serial.begin(9600);           // start serial port at 9600 bps:

  // set pixel 0 to dim green !!!AND!!!PURPLE!!!! to indicate being on and not instructios recieved
  //  light.setPixelColor(0, pixel.Color(0, 125, 0));
  //  light.setPixelColor(8, pixel.Color(100, 0, 100));
  //  light.show();
  visionlight ();

  analogWrite(RED, 0);
  analogWrite(GREEN, 255);
  analogWrite(BLUE, 133);
  analogWrite(WHITE, 0);
  light.setPixelColor(0, light.Color(0, 255, 133));
  light.show();
  Serial.println("hello, teal lights");
  Serial.println("Now awaiting instructions");

}

String INSTRUCTIONS = "";
void loop() {
  Wire.begin(7);
  delay(5);
  Wire.begin(8);
  delay(95);

  if (INSTRUCTIONS == "playOdeToJoy") {
    marioCounter2 = 0;
    rainbowCounter = 0;
    playOdeToJoy();
  } else if (INSTRUCTIONS == "playFifth") {
    marioCounter2 = 0;
    rainbowCounter = 0;
    playFifth();
  } else if (INSTRUCTIONS == "greenlight") {
    marioCounter2 = 0;
    rainbowCounter = 0;
    greenlight();
  } else if (INSTRUCTIONS == "whitelight") {
    marioCounter2 = 0;
    rainbowCounter = 0;
    whitelight();
  } else if (INSTRUCTIONS == "redlight") {
    marioCounter2 = 0;
    rainbowCounter = 0;
    redlight();
  } else if (INSTRUCTIONS == "bluelight") {
    marioCounter2 = 0;
    rainbowCounter = 0;
    bluelight();
  } else if (INSTRUCTIONS == "purplelight") {
    marioCounter2 = 0;
    rainbowCounter = 0;
    purplelight();
  } else if (INSTRUCTIONS == "yellowlight") {
    marioCounter2 = 0;
    rainbowCounter = 0;
    yellowlight();
  } else if (INSTRUCTIONS == "orangelight") {
    marioCounter2 = 0;
    rainbowCounter = 0;
    orangelight();
  } else if (INSTRUCTIONS == "teallight") {
    marioCounter2 = 0;
    rainbowCounter = 0;
    teallight();
  } else if (INSTRUCTIONS == "heartbeat") {
    marioCounter2 = 0;
    rainbowCounter = 0;
    heartbeat();
  } else if (INSTRUCTIONS == "rainbowlight") {
    marioCounter2 = 0;
    if (rainbowCounter == 0) {
      rainbowLight1();
      rainbowCounter ++;
    } else if (rainbowCounter == 1) {
      rainbowLight2();
      rainbowCounter ++;
    } else if (rainbowCounter == 2) {
      rainbowLight3();
      rainbowCounter = 0;
    }
  }else if (INSTRUCTIONS == "playMario") {
    rainbowCounter = 0;
    if (marioCounter2 == 0) {
      playMario1();
      marioCounter2 ++;
    } else if (marioCounter2 == 1) {
      playMario2();
      marioCounter2 ++;
    } else if (marioCounter2 == 2) {
      playMario3();
      marioCounter2 ++;
    }
  }else if (INSTRUCTIONS == "redblue") {
   marioCounter2 = 0;
   rainbowCounter = 0;
   redblue();
   }
  // if not recognized request go to teal
  else {
     teallight();
  }
  //  Serial.println(INSTRUCTIONS);
}

void receiveEvent(int howMany) {
  // function called whenever robrio sends us information
  INSTRUCTIONS = "";
  // read the string in from the wire into a variable called INSTRUCTIONS

  while ( Wire.available() > 0 )  {
    char n = (char)Wire.read();
    if (((int)n) > ((int)(' ')))
      INSTRUCTIONS += n;
  }
  Serial.print("received: ");
  Serial.println(INSTRUCTIONS);

}

void greenlight () {

  //for (int i = 0; i < 16; i++) {
  //  light.setPixelColor(i, pixel.Color( 0, 255, 0));
  //}
  //light.show();
  //  requestEvent();

  analogWrite(RED, 0);
  analogWrite(BLUE, 0);
  analogWrite(GREEN, 0);
  analogWrite(WHITE, 0);

  int r = 0;
  int g = 0;
  int b = 0;

  for (g = 0; g < 255; g++) {
    analogWrite(GREEN, g);
    delay(FADESPEED);
    light.setPixelColor(0, light.Color(0, g, 0));
    light.show();
  }
  for (g = 255; g > 0; g--) {
    analogWrite(GREEN, g);
    delay(FADESPEED);
    light.setPixelColor(0, light.Color(0, g, 0));
    light.show();
  }
}

void redlight () {

  //  for (int i = 0; i < 16; i++) {
  //    light.setPixelColor(i, pixel.Color( 255, 0, 0));
  //  }
  //  light.show();

  analogWrite(RED, 0);
  analogWrite(BLUE, 0);
  analogWrite(GREEN, 0);
  analogWrite(WHITE, 0);

  int r = 0;
  int g = 0;
  int b = 0;

  for (r = 0; r < 255; r++) {
    analogWrite(RED, r);
    delay(FADESPEED);
    light.setPixelColor(0, light.Color(r, 0, 0));
    light.show();
  }
  for (r = 255; r > 0; r--) {
    analogWrite(RED, r);
    delay(FADESPEED);
    light.setPixelColor(0, light.Color(r, 0, 0));
    light.show();
  }
}

void bluelight () {

  //  for (int i = 0; i < 16; i++) {
  //    light.setPixelColor(i, pixel.Color( 0, 0, 255));
  //  }
  //  light.show();

  analogWrite(RED, 0);
  analogWrite(BLUE, 0);
  analogWrite(GREEN, 0);
  analogWrite(WHITE, 0);

  int r = 0;
  int g = 0;
  int b = 0;

  for (b = 0; b < 255; b++) {
    analogWrite(BLUE, b);
    delay(FADESPEED);
    light.setPixelColor(0, light.Color(0, 0, b));
    light.show();
  }
  for (b = 255; b > 0; b--) {
    analogWrite(BLUE, b);
    delay(FADESPEED);
    light.setPixelColor(0, light.Color(0, 0, b));
    light.show();
  }
}

void purplelight () {

  //  for (int i = 0; i < 16; i++) {
  //    light.setPixelColor(i, pixel.Color( 0, 0, 255));
  //  }
  //  light.show();

  analogWrite(RED, 0);
  analogWrite(BLUE, 0);
  analogWrite(GREEN, 0);
  analogWrite(WHITE, 0);

  int r = 0;
  int g = 0;
  int b = 0;

  for (b = 0; b < 255; b++) {
    analogWrite(BLUE, b);
    analogWrite(RED, b);
    light.setPixelColor(0, light.Color(b, 0, b));
    light.show();
    delay(FADESPEED);
  }
  for (b = 255; b > 0; b--) {
    analogWrite(BLUE, b);
    analogWrite(RED, b);
    light.setPixelColor(0, light.Color(b, 0, b));
    light.show();
    delay(FADESPEED);
  }
}

void yellowlight () {

  //  for (int i = 0; i < 16; i++) {
  //    light.setPixelColor(i, pixel.Color( 0, 0, 255));
  //  }
  //  light.show();

  analogWrite(RED, 0);
  analogWrite(BLUE, 0);
  analogWrite(GREEN, 0);
  analogWrite(WHITE, 0);

  int r = 0;
  int g = 0;
  int b = 0;

  for (b = 0; b < 255; b++) {
    analogWrite(GREEN, b);
    analogWrite(RED, b);
    light.setPixelColor(0, light.Color(b, b, 0));
    light.show();
    delay(FADESPEED);
  }
  for (b = 255; b > 0; b--) {
    analogWrite(GREEN, b);
    analogWrite(RED, b);
    light.setPixelColor(0, light.Color(b, b, 0));
    light.show();
    delay(FADESPEED);
  }
}

void teallight () {

  //  for (int i = 0; i < 16; i++) {
  //    light.setPixelColor(i, pixel.Color( 0, 0, 255));
  //  }
  //  light.show();

  analogWrite(RED, 0);
  analogWrite(BLUE, 0);
  analogWrite(GREEN, 0);
  analogWrite(WHITE, 0);

  int r = 0;
  int g = 0;
  int b = 0;

  for (b = 0; b < 255; b++) {
    analogWrite(GREEN, b);
    analogWrite(BLUE, b * 0.7);
    light.setPixelColor(0, light.Color(0, b, b * 0.7));
    light.show();
    delay(FADESPEED);
  }
  for (b = 255; b > 0; b--) {
    analogWrite(GREEN, b);
    analogWrite(BLUE, b * 0.7);
    light.setPixelColor(0, light.Color(0, b, b * 0.7));
    light.show();
    delay(FADESPEED);
  }

}

void orangelight () {

  //  for (int i = 0; i < 16; i++) {
  //    light.setPixelColor(i, pixel.Color( 0, 0, 255));
  //  }
  //  light.show();

  analogWrite(RED, 0);
  analogWrite(BLUE, 0);
  analogWrite(GREEN, 0);
  analogWrite(WHITE, 0);

  int r = 0;
  int g = 0;
  int b = 0;

  for (b = 0; b < 255; b++) {
    analogWrite(RED, b);
    analogWrite(GREEN, b * 0.3);
    light.setPixelColor(0, light.Color(b, b * 0.3, 0));
    light.show();
    delay(FADESPEED);
  }
  for (b = 255; b > 0; b--) {
    analogWrite(RED, b);
    analogWrite(GREEN, b * 0.3);
    light.setPixelColor(0, light.Color(b, b * 0.3, 0));
    light.show();
    delay(FADESPEED);
  }

}


void whitelight () {

  analogWrite(RED, 0);
  analogWrite(BLUE, 0);
  analogWrite(GREEN, 0);
  analogWrite(WHITE, 0);

  int r = 0;
  int g = 0;
  int b = 0;
  int w = 0;

  for (w = 0; w < 255; w++) {
    analogWrite(WHITE, w);
    light.setPixelColor(0, light.Color(w, w, w));
    light.show();
    delay(FADESPEED);
  }
  for (w = 255; w > 0; w--) {
    analogWrite(WHITE, w);
    light.setPixelColor(0, light.Color(w, w, w));
    light.show();
    delay(FADESPEED);
  }

}


void heartbeat () {
  Serial.println("I'm Alive :)");
  analogWrite(RED, 0);
  analogWrite(BLUE, 0);
  analogWrite(GREEN, 0);
  analogWrite(WHITE, 0);

  int r = 0;
  int g = 0;
  int b = 0;

  for (b = 0; b < 175; b++) {
    analogWrite(RED, b);
       analogWrite(GREEN, b*0.01);
       analogWrite(BLUE, b*0.01);
    light.setPixelColor(0, light.Color(b, b*0.01, b*0.01));
    light.show();
    delay(1);
  }
  for (b = 175; b > 0; b--) {
    analogWrite(RED, b);
       analogWrite(GREEN, b*0.01);
      analogWrite(BLUE, b*0.01);
    light.setPixelColor(0, light.Color(b, b*0.01, b*0.01));
    light.show();
    delay(1);
  }
  delay(50);
  for (b = 0; b < 255; b++) {
    analogWrite(RED, b);
       analogWrite(GREEN, b*0.01);
       analogWrite(BLUE, b*0.01);
    light.setPixelColor(0, light.Color(b, b*0.01, b*0.01));
    light.show();
    delay(1);
  }
  for (b = 255; b > 0; b--) {
    analogWrite(RED, b);
       analogWrite(GREEN, b*0.01);
      analogWrite(BLUE, b*0.01);
    light.setPixelColor(0, light.Color(b, b*0.01, b*0.01));
    light.show();
    delay(1);
  }

  delay(700);
}


void redblue () {
  Serial.println("red blue flash");
  analogWrite(RED, 0);
  analogWrite(BLUE, 0);
  analogWrite(GREEN, 0);
  analogWrite(WHITE, 0);

  for (int b = 0; b < 255; b++) {
    analogWrite(RED, b);
    light.setPixelColor(0, light.Color(b, 0, 0));
    light.show();
    delay(1);
  }
  for (int b = 255; b > 0; b--) {
    analogWrite(RED, b);
    light.setPixelColor(0, light.Color(b, 0, 0));
    light.show();
    delay(1);
  }
  delay(1);
  for (int b = 0; b < 255; b++) {
    analogWrite(BLUE, b);
    light.setPixelColor(0, light.Color(b, 0, 0));
    light.show();
    delay(1);
  }
  for (int b = 255; b > 0; b--) {
    analogWrite(BLUE, b);
    light.setPixelColor(0, light.Color(b, 0, 0));
    light.show();
    delay(1);
  }
  delay(10);
}


void rainbowLight1 () {
  analogWrite(RED, 255);
  analogWrite(GREEN, 0);
  analogWrite(BLUE, 0);
  analogWrite(WHITE, 0);

  for (int b = 0; b < 255; b++) {
    analogWrite(RED, 255 - b);
    analogWrite(GREEN, b);
    light.setPixelColor(0, light.Color(255 - b, b, 0));
    light.show();
    delay(1);
  }
}


void rainbowLight2 () {
  analogWrite(RED, 0);
  analogWrite(GREEN, 255);
  analogWrite(BLUE, 0);
  for (int b = 0; b < 255; b++) {
    analogWrite(GREEN, 255 - b);
    analogWrite(BLUE, b);
    light.setPixelColor(0, light.Color(0, 255 - b, b));
    light.show();
    delay(1);

  }
}


void rainbowLight3 () {
  analogWrite(RED, 0);
  analogWrite(GREEN, 0);
  analogWrite(BLUE, 255);
  for (int b = 0; b < 255; b++) {
    analogWrite(BLUE, 255 - b);
    analogWrite(RED, b);
    light.setPixelColor(0, light.Color(b, 0, 255 - b));
    light.show();
    delay(1);
  }
}


void playOdeToJoy() {
  mySpeaker.beep(F2c, 250,  .75);
  delay(10);

  mySpeaker.beep(F2c, 250,  .75);
  delay(10);

  mySpeaker.beep(G2c, 250,  .75);
  delay(10);

  mySpeaker.beep(A2c, 250,  .75);
  delay(10);

  mySpeaker.beep(A2c, 250,  .75);
  delay(10);

  mySpeaker.beep(G2c, 250,  .75);
  delay(10);

  mySpeaker.beep(F2c, 250,  .75);
  delay(10);

  mySpeaker.beep(E2c, 250,  .75);
  delay(10);

  mySpeaker.beep(D1c, 250,  .75);
  delay(10);

  mySpeaker.beep(D1c, 250,  .75);
  delay(10);

  mySpeaker.beep(E2c, 250,  .75);
  delay(10);

  mySpeaker.beep(F2c, 250,  .75);
  delay(10);

  mySpeaker.beep(F2c, 375,  .75);
  delay(10);

  mySpeaker.beep(E2c, 150,  .75);
  delay(10);

  mySpeaker.beep(E2c, 500,  .75 );
  delay(10);
}

void playFifth () {

  mySpeaker.beep(E2c, 250, 0.5);
  delay(10);

  mySpeaker.beep(E2c, 250, 0.5);
  delay(10);

  mySpeaker.beep(E2c, 250, 0.5);
  delay(10);

  mySpeaker.beep(C1c, 1200, 0.5);
  delay(10);

  delay(1000);

  mySpeaker.beep(D1c, 250, 0.5);
  delay(10);

  mySpeaker.beep(D1c, 250, 0.5);
  delay(10);

  mySpeaker.beep(D1c, 250, 0.5);
  delay(10);

  mySpeaker.beep(B1c, 1200, 0.5);
  delay(10);
}


void playMario1 () {
  for (int x = 0; x < 8; x++) {
    int result = x % 2;
    Serial.println(result);
    if (result == 1) {
      Serial.println("blue");
      analogWrite(RED, 0);
      analogWrite(GREEN, 0);
      analogWrite(BLUE, 255);
    light.setPixelColor(0, light.Color(0, 0, 255));
    light.show();
    }
    if (result == 0) {
      Serial.println("red");
      analogWrite(RED, 255);
      analogWrite(GREEN, 0);
      analogWrite(BLUE, 0);
    light.setPixelColor(0, light.Color(255, 0, 0));
    light.show();
    }
    mySpeaker.beep(lineTwoNotes[x], speed * (lineTwoTimes[x] - 10), 0.75);
    delay(10);
  }
  delay(100);
}

void playMario2 () {
  for (int x = 0; x < 8; x++) {
    int result = x % 2;
    Serial.println(result);
    if (result == 1) {
      Serial.println("blue");
      analogWrite(RED, 0);
      analogWrite(GREEN, 0);
      analogWrite(BLUE, 255);
    light.setPixelColor(0, light.Color(0, 0, 255));
    light.show();
    }
    if (result == 0) {
      Serial.println("red");
      analogWrite(RED, 255);
      analogWrite(GREEN, 0);
      analogWrite(BLUE, 0);
    light.setPixelColor(0, light.Color(255, 0, 0));
    light.show();
    }
    mySpeaker.beep(lineThreeNotes[x], speed * (lineThreeTimes[x] - 10), 0.75);
    delay(10);
  }
  delay(100);
}

void playMario3 () {
  for (int x = 0; x < 11; x++) {
    int result = x % 2;
    Serial.println(result);
    if (result == 1) {
      Serial.println("blue");
      analogWrite(RED, 0);
      analogWrite(GREEN, 0);
      analogWrite(BLUE, 255);
    light.setPixelColor(0, light.Color(0, 0, 255));
    light.show();
    }
    if (result == 0) {
      Serial.println("red");
      analogWrite(RED, 255);
      analogWrite(GREEN, 0);
      analogWrite(BLUE, 0);
    light.setPixelColor(0, light.Color(255, 0, 0));
    light.show();
    }
    mySpeaker.beep(lineFourNotes[x], speed * (lineFourTimes[x] - 10), 0.75);
    delay(10);
  }
  delay(100);
}

void visionlight () {

  for (int i = 0; i < 24; i++) {
     strip.setPixelColor(i, strip.Color( 0, 255, 0));
  }
  strip.show();
}


// code for roborio requesting eventstatus with single example for the ultrasonic sensor
//void requestEvent() { //THIS IS THE SENSOR EVENT
//
//  unsigned int uS1 = sonar.ping(); // Send ping, get ping time in microseconds (uS).
//  delay(50);  // Wait 500ms between pings (about 2 pings/sec). 29ms should be the shortest delay between pings.
//  unsigned int uS2 = sonar.ping(); // Send ping, get ping time in microseconds (uS).
//  delay(50);  // Wait 500ms between pings (about 2 pings/sec). 29ms should be the shortest delay between pings.
//  unsigned int uS3 = sonar.ping(); // Send ping, get ping time in microseconds (uS).
//
//  unsigned int uS = (uS1 + uS2 + uS3) / 3;
//
//  Serial.print("Ping: ");
//  Serial.print(uS / US_ROUNDTRIP_CM); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
//  Serial.print("cm");
//  if (uS / US_ROUNDTRIP_CM < 10 and uS / US_ROUNDTRIP_CM > 2) {
//    //    Serial.println("SPROCKET");
//    Wire.write("SPROCKET");
//  } else {
//    Serial.println("EMPTY   ");
//  }
//    Wire.write("EMPTY   ");
//  }
//}

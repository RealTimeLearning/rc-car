/*
* Car driving code created by Stephen Baker
* Version 0.8: Line-Following
* "CH-" to turn OFF ultrasonic 
* "CH " for Self-Stopping mode
* "CH+" for Follow-Me mode
* "Next" for Line Following
*/

#include <IRremote.h>

#define RECV_PIN 11
IRrecv irrecv(RECV_PIN);
decode_results results;

// Setup motor controller
// motor one
#define enA 10 
#define in1 9
#define in2 8
// motor two
#define enB 5
#define in3 7
#define in4 6

// Ultrasonic
#define trigPin 12
#define echoPin 13
long duration, distance;

// Display
//#define MAX7219_DIN 4
//#define MAX7219_CS  3
//#define MAX7219_CLK 2
int ones, tens, hundreds;

//Line following
#define lightsensor1 3
#define lightsensor2 4
int lightval1 = 0;
int lightval2 = 0;

//Other variables
int spd = 100;  // inital speed = 100
int mode = 0;   

enum {  MAX7219_REG_DECODE    = 0x09,
        MAX7219_REG_INTENSITY = 0x0A,
        MAX7219_REG_SCANLIMIT = 0x0B,
        MAX7219_REG_SHUTDOWN  = 0x0C,
        MAX7219_REG_DISPTEST  = 0x0F
     };


void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  
  // set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  // Ultrasonic Pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Display
  //digitalWrite(MAX7219_CS, HIGH);
  //pinMode(MAX7219_DIN, OUTPUT);
  //pinMode(MAX7219_CS, OUTPUT);
  //pinMode(MAX7219_CLK, OUTPUT);
  
  // Line following
  pinMode(lightsensor1, INPUT);
  pinMode(lightsensor2, INPUT);
}


/* ---------------------------- // ---------------------------- */

// -----------------------------------------------
// Motor Movements: Forward, Reverse, Halt
// -----------------------------------------------
void Forward() //look 
{
  digitalWrite(in1, HIGH); 
  digitalWrite(in2, LOW); 
  analogWrite(enA, spd); 
  digitalWrite(in3, HIGH);  
  digitalWrite(in4, LOW);
  analogWrite(enB, spd);
}
void Reverse()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, spd);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB, spd);
}
void Halt()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}


// -----------------------------------------------
// Motor Movements: Right, Left
// -----------------------------------------------
void Right()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, 100);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, 125);
}
void Left()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, 125);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB, 100);
}


// -----------------------------------------------
// Speed counter
// -----------------------------------------------
void speedplus() {
  if (spd < 220)
  {
    spd = spd + 10;
  }
  Serial.print(spd);
}
void speedminus() {
  if (spd > 50) 
  {
    spd = spd - 10;
  }
  Serial.print(spd);
}


// -----------------------------------------------
// Ultrasonic
// -----------------------------------------------
void Ultrasonic()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;
}


// -----------------------------------------------
// 7 Segment Display
// -----------------------------------------------
//void output(byte address, byte data)
//{
//  digitalWrite(MAX7219_CS, LOW);
//  shiftOut(MAX7219_DIN, MAX7219_CLK, MSBFIRST, address);
//  shiftOut(MAX7219_DIN, MAX7219_CLK, MSBFIRST, data);
//  digitalWrite(MAX7219_CS, HIGH);
//}
//void DisplayDistance()
//{
//  Ultrasonic();
//  hundreds = distance / 100;
//  tens = (distance - hundreds * 100) / 10;
//  ones = distance % 10;
//  output(MAX7219_REG_DISPTEST, 0x00); //display test register - test mode off
//  output(MAX7219_REG_SHUTDOWN, 0x01); //shutdown register - normal operation
//  output(MAX7219_REG_INTENSITY, 0x06); //intensity register
//  output(MAX7219_REG_DECODE, 0xff); //decode mode register - CodeB decode all digits
//  output(MAX7219_REG_SCANLIMIT, 0x02); //scan limit register - display digits 0 & 1 only
//  output(0x03, hundreds);
//  output(0x02, tens);
//  output(0x01, ones); //digit 0 (rightmost digit) data
//  Serial.print(hundreds);
//  Serial.print(tens);
//  Serial.print(ones);
//  Serial.println("\n");
//  delay(50);
//  output(MAX7219_REG_SHUTDOWN, 0x00);   //shutdown
//}


// -----------------------------------------------
// Self Stopping
// -----------------------------------------------
void Selfstop()
{
  Ultrasonic();
  if (distance <= 0 || distance > 150) {
    Serial.println("Far Far Away");
  }
  else if (distance >= 10) {
    Serial.print(distance);
    Serial.println("cm");
    //Forward();
  }
  else {
    Halt();
    delay(1000);
    Reverse();
    delay(500);
    Right();
  }
}


// -----------------------------------------------
// Follow Me
// -----------------------------------------------
void FollowMe() {
  Ultrasonic();
  if (distance > 40) {
    Halt();
  }
  else if (distance > 10) {
    Serial.println("Fooollooow~~~~");
    Forward();
  }
  else {
    Serial.println("Tooooo clooosssee!!!!");
    Reverse();
  }
}

// -----------------------------------------------
// Table top robot
// -----------------------------------------------
void TableTop(){

lightval1 = digitalRead(lightsensor1);
//Serial.println(lightval1);

if (lightval1 == 0){ 
    Forward();
    delay(30);
  }
else {
    Halt();
    delay(100);
    Reverse();
    delay(500);
    if (random(0,2)){ //chooses a random value between 0 and 1
      Left();
      }
     else{
      Right();
      }
    
    delay(random(1000,3000)); //turn a random amount
}
 
}


// -----------------------------------------------
// Line Following
// -----------------------------------------------
void LineFollow() {
lightval1 = digitalRead(lightsensor1);
//Serial.println(lightval1);
lightval2 = digitalRead(lightsensor2);
//Serial.println(lightval2);

if (lightval1 == 1 && lightval2 == 1){ // forward
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(enA, 75);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(enB, 75);
    delay(30);
  }
else if (lightval1 == 1 && lightval2 == 0) { //right
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    analogWrite(enA, 85);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(enB, 110);
    delay(30);
  }
else if (lightval1 == 0 && lightval2 == 1) { //left
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(enA, 100);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    analogWrite(enB, 75);
    delay(30);
}
else if (lightval1 == 0 && lightval2 == 0) { //right
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    analogWrite(enA, 85);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(enB, 110);
    delay(30);
}
}


/* ---------------------------- // ---------------------------- */

// -----------------------------------------------
// Main Loop
// -----------------------------------------------
void loop() {
  if (irrecv.decode(&results)) {
    switch (results.value) {
      // Car mp3 remote
      case 0xFFA25D: mode = 0; Serial.println("CH-: Normal Driving"); break; // CH-
      case 0xFF629D: mode = 1; Serial.println("CH : Self-stopping mode"); break; // CH
      case 0xFFE21D: mode = 2; Serial.println("CH+: Follow me"); break; // CH+
      case 0xFF22DD: mode = 3; Serial.println("Prev: Table top robot"); break; // |<<
      case 0xFF02FD: mode = 4; Serial.println("Next: Line following"); break; // >>|
      case 0xFFC23D: Serial.println("Play / Pause"); break; // |>||
      case 0xFFE01F: speedminus(); Forward(); Serial.println("\t-: Decrease Speed"); break; // -
      case 0xFFA857: speedplus(); Forward(); Serial.println("\t+: Increase Speed"); break; // +
      case 0xFF906F: Serial.println("EQ"); break; // EQ
      case 0xFF9867: Serial.println("100+"); break; // 100+
      case 0xFFB04F: Serial.println("200+"); break; // 200+

      case 0xFF6897: Serial.println("0"); break; // 0
      case 0xFF30CF: Serial.println("1"); break; // 1
      case 0xFF18E7: Forward(); Serial.println("\t2: Forward"); break; // 2
      case 0xFF7A85: Serial.println("3"); break; // 3
      case 0xFF10EF: Left(); Serial.println("4: Left"); break; // 4
      case 0xFF38C7: Halt(); mode = 0; Serial.println("5: Stop"); break; // 5
      case 0xFF5AA5: Right(); Serial.println("6: Right"); break; // 6
      case 0xFF42BD: Serial.println("7"); break; // 7
      case 0xFF4AB5: Reverse(); Serial.print(spd); Serial.println("\t8: Reverse"); break; // 8
      case 0xFF52AD: Serial.println("9"); break; // 5
    }
    
    irrecv.resume(); // Receive the next value
  }
  
  //DisplayDistance();
  
  if (mode == 1) {
    Selfstop();
    
  }
  if (mode == 2) {
    FollowMe();
  }

  if (mode == 3) {
    TableTop();
  }
  
  if (mode == 4) {
    LineFollow();
  }

  
}

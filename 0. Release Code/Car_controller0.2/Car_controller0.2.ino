/*
* Car driving code created by Stephen Baker
* Version 0.2: IR + Forward + Reverse + Halt
*/

//code added to decode buttons from Duinotech remote
// only slightly modified from Library example
#include <IRremote.h>
int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;
// Setup motor controller
// motor one
int enA = 10;
int in1 = 9;
int in2 = 8;
// motor two
int enB = 5;
int in3 = 7;
int in4 = 6;


// -----------------------------------------------
// Setup
// -----------------------------------------------
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
}


// -----------------------------------------------
// Motor Movements: Forward, Reverse, Halt
// -----------------------------------------------
void Forward()
{
  // this function will run the motors forward
  // turn on motor A
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enA, 100);
  // turn on motor B
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enB, 100);
}
void Reverse()
{
  // this function will run the motors Reverse
  // turn on motor A
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  // set speed to 200 out of possible range 0~255
  analogWrite(enA, 100);
  // turn on motor B
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  // set speed to 200 out of possible range 0~255
  analogWrite(enB, 100);
}
void Halt()
{
  // this function will stop the motors
  // stop motor A
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  // stop motor B
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}


// -----------------------------------------------
// Main Loop
// -----------------------------------------------
void loop() {
  if (irrecv.decode(&results)) {
    //Serial.println(results.value, HEX);
    switch (results.value) {
      // Car mp3 remote
      case 0xFFA25D: Serial.println("CH-"); break; // CH-
      case 0xFF629D: Serial.println("CH "); break; // CH
      case 0xFFE21D: Serial.println("CH+"); break; // CH+
      case 0xFF22DD: Serial.println("Prev"); break; // |<<
      case 0xFF02FD: Serial.println("Next"); break; // >>|
      case 0xFFC23D: Serial.println("Play / Pause"); break; // |>||
      case 0xFFE01F: Serial.println("Vol -"); break; // -
      case 0xFFA857: Serial.println("Vol +"); break; // +
      case 0xFF906F: Serial.println("EQ"); break; // EQ
      case 0xFF9867: Serial.println("100+"); break; // 100+
      case 0xFFB04F: Serial.println("200+"); break; // 200+

      case 0xFF6897: Serial.println("0"); break; // 0
      case 0xFF30CF: Serial.println("1"); break; // 1
      case 0xFF18E7: Forward(); Serial.println("2: Forward"); break; // 2
      case 0xFF7A85: Serial.println("3"); break; // 3
      case 0xFF10EF: Serial.println("4"); break; // 4
      case 0xFF38C7: Halt(); Serial.println("5: Stop"); break; // 5
      case 0xFF5AA5: Serial.println("6"); break; // 6
      case 0xFF42BD: Serial.println("7"); break; // 7
      case 0xFF4AB5: Reverse(); Serial.println("8: Reverse"); break; // 8
      case 0xFF52AD: Serial.println("9"); break; // 9
    }
    irrecv.resume(); // Receive the next value
  }
}


/*
* Car driving code created by Stephen Baker
* Version 0.4: Speed control + & -
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
int counter = 100;  // inital speed = 100


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


/* ---------------------------- // ---------------------------- */

// -----------------------------------------------
// Motor Movements: Forward, Reverse, Halt
// -----------------------------------------------
void Forward()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, counter);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, counter);
}
void Reverse()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, counter);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB, counter);
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
  // For 90 degree turn, uncomment the following lines.
  // Adjust delay time if speed is changed.
  delay(850);
  Halt();
  delayMicroseconds(100);
  Forward();
}
void Left()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, 125);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB, 100);
  // For 90 degree turn, uncomment the following lines.
  // Adjust delay time if speed is changed.
  delay(850);
  Halt();
  delayMicroseconds(100);
  Forward();
}


// -----------------------------------------------
// Speed counter
// -----------------------------------------------
void counterplus() {
  if (counter < 220)
  {
    counter = counter + 10;
  }
  Serial.print(counter);
}
void counterminus() {
  if (counter > 50) 
  {
    counter = counter - 10;
  }
  Serial.print(counter);
}



/* ---------------------------- // ---------------------------- */

// -----------------------------------------------
// Main Loop
// -----------------------------------------------
void loop() {
  if (irrecv.decode(&results)) {
    switch (results.value) {
      // Car mp3 remote
      case 0xFFA25D: Serial.println("CH-"); break; // CH-
      case 0xFF629D: Serial.println("CH "); break; // CH
      case 0xFFE21D: Serial.println("CH+"); break; // CH+
      case 0xFF22DD: Serial.println("Prev"); break; // |<<
      case 0xFF02FD: Serial.println("Next"); break; // >>|
      case 0xFFC23D: Serial.println("Play / Pause"); break; // |>||
      case 0xFFE01F: counterminus(); Forward(); Serial.println("\t-: Decrease Speed"); break; // -
      case 0xFFA857: counterplus(); Forward(); Serial.println("\t+: Increase Speed"); break; // +
      case 0xFF906F: Serial.println("EQ"); break; // EQ
      case 0xFF9867: Serial.println("100+"); break; // 100+
      case 0xFFB04F: Serial.println("200+"); break; // 200+

      case 0xFF6897: Serial.println("0"); break; // 0
      case 0xFF30CF: Serial.println("1"); break; // 1
      case 0xFF18E7: Forward(); Serial.print(counter); Serial.println("\t2: Forward"); break; // 2
      case 0xFF7A85: Serial.println("3"); break; // 3
      case 0xFF10EF: Left(); Serial.println("4: Left"); break; // 4
      case 0xFF38C7: Halt(); Serial.println("5: Stop"); break; // 5
      case 0xFF5AA5: Right(); Serial.println("6: Right"); break; // 6
      case 0xFF42BD: Serial.println("7"); break; // 7
      case 0xFF4AB5: Reverse(); Serial.print(counter); Serial.println("\t8: Reverse"); break; // 8
      case 0xFF52AD: Serial.println("9"); break; // 5
    }
    irrecv.resume(); // Receive the next value
  }
}





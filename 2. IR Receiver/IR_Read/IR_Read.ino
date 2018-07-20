/*
* IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
* An IR detector/demodulator must be connected to the input RECV_PIN.
* Version 0.1 July, 2009
* Copyright 2009 Ken Shirriff
* http://arcfn.com
*/
//code added to decode buttons from Duinotech remote
// only slightly modified from Library example
#include <IRremote.h>
int RECV_PIN = 11;        // The pin that the signal pin of IR sensor is connected to
IRrecv irrecv(RECV_PIN);  // Create a new receiver object that would decode signals to key codes
decode_results results;   // A variable that receiver use to put the key codes into
void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}
void loop() {
  if (irrecv.decode(&results)) {          // Decode the button code and put it is "results" variable
    Serial.println(results.value, HEX);   // Print the code as a hexadecimal value
    irrecv.resume(); // Receive the next value
  }
  delay(100);
}

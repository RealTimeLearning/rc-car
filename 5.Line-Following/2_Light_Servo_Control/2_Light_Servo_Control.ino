#include <Servo.h>

int lightsensor = 4;
int lightval = 0;

Servo myservo;

void setup() {
  // put your setup code here, to run once:
pinMode(lightsensor, INPUT);
myservo.attach(3);

myservo.write(90);

Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
lightval = digitalRead(lightsensor);
Serial.println(lightval);
if (lightval == 1){
  myservo.write(0);
  Serial.println("White");
  }
else {
  myservo.write(180);
  Serial.println("Black");
  }

}

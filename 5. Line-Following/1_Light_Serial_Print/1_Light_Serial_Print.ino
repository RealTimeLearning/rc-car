int lightsensor = 4;
int lightval = 0;

void setup() {
  // put your setup code here, to run once:
pinMode(lightsensor, INPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
lightval = digitalRead(lightsensor);
Serial.println(lightval);
if (lightval == 1){
  Serial.println("White");
  }
else {
  Serial.println("Black");
  }

}

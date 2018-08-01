#define MAX7219_DIN 4
#define MAX7219_CS  3
#define MAX7219_CLK 2
#define trigPin 12
#define echoPin 13

long duration, distance;
int remainder, quotient;


// enumerate the MAX7219 registers
// See MAX7219 Datasheet, Table 2, page 7
enum {  MAX7219_REG_DECODE    = 0x09,
        MAX7219_REG_INTENSITY = 0x0A,
        MAX7219_REG_SCANLIMIT = 0x0B,
        MAX7219_REG_SHUTDOWN  = 0x0C,
        MAX7219_REG_DISPTEST  = 0x0F
     };
 

void setup() {
  Serial.begin(9600);
  digitalWrite(MAX7219_CS, HIGH);
  pinMode(MAX7219_DIN, OUTPUT);
  pinMode(MAX7219_CS, OUTPUT);
  pinMode(MAX7219_CLK, OUTPUT);
  // Ultrasonic Pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}


void output(byte address, byte data)
{
  digitalWrite(MAX7219_CS, LOW);
  shiftOut(MAX7219_DIN, MAX7219_CLK, MSBFIRST, address);
  shiftOut(MAX7219_DIN, MAX7219_CLK, MSBFIRST, data);
  digitalWrite(MAX7219_CS, HIGH);
}


void Ultrasonic()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;
  //Serial.println("Ultrasonic");
}


void DisplayDistance()
{
  Ultrasonic();
  remainder = distance % 10;
  quotient = distance / 10;
  output(MAX7219_REG_DECODE, 0xff); //decode mode register - CodeB decode all digits
  output(MAX7219_REG_SCANLIMIT, 0x01); //scan limit register - display digits 0 & 1 only
  output(0x02, quotient);
  output(0x01, remainder); //digit 0 (rightmost digit) data
  Serial.print(quotient);
  Serial.print(remainder);
  Serial.println("\n");
  delay(100);
}


void loop() {
  output(MAX7219_REG_DISPTEST, 0x00); //display test register - test mode off
  output(MAX7219_REG_SHUTDOWN, 0x01); //shutdown register - normal operation
  output(MAX7219_REG_INTENSITY, 0x06); //intensity register

  DisplayDistance();

  output(MAX7219_REG_SHUTDOWN, 0x00);   //shutdown
}

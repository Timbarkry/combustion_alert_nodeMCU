#include <Servo.h> 
Servo myServo;

void setup() {

pinMode(D1, OUTPUT);
pinMode(A0, INPUT); 
  Serial.begin(9600);
  
  
  
  // put your setup code here, to run once:

}

void loop() {
  
 int value = analogRead(A0);
  myServo.attach(D1);
  int value2 = map(value, 150, 850, 0, 180); 
  myServo.write(value2);
  
  Serial.println(value);
  
  // put your main code here, to run repeatedly:

}

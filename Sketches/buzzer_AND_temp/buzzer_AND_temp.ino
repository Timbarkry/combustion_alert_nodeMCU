#include <DHTesp.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);


int piezoPin = D7; 



void setup() {
  dht.setup(D4, DHTesp::DHT11); 
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(piezoPin, OUTPUT);
  delay(5000);
  

}

void loop() {
  // put your main code here, to run repeatedly:
  int temp = dht.readTemperature();
  int humd = dht.readHumidity(); 
  Serial.print(temp);
  if (temp > 25) {
    digitalWrite(piezoPin, HIGH);
    {tone(9,3047,400);
    delay(1000);
    noTone(8);
    delay(100);
  }
  delay(1000);
  Serial.print("ON T=");
  }
  else {digitalWrite(piezoPin, LOW); 

}

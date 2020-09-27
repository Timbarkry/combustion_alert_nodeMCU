#include <DHTesp.h>;  
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
DHTesp dht;

int piezoPin = D7;
float humidity = dht.getHumidity(); 
float temperature = dht.getTemperature();

void setup() {

  Serial.begin(9600);
  pinMode(piezoPin, OUTPUT);  
  dht.setup(D4, DHTesp::DHT11); 
  lcd.init(); 
  lcd.backlight();
  lcd.setCursor(0,0);
    delay(500);

}

void loop() {
delay(dht.getMinimumSamplingPeriod());
   
   String status_String = dht.getStatusString();
   if (status_String == "OK") {  

lcd.setCursor(0,0);
lcd.print("Temperature:");
lcd.print(temperature);
lcd.setCursor(0,1);
lcd.print("Humididty:");
lcd.print(humidity);
  delay(500);
  
  delay(dht.getMinimumSamplingPeriod());  
  
  }
  Serial.print(temperature); 
  if (temperature > 25) {
    digitalWrite(piezoPin, HIGH);
    {tone(7,3047,400);
    delay(1000);
    noTone(8);
    delay(100);
    }
    delay(1000);
    Serial.print("ON T="); 
   }
   else {digitalWrite(piezoPin, LOW);
   Serial.print("OFF T="); 
   }
}

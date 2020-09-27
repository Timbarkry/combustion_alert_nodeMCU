#include <DHTesp.h>;  
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
DHTesp dht;


void setup() {
 
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

   float humidity = dht.getHumidity(); 
   float temperature = dht.getTemperature();
   
lcd.setCursor(0,0);
lcd.print("Temperature:");
lcd.print(temperature);
lcd.setCursor(0,1);
lcd.print("Humididty:");
lcd.print(humidity);
  delay(500);
  
  delay(dht.getMinimumSamplingPeriod());
     
   }
}

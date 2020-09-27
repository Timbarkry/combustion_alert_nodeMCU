#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
pinMode(A0, INPUT);
lcd.init(); 
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Mama wills du Schokolade?");
  lcd.setCursor(0,1);
  lcd.print("Ja ich will Schokolade essen!");
  
  // put your setup code here, to run once:

}

void loop() {
  int value = analogRead(A0);
  lcd.scrollDisplayLeft();
  delay(1500);
 
    // put your main code here, to run repeatedly:

}

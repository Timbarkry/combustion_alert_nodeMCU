/*  ___   ___  ___  _   _  ___   ___   ____ ___  ____  
 * / _ \ /___)/ _ \| | | |/ _ \ / _ \ / ___) _ \|    \ 
 *| |_| |___ | |_| | |_| | |_| | |_| ( (__| |_| | | | |
 * \___/(___/ \___/ \__  |\___/ \___(_)____)___/|_|_|_|
 *                  (____/    
 * www.osoyoo.com IC2 Liquid Crysal Testing program
 * program tutorial : http://osoyoo.com/?p=72
 *  Copyright John Yu
 */

#include <ESP8266WiFi.h>   
#include <Wire.h>
#include <PubSubClient.h>
#include <LiquidCrystal_I2C.h>
 
LiquidCrystal_I2C lcd(0x27,16,2);  // run ic2_scanner sketch and get the IC2 address, which is 0x3f in my case,it could be 0x3f in many cases
 
void setup()
{
  lcd.init();                      // initialize the lcd
}
 
void loop()
{
// set cursor to first line
lcd.setCursor(0, 0);

// Print a message to the LCD.
  lcd.backlight();
  lcd.print("Hello!");
  lcd.setCursor(0,1);
  lcd.print("Osoyoo.com");
}

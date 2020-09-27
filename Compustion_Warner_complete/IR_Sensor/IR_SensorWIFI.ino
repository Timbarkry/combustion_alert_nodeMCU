
/*************************************************** 
  This is a library example for the MLX90614 Temp Sensor

  Designed specifically to work with the MLX90614 sensors in the
  adafruit shop
  ----> https://www.adafruit.com/products/1747 3V version
  ----> https://www.adafruit.com/products/1748 5V version

  These sensors use I2C to communicate, 2 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include <Adafruit_MLX90614.h>
#define BUZZER_PIN  D4

ESP8266WebServer server(80);
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

float temp=0;

long lastMillis = 0;
long currentMillis;

void handleRoot() {
  //Send the data of the poti to the client as string
  //PotiValue is parsed to string in decimal format
  //first parameter: success code (200). See http codes
  //second parameter: type of data
  //third parameter: Text we want to send
  server.send(200, "text/plain", String(mlx.readObjectTempC(), DEC));
}

//Method for handling requests on /SetLedState/
void handleSetLedState(){
  //Confirm the put request
  server.send(200); 
}

//Method for handling requests on /SetLedMode/
void handleSetMode(){
  //Confirm the put request
  server.send(200);
}




void setup() {
  Serial.begin(9600);
  Serial.println("Adafruit MLX90614 test");  
  mlx.begin(); 
   
  lcd.init(); 
  lcd.backlight();
  lcd.setCursor(0,0);
    delay(500);

  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

   WiFi.mode(WIFI_STA);
   WiFi.begin("FabLabGast", "FabLabSiegen");

   Serial.println("");

   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("Connected to FabLabGast");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/SetLedState/",HTTP_PUT, handleSetLedState);
  server.on("/SetMode/",HTTP_PUT, handleSetMode);

  server.begin();
  
  Serial.println("HTTP server started");
  
}

void loop() {
  lcd.setCursor(0,0);
  lcd.print("Warner ready...");
  Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
  lcd.setCursor(0,1);
  lcd.print ("Object = ");
  temp = mlx.readObjectTempC();
  lcd.print(temp);
  lcd.print(" C"); 
    Serial.println(WiFi.localIP());

  currentMillis = millis();
  if( currentMillis > lastMillis+50)
  {
    if (mlx.readObjectTempC() > 40) {
        digitalWrite(BUZZER_PIN, HIGH); 
        {tone(D4, 3047, 400);
        Serial.println(" Turn On BUZZER! ");
        delay(150);
        }
        lcd.setCursor(0,0);
        lcd.print(" ");
        lcd.print("!!! ALERT !!!");
        } else {
          digitalWrite(BUZZER_PIN, LOW);
        }
        lastMillis = currentMillis;
  }
  server.handleClient();
  Serial.println();
  delay(500);
}

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

int potiValue;

ESP8266WebServer server(80);

void handleRoot ()
{
 
  server.send(200, "text/plain", String(analogRead(AO));
}

void setup() {
  // put your setup code here, to run once:
  pinMode(DO,OUTPUT);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin("FabLabGast","FabLabSiegen");
  
  while(WiFi.status() != WL_CONNECTED)
 }

  delay(500);
  Serial.print(".");

 }
  Serial.printIn(".");
  Serial.printIn("Connected to FabLabGast");

  Serial.printIn(WiFi.localIP());

  server.on("/", handleRoot)


void loop() {
  // put your main code here, to run repeatedly:
  potiValue = analogRead(AO);

  if (potiValue > 512)
  {
    digitalWrite(DO,HIGH);
  }
  else
  {
    digitalWrite(DO,LOW); 
  }
  

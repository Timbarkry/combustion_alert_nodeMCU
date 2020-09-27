#include <DHTesp.h>;  
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Define NodeMCU D2 pin  connect to Piezo Buzzer
#define BUZZER_PIN  D7
LiquidCrystal_I2C lcd(0x27, 16, 2);
DHTesp dht;

// Update these with values suitable for your network.
const char* ssid = "FRITZ!Box 7430 DE";
const char* password = "79268819088798207933";
const char* mqtt_server = "broker.mqttdashboard.com";
//const char* mqtt_server = "iot.eclipse.org";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup_wifi() {
   delay(100);
  // We start by connecting to a WiFi network
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) 
    {
      delay(500);
      Serial.print(".");
    }
  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) 
{
  Serial.print("Command from MQTT broker is : [");
  Serial.print(topic);
  int p =(char)payload[0]-'0';
  // if MQTT comes a 0 turn off LED on D7
  if(p==0) 
  {
    digitalWrite(BUZZER_PIN, LOW); 
    Serial.println(" Turn Off BUZZER! ");
  } 
  // if MQTT comes a 1, turn on BUZZER on pin D7
  if(p==1)
  {
    digitalWrite(BUZZER_PIN, HIGH); 
    Serial.println(" Turn On BUZZER! ");
  }
  Serial.println();
} //end callback

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) 
  {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    //if you MQTT broker has clientID,username and password
    //please change following line to    if (client.connect(clientId,userName,passWord))
    if (client.connect(clientId.c_str()))
    {
      Serial.println("connected");
     //once connected to MQTT broker, subscribe command if any
      client.subscribe("OsoyooCommand");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 6 seconds before retrying
      delay(6000);
    }
  }
} //end reconnect()

void setup() {
  
  dht.setup(D4, DHTesp::DHT11); 
  lcd.init(); 
  lcd.backlight();
  lcd.setCursor(0,0);
    delay(500);
    // Main for the buzzer function 
    Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW); 
    

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

   if (!client.connected()) {
    reconnect();
  }
  client.setCallback(callback);
  client.loop();
}

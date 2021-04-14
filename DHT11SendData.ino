#include <ESP8266WiFi.h>
#include <DHT.h>
#include <ThingSpeak.h>

DHT dht(D5, DHT11);

WiFiClient client;

long myChannelNumber = <Your channel ID>;
const char myWriteAPIKey[] = "<Your channel write API key>";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.begin("<SSID of your WiFi network>", "<Password of your WiFi network>");
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print("..");
  }
  Serial.println();
  Serial.println("NodeMCU is connected!");
  Serial.println(WiFi.localIP());
  dht.begin();
  ThingSpeak.begin(client);
}

void loop() {
  // put your main code here, to run repeatedly:
  float t = dht.readTemperature();
  Serial.println("Temperature: " + (String) t);
  ThingSpeak.writeField(myChannelNumber, 2, t, myWriteAPIKey);
  delay(20000);
}

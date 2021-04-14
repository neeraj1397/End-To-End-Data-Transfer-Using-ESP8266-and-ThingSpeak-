#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <DNSServer.h>
#include <WiFiManager.h>

String readAPIKey = "<Your channel read API key>"; // Read API Key of ThingSpeak channel
String channelId = "<Your channel ID>";
String fieldNo = "1";
String resultCount = "1";
float temperature = 0;

//"http://api.thingspeak.com/channels/1024134/fields/2.json?api_key=702L9HBEV9F88HHV&results=1"


void setup(){
  Serial.begin(115200);
  Serial.flush();
  pinMode(D0, OUTPUT);
  wificonnect();
}


void loop(){
  temperature = GETreceive();
  if(temperature > 30){
    digitalWrite(D0, HIGH);
  }
  else{
    digitalWrite(D0, LOW);
  }
}


void wificonnect(){
  WiFiManager wifiManager;
  wifiManager.autoConnect("RS_Sensor_Node");
  Serial.println("Connected to RS_Sensor_Node :)");
}


float GETreceive(){
  HTTPClient http;
  float temperature = 0;
  Serial.print("[HTTP] begin...\n");
  //"http://api.thingspeak.com/channels/963373/fields/1.json?api_key=28WYJLR74BJ9ZKAT&results=1"
  String url = "http://api.thingspeak.com/channels/";
  url += channelId;
  url += "/fields/";
  url += fieldNo;
  url += ".json?api_key=";
  url += readAPIKey;
  url += "&results=";
  url += resultCount;
  Serial.println(url);
  http.begin(url);
  Serial.print("[HTTP] GET...\n");
  int httpCode = http.GET();
  if(httpCode > 0){
    Serial.printf("[HTTP] GET... code %d\n", httpCode);
    if(httpCode == HTTP_CODE_OK){
      String payload = http.getString();
      Serial.println(payload);
      int begin_b = payload.indexOf("\"entry_id");
      String dataStr = payload.substring(begin_b+25, begin_b+30);
      distance = dataStr.toFloat();
      Serial.print("Temperature: ");
      Serial.println(temperature);
    }
  }
  else{
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
  http.end();
  delay(20000);
  return temperature;
}

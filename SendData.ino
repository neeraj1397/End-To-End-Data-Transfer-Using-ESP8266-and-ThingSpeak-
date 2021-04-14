#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <DNSServer.h>
#include <WiFiManager.h>

WiFiClient client;

String writeApiKey = "<Write API key of your channel>"; // Write API Key of your Thingspeak channel.
const char* server = "api.thingspeak.com";
int fieldNo = 1;


void setup(){
  Serial.begin(115200);
  delay(1);
  Serial.flush();
  wificonnect();
}


void loop(){
  int randomData = random(0,99);
  POSTSend(randomData);
}


void wificonnect(){
  WiFiManager wifiManager;
  wifiManager.autoConnect("RS_Sensor_Node");
  Serial.println("Connected to RS_Sensor_Node :)");
}


void POSTSend(int data){
  if(client.connect(server, 80)){
    String postStr = writeApiKey;
    postStr += "&field";
    postStr += fieldNo;
    postStr += "=";
    postStr += data;
    postStr += "\r\n\r\n";
    client.print("POST /update HTTP/1.1\n");
    client.print("HOST: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: "+writeApiKey+"\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n"); // Example from Mathworks
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
    delay(1000);
    String line="";
    while(client.available()){
      line = client.readStringUntil('\r');
      Serial.print(line);
    }
  }
  client.stop();
  Serial.println("Waiting...");
  delay(20000);
}

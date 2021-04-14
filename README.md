# End-To-End-Data-Transfer-Using-ESP8266-and-ThingSpeak-
This is a beginner friendly IoT project which uses ThingSpeak cloud platform to collect and analyze sensor data. Based on the obtained sensor data, we actuate other IoT devices.

Components: NodeMCU (2), DHT11 Temperature and Humidity Sensor, LED (1).
Libraries: WiFiManager, ThingSpeak, ESP8266HTTPClient, ESP8266WiFi.h.

A NodeMCU uploads random or temperature data acquired by DHT11 sensor and uploads it to a ThingSpeak channel. An other NodeMCU triggers an LED when the temperature goes beyond 30 degrees centigrade. WiFiManager library enables the NodeMCU to dynamically connect to a WiFi network without hard-coding the network SSID and password.

Two versions of code sending the sensor data are uploaded. First version uploads random data to ThingSpeak channel using HTTP POST method. It uses WiFiManager library to dynamically connect to a WiFi network. The second version uploads DHT11 temperature data to ThingSpeak channel. It uses ThingSpeak.h library instead of HTTP methods. The receiver code uses HTTP GET method to acquire the temperature data from ThingSpeak channel.

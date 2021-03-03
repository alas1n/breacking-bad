#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <WiFiManager.h>


unsigned long lastTime = 0;
unsigned long timerDelay = 1000; // Set timer to 5 seconds (5000)

// Timer: Auxiliary variables
unsigned long now = millis();


//Your Domain name with URL path or IP address with path
String Receiver = "http://5.253.26.221:5000/receive";
String Sender = "http://5.253.26.221:5000/send";
void setup() {
// put your setup code here, to run once:
Serial.begin(115200);
WiFiManager wifiManager;
Serial.println("Conecting.....");
wifiManager.autoConnect("HELLOW");
Serial.println("connected");
}
void loop() {
  now = millis();
  if ((now - lastTime) > timerDelay) {
    lastTime = now;
    if(WiFi.status() == WL_CONNECTED){
      HTTPClient http;
      Serial.println("Receiving");
      String serverPath = Receiver;
      http.begin(serverPath.c_str());
      int httpResponseCode = http.GET();
      Serial.print("http.GET():");
      Serial.println(http.GET());
      if (httpResponseCode > 0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
      }
      http.end();
    } 
    else {
      Serial.println("WiFi Disconnected");
    }
  }
}
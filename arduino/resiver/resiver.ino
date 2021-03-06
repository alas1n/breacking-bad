/*
  Rui Santos
  Complete project details at Complete project details at https://RandomNerdTutorials.com/esp8266-nodemcu-http-get-post-arduino/

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

int ledPin = 12;
int out_pin = 15;
int in_pin = 4;
int BUTTONstate = 0;
int number = 0;

const char* ssid = "co-line";
const char* password = "coline9713";

//Your Domain name with URL path or IP address with path
//String serverName = "http://httpbin.org/ip";
String serverName = "https://70806da3ab95.ngrok.io/resive";

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 500;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(out_pin, OUTPUT);
  pinMode(in_pin, INPUT);
  Serial.begin(115200); 

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}

void loop() {
  BUTTONstate = digitalRead(in_pin);
  //Send an HTTP POST request every 10 minutes
    if ((millis() - lastTime) > timerDelay) {
      
      //Check WiFi connection status
      if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;
      String serverPath = serverName;

      // Your Domain name with URL path or IP address with path
      http.begin(serverPath.c_str());
      
      // Send HTTP GET request
      int httpResponseCode = http.GET();
      
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
        Serial.println(number);
        if (payload == "1") {
          Serial.println("payload");
          Serial.println(payload);
          Serial.println("Light is ON");
          digitalWrite(ledPin, HIGH);
          delay(2000);
          Serial.println("Light is OFF");
          digitalWrite(ledPin, LOW);
        }
        else {
          Serial.println("Light is OFF");
        }
        number++;
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}

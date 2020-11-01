#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

int timeSeconds = 1;

int interruptPin = 0;
int ledPin = 2;
int value = 0;

// Timer: Auxiliary variables
unsigned long now = millis();
unsigned long lastTrigger = 0;
boolean startTimer = false;


const char* ssid = "co-line";
const char* password = "coline9713";

const char * headerKeys[] = {"Value"} ;
const size_t numberOfHeaders = 1;

//Your Domain name with URL path or IP address with path
String Resiver = "http://70806da3ab95.ngrok.io/resive";
String Sender = "http://70806da3ab95.ngrok.io/send";

unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 500;


ICACHE_RAM_ATTR void detectsMovement() {
  if ((millis() - lastTime) > timerDelay) {
    if(WiFi.status()== WL_CONNECTED){
        HTTPClient http;
  Serial.println("Sending");
////////////////////////////////SENDER////////////////////////////////
  String serverPath = Sender;
  http.begin(serverPath.c_str());
  http.GET();
  http.end();
  startTimer = true;
  lastTrigger = millis();
    }
  }else {
    Serial.println("WiFi Disconnected");
    }

}

void setup() {
  Serial.begin(115200);

  attachInterrupt(digitalPinToInterrupt(interruptPin), detectsMovement, FALLING);
  pinMode(interruptPin, INPUT);
  pinMode(ledPin, OUTPUT);

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
  // Current time
  now = millis();

  if(startTimer && (now - lastTrigger > (timeSeconds*500))) {
    
  
  if ((millis() - lastTime) > timerDelay) {
    if(WiFi.status()== WL_CONNECTED){
//      if (digitalRead(interruptPin) == LOW) {
//        HTTPClient http;
//        Serial.println("Sending");
//////////////////////////////////SENDER////////////////////////////////
//        String serverPath = Sender;
//        http.begin(serverPath.c_str());
////        int httpResponseCode = http.GET();
//        http.GET();
//        http.end();
//        } 
//        else {
////////////////////////////////Resiver////////////////////////////////
          HTTPClient http;
          Serial.println("Resiving");
          String serverPath = Resiver;
          http.begin(serverPath.c_str());
          http.collectHeaders(headerKeys, numberOfHeaders);
          int httpResponseCode = http.GET();
          if (httpResponseCode>0) {
//            Serial.print("HTTP Response code: ");
//            Serial.println(httpResponseCode);
//            String payload = http.getString();
//            Serial.println(payload);
            Serial.print("value: ");
            Serial.println(http.header("Value"));
            if (value < http.header("Value").toInt()) {
              digitalWrite(ledPin, LOW);
              Serial.println("LED ON");
              delay(500);
              digitalWrite(ledPin, HIGH);
              Serial.println("LED OFF");
              value = http.header("Value").toInt(); 
              }
            }
            http.end();
//            }
       }
    }
  else {
    Serial.println("WiFi Disconnected");
    }
    startTimer = false;
  }
}

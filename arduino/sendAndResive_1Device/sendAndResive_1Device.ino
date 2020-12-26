#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <WiFiManager.h>

bool Receiving = true;

int interruptPin = 5;
// int ledPin = 2;
int value = 0;

int LED1 = 14;
int LED2 = 12;
int LED3 = 13;
int LED4 = 15;
int RGB1 = 1;
int RGB2 = 3;

// Timer: Auxiliary variables
unsigned long now = millis();
unsigned long lastTime = 0;
unsigned long nowInterrupt = millis();
unsigned long lastTimeInterrupt = 0;
unsigned long timerDelay = 500; // Set timer to 5 seconds (5000)

const char* ssid = "Alasin";
const char* password = "Xir5y3ky!!";

// const char * headerKeys[] = {"Value"} ;
// const size_t numberOfHeaders = 1;

//Your Domain name with URL path or IP address with path
String Receiver = "http://5.253.26.221:5000/receive";
String Sender = "http://5.253.26.221:5000/send";
String Address = "http://5.253.26.221:5000/send";




//---SENDER---//Using Interrupts:
ICACHE_RAM_ATTR void SendRequest() {
  // Receiving = false;
  // nowInterrupt = millis(); 
  // if ((millis() - lastTimeInterrupt) > timerDelay) {
  //   lastTimeInterrupt = nowInterrupt;
  // // WL_NO_SHIELD == 255 // WL_IDLE_STATUS ==	0 // WL_NO_SSID_AVAIL == 1 // WL_SCAN_COMPLETED == 2 // WL_CONNECTED ==	3 // WL_CONNECT_FAILED ==	4 // WL_CONNECTION_LOST == 5 // WL_DISCONNECTED == 6
  //   if(WiFi.status()== WL_CONNECTED) { 
  //     HTTPClient http;
  //     Serial.println("Sending");
  //     String serverPath = Sender;
  //     http.begin(serverPath.c_str());
  //     // http.GET();
  //     int httpResponseCode = http.GET();
  //     Serial.println(httpResponseCode);
  //     if (httpResponseCode>0) {
  //       Serial.print("HTTP Response code: ");
  //       Serial.println(httpResponseCode);
  //       String payload = http.getString();
  //       Serial.println(payload);
  //     }
  //     // http.end();
  //     Receiving = true;
  //   } 
  //   else {
  //     Serial.print("WiFi Disconnected: ");
  //     Serial.print("WiFi.status(): ");
  //     Serial.println(WiFi.status());
  //   }
  // }
  Receiving = false;
}

void setup() {
  Serial.begin(115200);
  
  // Define interrupt Pin:
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), SendRequest, RISING);

  // PinMode for Lamps:
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(RGB1, OUTPUT);
  pinMode(RGB2, OUTPUT);

  
  // connecting to wifi In any network with mobile : 192.168.4.1
  WiFiManager wifiManager;
  Serial.println("Conecting.....");
  wifiManager.autoConnect("HELLOW");
  Serial.println("connected");
  
  //// connecting to wifi with preDefined ssid and password
  // WiFi.begin(ssid, password);
  // Serial.println("Connecting");
  // while(WiFi.status() != WL_CONNECTED) {
  //   delay(500);
  //   Serial.print(".");
  // }
  // Serial.println("");
  // Serial.print("Connected to WiFi network with IP Address: ");
  // Serial.println(WiFi.localIP());
  // Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}

void loop() {
  // Current time
  now = millis();  
  //---send or receive---//
  if ((now - lastTime) > timerDelay) {
    if (Receiving) {
      Address = Receiver;
    } 
    else {
      Address = Sender;
      Receiving = true;
    }
    lastTime = now;
    if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;
      Serial.println(Address);
      String serverPath = Address;
      http.begin(serverPath.c_str());
      int httpResponseCode = http.GET();
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
        value = payload.toInt(); 
        valueChecker(value);
      }
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
  }
}


void valueChecker(int val) {
  if(val == 0) {
    digitalWrite(LED1,HIGH);
    digitalWrite(LED2,LOW);
    digitalWrite(LED3,LOW);
    digitalWrite(LED4,LOW);
    digitalWrite(RGB1,LOW);
    digitalWrite(RGB2,LOW);
  } 
  else if (val == 1) {
    digitalWrite(LED1,LOW);
    digitalWrite(LED2,HIGH);
    digitalWrite(LED3,LOW);
    digitalWrite(LED4,LOW);
    digitalWrite(RGB1,LOW);
    digitalWrite(RGB2,LOW);
  } 
  else if (val == 2) {
    digitalWrite(LED1,LOW);
    digitalWrite(LED2,LOW);
    digitalWrite(LED3,HIGH);
    digitalWrite(LED4,LOW);
    digitalWrite(RGB1,LOW);
    digitalWrite(RGB2,LOW);
  } 
  else if (val == 3) {
    digitalWrite(LED1,LOW);
    digitalWrite(LED2,LOW);
    digitalWrite(LED3,LOW);
    digitalWrite(LED4,HIGH);
    digitalWrite(RGB1,LOW);
    digitalWrite(RGB2,LOW);
  } 
  else if (val == 4) {
    digitalWrite(LED1,LOW);
    digitalWrite(LED2,LOW);
    digitalWrite(LED3,LOW);
    digitalWrite(LED4,LOW);
    digitalWrite(RGB1,HIGH);
    digitalWrite(RGB2,LOW);
  } 
  else if (val == 5) {
    digitalWrite(LED1,LOW);
    digitalWrite(LED2,LOW);
    digitalWrite(LED3,LOW);
    digitalWrite(LED4,LOW);
    digitalWrite(RGB1,LOW);
    digitalWrite(RGB2,HIGH);
  } 
  else if (val == 6) {
    digitalWrite(LED1,HIGH);
    digitalWrite(LED2,LOW);
    digitalWrite(LED3,LOW);
    digitalWrite(LED4,LOW);
    digitalWrite(RGB1,HIGH);
    digitalWrite(RGB2,HIGH);
  } 
}

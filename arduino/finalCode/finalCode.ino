#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiManager.h>

// unique Id for this device
const char *DEVICE_ID = "1";

bool Receiving = true;

int interruptPin = 5;
int value = 1;
int localValue = 2;

int LED1 = 16;
int LED2 = 4;
int LED3 = 0;
int LED4 = 2;
int RGB1 = 12;
int RGB2 = 13;
int RGB3 = 14;

// Timer: Auxiliary variables
unsigned long now = millis();
unsigned long lastTimeReq = 0;
unsigned long lastTimeSleep = 0;
unsigned long reqTimerDelay = 1000;    // time stamp between each request
unsigned long sleepTimerDelay = 10000000; // time stamp for sleep

const char *ssid = "Develoop";
const char *password = "123Develoop456";

// Domain name with URL path or IP address with path
String Receiver = "http://lamp.develoop.run/api/v1/status/1";
String Sender = "http://lamp.develoop.run/api/v1/set/1";

String BASEURL = "http://lamp.develoop.run/api/v1/";
String Address = "";
String Set = "set/";
String Status = "status/";
String ValueString = "";

//---SENDER---//Using Interrupts:
ICACHE_RAM_ATTR void SendRequest()
{
    Receiving = false;
}

void setup()
{
    Serial.begin(115200);

    // Define interrupt Pin:
    pinMode(interruptPin, INPUT);
    attachInterrupt(digitalPinToInterrupt(interruptPin), SendRequest, RISING);

    // PinMode for Lamps:
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    pinMode(LED4, OUTPUT);
    pinMode(RGB1, OUTPUT);
    pinMode(RGB2, OUTPUT);
    pinMode(RGB3, OUTPUT);

    // connecting to wifi In any network with mobile : 192.168.4.1
    WiFiManager wifiManager;
    Serial.println("Conecting.....");
    wifiManager.autoConnect("LAMP");
    Serial.println("connected");
}

void loop()
{
    // Current time
    now = millis();

    //--- send or receive request ---//
    if ((now - lastTimeReq) > reqTimerDelay) // send request if (reqTimerDelay) time pasesd
    {
        lastTimeReq = now;
        changeSendOrRecvie();
        sendRequest();

        // sleep delay loop //
        if (localValue == value){
            if ((now - lastTimeSleep) > sleepTimerDelay) 
            {
                 Serial.println("time to sleep");
                 valueChecker(-1);
            }
        }
        else 
        {
            // if (value != 0)
            // {
                valueChecker(localValue);
                localValue = value;
                Serial.println("Two devides are activate");
                lastTimeSleep = now;
            // }
        }
   
    }
}


void changeSendOrRecvie()
{
    if (Receiving)
    {
        Address = BASEURL + Status + DEVICE_ID;
    }
    else
    {   
        value = value + 1;
        if (value == 29) {
            value = 1;
        }
        Address = BASEURL + Set + DEVICE_ID + "?val=" + String(value);
        Receiving = true;
    }
}

void sendRequest()
{
    if (WiFi.status() == WL_CONNECTED)
    {
        HTTPClient http;
        http.begin(Address);
        Serial.println("Address");
        Serial.println(Address);
        http.addHeader("Cache-Control", "max-age=0", false, false);
        int httpResponseCode = http.GET();

        if (httpResponseCode > 0)
        {
            String payload = http.getString();
            if(payload.toInt() != 0)
            {
                value = payload.toInt();
            }
            Serial.print("value ");
            Serial.println(value);
        }
        http.end();
    }
    else
    {
        Serial.println("WiFi Disconnected");
    }
}

void valueChecker(int val)
{
    if (val == -1)
    {
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, LOW);
        digitalWrite(LED4, LOW);
        // digitalWrite(RGB1, LOW);
        // digitalWrite(RGB2, LOW);
        // digitalWrite(RGB3, LOW);
    }
    else if (val == 1)
    {
        digitalWrite(LED1, HIGH);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, LOW);
        digitalWrite(LED4, LOW);
        digitalWrite(RGB1, HIGH);
        digitalWrite(RGB2, LOW);
        digitalWrite(RGB3, LOW);
    }
    else if (val == 2)
    {
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, HIGH);
        digitalWrite(LED3, LOW);
        digitalWrite(LED4, LOW);
        digitalWrite(RGB1, HIGH);
        digitalWrite(RGB2, LOW);
        digitalWrite(RGB3, LOW);
    }
    else if (val == 3)
    {
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, HIGH);
        digitalWrite(LED4, LOW);
        digitalWrite(RGB1, HIGH);
        digitalWrite(RGB2, LOW);
        digitalWrite(RGB3, LOW);
    }
    else if (val == 4)
    {
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, LOW);
        digitalWrite(LED4, HIGH);
        digitalWrite(RGB1, HIGH);
        digitalWrite(RGB2, LOW);
        digitalWrite(RGB3, LOW);
    }
    else if (val == 5)
    {
        digitalWrite(LED1, HIGH);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, LOW);
        digitalWrite(LED4, LOW);
        digitalWrite(RGB1, LOW);
        digitalWrite(RGB2, HIGH);
        digitalWrite(RGB3, LOW);
    }
    else if (val == 6)
    {
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, HIGH);
        digitalWrite(LED3, LOW);
        digitalWrite(LED4, LOW);
        digitalWrite(RGB1, LOW);
        digitalWrite(RGB2, HIGH);
        digitalWrite(RGB3, LOW);
    }
    else if (val == 7)
    {
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, HIGH);
        digitalWrite(LED4, LOW);
        digitalWrite(RGB1, LOW);
        digitalWrite(RGB2, HIGH);
        digitalWrite(RGB3, LOW);
    }
    else if (val == 8)
    {
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, LOW);
        digitalWrite(LED4, HIGH);
        digitalWrite(RGB1, LOW);
        digitalWrite(RGB2, HIGH);
        digitalWrite(RGB3, LOW);
    }
    else if (val == 9)
    {
        digitalWrite(LED1, HIGH);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, LOW);
        digitalWrite(LED4, LOW);
        digitalWrite(RGB1, LOW);
        digitalWrite(RGB2, LOW);
        digitalWrite(RGB3, HIGH);
    }
    else if (val == 10)
    {
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, HIGH);
        digitalWrite(LED3, LOW);
        digitalWrite(LED4, LOW);
        digitalWrite(RGB1, LOW);
        digitalWrite(RGB2, LOW);
        digitalWrite(RGB3, HIGH);
    }
    else if (val == 11)
    {
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, HIGH);
        digitalWrite(LED4, LOW);
        digitalWrite(RGB1, LOW);
        digitalWrite(RGB2, LOW);
        digitalWrite(RGB3, HIGH);
    }
    else if (val == 12)
    {
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, LOW);
        digitalWrite(LED4, HIGH);
        digitalWrite(RGB1, LOW);
        digitalWrite(RGB2, LOW);
        digitalWrite(RGB3, HIGH);
    }
    else if (val == 13)
    {
        digitalWrite(LED1, HIGH);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, LOW);
        digitalWrite(LED4, LOW);
        digitalWrite(RGB1, HIGH);
        digitalWrite(RGB2, HIGH);
        digitalWrite(RGB3, LOW);
    }
    else if (val == 14)
    {
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, HIGH);
        digitalWrite(LED3, LOW);
        digitalWrite(LED4, LOW);
        digitalWrite(RGB1, HIGH);
        digitalWrite(RGB2, HIGH);
        digitalWrite(RGB3, LOW);
    }
    else if (val == 15)
    {
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, HIGH);
        digitalWrite(LED4, LOW);
        digitalWrite(RGB1, HIGH);
        digitalWrite(RGB2, HIGH);
        digitalWrite(RGB3, LOW);
    }
    else if (val == 16)
    {
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, LOW);
        digitalWrite(LED4, HIGH);
        digitalWrite(RGB1, HIGH);
        digitalWrite(RGB2, HIGH);
        digitalWrite(RGB3, LOW);
    }
    else if (val == 17)
    {
        digitalWrite(LED1, HIGH);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, LOW);
        digitalWrite(LED4, LOW);
        digitalWrite(RGB1, HIGH);
        digitalWrite(RGB2, LOW);
        digitalWrite(RGB3, HIGH);
    }
    else if (val == 18)
    {
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, HIGH);
        digitalWrite(LED3, LOW);
        digitalWrite(LED4, LOW);
        digitalWrite(RGB1, HIGH);
        digitalWrite(RGB2, LOW);
        digitalWrite(RGB3, HIGH);
    }
    else if (val == 19)
    {
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, HIGH);
        digitalWrite(LED4, LOW);
        digitalWrite(RGB1, HIGH);
        digitalWrite(RGB2, LOW);
        digitalWrite(RGB3, HIGH);
    }
    else if (val == 20)
    {
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, LOW);
        digitalWrite(LED4, HIGH);
        digitalWrite(RGB1, HIGH);
        digitalWrite(RGB2, LOW);
        digitalWrite(RGB3, HIGH);
    }
    else if (val == 21)
    {
        digitalWrite(LED1, HIGH);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, LOW);
        digitalWrite(LED4, LOW);
        digitalWrite(RGB1, LOW);
        digitalWrite(RGB2, HIGH);
        digitalWrite(RGB3, HIGH);
    }
    else if (val == 22)
    {
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, HIGH);
        digitalWrite(LED3, LOW);
        digitalWrite(LED4, LOW);
        digitalWrite(RGB1, LOW);
        digitalWrite(RGB2, HIGH);
        digitalWrite(RGB3, HIGH);
    }
    else if (val == 23)
    {
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, HIGH);
        digitalWrite(LED4, LOW);
        digitalWrite(RGB1, LOW);
        digitalWrite(RGB2, HIGH);
        digitalWrite(RGB3, HIGH);
    }
    else if (val == 24)
    {
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, LOW);
        digitalWrite(LED4, HIGH);
        digitalWrite(RGB1, LOW);
        digitalWrite(RGB2, HIGH);
        digitalWrite(RGB3, HIGH);
    }
    else if (val == 25)
    {
        digitalWrite(LED1, HIGH);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, LOW);
        digitalWrite(LED4, LOW);
        digitalWrite(RGB1, HIGH);
        digitalWrite(RGB2, HIGH);
        digitalWrite(RGB3, HIGH);
    }
    else if (val == 26)
    {
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, HIGH);
        digitalWrite(LED3, LOW);
        digitalWrite(LED4, LOW);
        digitalWrite(RGB1, HIGH);
        digitalWrite(RGB2, HIGH);
        digitalWrite(RGB3, HIGH);
    }
    else if (val == 27)
    {
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, HIGH);
        digitalWrite(LED4, LOW);
        digitalWrite(RGB1, HIGH);
        digitalWrite(RGB2, HIGH);
        digitalWrite(RGB3, HIGH);
        ;
    }
    else if (val == 28)
    {
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, LOW);
        digitalWrite(LED4, HIGH);
        digitalWrite(RGB1, HIGH);
        digitalWrite(RGB2, HIGH);
        digitalWrite(RGB3, HIGH);
    }
}
/*------------------------------------------------------------------------------
 07/01/2018
 Author: Makerbro
 Platforms: ESP8266
 Language: C++/Arduino
 File: webserver_html.ino
 ------------------------------------------------------------------------------
 Description: 
 Code for YouTube video demonstrating how to use HTML weppages in a web 
 server's response.
 https://youtu.be/VNgFbQAVboA

 Do you like my videos? You can support the channel:
 https://patreon.com/acrobotic
 https://paypal.me/acrobotic
 ------------------------------------------------------------------------------
 Please consider buying products from ACROBOTIC to help fund future
 Open-Source projects like this! We'll always put our best effort in every
 project, and release all our design files and code for you to use. 

 https://acrobotic.com/
 https://amazon.com/acrobotic
 ------------------------------------------------------------------------------
 License:
 Please see attached LICENSE.txt file for details.
------------------------------------------------------------------------------*/
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>

ESP8266WebServer server;
WebSocketsServer webSocket = WebSocketsServer(81);

uint8_t pin_led = 2;
char* ssid = "co-line";
char* password = "coline9713";

char webpage[] PROGMEM = R"=====(
<html>
<head>
 <script>
  var Socket;
  function init() {
      Socket = new WebSocket('ws://' + window.location.hostname + ':81/');
      Socket.onmessage = function(event){
        document.getElementById("rxConsole").value += event.data;
      }
    }
    function sendText(){
      Socket.send(document.getElementById("txBar").value);
      document.getElementById("txBar").value = "";
    }
 </script>
</head>
<body onload="javascript:init()">
  <div>
    <textarea id="rxConsole"></textarea>
  </div>
  <hr/>
  <div>
    <input type="text" id="txBar" onkeydown="if(event.keyCode == 13) sendText();" />
  </div>
</html>
)=====";

void setup()
{
 pinMode(pin_led, OUTPUT);
 WiFi.begin(ssid,password);
 Serial.begin(115200);
 while(WiFi.status()!=WL_CONNECTED)
 {
   Serial.print(".");
   delay(500);
 }
 Serial.println("");
 Serial.print("IP Address: ");
 Serial.println(WiFi.localIP());

server.on("/",[](){
    server.send_P(200, "text/html", webpage);  
  });
 server.begin();
 webSocket.begin();
 webSocket.onEvent(webSocketEvent);
}

void loop()
{
 webSocket.loop();
 server.handleClient();
 if(Serial.available() > 0){
    char c[] = {(char)Serial.read()};
    webSocket.broadcastTXT(c, sizeof(c));
 }
}


void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length){
  if(type == WStype_TEXT){
    for(int i = 0; i < length; i++)
      Serial.print((char) payload[i]);
    Serial.println();
    
  }
  
}

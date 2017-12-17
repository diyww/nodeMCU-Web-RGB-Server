#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "ENV.h"

ESP8266WebServer server; //Web server variable
  
void setup() {

  WiFi.begin(ssid, password);
  WiFi.config(ip, gateway, subnet);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
   
  //RED
  pinMode(D0, OUTPUT);
  //GREEN
  pinMode(D1, OUTPUT);
  //BLUE
  pinMode(D2, OUTPUT);

  //setting up the server data
  server.on("/", []() {
    if(server.arg("r")){
      setRedPin(server.arg("r").toInt());
    }
    if(server.arg("g")){
      setGreenPin(server.arg("g").toInt());
    }
    if(server.arg("b")){
      setBluePin(server.arg("b").toInt());
    }
    server.send(200, "ok");
   });
   server.begin(); 
}

void loop() {
  server.handleClient(); 
}

void setBluePin(int value) {
  analogWrite(D0, rgbToPin(value));
}

void setRedPin(int value) {
  analogWrite(D1, rgbToPin(value));
}

void setGreenPin(int value) {
  analogWrite(D2, rgbToPin(value));
}

int rgbToPin(int rgbValue){
  return rgbValue << 2;
}


#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
//----------------------------------------

#include "PageIndex.h" //--> Include the contents of the User Interface Web page, stored in the same folder as the .ino file

#define LIGHT1 D0 //--> Defining LIGHT Port
#define LIGHT2 D1 //--> Defining LIGHT Port


//----------------------------------------Make a wifi name and password as access point
const char* ssid = "NEW_DESIGN_CENTER";
const char* password = "12345678";
//----------------------------------------

ESP8266WebServer server(80);  //--> Server on port 80

//----------------------------------------This routine is executed when you open NodeMCU ESP8266 IP Address in browser
void handleRoot() {
  //String s = MAIN_page; //Read HTML contents
  server.send(200, "text/html", MAIN_page); //Send web page
}
//----------------------------------------
//----------------------------------------Procedure for turning lights on or off
void handleLIGHT1() {
  String LIGHTState1 = "OFF";
  String t_state1 = server.arg("LIGHTState1");
  Serial.print(t_state1);
  if(t_state1 == "1")  {
    digitalWrite(LIGHT1,HIGH); //LED ON
    LIGHTState1 = "ON"; //Feedback parameter
    Serial.println(" | LIGHT1 ON");
  }
  else  {
    digitalWrite(LIGHT1,LOW); //LED OFF
    LIGHTState1 = "OFF"; //Feedback parameter 
    Serial.println(" | LIGHT1 OFF"); 
  }
  server.send(200, "text/plane", LIGHTState1); //Send web page
}

void handleLIGHT2() {
  String LIGHTState2 = "OFF";
  String t_state2 = server.arg("LIGHTState2");
  Serial.print(t_state2);
  if(t_state2 == "1")  {
    digitalWrite(LIGHT2,HIGH); //LED ON
    LIGHTState2 = "ON"; //Feedback parameter
    Serial.println(" | LIGHT2 ON");
  }
  else  {
    digitalWrite(LIGHT2,LOW); //LED OFF
    LIGHTState2 = "OFF"; //Feedback parameter 
    Serial.println(" | LIGHT2 OFF"); 
  }
  server.send(200, "text/plane", LIGHTState2); //Send web page
}
//----------------------------------------
//----------------------------------------SETUP
void setup(void){
  Serial.begin(115200);
  delay(500);

  pinMode(LIGHT1,OUTPUT); //--> LIGHT port Direction output
  pinMode(LIGHT2,OUTPUT); //--> LIGHT port Direction output
  
  WiFi.softAP(ssid, password);  //--> Start Making ESP8266 NodeMCU as an access point

  IPAddress apip = WiFi.softAPIP(); //--> Get the IP server
  Serial.print("Connect your wifi laptop/mobile phone to this NodeMCU Access Point : ");
  Serial.println(ssid);
  Serial.print("Visit this IP : ");
  Serial.print(apip); //--> Prints the IP address of the server to be visited
  Serial.println(" in your browser.");
 
  server.on("/", handleRoot); //--> Routine to handle at root location. This is to display web page.
  server.on("/setLIGHT1", handleLIGHT1);  //--> Routine to handle the call procedure handleLIGHT
  server.on("/setLIGHT2", handleLIGHT2);  //--> Routine to handle the call procedure handleLIGHT
  
  server.begin(); //--> Start server
  Serial.println("HTTP server started");
}
//----------------------------------------
//----------------------------------------LOOP
void loop(void){
  server.handleClient();  //--> Handle client requests
}
//----------------------------------------

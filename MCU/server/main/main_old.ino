//Wires in normal close holes.
//normal close without ESP is suddenly OPEN

#include <WiFi.h>
#include <WiFiClient.h>
#include <mDNS.h>
#include <WebServer.h>

#include "Utils.h"
#include "Const.h"


WebServer server(80);

void handleRoot()
{
  server.send(200, "text/plain", "hello from esp8266!");
}

void handleNotFound()
{
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++)
  {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void handleLogin() {                         // If a POST request is made to URI /login
  if( ! server.hasArg("id") || ! server.hasArg("time") 
      || server.arg("id") == NULL || server.arg("time") == NULL) { // If the POST request doesn't have username and password data
    server.send(400, "text/plain", "400: Invalid Request");         // The request is invalid, so send HTTP status 400
    return;
  }
   else {                                                                             
    server.send(200, "text/html", "<h1>Welcome, " + server.arg("username") + "!</h1><p>OK</p>");
    Serial.print(server.arg("id"));
    Serial.print("\t");
    Serial.print(server.arg("time"));
    Serial.print("\t");
    Serial.println(server.arg("noise"));
  }
}


void setup(void)
{
  Serial.begin(115200);
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
   
  Serial.print("AP IP address: ");
  Serial.println(myIP);


  server.on("/", HTTP_GET, handleRoot);     
  server.on("/api/login", HTTP_POST, handleLogin); 


  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void)
{
  server.handleClient();
}

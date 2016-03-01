/****************
 * AP Mode Demo *
 ****************/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <String>

// WiFi SSID and credentials.
const char *ssid = "EnterTheESP";
const char *password = "thereisnospoon";

// Web server.
ESP8266WebServer server(80);

unsigned long responses_sent = 0;

void handleRoot(){
  responses_sent++;
  server.send(200, "text/html", "Congratulations! You are the " + String(responses_sent) +
                                "user!");
}

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP Address: ");
  Serial.println(myIP);

  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started!");
}

void loop() {
  server.handleClient();
}

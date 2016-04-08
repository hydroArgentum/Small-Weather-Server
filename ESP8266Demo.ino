/****************
 * ESP8266 Demo *
 ****************/
// Libraries included.
// Arduino base WiFi 
// ESP8266 WiFi and Web Server.
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
// BME280 library and dependencies.
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <SPI.h>

// Defined constants.
// These are chip select pins that could be mapped to any available GPIO.
// BME280 chip select pin.
#define BME280_CS 5
// SD chip select pin.
#define SD_CS 4
// WiFi information. ESP8266 supports WPA2-PSK.
// ESP8266 should support WEP, WPA.
// WPA2-Enterprise + EAP-TLS should be supported, but WPA2-Enterprise + PEAP.
// There might be a workaround for authentication based on eduroam.
// We probably won't use eduroam just to do it though.
const char* ssid = "esp8266demo";
const char* key = "opensource";

// Global variables.
// BME280 module.
Adafruit_BME280 bme280(BME280_CS);
// WiFi Server.
// Specify the port of the server using the argument.
ESP8266WebServer server(80);

/************************************************************************************************
 * Begin UART communication.                                                                    *
 * Note that it is not possible to determine whether a connection has been successfuly bridged. *
 ************************************************************************************************/
void serial_setup(){
  // Setup UART module.
  Serial.begin(115200);
  // Serial connection complete.
  Serial.println("Serial connection complete!");
}

void BME280_setup(){
  // Setup BME280 module with default pins.
  // Default SPI pins.
  if (!bme280.begin()){
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while(1);
  }
  Serial.println("BME280 connection complete!");
}

void WiFi_setup(){
  // Setup WIFI.
  WiFi.begin(ssid, key);
  // Wait for connection.
  while (WiFi.status() != WL_CONNECTED){
    // Note, the ESP8266 cannot connect while Serial is busy, so we have
    // to create a delay so that it has time to connect.
    delay(500);
    Serial.print(".");
  }
  // Connection completed.
  Serial.println();
  Serial.println("WiFi connection complete!");
}

void WiFi_diagnostics(){
  // WiFi diagnostics.
  Serial.print("Connected to: ");
  Serial.println(ssid);
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Subnet Mask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway Address: ");
  Serial.println(WiFi.gatewayIP());
}

void serverHandler(){
  // Controls the server response to a request.
  Serial.println("Client request handled!");
  server.send(200, "text/plain", "You are connected.");
}

void WiFi_handler(){
  // Controls URI.
  server.onNotFound(serverHandler);

  // Start server.
  server.begin();
  Serial.println("Server ready!");
}

void setup() {
  // Start UART communication.
  serial_setup();
  // Setup BME280.
  BME280_setup();
  // Setup WiFi.
  WiFi_setup();
  // Check WiFi.
  WiFi_diagnostics();
  // Start server.
  WiFi_handler();
}

void loop() {
  server.handleClient();
}


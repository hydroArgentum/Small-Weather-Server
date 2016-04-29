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
// Data.
float temperature = 0;
float pressure = 0;
float humidity = 0;
// WiFi Server.
// Specify the port of the server using the argument.
ESP8266WebServer server(80);
// Set/Reset.
unsigned char sr_var = 1;
// Number of clients served.
unsigned long clients_served = 0;

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
  WiFi.mode(WIFI_STA);
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
  clients_served++;
  server.send(200, "text/plain", "Current temperature: " + String(temperature) + char(0xB0) + "C\n"
              + "Current pressure: " + String(pressure) + "hPa\n"
              + "Current humidity: " + String(humidity) + "%\n"
              + "Client #: " + String((clients_served + 1) / 2));
}

void WiFi_handler(){
  // Controls URI.
  server.onNotFound(serverHandler);

  // Start server.
  server.begin();
  Serial.println("Server ready!");
}

void GPIO_setup(){
  // Blue LED.
  pinMode(2, OUTPUT);
  // Button.
  pinMode(16, INPUT);
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
  // GPIO configuration.
  GPIO_setup();
}

void loop() {
  if (sr_var){
    if (digitalRead(16) == HIGH){
      server.handleClient();
      temperature = bme280.readTemperature();
      pressure = bme280.readPressure() / 100.0F;
      humidity = bme280.readHumidity();
    }
    else{
      while (digitalRead(16) == LOW);
      sr_var = 0;
      digitalWrite(2, LOW);
    }
  }
  else {
    if (digitalRead(16) == LOW){
      while (digitalRead(16) == LOW);
      sr_var = 1;
      clients_served = 0;
      digitalWrite(2, HIGH);
    }
  }
}


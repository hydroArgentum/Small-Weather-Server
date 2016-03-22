/****************
 * ESP8266 Demo *
 ****************/

// Libraries included.
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

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
const char* ssid = "";
const char* password = "";

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
  
}

void setup() {
  // Start UART communication.
  serial_setup();
}

void loop() {
  // put your main code here, to run repeatedly:

}

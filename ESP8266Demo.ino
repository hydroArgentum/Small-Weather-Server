/****************
 * ESP8266 Demo *
 ****************/
// Libraries included.
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
const char* password = "rcos";

// BME280 module.
Adafruit_BME280 bme280(BME280_CS);

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

void setup() {
  // Start UART communication.
  serial_setup();
  // Setup BME280.
  BME280_setup();
}

void loop() {
  // put your main code here, to run repeatedly:

}

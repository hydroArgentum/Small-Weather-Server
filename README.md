# Small-Weather-Server
A small weather server based on the ESP8266 and the BME280.

## Contents
- Instructions

## Instructions
This project uses the Arduino IDE and the Arduino core for ESP8266 WiFi Chip.

1. Install the Arduino IDE v1.6.5 at the very least (while later revisions work for me, if you are adamant about setting your enviornment as close to the requirements as possible, the option is there) you can find the Arduino IDE at the [Arduino Website](https://www.arduino.cc/en/Main/Software).
2. Start Arduino and navigate to File -> Preferences.
3. Add one of the following: 

   Stable version: 'http://arduino.esp8266.com/stable/package_esp8266com_index.json'... 

   Staging version: 'http://arduino.esp8266.com/staging/package_esp8266com_index.json'... 

   You can find these links on the Arduino core for ESP8266 WiFi Chip(https://raw.githubusercontent.com/esp8266/Arduino/master/README.md).
4. Save preferences and close.
5. Navigate to Tools -> Board *** -> Boards Manager... 

   Note that \*\*\* is just a filler and something else will take its place. 
6. Install 'esp8266'. You can also search for it to make it easier to find.
7. Remember to set the board using Tools -> Board *** -> ESP8266 Modules. Some preconfigured settings are available for certain models. If your board is not listed on there, try using "Generic ESP8266 Module" and make sure that your model and requirements are reflected by the settings that follow the "Board" context menu (the manufacturer should have some documentation about how to use this). 

Other than this, the rest of the setup on the software side should be similar to setting up an Arduino board.

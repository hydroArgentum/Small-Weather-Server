# Small-Weather-Server
A small weather server based on the ESP8266 and the BME280.

Note: Currently, WPA-Enterprise + EAP-TLS is supported, but only because it is a server-client interface.
Username/password interfaces such as those required by WPA-Enterprise + PEAP, is not supported.

Also, to get WPA-Enterprise + EAP-TLS will require adding "-lwpa2" parameter to the compiler.
Because that is outside the context of the project, WPA-Enterprise will not be supported.

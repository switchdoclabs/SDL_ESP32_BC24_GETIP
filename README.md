SDL_ESP32_BC24_GETIP <BR>SDL_ESP32_BC24_GETIP
<BR>
SwitchDoc Labs <BR>
Start: June 2018<BR>
www.switchdoc.labs<BR>
<BR>
<BR>

This software library is designed to provide a flexible way of provisioning WiFiconnections in a system and router flexible way.

It consists of three different methods:<BR>
- SmartConfig<BR>
- WPS Button on AP<BR>
- Local AP on ESP32 (192.168.4.1)<BR>

Note:  This was developed for the BC24 ESP32 Based 24 RGBW Pixel LED Board <BR>

<H2>
SmartConfig<BR>
</H2>
This method uses the TI method of provisiong
"SmartConfig" was invented by TI. You can refer to it here:<BR>
https://community.particle.io/t/smart-config-the-missing-manual-now-available/442<BR>
In order to do SmartConfig, you need a smartphone or tablet (Android or iOS) that connected to WiFi network (which you want ESP32 to connect to) and installed a special application. 
On this application, you just supply the ssid and password of WiFi network so that the application can use, encode them and then broadcast (via UDP) encoded ssid and password (under packet format) over the air. 
When this software is being run, the ESP32 (with the SmartConfig software loaded) will capture these packets, decode back ssid and password and use them to connect to Wifi network. 

After connecting to WiFi, the  ESP32 will use mDNS to multicast a message to the application to notify that it has successfully connected to WiFi.

The source code of special application is supplied by Espressif. You can download at:<BR>
https://github.com/EspressifApp/EsptouchForAndroid<BR>
https://github.com/EspressifApp/EsptouchForIOS<BR>
This application is also available on App Store. You can use it to test SmartConfig feature.<BR>
- For Android, this application is available under name "IOT_Espressif" or another application "ESP8266 SmartConfig" (this is for ESP8266 but you can use it for ESP32):<BR>

https://play.google.com/store/apps/details?id=com.cmmakerclub.iot.esptouch<BR>
https://play.google.com/store/apps/details?id=com.espressif.iot<BR>
<P>
- For iOS, this application is available under name "Espressif Esptouch":<BR>
https://itunes.apple.com/us/app/espressif-esptouch/id1071176700?mt=8  <BR>

There is also another app on the iOS Appstore, search on "SmartConfig"<BR>
<BR>
See how to use all three in the SDL_ESP32_BC24_GETIP.ino file.

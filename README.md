<H1>SDL_ESP32_BC24_GETIP <BR>
<BR>
SwitchDoc Labs <BR></H1>
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
  
  In order to install the Arduino IDE with support for the ESP32 on the BC24, please follow the tutorial here:

http://www.switchdoc.com/2018/07/tutorial-arduino-ide-esp32-bc24/

Select the Adafruit ESP32 Feather under Tools

If you get a "\SDL_ESP32_BC24DEMO\SDL_ESP32_BC24DEMO.ino:69:21: fatal error: TimeLib.h: No such file or directory"

Go to this link github.com/PaulStoffregen/Time and download the .zip file. Then, in the IDE, go to Sketch>Include Library and click on Add .ZIP Library... In your file download area, you should be able to find the Time-Master.zip. Click on it and Open. It will install the Time.h required for the compilation of the sketch. Try to compile. If you get a repeat error, ,then close the IDE and restart it. Then re-compiling should work.

Plug a USB Micro to USB connector into your computer (the one with the power supply will work) to establish the connection.

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
<H2>
WPS Button on AP<BR>
</H2>
Wi-Fi Protected Setup (WPS; originally, Wi-Fi Simple Config) is a network security standard to create a secure wireless home network.

Introduced in 2006, the goal of the protocol is to allow home users who know little of wireless security and may be intimidated by the available security options to set up Wi-Fi Protected Access, as well as making it easy to add new devices to an existing network without entering long passphrases.

This library will wait 60 seconds (in the example) for the WPS packets to be recieved by the ESP32.  

A major security flaw was revealed in December 2011 that affects wireless routers with the WPS PIN feature, which most recent models have enabled by default.

This software does not use the PIN feature.

<H2>
Local AP (192.168.4.1)<BR>
</H2>


For the third provisioning method, the ESP32 is set up as an access point (192.168.4.1) - look at your list of WiFi APs on your computer when it is running.   A small web server is started that will allow you to select the AP that you want the ESP32 to connect to and then you can enter the password for the access point.
It runs for 60 seconds by default.

<H2>
Notes<BR>
</H2>

The two general defines in the example are: <BR>
- BC24:<BR>
Define BC24 if you are using a BC24 ESP32 based device.  THere are visual clues for what the ESP32 is doing while provisioning.   See the archive at:<BR>
https://github.com/switchdoclabs/SDL_ESP32_BC24NEO

- BC24DEBUG:<BR>
Define BC24DEBUG (by default in the example it is defined) to see lots of debugging information which can help resolve problems and issues.
Remember that all of these features may fail and have to be repeated.  Nature of the beast.

See how to use all three in the SDL_ESP32_BC24_GETIP.ino file.

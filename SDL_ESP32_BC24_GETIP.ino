//
//
// SDL_ESP32_BC24_GETIP Demo Program
// SwitchDoc Labs
//
// June 2018
//


#if defined(ARDUINO) && ARDUINO >= 100
// No extras
#elif defined(ARDUINO) // pre-1.0
// No extras
#elif defined(ESP_PLATFORM)
#include "arduinoish.hpp"
#endif

#define BC24DEBUG

#include <WiFi.h>

#include <esp_wps.h>
#include <esp_smartconfig.h>

#define ESP_WPS_MODE WPS_TYPE_PBC

esp_wps_config_t config = WPS_CONFIG_INIT_DEFAULT(ESP_WPS_MODE);


#include <WiFiClientSecure.h>
#include <HTTPClient.h>

// AP Variables

#include "WiFiManager.h"          //https://github.com/tzapu/WiFiManager

//gets called when WiFiManager enters configuration mode


void configModeCallback (WiFiManager *myWiFiManager)
//void configModeCallback ()
{

  Serial.println("Entered config mode");

  Serial.println(WiFi.softAPIP());

}

#define WEB_SERVER_PORT 80
String APssid;

String Wssid;
String WPassword;

WiFiServer server(WEB_SERVER_PORT);

// include GET IP routines
#include "SDL_ESP32_BC24_GETIP.h"


String WiFi_SSID = "";
String WiFi_psk = "";



bool WiFiPresent = false;

void setup() {

  Serial.begin(115200);

  Serial.println();
  Serial.println();
  Serial.println("--------------------");
  Serial.println("WiFi Provisioning ESP32 Software Demo");
  Serial.println("--------------------");
  Serial.print("Version: 1.0");


  Serial.print("Compiled at:");
  Serial.print (__TIME__);
  Serial.print(" ");
  Serial.println(__DATE__);

  WiFiPresent = false;

  if (WiFiPresent == false)
  {
    // do SmartConfig
#define WAITFORSTART 15
#define WAITFORCONNECT 20

    WiFiPresent = SmartConfigGetIP(WAITFORSTART, WAITFORCONNECT);

  } // if not already programmed before





  if (WiFiPresent != true)
  {
#define WPSTIMEOUTSECONDS 60
    // now try WPS Button

    WiFiPresent = WPSGetIP(WPSTIMEOUTSECONDS);

  }

  if (WiFiPresent != true)
  {
#define APTIMEOUTSECONDS 60
    WiFiPresent = localAPGetIP(APTIMEOUTSECONDS);
  }


  if (WiFiPresent == true)
  {


    Serial.println("-------------");
    Serial.println("WiFi Connected");
    Serial.println("-------------");
    WiFi_SSID = WiFi.SSID();
    WiFi_psk = WiFi.psk();
    Serial.print("SSID=");
    Serial.println(WiFi_SSID);

    Serial.print("psk=");
    Serial.println(WiFi_psk);
  }
  else
  {
    Serial.println("-------------");
    Serial.println("WiFi NOT Connected");
    Serial.println("-------------");
  }

}

void loop() {
  // put your main code here, to run repeatedly:

}

//
// SDL_ESP_BC24_GETIP
// Collection of routines to get IP from  AP Access Point
// SwitchDoc
// June 2018 Version 1.0
//
//
// 1) SmartConfig
// 3) WPS Button
// 4) Local AP

// definitions

// BC24 - define if you have a BC24 (that has an ESP32 on board)
// BC24DEBUG - define if you want debugging output


void WiFiEvent(WiFiEvent_t event, system_event_info_t info);

int WPSReconnectCount = 0;   // for timeout on WPS

// SmartConfig

bool SmartConfigGetIP(long waitForStartSeconds, long secondsToWaitAfterStart)
{

  bool myWiFiPresent;
  myWiFiPresent = false;

  // setup WiFi
  //Init WiFi as Station, start SmartConfig
  esp_err_t error_code = 0;


  WiFi.mode(WIFI_AP_STA);
#ifdef BC24DEBUG
  Serial.print("error_code=");
  Serial.println(error_code);
#endif
  WiFi.beginSmartConfig();

  //Wait for SmartConfig packet from mobile
  Serial.println("Waiting for SmartConfig.");

  for (int i = 0; i < waitForStartSeconds; i++)
  {
    if (WiFi.smartConfigDone())
    {

      Serial.println("");
      Serial.println("SmartConfig received.");
      //Wait for WiFi to connect to AP
      Serial.println("Waiting for SmartConfig WiFi Start");

      for (int i = 0; i < secondsToWaitAfterStart ; i++)
      {
        if (WiFi.status() == WL_CONNECTED)
        {

          Serial.println("");
          Serial.println("WiFI Connected.");
          myWiFiPresent = true;
#ifdef BC24
          BC24ThreeBlink(Green, 1000);
#else
             vTaskDelay(1000 / portTICK_PERIOD_MS);
#endif
          break;
        }

        delay(500);
        Serial.print(".");
        myWiFiPresent = false;
#ifdef BC24
        BC24ThreeBlink(White, 1000);
#else
        vTaskDelay(1000 / portTICK_PERIOD_MS);
#endif
      }
      Serial.println();
      break;
    }
    //delay(500);
    Serial.print(".");
#ifdef BC24
    BC24ThreeBlink(Blue, 1000);
#else
    vTaskDelay(1000 / portTICK_PERIOD_MS);
#endif
  }
  if (myWiFiPresent == false)
  {
    esp_smartconfig_stop();

    Serial.println("No Wifi Present from Smart Config");
  }
  else
  {
    Serial.println("Wifi Present from Smart Config");
  }

#ifdef BC24
  BC24ThreeBlink(Red, 1000);
#else
  vTaskDelay(1000 / portTICK_PERIOD_MS);
#endif
  return myWiFiPresent;
}


//
// WPS Button GET IP
//
bool WPSGetIP(long timeOutSeconds)
{


  bool myWiFiPresent;
  myWiFiPresent = false;
  // set timeout

  esp_err_t error_code = 0;

  Serial.println("Now Try WPS Button");

  WiFi.disconnect();
  // Smart Config Failed - now try WPS Button
#ifdef BC24
  BC24ThreeBlink(White, 1000);
#else
  vTaskDelay(1000 / portTICK_PERIOD_MS);
#endif
  long timeout;
  timeout = millis() +  timeOutSeconds * 1000;

  WiFi.onEvent(WiFiEvent);

  WiFi.mode(WIFI_MODE_STA);
  Serial.print("error_code=");
  Serial.println(error_code);


  Serial.println("Starting WPS");
#ifdef BC24
  BC24TwoBlink(White, 1000);
#else
  vTaskDelay(1000 / portTICK_PERIOD_MS);
#endif
  error_code = esp_wifi_wps_enable(&config);
#ifdef BC24DEBUG
  Serial.print("error_code=");
  Serial.println(error_code, HEX);
#endif

  error_code = esp_wifi_wps_start(0);
#ifdef BC24DEBUG
  Serial.print("error_code=");
  Serial.println(error_code, HEX);
#endif
  // attempt to connect to Wifi network:
  while (WiFi.status() != WL_CONNECTED) {
    // Connect to WPA/WPA2 network. Change this line if using open or WEP     network:
#ifdef BC24
    BC24TwoBlink(White, 1000);
#else
  vTaskDelay(1000 / portTICK_PERIOD_MS);
#endif
    Serial.print(".");
    if (timeout < millis())
    {
      break;
    }

  }
  if (WiFi.status() != WL_CONNECTED)
  {
    esp_wifi_wps_disable();
    Serial.println("WPS Failure");
    myWiFiPresent = false;
#ifdef BC24
    BC24TwoBlink(Red, 1000);
#else
  vTaskDelay(1000 / portTICK_PERIOD_MS);
#endif

  }
  else
  {
    myWiFiPresent = true;
    Serial.println("WPS Success - WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
#ifdef BC24
    BC24TwoBlink(Green, 1000);
#else
  vTaskDelay(1000 / portTICK_PERIOD_MS);
#endif
  }

  return myWiFiPresent;
}


//
// Use Local AP  (192.168.4.1)
//


bool localAPGetIP(long apTimeOutSeconds)
{

  bool myWiFiPresent;
  myWiFiPresent = false;

  // set up AP point for reading ssid/password since SmartConfig didn't work
  // Set up Wifi


#define WL_MAC_ADDR_LENGTH 6
  // Append the last two bytes of the MAC (HEX'd) to string to make unique
  uint8_t mac[WL_MAC_ADDR_LENGTH];
  WiFi.softAPmacAddress(mac);
  String macID = String(mac[WL_MAC_ADDR_LENGTH - 2], HEX) +
                 String(mac[WL_MAC_ADDR_LENGTH - 1], HEX);
  macID.toUpperCase();
  APssid = "BigCircle24-" + macID;


  //WiFiManager
  //Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;
#ifdef BC24DEBUG
  wifiManager.setDebugOutput(true);
#else
  wifiManager.setDebugOutput(false);
#endif
  //reset saved settings
  //wifiManager.resetSettings();
#ifdef BC24
  BC24OneBlink(White, 1000);

  Serial.println("Before Semaphore Give");
  xSemaphoreGive( xSemaphoreSingleBlink);   // Turn on single blink
  Serial.println("After Semaphore Give");
#else
  vTaskDelay(1000 / portTICK_PERIOD_MS);
#endif
  //set callback that gets called when connecting to previous WiFi fails, and enters Access Point mode
  wifiManager.setAPCallback(configModeCallback);
  //fetches ssid and pass and tries to connect
  //if it does not connect it starts an access point with the specified name
  wifiManager.setTimeout(apTimeOutSeconds);
  //and goes into a blocking loop awaiting configuration
  if (!wifiManager.autoConnect(APssid.c_str())) {
    Serial.println("failed to connect and hit timeout");
#ifdef BC24
    blinkLED(4, 300);  // blink 4, failed to connect
    BC24OneBlink(Red, 1000);
#else
  vTaskDelay(1000 / portTICK_PERIOD_MS);
#endif
    //reset and try again, or maybe put it to deep sleep
    //ESP.reset();
    //delay(1000);
    myWiFiPresent = false;
  }
#ifdef BC24
  xSemaphoreTake( xSemaphoreSingleBlink, 10);   // Turn off single blink
#endif
  if (WiFi.status()  == WL_CONNECTED)
  {
    myWiFiPresent = true;
#ifdef BC24
    BC24OneBlink(Green, 1000);
#else
  vTaskDelay(1000 / portTICK_PERIOD_MS);
#endif
  }


  return myWiFiPresent;
}


// for WPS
void WiFiEvent(WiFiEvent_t event, system_event_info_t info) {
  switch (event) {
    case SYSTEM_EVENT_STA_START:
      Serial.println("Station Mode Started");
      break;
    case SYSTEM_EVENT_STA_GOT_IP:
      Serial.println("Connected to :" + String(WiFi.SSID()));
      Serial.print("Got IP: ");
      Serial.println(WiFi.localIP());
      break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
      Serial.println("Disconnected from station, attempting reconnection");
      if (WPSReconnectCount < 10)
      {
        WiFi.reconnect();
        WPSReconnectCount++;

      }
      esp_wifi_wps_disable();
      delay(10);
      break;
    case SYSTEM_EVENT_STA_WPS_ER_SUCCESS:
      Serial.println("WPS Successful, stopping WPS and connecting to: " + String(WiFi.SSID()));
      esp_wifi_wps_disable();
      delay(10);
      WiFi.begin();
      break;
    case SYSTEM_EVENT_STA_WPS_ER_FAILED:
      Serial.println("WPS Failed");
      esp_wifi_wps_disable();
      //esp_wifi_wps_enable(&config);
      //esp_wifi_wps_start(0);
      break;
    case SYSTEM_EVENT_STA_WPS_ER_TIMEOUT:
      Serial.println("WPS Timeout");
      esp_wifi_wps_disable();
      //esp_wifi_wps_enable(&config);
      //esp_wifi_wps_start(0);
      break;

    default:
      break;
  }
}


// Macro for Timing
#define runEvery(t) for (static uint16_t _lasttime;\
                         (uint16_t)((uint16_t)millis() - _lasttime) >= (t);\
                         _lasttime += (t))

// Instantiate classes
WiFiUDP UDP;
INA_Class INA1;
INA_Class INA2;

#if defined(THINGER)
ThingerESP8266 thing(THINGER_USERNAME, THINGER_DEVICE, THINGER_CREDENTIALS);
#endif

// Functions

// WiFi Managemement
#if defined (SMARTCONFIG)
void getWiFi()
{
  WiFi.mode(WIFI_STA);
  //WiFi.disconnect();
  wifi_station_set_auto_connect(true);
  wifi_station_set_hostname(HOST_NAME);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    int cnt = 0;
    //    Console3.print(".");
    if (cnt++ >= wifiMaxTries) {
      WiFi.beginSmartConfig();
      while (1) {
        delay(wifiRepeatInterval);
        if (WiFi.smartConfigDone())
        {
          Console3.println("SmartConfig Success");
          break;
        }
      }
    }
  }
  ip = WiFi.localIP();
}
#else
void getWiFi()
{
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  wifi_station_set_auto_connect(true);
  wifi_station_set_hostname(HOST_NAME);
  wifiConnectCounter = 1;
  Console3.println();
  while (WiFi.status() != WL_CONNECTED) {
    delay(wifiRepeatInterval);
    Console3.print(".");
    wifiConnectCounter++;
    if (wifiConnectCounter > wifiMaxTries) {
      delay(wifiRepeatInterval * 1000 * 1000);
      wifiConnectCounter = 0;
    }
  }
  ip = WiFi.localIP();
}
#endif

void disConnect()
{
  //  WiFi.disconnect(); //temporarily disconnect WiFi as it's no longer needed
  WiFi.mode(WIFI_OFF);
  // WiFi.forceSleepBegin();  can it save power?
  // WiFi.forceSleepWake();
}

void myIP()
{
  sprintf(charbuff, "IP= %03d.%03d.%03d.%03d", ip[0], ip[1], ip[2], ip[3]);
}

// Time management
void getNTP()
{
  configTime(MYTZ, NTP_SERVER);
  now = time(nullptr);
  Epoch = now;
}

void getEpoch()
{
  now = time(nullptr);
  Epoch = now;
}

void getTimeData()
{
  timeinfo  = localtime(&now);  // cf: https://www.cplusplus.com/reference/ctime/localtime/
  Second    = timeinfo->tm_sec;
  Minute    = timeinfo->tm_min;
  Hour      = timeinfo->tm_hour;
  Weekday   = timeinfo->tm_wday + 1 ;
  Day       = timeinfo->tm_mday;
  Month     = timeinfo->tm_mon + 1;
  Year      = timeinfo->tm_year + 1900; //returns years since 1900
  strftime (DayName , 12, "%A", timeinfo); //cf: https://www.cplusplus.com/reference/ctime/strftime/
  strftime (MonthName, 12, "%B", timeinfo);
  strftime (Time, 10, "%T", timeinfo);
  strftime (Date, 12, "%d/%m/%Y", timeinfo);
}

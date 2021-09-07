// Macro for Timing
#define runEvery(t) for (static uint16_t _lasttime;\
                         (uint16_t)((uint16_t)millis() - _lasttime) >= (t);\
                         _lasttime += (t))

// Instantiate classes
WiFiUDP UDP;
INA_Class INA;

#if defined(THINGER)
ThingerESP8266 thing(THINGER_USERNAME, THINGER_DEVICE, THINGER_DEVICE_CREDENTIALS);
#endif

# if defined(INFLUX)
InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN, InfluxDbCloud2CACert);
#endif

// Functions

// WiFi Managemement

void getWiFi()
{
#ifdef ERASE_WIFI_CREDENTIALS
  WiFi.disconnect(true);
#endif
  WiFi.reconnect();
  WiFi.waitForConnectResult();
  WiFi.hostname(DEVICE_NAME);
  if (WiFi.status() != WL_CONNECTED)
  {
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    //    WiFi.setAutoConnect();
    //    WiFi.setAutoReconnect();
    wifiConnectCounter = 1;
    Console4.println();
    while (WiFi.status() != WL_CONNECTED)
    {
      delay(wifiRepeatInterval);
      Console4.print(".");
      wifiConnectCounter++;
      if (wifiConnectCounter > wifiMaxTries)
      {
        //        if (WiFi.status() == WL_NO_SSID_AVAIL) Console4.println("SSID?");
        //        if (WiFi.status() == WL_CONNECT_WRONG_PASSWORD) Console4.println("PASS?");
        Console4.printf("\n\nBad SSID or PASS?\n");
        //Turn off WiFi
        WiFi.forceSleepBegin();
        // WiFi.mode(WIFI_OFF);
        Console4.printf("\nRunning offline, enter time date & time (dd/mm/yyyy hh:mm:ss) before using the menu\n");
        break;
      }
      else
      {
        Console4.printf("RSSI: %d dBm\n", WiFi.RSSI());
      }
    }
    delay(100);
  }
  ip = WiFi.localIP();
}

void myIP()
{
  sprintf(charbuff, "IP= %03d.%03d.%03d.%03d", ip[0], ip[1], ip[2], ip[3]);
}

// Time management
void getNTP()
{
  configTime(TZ, NTP_SERVER);
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
  strftime (DayName,   12, "%A", timeinfo); //cf: https://www.cplusplus.com/reference/ctime/strftime/
  strftime (MonthName, 12, "%B", timeinfo);
  strftime (Time,      10, "%T", timeinfo);
  strftime (Date,      12, "%d/%m/%Y", timeinfo);
}

void setTimefromSerial()
{
  if (Serial.available() > 0)
  {
    // read in the user input
    Day = Serial.parseInt();
    Month = Serial.parseInt();
    Year = Serial.parseInt();
    Hour = Serial.parseInt();
    Minute = Serial.parseInt();
    Second = Serial.parseInt();
    Console1.printf("\nNew time: %u/%u/%u %u:%u:%u\n", Day, Month, Year, Hour, Minute, Second);
    boolean validDate = (inRange(Day, 1, 31) && inRange(Month, 1, 12) && inRange(Year, 2021, 2031));
    boolean validTime = (inRange(Hour, 0, 23) && inRange(Minute, 0, 59) && inRange(Second, 0, 59));
    if (validTime && validDate)
    {
      configTime(TZ, 0, "pool.ntp.org");    // Repair timezone
      tzset();

      struct tm t;                         //Prepare time strucure
      time_t t_of_day;
      t.tm_year = Year - 1900; // Year - 1900
      t.tm_mon = Month - 1;     // Month, where 0 = jan
      t.tm_mday = Day ;      // Day of the month
      t.tm_hour = Hour;
      t.tm_min = Minute;
      t.tm_sec = Second;
      t.tm_isdst = -1;         // Is DST on? 1 = yes, 0 = no, -1 = unknown
      t_of_day = mktime(&t);
      Console4.printf("Epoch = %10lu", t_of_day);
      struct timeval tv;                   //Extending to mandatory microseconds
      tv.tv_sec = t_of_day;  // epoch time (seconds)
      tv.tv_usec = 0;    // microseconds
      settimeofday(&tv, 0);                //Setting Clock
      Console4.printf("\nTime set, Menu ready to listen\n");
    }
  }
}

void buffTimeData()
{
  strftime(charbuff, sizeof(charbuff), "%R %x", timeinfo);
}

bool inRange(int x, int low, int high) {
  if (x >= low && x <= high)
    return true;
  return false;
}

//Conversions Volt <-> PWM
float pwm2bat(unsigned int pwm)
{
  float bat;
  if (not high_power_enable)
  {
    bat = float(map(pwm, 1024, 0, INJ_LP_MIN, INJ_LP_MAX) / 1000);
  } else {
    bat = float(map(pwm, 1024, 0, INJ_HP_MIN, INJ_HP_MAX) / 1000);
  }
  return bat;
}

unsigned int  bat2pwm(float bat)
{
  unsigned int pwm;
  if (high_power_enable)
  {
    pwm = map(int(bat * 1000), INJ_HP_MIN, INJ_HP_MAX, 1024, 0 );
  } else {

  } pwm = map(int(bat * 1000), INJ_LP_MIN, INJ_LP_MAX, 1024, 0 );
  return pwm;
}

float pwm2aux(unsigned int pwm)
{
  float aux = float(map(pwm, 1024, 0, INJ_AUX_MIN, INJ_AUX_MAX) / 1000);
  return aux;
}

unsigned int aux2pwm(float aux)
{
  unsigned int pwm = map(int(aux * 1000), INJ_AUX_MIN, INJ_AUX_MAX, 1024, 0);
  return pwm;
}

/*boolean time_dashboard.phase()
  {
  phase_timer ++;
  phase_duration[dashboard.phase] = phase_timer;
  expired = false;
  if (phase_timer > phase_limit[dashboard.phase]) expired = true;
  return expired;
  }
*/

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

// Functions

// WiFi Managemement

void getWiFi()
{
#ifdef ERASE_WIFI_CREDENTIALS
  WiFi.disconnect(true);
#endif
  WiFi.reconnect();
  WiFi.waitForConnectResult();
  WiFi.hostname(HOST_NAME);
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
        Console4.printf("\nRunning offline, back in the 70's\n");
        break;
      }
      else
      {
        Console4.printf("RSSI: %d dBm\n", WiFi.RSSI());
      }
    }
    ip = WiFi.localIP();
  }
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
    Console1.printf("\nI have understood %u/%u/%u %u:%u:%u\n", Day, Month, Year, Hour, Minute, Second);
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
      Console4.printf("\nWelcome back in the present!, Menu ready to listen\n");
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

int do_perturb_and_observe_mppt() { // performs Perturb & Observe MPPT; changes pwm_value to maximise power
  if (dashboard.Wbat < last_power) { // power has gone down - change direction
    bat_delta = - bat_delta;
  }       // "else" power is the same or increased  - keep direction
  dashboard.Wbat < last_power;
  bat_injection += bat_delta;
  bat_injection = constrain (bat_injection, 0, 255);
  analogWrite (PWM_AUX, bat_injection);
}

int do_incremental_conductance_mppt() { // performs Inc Conductance MPPT; changes pwm_value to maximise power
  //place code here
}

int do_CV () { // performs fix voltage operation at target
  if (dashboard.Vbat > bat_target) {
    aux_delta = abs(aux_delta);
  } else {                // decrease pwm value
    aux_delta = - abs(aux_delta);
  }
  bat_injection += aux_delta;
  bat_injection = constrain (bat_injection, 0, 1024);
  analogWrite (PWM_AUX, bat_injection);
}

int do_CC () { // performs fix current operation at target
  if (dashboard.Ibat > bat_target) { // increase pwm value
    aux_delta = abs(aux_delta);
  } else {                // decrease pwm value
    aux_delta = - abs(aux_delta);
  }
  bat_injection += aux_delta;
  bat_injection = constrain (bat_injection, 0, 1024);
  analogWrite (PWM_AUX, bat_injection);
}

float pwm2volt (float pwm)
{
  int volt = map(pwm, 1024, 0, long(MIN_VOLT * 100), long(MAX_VOLT * 100));
  return volt;
}

float volt2pwm (float volt)
{
  int pwm = map(volt, long(MIN_VOLT * 100), long(MAX_VOLT * 100), 1024, 0);
  return pwm;
}

/*boolean time_phase()
  {
  phase_timer ++;
  phase_duration[phase] = phase_timer;
  expired = false;
  if (phase_timer > phase_limit[phase]) expired = true;
  return expired;
  }*/

void do_CVCC () {   // stay at or below voltage and current targets
  if (dashboard.Ibat > bat_target || dashboard.Vbat > bat_target) { // increase pwm value to decrease charging
    bat_delta = abs(bat_delta);
    bat_injection += bat_delta;
    bat_injection = constrain (bat_injection, 0, 255);
    analogWrite (PWM_BAT, bat_injection);
  } else {                // increase charging subject to capacity
    do_perturb_and_observe_mppt();
  }
}

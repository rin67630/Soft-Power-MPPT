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
  strftime (DayName,   12, "%A", timeinfo); //cf: https://www.cplusplus.com/reference/ctime/strftime/
  strftime (MonthName, 12, "%B", timeinfo);
  strftime (Time,      10, "%T", timeinfo);
  strftime (Date,      12, "%d/%m/%Y", timeinfo);
}

int do__perturb_and_observe_mppt() { // performs Perturb & Observe MPPT; changes pwm_value to maximise power
  if (dashboard.Wbat < last_power) { // power has gone down - change direction
    bat_delta = - bat_delta;
  }       // "else" power is the same or increased  - keep direction
  dashboard.Wbat < last_power;
  bat_injection += bat_delta;
  bat_injection = constrain (bat_injection, 0, 255);
  analogWrite (PWM_AUX, bat_injection);
}

int do__incremental_conductance_mppt() { // performs Inc Conductance MPPT; changes pwm_value to maximise power
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
    do__perturb_and_observe_mppt();
  }
}

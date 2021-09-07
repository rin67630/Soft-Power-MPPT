void setup()
{
  delay(1000); // Wait for serial monitor to be started
  // Serial initialisation
  Serial.begin (SERIAL_SPEED); // On USB port
  Serial1.begin(SERIAL_SPEED); // On GPIO2 / D4
  Serial.setDebugOutput(true);
  Wire.begin(SDA, SCL);
  Console4.print("Reset by: "); Console4.print(ESP.getResetReason());
  Console4.printf("\nESP-Karajan at work,Serial @ %u Baud\nTrying to connect\n\n", SERIAL_SPEED);

  pinMode(RELAY1   , OUTPUT);
  pinMode(RELAY2   , OUTPUT);
  pinMode(LP_BUCK  , OUTPUT);
  pinMode(HP_BUCK  , OUTPUT);
  pinMode(AUX_BUCK , OUTPUT);
  /*
    // Witty Color LEDs
    pinMode(STDLED, OUTPUT);
    pinMode(REDLED, OUTPUT);
    pinMode(GRNLED, OUTPUT);
    pinMode(BLULED, OUTPUT);
  */

  // Start dashboard with defaults
  dashboard.CVbat = 14.400 ;
  dashboard.CCbat = 3.000 ;
  dashboard.CVpan = 19.000 ;
  dashboard.CVaux = 5.0 ;
  bat_injection = INJ_NEUTRAL;
  aux_injection = INJ_NEUTRAL;
  aux_enable = false;

  // Start outputs with defaults
  digitalWrite(RELAY1, not relay1_value);
  digitalWrite(RELAY2, not relay2_value);
  digitalWrite(HP_BUCK, high_power_enable);
  digitalWrite(LP_BUCK, not high_power_enable);
  digitalWrite(AUX_BUCK, aux_enable);
  analogWrite (PWM_BAT, bat_injection);
  analogWrite (PWM_AUX, aux_injection);

#ifndef DISPLAY_IS_NONE
  // Initialising the UI will init the display too.
  display.init();
  delay(1000);
#ifdef DISPLAY_REVERSED
  display.flipScreenVertically();
#endif
  display.clear();
  delay(50);
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0, 0,  DEVICE_NAME);
  display.drawString(0, 12, "Try connect..");
  display.display();
#endif

#if defined BAT_SOURCE_IS_INA
  // INA 226 Panel Sensor
  INA.begin( AMPERE0 , SHUNT0, 0);      // Define max Ampere, Shunt value, Address
  INA.setBusConversion(100);            // Maximum conversion time 100ms
  INA.setShuntConversion(100);          // Maximum conversion time 100ms
  INA.setAveraging(32);                  // Average each reading n-times
  INA.setMode(INA_MODE_CONTINUOUS_BOTH); // Bus/shunt measured continuously
  //  INA.alertOnPowerOverLimit(true;450000); //Set alert when power over 45W.
#endif

#if defined PAN_SOURCE_IS_INA
  // INA 226 Battery Sensor
  INA.begin( AMPERE1 , SHUNT1, 1);      // Define max Ampere, Shunt value, Address
  INA.setBusConversion(100);            // Maximum conversion time 100ms
  INA.setShuntConversion(100);          // Maximum conversion time 100ms
  INA.setAveraging(32);                 // Average each reading n-times
  INA.setMode(INA_MODE_CONTINUOUS_BOTH); // Bus/shunt measured continuously
  //  INA.alertOnPowerOverLimit(true;450000); //Set alert when power over 45W.
#endif

#if defined AUX_SOURCE_IS_INA
  // INA 226 Panel Sensor
  INA.begin( AMPERE2 , SHUNT2, 2);      // Define max Ampere, Shunt value, Address
  INA.setBusConversion(100);            // Maximum conversion time 100ms
  INA.setShuntConversion(100);          // Maximum conversion time 100ms
  INA.setAveraging(32);                  // Average each reading n-times
  INA.setMode(INA_MODE_CONTINUOUS_BOTH); // Bus/shunt measured continuously
  //  INA.alertOnPowerOverLimit(true;50000); // Set alert when power over 5W.
#endif

  // Networking and Time
  getWiFi();
  WiFi.setOutputPower(WIFI_POWER);
  delay(100);

  if (WiFi.status() == WL_CONNECTED)
  {
    // Over the Air Framework
    ArduinoOTA.onStart([]()
    {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH) {
        type = "sketch";
      } else { // U_FS
        type = "filesystem";
      }
      // NOTE: if updating FS this would be the place to unmount FS using FS.end()
      Console4.println("Start updating " + type);
    });
    ArduinoOTA.onEnd([]()
    {
      Console4.println("\nEnd");
    });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total)
    {
      Console4.printf("Progress: %u%%\r", (progress / (total / 100)));
    });
    ArduinoOTA.onError([](ota_error_t error)
    {
      Console4.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) {
        Console4.printf("Auth Failed\n");
      } else if (error == OTA_BEGIN_ERROR) {
        Console4.printf("Begin Failed\n");
      } else if (error == OTA_CONNECT_ERROR) {
        Console4.printf("Connect Failed\n");
      } else if (error == OTA_RECEIVE_ERROR) {
        Console4.printf("Receive Failed\n");
      } else if (error == OTA_END_ERROR) {
        Console4.printf("End Failed\n");
      }
    });
    ArduinoOTA.setHostname(DEVICE_NAME);
    ArduinoOTA.begin();
    Console4.printf("OTA Ready\n MAC address: %s\nHostname: %s \n", WiFi.macAddress().c_str(), WiFi.hostname().c_str());
#ifndef DISPLAY_IS_NONE

    sprintf(charbuff, "IP= %03d . %03d",  ip[2], ip[3]); display.drawString(0, 24, charbuff);
    display.display();
    delay(2000);
#endif
    getNTP();
    // Begin listening to UDP port
    UDP.begin(UDP_PORT);
    Console4.printf("UDP ports: %u, %u\n", UDP_PORT, UDP_PORT + 1);
    // IOT initialisation
#if defined (THINGER)
    Console4.printf(" Initializing Thinger\n");
    // definition of structures for transmission
    // digital pin control example (i.e. turning on/off a light, a relay, configuring a parameter, etc)
    // resource output example (i.e. reading a sensor value) https://docs.thinger.io/coding#define-output-resources
    // https://docs.thinger.io/coding#read-multiple-data

    // it is a bit confusing, but Thinger code placed in setup will be exceuted **periodically when required by the dashboard.

    thing["menu"] << [](pson & in) {
      displayPage    = in["displayPage"];
      displaySubPage = in["displaySubPage"];
      serialPage     = in["serialPage"];
    };

    thing["relay1"] << [](pson & in) {
      if (in.is_empty()) {
        in = relay1_value;
      } else {
        relay1_value = in;
      }
    };
    thing["relay2"] << [](pson & in) {
      if (in.is_empty()) {
        in = relay2_value;
      } else {
        relay2_value = in;
      }
    };
    thing["DC_out1"] << [](pson & in)
    {
      if (in.is_empty()) {
        in = high_power_enable;
      } else {
        yield();
        // high_power_enable = in;
      }
    };

    thing["DC_out2"] << [](pson & in)
    {
      if (in.is_empty()) {
        in = aux_enable;
      } else {
        yield();
        aux_enable = in;
      }
    };

 // Setpoint processing: Thinger input is currently only integer, so slider value is * 1000 and ESP processing makes a float out of it.  
    thing["scv"]  = [](pson & in, pson & out)
    {
      if (in.is_empty())
      {
        in = CVbat * 1000;
      } else {
      dashboard.CVbat = float(in) / 1000;
      }
      out = dashboard.CVbat;
      dashboard.CVinj = dashboard.CVbat;      
    };

    thing["scc"]  = [](pson & in, pson & out)
    {
      if (in.is_empty())
      {
        in = CCbat * 1000;
      } else {
      dashboard.CCbat = float(in) / 1000;
      }
      out = dashboard.CCbat;
      dashboard.CCinj = dashboard.CCbat;
    };

    thing["scp"]  = [](pson & in, pson & out)
    {
      if (in.is_empty())
      {
        in = CVpan * 1000;
      } else {
      dashboard.CVpan = float(in) / 1000;
      }
      out = dashboard.CVpan;
    };
    
    thing["aux"]  = [](pson & in, pson & out)
    {
      if (in.is_empty())
      {
        in = CVaux * 1000;
      } else {
      dashboard.CVaux = float(in) / 1000;
      }
      out = dashboard.CVaux;
    };
    
    thing["mode"]  = [](pson & in, pson & out)
    {
      if (in.is_empty())
      {
        in = dashboard.modus;
      } else {
        dashboard.modus = in;
      }
      out = modus_description[dashboard.modus];
    };

    thing["control"] >> [](pson & out)
    {
      out["bat_CV"]          = dashboard.CVbat;
      out["bat_CC"]          = dashboard.CCbat;
      out["pan_CV"]          = dashboard.CVpan;
      out["inj_CV"]          = dashboard.CVinj;
      out["inj_CC"]          = dashboard.CCinj;      
      out["inj_DV"]          = dashboard.DVinj;
      out["aux_CV"]          = dashboard.CVaux;
      out["bat_inj"]         = bat_injection;
      out["aux_inj"]         = aux_injection;
      out["relay1"]          = relay1_value;
      out["relay2"]          = relay2_value;
      out["DC1"]             = high_power_enable;
      out["DC2"]             = aux_enable;
      out["phaseTXT"]        = phase_description[dashboard.phase];
      out["modusTXT"]        = modus_description[dashboard.modus];
    };

    thing["measure"] >> [](pson & out)
    {
      out["Iin"]             = dashboard.Ipan ;
      out["Vbat"]            = dashboard.Vbat ;
      out["Win"]             = dashboard.Wpan ;
      out["Ipan"]            = dashboard.Ipan ;
      out["Vpan"]            = dashboard.Vpan ;
      out["Wpan"]            = dashboard.Wpan ;
      out["Itot"]            = dashboard.Ipan + dashboard.Iaux;
      out["Iout"]            = dashboard.Iaux ;
      out["Vaux"]            = dashboard.Vaux ;
      out["Wout"]            = dashboard.Waux ;
      out["ohm"]             = dashboard.internal_resistance ;
      out["efficiency"]      = dashboard.efficiency;
      out["percent_charged"] = dashboard.percent_charged;
    };

    thing["weather"] >> [](pson & out)
    {
      out["temperature"] = outdoor_temperature;
      out["humidity"]    = outdoor_humidity;
      out["pressure"]    = outdoor_pressure;
      out["wind"]        = wind_speed;
      out["direction"]   = wind_direction;
      out["summary"]     = weather_summary;
    };

    thing["DAY"] >> [](pson & out)
    {
      out["BAhDay"] = AhBat[27];
      out["BV@0h"]  = voltageAt0H;
      out["BVDiff"] = voltageDelta;
      out["B00h"] = AhBat[0];
      out["B01h"] = AhBat[1];
      out["B02h"] = AhBat[2];
      out["B03h"] = AhBat[3];
      out["B04h"] = AhBat[4];
      out["B05h"] = AhBat[5];
      out["B06h"] = AhBat[6];
      out["B07h"] = AhBat[7];
      out["B08h"] = AhBat[8];
      out["B09h"] = AhBat[9];
      out["B10h"] = AhBat[10];
      out["B11h"] = AhBat[11];
      out["B12h"] = AhBat[12];
      out["B13h"] = AhBat[13];
      out["B14h"] = AhBat[14];
      out["B15h"] = AhBat[15];
      out["B16h"] = AhBat[16];
      out["B17h"] = AhBat[17];
      out["B18h"] = AhBat[18];
      out["B19h"] = AhBat[19];
      out["B20h"] = AhBat[20];
      out["B21h"] = AhBat[21];
      out["B22h"] = AhBat[22];
      out["B23h"] = AhBat[23];
    };

    thing["HOUR"] >> [](pson & out)
    {
      out["Vbat"]         = dashboard.Vbat;
      out["Iin"]         = dashboard.Ipan;
      out["Win"]         = dashboard.Wpan;
      out["Ipan"]         = dashboard.Ipan ;
      out["Vpan"]         = dashboard.Vpan ;
      out["Wpan"]         = dashboard.Wpan ;
      out["VbatPlot"]     = dashboard.Vbat - 10;
      out["VpanPlot"]     = dashboard.Vpan - 10 ;
      out["Ohm"]          = dashboard.internal_resistance ;
      out["AhBat"]        = AhBat[25];
      out["percent_charged"] = dashboard.percent_charged;

      out["temperature"]  = outdoor_temperature;
      out["humidity"]     = outdoor_humidity;
      out["pressure"]     = outdoor_pressure;
      out["wind"]         = wind_speed;
      out["direction"]    = wind_direction;
      out["summary"]      = weather_summary;
    };

    thing["MIN"] >> [](pson & out)
    {
      out["Iin"]         = dashboard.Ipan ;
      out["Vbat"]         = dashboard.Vbat ;
      out["Win"]         = dashboard.Wpan ;
      out["Ipan"]         = dashboard.Ipan ;
      out["Vpan"]         = dashboard.Vpan ;
      out["Wpan"]         = dashboard.Wpan ;
      out["VbatPlot"]     = dashboard.Vbat - 10;
      out["VpanPlot"]     = dashboard.Vpan - 10 ;
      out["Iout"]         = dashboard.Iaux ;
      out["Vaux"]         = dashboard.Vaux ;
      out["Wout"]         = dashboard.Waux ;
      out["AhBat"]        = AhBat[25];
      out["efficiency"]   = dashboard.efficiency;
    };

    //Communication with Thinger.io
    thing.handle();
    delay(1000); // Wait for contact to happen.
    // Retrieve Persistance values

    pson persistance;
#if (defined BAT_SOURCE_IS_INA) || (defined BAT_SOURCE_IS_UDP)
    thing.get_property("persistance", persistance);
    currentInt          = persistance["currentInt"];
    nCurrent            = persistance["nCurrent"];
    AhBat[25]           = persistance["Ah/hour"];
    AhBat[27]           = persistance["Ah/yesterday"];
    voltageDelta        = persistance["voltageDelta"];
    voltageAt0H         = persistance["voltageAt0H"];
#endif
    outdoor_temperature = persistance["temperature"];
    outdoor_humidity    = persistance["humidity"];
    outdoor_pressure    = persistance["pressure"];
    wind_speed          = persistance["wind"];
    wind_direction      = persistance["direction"];

    pson BATmAh;
    thing.get_property("BAT", BATmAh);  // 0..23=hour, 25=dashboard.Ipan, 26=BATmAh 24h, 27= AhBatDay, 28=AhBatNight, 29=AhBat22-24
    AhBat[0]  = BATmAh["00h"];
    AhBat[1]  = BATmAh["01h"];
    AhBat[2]  = BATmAh["02h"];
    AhBat[3]  = BATmAh["03h"];
    AhBat[4]  = BATmAh["04h"];
    AhBat[5]  = BATmAh["05h"];
    AhBat[6]  = BATmAh["06h"];
    AhBat[7]  = BATmAh["09h"];
    AhBat[8]  = BATmAh["08h"];
    AhBat[9]  = BATmAh["09h"];
    AhBat[10] = BATmAh["10h"];
    AhBat[11] = BATmAh["11h"];
    AhBat[12] = BATmAh["12h"];
    AhBat[13] = BATmAh["13h"];
    AhBat[14] = BATmAh["14h"];
    AhBat[15] = BATmAh["15h"];
    AhBat[16] = BATmAh["16h"];
    AhBat[17] = BATmAh["17h"];
    AhBat[18] = BATmAh["18h"];
    AhBat[19] = BATmAh["19h"];
    AhBat[20] = BATmAh["20h"];
    AhBat[21] = BATmAh["21h"];
    AhBat[22] = BATmAh["22h"];
    AhBat[23] = BATmAh["23h"];
    AhBat[25] = BATmAh["LastHour"];
    AhBat[27] = BATmAh["Yesterday"];
    AhBat[26] = BATmAh["Today"];
/*
// no Thinger
      // Persistance over Structure and memcpy.
      EEPROM.get(addr,data);
      EEPROM.put(addr,data);
      EEPROM.commit();
*/
#endif  //end if defined THINGER
  }

  delay(1000);

  getEpoch();            // writes the Epoch (Numbers of seconds till 1.1.1970...
  getTimeData();         // breaks down the Epoch into discrete values.

  sprintf(charbuff, "Now is %s, %02d %s %04d %02d:%02d:%02d. Epoch =%10lu\n", DayName, Day, MonthName, Year, Hour, Minute, Second, Epoch);  Console4.println(charbuff);

#if defined BAT_SOURCE_IS_NONE
  dashboard.Vbat = (MAX_VOLT + MIN_VOLT) / 2;
  dashboard.Ipan = 0;
#else

#endif

  // Initialisations.

  serialPage = '0';           // default reporting page AK Modulbus
  //  digitalWrite(STDLED, true);

}
//end Setup

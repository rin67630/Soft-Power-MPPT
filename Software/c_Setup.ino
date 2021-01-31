void setup()
{
  delay(3000); // Wait for serial monitor to be started
  // Serial initialisation
  Serial.begin (SERIAL_SPEED); // On USB port
  Serial1.begin(SERIAL_SPEED); // On GPIO2 / D4
  Wire.begin(SDA, SCL);
  Console3.printf("\n\n\nESP-Karajan at work,\nSerial @ %u Baud\n", SERIAL_SPEED);

  pinMode(RELAY1   , OUTPUT);
  pinMode(RELAY2   , OUTPUT);
  pinMode(LP_BUCK  , OUTPUT);
  pinMode(HP_BUCK , OUTPUT);
  pinMode(AUX_BUCK  , OUTPUT);
  pinMode(PWM_BAT , OUTPUT);
  pinMode(PWM_AUX ,   OUTPUT);
  /*
    // Witty Color LEDs
    pinMode(STDLED, OUTPUT);
    pinMode(REDLED, OUTPUT);
    pinMode(GRNLED, OUTPUT);
    pinMode(BLULED, OUTPUT);
  */
  
  bat_injection = INJ_NEUTRAL;
  digitalWrite(RELAY1, not relay1_value);
  digitalWrite(RELAY2, not relay2_value);
  digitalWrite(HP_BUCK, high_power_buck_value);
  digitalWrite(LP_BUCK, not high_power_buck_value);
  digitalWrite(AUX_BUCK, aux_buck_value);
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
  display.drawString(0, 0,  HOST_NAME);
  display.drawString(0, 12, "Getting online..");
  display.display();
#endif


  // Networking and Time
  getWiFi();
  ArduinoOTA.setHostname(HOST_NAME);

  //WiFi.printDiag(Serial);
  Console3.printf("\MAC address: %s , \nHostname: %s \nIP address::", WiFi.macAddress().c_str(), WiFi.hostname().c_str());
  Console3.println(WiFi.localIP());

#ifndef DISPLAY_IS_NONE
  display.drawString(0, 24, "IP=");
  sprintf(charbuff, "IP= %03d.%03d",  ip[2], ip[3]); display.drawString(0, 24, charbuff);
  display.display();
  delay(6000);
#endif

  getNTP();
  delay(3000);

  getEpoch();            // writes the Epoch (Numbers of seconds till 1.1.1970...
  getTimeData();         // breaks down the Epoch into discrete values.

  sprintf(charbuff, "Now is %02d:%02d:%02d. The Epoch is: %10lu\r\nDate is %s, %02d %s %04d", Hour, Minute, Second, Epoch, DayName, Day, MonthName, Year);
  Console3.println(charbuff);
  
  



  // Over the Air Framework
  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_FS
      type = "filesystem";
    }
    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    Console3.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Console3.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Console3.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Console3.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Console3.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Console3.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Console3.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Console3.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Console3.println("End Failed");
    }
  });

  // Begin listening to UDP port
  UDP.begin(UDP_PORT);
  Console3.print("Communicating on UDP port: ");
  Console3.print(UDP_PORT);

  // Weather
  //myPlace.setLocation( 51.3683, 6.9293 );
  //myPlace.setUnit("metric");



#if defined AUX_SOURCE_IS_INA
  // INA 226 Panel Sensor
  INA.begin( AMPERE2 , SHUNT2, 2);      // Define max Ampere, Shunt value, Address
  INA.setBusConversion(8244);            // Maximum conversion time 8.244ms
  INA.setShuntConversion(8244);          // Maximum conversion time 8.244ms
  INA.setAveraging(32);                  // Average each reading n-times
  INA.setMode(INA_MODE_CONTINUOUS_BOTH); // Bus/shunt measured continuously
  //  INA.alertOnPowerOverLimit(true;50000); // Set alert when power over 5W.
#endif

#if defined PAN_SOURCE_IS_INA
  // INA 226 Panel Sensor
  INA.begin( AMPERE0 , SHUNT0, 0);      // Define max Ampere, Shunt value, Address
  INA.setBusConversion(8244);            // Maximum conversion time 8.244ms
  INA.setShuntConversion(8244);          // Maximum conversion time 8.244ms
  INA.setAveraging(32);                  // Average each reading n-times
  INA.setMode(INA_MODE_CONTINUOUS_BOTH); // Bus/shunt measured continuously
  //  INA.alertOnPowerOverLimit(true;450000); //Set alert when power over 45W.
#endif

#if defined BAT_SOURCE_IS_INA
  // INA 226 Battery Sensor
  INA.begin( AMPERE1 , SHUNT1, 1);      // Define max Ampere, Shunt value, Address
  INA.setBusConversion(8244);            // Maximum conversion time 8.244ms
  INA.setShuntConversion(8244);          // Maximum conversion time 8.244ms
  INA.setAveraging(32);                 // Average each reading n-times
  INA.setMode(INA_MODE_CONTINUOUS_BOTH); // Bus/shunt measured continuously
  //  INA.alertOnPowerOverLimit(true;450000); //Set alert when power over 45W.
#endif

#if defined BAT_SOURCE_IS_NONE
  dashboard.Vbat = (MAX_VOLT + MIN_VOLT) / 2;
  dashboard.Ibat = 0;
#else

#endif

  // IOT initialisation
#if defined (THINGER)
  // definition of structures for transmission
  // digital pin control example (i.e. turning on/off a light, a relay, configuring a parameter, etc)
  // resource output example (i.e. reading a sensor value) https://docs.thinger.io/coding#define-output-resources
  //https://docs.thinger.io/coding#read-multiple-data

  thing["menu"] << [](pson & in) {
    displayPage    = in["displayPage"];
    displaySubPage = in["displaySubPage"];
    serialPage     = in["serialPage"];
  };

  thing["relay1"] << [](pson & in) {
    if (in.is_empty()) {
      in = relay1_value;
    }
    else {
      relay1_value = in;
    }
  };
  thing["relay2"] << [](pson & in) {
    if (in.is_empty()) {
      in = relay2_value;
    }
    else {
      relay2_value = in;
    }
  };
  thing["DC_out1"] << [](pson & in) {
    if (in.is_empty()) {
      in = high_power_buck_value;
    }
    else {
      high_power_buck_value = in;
    }
  };
  thing["DC_out2"] << [](pson & in) {
    if (in.is_empty()) {
      in = aux_buck_value;
    }
    else {
      aux_buck_value = in;
    }
  };

  thing["scc"] << inputValue(bat_injection);
  thing["aux"] << inputValue(aux_injection);

  thing["control"] >> [](pson & out)
  {
    out["scc_inj"]         = bat_injection;
    out["scc_mvolt"]       = bat_injection_mvolt;
    out["scc_tar"]         = scc_target;
    out["aux_inj"]         = aux_injection;
    out["aux_mvolt"]       = aux_injection_mvolt;
    out["aux_tar"]         = aux_target;
    out["relay1"]          = relay1_value;
    out["relay2"]          = relay2_value;
    out["DC1"]             = high_power_buck_value;
    out["DC2"]             = aux_buck_value;
  };

  thing["measure"] >> [](pson & out)
  {
    out["Ibat"]            = dashboard.Ibat ;
    out["Vbat"]            = dashboard.Vbat ;
    out["Wbat"]            = dashboard.Wbat ;
    out["Ipan"]            = dashboard.Ipan ;
    out["Vpan"]            = dashboard.Vpan ;
    out["Wpan"]            = dashboard.Wpan ;
    out["Iaux"]            = dashboard.Iaux ;
    out["Vaux"]            = dashboard.Vaux ;
    out["Waux"]            = dashboard.Waux ;
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
    out["BAhDay"] = AhBat[26];
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
    out["temperature"]  = outdoor_temperature;
    out["humidity"]     = outdoor_humidity;
    out["pressure"]     = outdoor_pressure;
    out["wind"]         = wind_speed;
    out["direction"]    = wind_direction;
    out["summary"]      = weather_summary;
    out["Vbat"]         = dashboard.Vbat;
    out["Ibat"]         = dashboard.Ibat;
    out["Wbat"]         = dashboard.Wbat;
    out["Ipan"]         = dashboard.Ipan ;
    out["Vpan"]         = dashboard.Vpan ;
    out["Wpan"]         = dashboard.Wpan ;
    out["Ohm"]          = dashboard.internal_resistance ;
    out["percent_charged"] = dashboard.percent_charged;
  };

  thing["MIN"] >> [](pson & out)
  {
    out["Ibat"]         = dashboard.Ibat ;
    out["Vbat"]         = dashboard.Vbat ;
    out["Wbat"]         = dashboard.Wbat ;
    out["Ipan"]         = dashboard.Ipan ;
    out["Vpan"]         = dashboard.Vpan ;
    out["Wpan"]         = dashboard.Wpan ;
    out["Iaux"]         = dashboard.Iaux ;
    out["Vaux"]         = dashboard.Vaux ;
    out["Waux"]         = dashboard.Waux ;
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
  AhBat[26]           = persistance["Ah/yesterday"];
  voltageDelta        = persistance["voltageDelta"];
  voltageAt0H         = persistance["voltageAt0H"];
  dashboard.internal_resistance       = persistance["resistance"];
#endif
  outdoor_temperature = persistance["temperature"];
  outdoor_humidity    = persistance["humidity"];
  outdoor_pressure    = persistance["pressure"];
  wind_speed          = persistance["wind"];
  wind_direction      = persistance["direction"];

  pson BATmAh;
  thing.get_property("BAT", BATmAh);  // 0..23=hour, 25=dashboard.Ibat, 26=BATmAh 24h, 27= AhBatDay, 28=AhBatNight, 29=AhBat22-24
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
  AhBat[26] = BATmAh["Yesterday"];
  AhBat[27] = BATmAh["Today"];
#else // no Thinger
  /*
    // Persistance over Structure and memcpy.
    EEPROM.get(addr,data);
    EEPROM.put(addr,data);
    EEPROM.commit();
  */
#endif  //end if defined THINGER
  // Initialisations.

  serialPage = '0';           // default reporting page AK Modulbus
  //  digitalWrite(STDLED, true);

#if defined (OFFLINE)
  Console3.println(F("Going off-line "));
  WiFi.mode(WIFI_OFF);
  Console3.println (F("Sketch is now running offline with own time"));
#endif

  ArduinoOTA.begin();
  Console3.println("\nOTA-Ready");
  Console2.print("\nNAT|PKTime  |PKdB|Leq4|t10|Leq3|\n");
}
//end Setup

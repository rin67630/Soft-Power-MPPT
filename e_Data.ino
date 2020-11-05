void data125mSRun()
{
  // === ( Actions)  ====
  digitalWrite(RELAY1,!Relay1_value);
  digitalWrite(RELAY2,!Relay2_value);
  digitalWrite(DC_OUT1,DC_Out1_value);
  digitalWrite(DC_OUT2,DC_Out2_value);
  analogWrite (CC_CONTR,CC_value);
  analogWrite (CV_CONTR,CV_value);

 
  // === ( Getting noise level from A0 ) ===
  yield();
}

void data1SRun()
{
  yield();
  // === (Getting Weather from OpenWeatherMap every 5 minutes
#if defined WEATHER_SOURCE_IS_URL
  if (Minute % 5 == 1 && Second == 32)                    // call every 5 minutes
  {
    HTTPClient http;
    http.begin(OPEN_WEATHER_MAP_URL);
    int httpCode2 = http.GET();
    if (httpCode2 == HTTP_CODE_OK)
    {
      JSONpayload = http.getString();
      DynamicJsonDocument doc(1024);
      auto error = deserializeJson(doc, JSONpayload.c_str());
      if ( not error)
      {
        outdoor_temperature  = doc["main"]["temp"];
        outdoor_pressure     = doc["main"]["pressure"];
        outdoor_humidity     = doc["main"]["humidity"];
        wind_speed           = doc["wind"]["speed"];
        wind_direction       = doc["wind"]["deg"];
        cloudiness           = doc["clouds"]["all"];  // % Clouds
        const char* w        = doc["weather"][0]["description"]; weather_summary = w;
        sunrise              = doc["sys"]["sunrise"];
        sunset               = doc["sys"]["sunset"];
      }
    }
    http.end();
  }
#endif


  // === (Getting Battery values from another ESP over UDP
#if defined (BATTERY_SOURCE_IS_UDP)
  // I use a quick and dirty method called 'type punning' copying the memory block of a structure into an array of chars,
  // transmitting this array, and copying back the memory block of the array into the same structure on the other side.
  // I dont use any header info, only the difference of size permits to assign the received packets to sound or battery.
  // it is quick and damn efficient, but NOT portable and YOU must take care to have the same structures on both systems
  // and different sizes for Battery and Sound...

  int packetSize = UDP.parsePacket();
  // if (packetSize) Console3.printf("Packet size: %u, Battery size; %u \n", packetSize, sizeof(battery));
  // if (packetSize) digitalWrite(STDLED, false);    // Blink built-in LED on received packets
  if (packetSize == sizeof(battery))
  {
    UDP.read(batteryPayload, UDP_TX_PACKET_MAX_SIZE);
    memcpy(&battery, batteryPayload, sizeof(battery));
    // Console1.printf("Ah: %2.1f, Volt: %2.1f, Amp: %2.1f, Watt: %2.1f, %%Batt: %2.1f\n", AhBat, battery.voltage , battery.current , battery.power , percent_charged);
    delay(3);    // let built-in LED blink slightly stronger on battery packet
  }
  //digitalWrite(STDLED, true);
#endif

  // === ( Getting panel voltage from A0 ) ===
#if defined (PANEL_SOURCE_IS_A0)
  // Performing 3 reads to get a reliable reading.
  A0Raw = analogRead(A0);  // 1st read  0...1V = 0 ..1023
  delay(3);
  A0Raw += analogRead(A0); // 2nd read
  delay(3);
  A0Raw += analogRead(A0); // 3rd read
  A0Raw = A0Raw / 3;
  battery.panel += (float(map(A0Raw, 0, 1023, 0, PANEL_MAX))/1000 - battery.panel) /10; // Volt Smoothed 10seconds
#endif

#if defined (PANEL_SOURCE_IS_INA)
  // Panel measurements from INA226
  ina2_voltage   = INA2.getBusMilliVolts(0);
  //ina1_voltage = 12000;
  ina2_shunt     = INA2.getShuntMicroVolts(0);
  ina2_current   = INA2.getBusMicroAmps(0);     
  ina2_power     = INA2.getBusMicroWatts(0);
  voltage2  += (ina2_voltage / 1000   - voltage2) / 10; // Volt Smoothed 10seconds
  current2 += (ina2_current / 1000000 - current2) / 10; // Ampere Smoothed 10seconds, set divisor negative to reverse current if required
  battery.panel = voltage2;
#endif

  //=== ( Measure Battery
#if defined BATTERY_SOURCE_IS_INA
  // Battery measurements from INA226
  float v = ina1_voltage;
  float w = ina1_current;
  ina1_voltage   = INA1.getBusMilliVolts(0);
  //ina1_voltage = 12000;
  ina1_shunt     = INA1.getShuntMicroVolts(0);
  ina1_current   = INA1.getBusMicroAmps(0);     
  ina1_power     = INA1.getBusMicroWatts(0);
  delta_voltage = ina1_voltage - v;          // mV
  delta_current = (ina1_current - w) /1000;   // mA
  
  voltage1 += (ina1_voltage / 1000   - voltage1) / 10; // Volt Smoothed 10seconds
  current1 += (ina1_current / 1000000 - current1) / 10; // Ampere Smoothed 10seconds, set divisor negative to reverse current if required
  battery.voltage = voltage1;
  battery.current = current1;
  battery.power = voltage1 * current1;
  
  if (Hour < 24)   //Internal resistance evaluated during night, when no solar influence is expected. A load that generates sometimes peaks >50mA is requested for entropy.
    {
      // Evaluate battery internal resistance (r = dv / di) if deltaCurrent > 50mA.
      if (fabs(delta_current) > 50) battery.ohm = fabs(delta_voltage / delta_current);
    }

#endif

  // continuing either with values from above, or from UDP transmission
  if (NewMinute)
  {
    // Evaluate battery charge
    float d = 0;
    if (battery.current >= 0.3)
    {
      d = 500;   // mV
    }
    else if (battery.current <= 0.3)
    {
      d = -500;   // mV
    }
    percent_charged = map(battery.voltage * 1000, MIN_VOLT * 1000 + d, MAX_VOLT * 1000 + d - 800, 0, 100);
    percent_charged = constrain( percent_charged, 0, 100);
  }// end if new minute


  //=== ( Daily Battery voltage comparison just before midnight
  if (SecondOfDay == 86000) voltageAt0H  = battery.voltage;               // taking the voltage at 23:55 to evaluate if the battery gained/lost during the previous day.
  if (SecondOfDay == 85899) voltageDelta = battery.voltage - voltageAt0H; // set ranges at 33:53:59

  //=== ( Battery Stat integration
  currentInt += battery.current;
  nCurrent ++;

  if (HourExpiring)
  {
    AhBat[Hour] = currentInt / nCurrent;
    nCurrent = 0;
    currentInt = 0;
    AhBat[25] = AhBat[Hour];   //last hour
    AhBat[27] = 0;              // today (0h->current hour)
    for  (byte n = 0; n < Hour; n++)
    {
      AhBat[27] = AhBat[27] + AhBat[n];
    }
  } // end hour expiring

  if (DayExpiring)
  {
    AhBat[26] = AhBat[27];
  }
} // end of 1S run

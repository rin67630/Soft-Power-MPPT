void data125mSRun()
{
  // === ( Actions)  ====
  digitalWrite(RELAY1, not relay1_value);
  digitalWrite(RELAY2, not relay2_value);
  digitalWrite(HP_BUCK, high_power_buck_value);
  digitalWrite(LP_BUCK, not high_power_buck_value); 
  digitalWrite(AUX_BUCK, aux_buck_value);
  analogWrite (PWM_BAT, bat_injection);
  analogWrite (PWM_AUX, aux_injection);
  delay(50);
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
#if defined (BAT_SOURCE_IS_UDP)
  // I am using a quick and dirty method called 'type punning' copying the memory block of a structure into an array of chars,
  // transmitting this array, and copying back the memory block of the array into the same structure on the other side.
  // I dont use any header info, only the difference of size permits to assign the received packets to sound or dashboard.
  // it is quick and damn efficient, but NOT portable and YOU must take care to have the same structures on both systems
  // and different sizes for Battery and Sound...

  int packetSize = UDP.parsePacket();
  // if (packetSize) Console3.printf("Packet size: %u, Battery size; %u \n", packetSize, sizeof(battery));
  // if (packetSize) digitalWrite(STDLED, false);    // Blink built-in LED on received packets
  if (packetSize == sizeof(battery))
  {
    UDP.read(batteryPayload, UDP_TX_PACKET_MAX_SIZE);
    memcpy(&battery, batteryPayload, sizeof(battery));
    // Console1.printf("Ah: %2.1f, Volt: %2.1f, Amp: %2.1f, Watt: %2.1f, %%Batt: %2.1f\n", AhBat, dashboard.Vbat , dashboard.Ibat , dashboard.Wbat , dashboard.percent_charged);
    delay(3);    // let built-in LED blink slightly stronger on battery packet
  }
  //digitalWrite(STDLED, true);
#endif

  // === (Computing injection voltages) ===
  if (not aux_buck_value) aux_injection = 1024;
  if (not high_power_buck_value)
  {
  bat_injection_mvolt = map(bat_injection,1024, 0, INJ_LP_MIN, INJ_LP_MAX);
  }else{
  bat_injection_mvolt = map(bat_injection,1024, 0, INJ_HP_MIN, INJ_HP_MAX);  
  }
  aux_injection_mvolt = map(aux_injection,1024, 0, INJ_AUX_MIN, INJ_AUX_MAX);
  
  // === ( Getting panel voltage from A0 ) ===
#if defined (PAN_SOURCE_IS_A0)
  // Performing 3 reads to get a reliable reading.
  A0Raw = analogRead(A0);  // 1st read  0...1V = 0 ..1023
  delay(3);
  A0Raw += analogRead(A0); // 2nd read
  delay(3);
  A0Raw += analogRead(A0); // 3rd read
  A0Raw = A0Raw / 3;
  dashboard.Vpan += (float(map(A0Raw, 0, 1023, 0, PANEL_MAX)) / 1000 - dashboard.Vpan) / 10; // Volt Smoothed 10seconds
#endif

  // === ( Getting aux voltage from A0 ) ===
#if defined (AUX_SOURCE_IS_A0)
  // Performing 3 reads to get a reliable reading.
  A0Raw = analogRead(A0);  // 1st read  0...1V = 0 ..1023
  delay(3);
  A0Raw += analogRead(A0); // 2nd read
  delay(3);
  A0Raw += analogRead(A0); // 3rd read
  A0Raw = A0Raw / 3;
  dashboard.Vaux += (float(map(A0Raw, 0, 1023, 0, PANEL_MAX)) / 1000 - dashboard.Vaux) / 10; // Volt Smoothed 10seconds
#endif

#if defined (PAN_SOURCE_IS_INA)
  // Panel measurements from INA226
  ina2_voltage   = INA.getBusMilliVolts(1);
  ina2_shunt     = INA.getShuntMicroVolts(1);
  ina2_current   = INA.getBusMicroAmps(1);
  ina2_power     = INA.getBusMicroWatts(1);
  dashboard.Vpan  += (ina2_voltage / 1000   - dashboard.Vpan) / 3; // Volt smoothed 3seconds
  dashboard.Ipan += (ina2_current / IFACTORP - dashboard.Ipan) / 3; // Ampere Smoothed 3seconds, set divisor negative to reverse current if required
  dashboard.Wpan = dashboard.Vpan * dashboard.Ipan; +0.001;
#endif

#if defined (AUX_SOURCE_IS_INA)
  // Auxiliary out measurements from INA226
  ina3_voltage   = INA.getBusMilliVolts(2);
  ina3_shunt     = INA.getShuntMicroVolts(2);
  ina3_current   = INA.getBusMicroAmps(2);
  ina3_power     = INA.getBusMicroWatts(2);
  dashboard.Vaux  += (ina3_voltage / 1000   - dashboard.Vaux) / 3; // Volt smoothed 3seconds
  dashboard.Iaux += (ina3_current / IFACTORP - dashboard.Iaux) / 3; // Ampere Smoothed 3seconds, set divisor negative to reverse current if required
  dashboard.Waux = dashboard.Vaux * dashboard.Iaux; +0.001;
#endif

  //=== ( Measure Battery
#if defined (BAT_SOURCE_IS_INA)
  // Battery measurements from INA226
  float v = ina1_voltage;
  float w = ina1_current;
  ina1_voltage   = INA.getBusMilliVolts(0);
  ina1_shunt     = INA.getShuntMicroVolts(0);
  ina1_current   = INA.getBusMicroAmps(0);
  ina1_power     = INA.getBusMicroWatts(0);
  delta_voltage = ina1_voltage - v;          // mV
  delta_current = (ina1_current - w) / 1000;   // mA
  dashboard.Vbat += (ina1_voltage / 1000   - dashboard.Vbat) / 3; // Volt Smoothed 3seconds
  dashboard.Ibat += (ina1_current / IFACTORB - dashboard.Ibat) / 3; // Ampere Smoothed 3seconds, set divisor negative to reverse current if required
  dashboard.Wbat = dashboard.Wbat = dashboard.Vbat * dashboard.Ibat;

  //  if (Hour < 4)   //Internal resistance evaluated during night, when no solar influence is expected. A load that generates sometimes peaks >50mA is requested for entropy.
  //    {
  // Evaluate battery internal resistance (r = dv / di) if deltaCurrent > 50mA.
  if (fabs(delta_current) > 50) dashboard.internal_resistance = fabs(delta_voltage / delta_current);
  //    }
#endif

#if defined (PAN_SOURCE_IS_INA) && defined (BAT_SOURCE_IS_INA)
if (dashboard.Wpan > 0.03)
{
dashboard.efficiency = constrain((dashboard.Wbat + dashboard.Waux) / dashboard.Wpan * 100, -50, 97.5);
}else{
dashboard.efficiency = 0;
}
#endif

  // continuing either with values from above, or from UDP transmission
  if (NewMinute)
  {
    // Evaluate battery charge
    float d = 0;
    if (dashboard.Ibat >= 0.3)
    {
      d = 500;   // mV
    }
    else if (dashboard.Ibat <= 0.3)
    {
      d = -500;   // mV
    }
    dashboard.percent_charged = map(dashboard.Vbat * 1000, MIN_VOLT * 1000 + d, MAX_VOLT * 1000 + d - 800, 0, 100);
    dashboard.percent_charged = constrain( dashboard.percent_charged, 0, 100);

    // Battery charging procedure
    phase_timer ++;
    phase_duration[phase] = phase_timer;
    expired = false;
    if (phase_timer > phase_limit[phase]) expired = true;

/*
    switch (phase)
    {
      case NIGHT:        //0 panel voltage < battery voltage Low-Power mode
        LP_buck_value = LOW;
        if (dashboard.Vpan > (dashboard.Vbat + 1))
        {
          phase_timer = 0;
          if (dashboard.Vbat > LOWLIM)
          {
            phase = RECOVERY;
            aux_injection = 1024;
            LP_buck_value = LOW;
          }
          else
          {
            phase = BULK;
            aux_injection = 580;
            LP_buck_value = HIGH;
          }
        }
        break;
      case RECOVERY:     //1 battery voltage < LOWLIM, panel current > low limit, cut off load
        //Deeply discharged batteries are automatically trickle charged at 17.5% of current limit
        //until the cell voltage exceeds 75% of FLOAT.

        break;
      case BULK:         //2 battery voltage < FLOAT, current limited by battery
        // Bulk is terminated once the charging voltage reaches Absorption level -> absorbption
        break;
      case MPPT:         //3 battery voltage < FLOAT, current limited by panel
        // MPPT is terminated once the charging voltage reaches Absorption level -> absorbption
        break;
      case ABSORPTION:   //4  battery voltage > FLOAT < ABSORB, current limited by battery and time
        // Absorption is terminated once the charging current drops to 38% current limit -> floatcharge.
        break;
      case FLOATCHARGE:  //5 battery voltage = FLOAT
        // Floatcharge terminates only by night.
        break;
      case EQUALIZATION: //6 battery voltage = EQUALIZE, current limited by battery and time
        // Equalization needs finished absorption and a manual trigger.
        break;
      case OVERCHARGE:   //7 battery voltage > ABSORB and not EQUALIZATION
        // This is an error: stop charging and alert.
        break;
      case DISCHARGED:   //8 battery voltage < LOWLIM, panel current < low limit , cut off load
        // This is an error: cut off load.
        break;
      case PAUSE:        //9  no charge, wait for a defined time
        break;
      case NOBAT:        //10 no battery current possible at Vbat = ABSORB
        break;
      case EXAMINE:      //11 evaluate battery condition
        break;
    }
*/
  }// end if new minute


  //=== ( Daily Battery voltage comparison just before midnight
  if (SecondOfDay == 86000) voltageAt0H  = dashboard.Vbat;               // taking the voltage at 23:55 to evaluate if the battery gained/lost during the previous day.
  if (SecondOfDay == 85899) voltageDelta = dashboard.Vbat - voltageAt0H; // set ranges at 33:53:59

  //=== ( Battery Stat integration
  currentInt += dashboard.Ibat;
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

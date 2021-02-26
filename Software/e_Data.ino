void data125mSRun()
{

  // === ( Measures)  ====

#if defined (PAN_SOURCE_IS_A0)
  // Performing 3 reads to get a reliable reading.
  A0Raw = analogRead(A0);  // 1st read  0...1V = 0 ..1023
  delay(3);
  A0Raw += analogRead(A0); // 2nd read
  delay(3);
  A0Raw += analogRead(A0); // 3rd read
  A0Raw = A0Raw / 3;
  dashboard.Vpan += (float(map(A0Raw, 0, 1023, 0, PANEL_MAX)) / 1000 - dashboard.Vpan) / 10; // Volt Smoothed 1seconds
#endif

#if defined (AUX_SOURCE_IS_A0)
  // Performing 3 reads to get a reliable reading.
  A0Raw = analogRead(A0);  // 1st read  0...1V = 0 ..1023
  delay(3);
  A0Raw += analogRead(A0); // 2nd read
  delay(3);
  A0Raw += analogRead(A0); // 3rd read
  A0Raw = A0Raw / 3;
  //dashboard.Vaux += (float(map(A0Raw, 0, 1023, 0, PANEL_MAX)) / 1000 - dashboard.Vaux) / 10; // Volt Smoothed 1seconds
#endif

#if defined (PAN_SOURCE_IS_INA)
  // Panel measurements from INA226
  ina2_voltage   = INA.getBusMilliVolts(1);
  ina2_shunt     = INA.getShuntMicroVolts(1);
  ina2_current   = INA.getBusMicroAmps(1);
  ina2_power     = INA.getBusMicroWatts(1);
  dashboard.Vpan  += (ina2_voltage / 1000   - dashboard.Vpan) / 3; // Volt smoothed 0.3seconds
  dashboard.Ipan += (ina2_current / IFACTORP - dashboard.Ipan) / 3; // Ampere Smoothed 0.3seconds, set divisor negative to reverse current if required
  dashboard.Wpan = dashboard.Vpan * dashboard.Ipan; +0.001;
#endif

#if defined (AUX_SOURCE_IS_INA)
  // Auxiliary out measurements from INA226
  ina3_voltage   = INA.getBusMilliVolts(2);
  ina3_shunt     = INA.getShuntMicroVolts(2);
  ina3_current   = INA.getBusMicroAmps(2);
  ina3_power     = INA.getBusMicroWatts(2);
  //dashboard.Vaux  += (ina3_voltage / 1000   - dashboard.Vaux) / 3; // Volt smoothed 0.3seconds
  dashboard.Iout += (ina3_current / IFACTORA - dashboard.Iout) / 3; // Ampere Smoothed 0.3seconds, set divisor negative to reverse current if required
  dashboard.Wout = dashboard.Vbat * dashboard.Iout; +0.001;
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
  dashboard.Vbat += (ina1_voltage / 1000   - dashboard.Vbat) / 3; // Volt Smoothed 0.3seconds
  dashboard.Iin += (ina1_current / IFACTORB - dashboard.Iin) / 3; // Ampere Smoothed 0.3seconds, set divisor negative to reverse current if required
  dashboard.Win = dashboard.Win = dashboard.Vbat * dashboard.Iin;
#endif

  // Evaluate battery internal resistance (r = dv / di) if deltaCurrent > 50mA.
  if (fabs(delta_current) > 50) dashboard.internal_resistance = fabs(delta_voltage / delta_current);


  // === ( Actions)  ====

  // PWM to charger buck: dashboard.DVinj is our adjustment variable. It is the difference between the battery voltage and the desired voltage.

  switch (dashboard.modus)
  {
    case CVFX:  // fix voltage
      dashboard.DVinj = dashboard.CVbat - dashboard.Vbat;
      break;
    case CVTR:  // voltage ahead tracking
      dashboard.DVinj = dashboard.CCbat / 10 ;
      break;
    case CCFX:  // fix current
      dashboard.DVinj = dashboard.DVinj + (dashboard.Iin + dashboard.Iout - dashboard.CCinj) * -0.005;
      break;
    case PVFX:  // fix panel voltage
      dashboard.CCinj = dashboard.CCinj + (dashboard.Vpan - dashboard.CVpan) * 0.0005;
      dashboard.CCinj = constrain( dashboard.CCinj, 1, 8) ;
      dashboard.DVinj = dashboard.DVinj + (dashboard.Iin + dashboard.Iout - dashboard.CCinj) * -0.003;      
      break;
    case MPPT:  // maximum power point tracking Perturb and Observe
      dP  = dashboard.Win + dashboard.Wout - MPPT_last_power;
      dV  = dashboard.Vpan - MPPT_last_voltage;
      MPPT_last_power = dashboard.Win + dashboard.Wout ;
      MPPT_last_voltage = dashboard.Vpan;
      if (dP > 0)
      {
        if (dV > 0)
        {
          dashboard.CCinj-= 0.003;
        } else {
          dashboard.CCinj+= 0.003;
        }

      } else {
        if (dV > 0)
        {
          dashboard.CCinj+= 0.003;
        } else {
          dashboard.CCinj-= 0.003;
        }
      }
      break;
    case AUTO:  // automatic
      // placeholder code, more to come...
      dashboard.CVbat = 14.400;
      dashboard.CVpan = 19.000;
      dashboard.CCbat = 3.000;
      break;
  }

  dashboard.CVinj = dashboard.DVinj + dashboard.Vbat;
  dashboard.CVinj = constrain( dashboard.CVinj, phase_voltage[8], dashboard.CVbat) ;
  dashboard.DVinj = dashboard.CVinj - dashboard.Vbat;
  dashboard.DVinj = constrain( dashboard.DVinj, -0.25, 0.50);
  bat_injection = bat2pwm(dashboard.CVinj);
  bat_injection =  constrain( bat_injection, 0, 1024);

  // PWM to aux buck
  dashboard.Vaux  = dashboard.CVaux;
  if (not aux_enable) dashboard.Vaux  = 0;
  aux_injection = aux2pwm(dashboard.Vaux);

  digitalWrite(RELAY1, not relay1_value);
  digitalWrite(RELAY2, not relay2_value);
  digitalWrite(HP_BUCK, high_power_enable);
  digitalWrite(LP_BUCK, not high_power_enable);
  digitalWrite(AUX_BUCK, aux_enable);
  analogWrite (PWM_BAT, bat_injection);
  analogWrite (PWM_AUX, aux_injection);

} // end 125msRun

void data1SRun()
{

  // High power buck is activated up from 15W from panel, low power buck activated down from 10W
  if (dashboard.Wpan > 10) high_power_enable = true;
  if (dashboard.Wpan < 5)  high_power_enable = false;

  // === (Getting Weather from OpenWeatherMap every 5 minutes
#if defined WEATHER_SOURCE_IS_URL
  if (WiFi.status() == WL_CONNECTED)
  {
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
        }
      }
      http.end();
    }
  }
#endif


  // === (Getting Battery values from another ESP over UDP
#if defined (UDP_SLAVE)
  if (WiFi.status() == WL_CONNECTED)
  {
    // I am using a quick and dirty method called 'type punning' copying the memory block of a structure into an array of chars,
    // transmitting this array, and copying back the memory block of the array into the same structure on the other side.
    // I dont use any header info, only the difference of size permits to assign the received packets to sound or dashboard.
    // it is quick and damn efficient, but NOT portable and YOU must take care to have the same structures on both systems
    // and different sizes for Battery and Sound...

    int packetSize = UDP.parsePacket();
    if (packetSize == sizeof(dashboard))
    {
      UDP.read(dashboardPayload, UDP_TX_PACKET_MAX_SIZE);
      memcpy(&dashboard, dashboardPayload, sizeof(dashboard));
      // Console1.printf("Ah: %2.1f, Volt: %2.1f, Amp: %2.1f, Watt: %2.1f, %%Batt: %2.1f\n", AhBat, dashboard.Vbat , dashboard.Iin , dashboard.Win , dashboard.percent_charged);
      delay(3);    // let built-in LED blink slightly stronger on battery packet
    }
    //digitalWrite(STDLED, true);
  }
#endif


#if defined (PAN_SOURCE_IS_INA) && defined (BAT_SOURCE_IS_INA)
  if (dashboard.Wpan > 0.03)
  {
    dashboard.efficiency = constrain((dashboard.Win + dashboard.Wout) / dashboard.Wpan * 100, -50, 97.5);
  } else {
    dashboard.efficiency = 0;
  }
#endif

  // continuing either with values from above, or from UDP transmission
  if (NewMinute)
  {
    // Evaluate battery charge
    float d = 0;
    if (dashboard.Iin >= 0.3)
    {
      d = 500;   // mV
    }
    else if (dashboard.Iin <= 0.3)
    {
      d = -500;   // mV
    }
    dashboard.percent_charged = map(dashboard.Vbat * 1000, MIN_VOLT * 1000 + d, MAX_VOLT * 1000 + d - 800, 0, 100);
    dashboard.percent_charged = constrain( dashboard.percent_charged, 0, 100);

    // Battery charging procedure
    phase_timer ++;
    phase_duration[dashboard.phase] = phase_timer;
    expired = false;
    if (phase_timer > phase_limit[dashboard.phase]) expired = true;

    /*
        switch (dashboard.phase)
        {
          case NIGHT:        //0 panel voltage < battery voltage Low-Power mode
            LP_enable = LOW;
            if (dashboard.Vpan > (dashboard.Vbat + 1))
            {
              phase_timer = 0;
              if (dashboard.Vbat > LOWLIM)
              {
                dashboard.phase = RECOVERY;
                aux_injection = 1024;
                LP_enable = LOW;
              }
              else
              {
                dashboard.phase = BULK;
                aux_injection = 580;
                LP_enable = HIGH;
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
  currentInt += dashboard.Iin;
  nCurrent ++;

  if (HourExpiring)
  {
    AhBat[Hour] = currentInt / nCurrent;
    nCurrent = 0;
    currentInt = 0;
    AhBat[25] = AhBat[Hour];   //last hour
    AhBat[26] = 0;              // today (0h->current hour)
    for  (byte n = 0; n < Hour; n++)
    {
      AhBat[26] = AhBat[26] + AhBat[n];
    }
    Vbat[Hour] = dashboard.Vbat;
    Vbat[25] = dashboard.Vbat;
    Vbat[26] = 0;              // today (0h->current hour)
    for  (byte n = 0; n < Hour; n++)
    {
      Vbat[26] = Vbat[26] + Vbat[n];
    }
    Vbat[26] = Vbat[26] / (Hour + 1) ;
  } // end hour expiring

  if (DayExpiring)
  {
    AhBat[27] = AhBat[26];
    AhBat[28] = AhBat[27];
    AhBat[29] = AhBat[28];
    AhBat[30] = AhBat[29];
    Vbat[27] = Vbat[26];
    Vbat[28] = Vbat[27];
    Vbat[29] = Vbat[28];
    Vbat[30] = Vbat[29];
  }
} // end of 1S run

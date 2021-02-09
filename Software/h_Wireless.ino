void wirelessRun()
{
  yield();
  if (GracePause) GracePause--;
  if (WiFi.status() == WL_CONNECTED)
  {
#if defined (THINGER)

    MillisMem = millis();
    if (not GracePause) thing.handle();               // do not call permanently Thinger if it takes too long to respond.
    if (millis() - MillisMem > 500) GracePause = 30;  // if the Thinger call took longer than 500mS, make 30s pause before retrying

    thing.stream("energy");                       // Fast update


#if defined (WRITE_BUCKETS)
    if (triglEvent)   thing.write_bucket("EVENT", "EVENT");
    if (NewDay)       thing.write_bucket("DAY", "DAY");
    if (HourExpiring) thing.write_bucket("HOUR", "HOUR");
    if (NewMinute)    thing.write_bucket("MIN", "MIN");
#endif

    if (Minute % 6 == 2)           //every 6 minutes update persistance data
    {
      //Persistance
      pson persistance;
#if (defined BAT_SOURCE_IS_INA) || (defined BAT_SOURCE_IS_UDP)
      persistance["currentInt"]    = currentInt ;
      persistance["nCurrent"]      = nCurrent;
      persistance["Ah/hour"]       = AhBat[25];
      persistance["Ah/yesterday"]  = AhBat[27];
      persistance["voltageDelta"]  = voltageDelta;
      persistance["voltageAt0H"]   = voltageAt0H;
#endif
      persistance["temperature"]   = outdoor_temperature;
      persistance["humidity"]      = outdoor_humidity;
      persistance["pressure"]      = outdoor_pressure;
      persistance["wind"]          = wind_speed;
      persistance["direction"]     = wind_direction;
      persistance["summary"]       = weather_summary;
      persistance["last_update"]   = SecondOfDay;
      thing.set_property("persistance", persistance, true);
    }

    if (Minute % 6 == 5)           //every 6 minutes update persistance data
    {
      pson BATmAh;// 0..23=hour, 25=current, 26=BATmAh 24h, 27= AhBatDay
      BATmAh["00h"] = AhBat[0];
      BATmAh["01h"] = AhBat[1];
      BATmAh["02h"] = AhBat[2];
      BATmAh["03h"] = AhBat[3];
      BATmAh["04h"] = AhBat[4];
      BATmAh["05h"] = AhBat[5];
      BATmAh["06h"] = AhBat[6];
      BATmAh["07h"] = AhBat[7];
      BATmAh["08h"] = AhBat[8];
      BATmAh["09h"] = AhBat[9];
      BATmAh["10h"] = AhBat[10];
      BATmAh["11h"] = AhBat[11];
      BATmAh["12h"] = AhBat[12];
      BATmAh["13h"] = AhBat[13];
      BATmAh["14h"] = AhBat[14];
      BATmAh["15h"] = AhBat[15];
      BATmAh["16h"] = AhBat[16];
      BATmAh["17h"] = AhBat[17];
      BATmAh["18h"] = AhBat[18];
      BATmAh["19h"] = AhBat[19];
      BATmAh["20h"] = AhBat[20];
      BATmAh["21h"] = AhBat[21];
      BATmAh["22h"] = AhBat[22];
      BATmAh["23h"] = AhBat[23];
      BATmAh["LastHour"] = AhBat[25];
      BATmAh["Yesterday"] = AhBat[27];
      BATmAh["Today"] = AhBat[26];
      thing.set_property("BAT", BATmAh);
    }
#endif // defined Thinger

#if defined (PUBLISH_REPORT)               // Read with NetCat Bash command nc -u -l [UDP_PORT +1]
    if (DayExpiring || triglEvent)
    {
      UDP.beginPacket(REPORT_TARGET, UDP_PORT + 1);
      if (DayExpiring)
      {
        UDP.printf("\nHour|   Ah    |    V    |    W    |\n");
        for  (byte n = 0; n < 31; n++)
        {
          if (n == 24)
          {
            UDP.printf("Extra ""hours"" 25:H-1, 26:today, 27:D-1, 28:D-2..\n");
          }
          else
          {
            UDP.printf("%02u  | %+07.3f | %+07.3f | %+07.3f |\n", n, AhBat[n], VBat[n], AhBat[n] * VBat[n]);
          }
        }
      }
      if (triglEvent)
      {
        UDP.printf("Event reporting to be defined");
      }
      UDP.endPacket();
    }
#endif

    if (NewMinute)
    {
#if defined (UDP_MASTER)
      memcpy(dashboardPayload, &dashboard, sizeof(dashboard));
      UDP.beginPacket(DATA_TARGET, UDP_PORT);
      UDP.write(dashboardPayload, sizeof(dashboard));
      UDP.endPacket();
#else
      yield();
#endif
    }
    yield();
  }
}

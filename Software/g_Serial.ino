void serialRun()
{
  yield();
  if (DayExpiring && (serialPeriodicity == 'd')    ||
      HourExpiring && (serialPeriodicity == 'h')   ||
      MinuteExpiring && (serialPeriodicity == 'm') ||
      (serialPeriodicity == 's') || (serialPeriodicity == '!'))
  {
    switch (serialPage)
    {
      case 'W':   // Weather Plot
        Console1.printf("Temp:%+05.1f Hum:%.1f Press:%.0f WindSpeed:%.1f Direction:%u\n", outdoor_temperature, outdoor_humidity, outdoor_pressure, wind_speed, wind_direction);
        if (serialPeriodicity == '!') serialPage = 0; // One shot reset serial page.
        break;
      case 'E':   // Energy plot every
        Console1.printf("Ah:%+07.3f Panel:%06.3f V-10:%06.3f Amp:%06.3f Watt:%+07.3f\n", AhBat[26], dashboard.Vpan -10, dashboard.Vbat - 10, dashboard.Ipan, dashboard.Wpan);
        if (serialPeriodicity == '!') serialPage = 0; // One shot reset serial page.
        break;
      case '~':   // WiFi status report
        Console3.printf("RSSI:%d dBm\n", WiFi.RSSI());
        if (serialPeriodicity == '!') serialPage = 0; // One shot reset serial page.
        break;
    }  // end switch (serialPage)

  }


  // ***  One shot reports  ***
  switch (serialPage)
  {
    case 'S': // Summary
      sprintf(charbuff, " \nSummary Report for \n%s, %02d %s %04d ", DayName , Day , MonthName, Year);
      Console1.print(charbuff);
      Console1.printf("\nHour|    Ah   |    V    |    W    |\n");
      for  (byte n = 0; n < 31; n++)
      {
        if (n == 24)
        {
          Console1.printf("Extra ""hours"" 25:H-1, 26:today, 27:D-1, 28:D-2..\n");
        }
        else
        {
          Console1.printf("%02u  | %+07.3f | %+07.3f | %+07.3f |\n", n, AhBat[n], Vbat[n], AhBat[n] * Vbat[n]);
        }
      }
      serialPage = 0;
      break;
  }
}

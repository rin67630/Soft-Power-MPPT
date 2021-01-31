void serialRun()
{
  yield();
  //Trace noise on second serial port
  if (DayExpiring)
  {
    sprintf(charbuff, " \nDaily Report for \n%s, %02d %s %04d ", DayName , Day , MonthName, Year);
    Console2.print(charbuff);

    Console2.print("\nHour|  Ah    |\n");
    for  (byte n = 0; n < 30; n++)
    {
      if (n == 24)
      {
        Console2.printf("Extra ""hours"" cf. Man.\n");
      }
      else
      {
        Console2.printf("%02u  | %+02.3f |\n", n, AhBat[n]);
      }
    }
    Console2.print("\nEvent|Time  | Event\n");
  }
  if (trigEvent)
  {
    Console2.printf(" Event ");
  }
  switch (serialPage)
  {
    // ***  Periodical compound Reports  ***
    case 'P':
      if (DayExpiring  && serialDay)
      {
        sprintf(charbuff, " \nDaily Report for \n%s, %02d %s %04d ", DayName , Day , MonthName, Year);
        Console1.print(charbuff);

        Console1.print("\nHour| Ah    |\n");
        for  (byte n = 0; n < 30; n++)
        {
          if (n == 24)
          {
            Console1.printf("Extra ""hours"" cf. Man.\n");
          }
          else
          {
            Console1.printf("%02u  %+02.3f |\n", n, AhBat[n]);
          }
        }
        Console1.print(" Event to be defined");
      }
      if (HourExpiring && serialHur)
      {
        Console1.printf("BatAhBat:%1.3f WindSpeed:%2.1f Direction:%3.0f\n", AhBat, wind_speed , wind_direction);
      }
      if (MinuteExpiring && serialMin)
      {
        Console1.printf("Bat_Volt:1%2.3f Bat_Watt:%2.3f Bat_Level:%2.1f \n", dashboard.Vbat - 10, dashboard.Wbat, dashboard.percent_charged / 10);
      }
      if (SerialEvent && trigEvent)
      {
        Console1.print("\nETime  |Event");  
        Console1.print(eventTime);  Console1.printf("Event to be defined");
      }
      if (serialSec)
        Console1.printf("Second Report to be defined");
      break;

    // ***  One shot reports  ***
    case 'R': // Daily report
      sprintf(charbuff, " \nDaily Report for \n%s, %02d %s %04d ", DayName , Day , MonthName, Year);
      Console1.print(charbuff);

      Console1.print("\nHour| Ah    |\n");
      for  (byte n = 0; n < 30; n++)
      {
        if (n == 24)
        {
          Console1.printf("Extra ""hours"" cf. Man.\n");
        }
        else
        {
          Console1.printf("%02u  | %+02.3f |\n", n, AhBat[n]);
        }
      }
      serialPage = 0;
      break;


    case 'W': //Weather Report
      Console1.printf("Temp: %2.1f Hum: %2.1f Press: %4.0f WindSpeed: %2.1f Direction: %u Weather: ", outdoor_temperature, outdoor_humidity, outdoor_pressure, wind_speed, wind_direction);
      Console1.println(weather_summary);
      serialPage = 0;
      break;

    case 'T': //Trace
      Console1.printf("Trece functionality");
      break;

    case 'B':  //Battery Report
      Console1.print  ("\n Hour   |");
      for  (byte n = 0; n < 12; n++)
      {
        Console1.printf("   %02u   |", n);
      }
      Console1.print  ("\n Bat Ah |");
      for  (byte n = 0; n < 12; n++)
      {
        Console1.printf(" %+02.3f |", AhBat[n]);
      }
      Console1.print  ("\n Hour   |");
      for  (byte n = 12; n < 24; n++)
      {
        Console1.printf("   %02u   |", n);
      }
      Console1.print  ("\n Bat Ah |");
      for  (byte n = 12; n < 24; n++)
      {
        Console1.printf(" %+02.3f |", AhBat[n]);
      }
      Console1.println("");
      serialPage = 0;
      break;
    case 'b':
      Console1.printf("Ah: %+2.3f, Panel: %2.3f, Volt: %2.3f, Amp: %2.3f, Watt: %2.3f, microV: %6.0f,%%Batt: %2.1f IntRes: %1.3f\n", AhBat[27], dashboard.Vpan, dashboard.Vbat, dashboard.Ibat, dashboard.Wbat, ina1_shunt, dashboard.percent_charged, dashboard.internal_resistance);
      break;
  }  // end switch (serialPage)
}

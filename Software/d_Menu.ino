void menuRun()
{
  if (Year < 2020)
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
      Console1.printf("I have understood %u/%u/%u %u:%u:%u\n", Day, Month, Year, Hour, Minute, Second);
      boolean validDate = (inRange(Day, 1, 31) && inRange(Month, 1, 12) && inRange(Year, 2021, 2031));
      boolean validTime = (inRange(Hour, 0, 23) && inRange(Minute, 0, 59) && inRange(Second, 0, 59));
      if (validTime && validDate)
      {
        //setTime(Hour,Minute,Second,Day,Month,Year);
        struct tm t;
          time_t t_of_day;
          t.tm_year = Year-1900;  // Year - 1900
          t.tm_mon = Month-1;       // Month, where 0 = jan
          t.tm_mday = Day-1;        // Day of the month
          t.tm_hour = Hour;
          t.tm_min = Minute;
          t.tm_sec = Second;
          t.tm_isdst = 1;         // Is DST on? 1 = yes, 0 = no, -1 = unknown
        t_of_day = mktime(&t);
        sprintf(charbuff, "Now is %02d:%02d:%02d. The Epoch is: %10lu\r\nDate is %s, %02d %s %04d", Hour, Minute, Second, t_of_day, DayName, Day, MonthName, Year);
        Console3.println(charbuff);
        struct timeval tv;
          tv.tv_sec = t_of_day;  // epoch time (seconds)
          tv.tv_usec = 0;    // microseconds
         settimeofday(&tv,0);
      }
    }
  }
  if (Console0.available())   inbyte = Console0.read(); //Serial input available
  switch (inbyte)
  {
    //====(Serial Menu)======
    case '0': //Display mode 0
      displayPage = 0;
      Console1.println ("Off");
      break;
    case '1': //Display mode 1
      displayPage = 1;
      Console1.println ("D=1");
      break;
    case '2': //Display mode 2
      displayPage = 2;
      Console1.println ("D=2");
      break;
    case '3': //Display mode 3
      displayPage = 3;
      Console1.println ("D=3");
      break;
    case '?': //List parameters
      Console1.printf("Par.List \n DPage: %d DSPage: %d SPage: %d\n", displayPage, displaySubPage, serialPage);
      break;
    case 'Z':  //Reset
      Console1.println ("\nResetting in 10s...");
      delay(10000);
      ESP.restart();
      break;
    case 'T': // Print time
      Console1.println();
      Console1.println(ctime(&now));
      break;
    case '+': //Increase Offset
      bat_injection ++;
      Console1.print ("+1bat=");
      Console1.println (bat_injection);
      break;
    case '-': //Reduce Offset
      bat_injection --;
      Console1.print ("-1bat=");
      Console1.println (bat_injection);
      break;
    case '>': //Increase Offset by 20
      bat_injection = bat_injection + 20;
      Console1.print ("+10bat=");
      Console1.println (bat_injection);
      break;
    case '<': //Reduce Offset by 20
      bat_injection = bat_injection - 20;
      Console1.print ("-10bat=");
      Console1.println (bat_injection);
      break;

    // ***Options for periodical Reports**
    case 'D': //Day Report
      serialDay = true;
      break;
    case 'd': //no Day Report
      serialDay = false;
      break;
    case 'H': //Hour Report
      serialHur = true;
      break;
    case 'h': //No Hour Report
      serialHur = false;
      break;
    case 'M': //Minute Report
      serialMin = true;
      break;
    case 'm': //no Minute Report
      serialMin = false;
      break;
    case 'S': //Second Report
      serialSec = true;
      break;
    case 's': //No Second Report
      serialSec = false;
      break;
    case 'E': //Events
      SerialEvent = true;
      break;
    case 'e': //No Events
      SerialEvent = false;
      break;
    // ***On/Off for periodical Reports**
    case 'R': //Daily Report
      serialPage = 'R';
      break;
    case 'P': //Periodical Reports
      serialPage = 'P';
      break;
    case 'p': //no more Periodical Reports
      serialPage = 0;
      break;
    case 'B':  //Battery Report one shot
      serialPage = 'B';
      Console1.println ("\nBattery History :");
      break;
    case 'b':  //Battery Report one shot
      serialPage = 'b';
      Console1.println ("\nBattery Status :");
      break;
    case 'W':  //Weather Report one shot
      serialPage = 'W';
      Console1.println ("\nWeather report :");
      break;
    case '~':
      serialPage = '~';
      Console1.println ("\nWiFi report :");
      WiFi.printDiag(Console3);
      Console3.flush();
      break;
  } //end switch (inbyte)

  inbyte = 0 ;
}

void menuRun()
{
  if (Year < 2020) setTimefromSerial();
  byte n;
  byte m;
  if (Console0.available())   inbyte = Console0.read(); //Serial input available
  switch (inbyte)
  {
    //====(Serial Menu)======

    // *** Actions***
    case '0': //Display mode 0
      displayPage = 0;
      Console1.printf ("Off\n");
      break;
    case '1': //Display mode 1
      displayPage = 1;
      Console1.printf ("D=1\n");
      break;
    case '2': //Display mode 2
      displayPage = 2;
      Console1.printf ("D=2\n");
      break;
    case '3': //Display mode 3
      displayPage = 3;
      Console1.printf ("D=3\n");
      break;
    case '4': //Display mode 3
      displayPage = 4;
      Console1.printf ("D=3\n");
      break;
    case '5': //Display mode 3
      displayPage = 5;
      Console1.printf ("D=3\n");
      break;
    case '+': //Increase Offset
      dashboard.CCbat ++;
      Console1.printf ("+1 bat=%i", bat_injection);
      break;
    case '-': //Reduce Offset
      dashboard.CCbat --;
      Console1.printf ("-1 bat=%i", bat_injection);
      break;
    case '>': //Increase Offset by 20
      dashboard.CCbat += 20;
      Console1.printf ("+10 bat=%i", bat_injection);
      break;
    case '<': //Reduce Offset by 20
      dashboard.CCbat -= 20;
      Console1.printf ("-10 bat=%i", bat_injection);
      break;
    case 'R': // Relay control
      n = Serial.parseInt();
      switch (n)
      {
        case 10:
          Console1.printf ("\nRelay1 OFF");
          relay1_value = false;
          break;
        case 11:
          Console1.printf ("\nRelay1 ON");
          relay1_value = true;
          break;
        case 20:
          Console1.printf ("\nRelay2 OFF");
          relay2_value = false;
          break;
        case 21:
          Console1.printf ("\nRelay2 ON");
          relay2_value = true;
          break;
      }
    case 'A': // Aux control:  A0 or A stops, e.g. A5.43 sets to 5.43V
      n = Serial.parseInt();
      m = Serial.parseInt();
      if (not n && not m)
      {
        aux_enable = false;
      } else {
        aux_enable = true;
        dashboard.CVaux = 1000 * n + m;
      }
      break;
    case 'Z':  //Reset
      Console1.printf ("\nResetting in 10s...\n");
      delay(10000);
      ESP.restart();
      break;

    // ***One shot Reports**
    case 'S':  //Summary Report
      Console1.printf ("\nSummary Report\n");
      serialPage = 'S';
      break;
    case 'P': //Parameter List
      Console1.printf("Par.List \n BatPWM: %i Bat CV %6.2f Bat CC %6.3f AuxPWM: %i Aux CV %6.3f", bat_injection, dashboard.CVbat, dashboard.CCbat, aux_injection, dashboard.CVaux);
      break;
    case '?': //List Variables
      Console1.printf("Page.List \n DPage: %d DSPage: %d SPage: %d\n", displayPage, displaySubPage, serialPage);
      break;
    case 't': // Print time
      Console1.println(ctime(&now));
      break;
    case 'T': // Enter time
      setTimefromSerial();
      break;

    // ***Options for periodical Reports**
    case 'd': //Day Report
      serialPeriodicity = 'd';
      break;
    case 'h': //Hour Report
      serialPeriodicity = 'h';
      break;
    case 'm': //Minute Report
      serialPeriodicity = 'm';
      break;
    case 's': //Second Report
      serialPeriodicity = 's';
      break;
    case '!': //Unique (One shot)
      serialPeriodicity = '!';
      break;
    case '#': //Stop Reports
      serialPeriodicity = '0';
      break;
    case 'e': //Toggle Events
      serialEvent = not serialEvent;
      break;

    // ***Periodical Reports/Plots**
    case 'E':  //Energy Plot
      serialPage = 'E';
      //      Console1.printf ("\nEnergy plot :\n");
      break;
    case 'W':  //Weather Plot
      serialPage = 'W';
      //      Console1.printf ("\nWeather Plot :\n");
      break;
    case '~':  //Redio Report / WiFi
      serialPage = '~';
      Console1.printf ("\nWiFi Plot :\n");
      WiFi.printDiag(Console1);
      Console1.flush();
      break;
  } //end switch (inbyte)

  inbyte = 0 ;
}

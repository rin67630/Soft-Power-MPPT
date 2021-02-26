void displayRun()
{
  yield();

#ifdef DISPLAY_IS_OLED64x48
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
  display.drawString(0, 0,  "Panl =" + String(dashboard.Vpan)   + "V");
  display.drawString(0, 12, "Batt  =" + String(dashboard.Vbat) + "V");
  //    display.drawString(0, 24, "Curr  ="+String(dashboard.Iin) +"A");
  sprintf(charbuff, "Curr  =%1.3fA", dashboard.Iin); display.drawString(0, 24, charbuff);
  display.drawString(0, 36, "Powr="  + String(dashboard.Win)   + "W");
  display.display();
#endif
#ifdef DISPLAY_IS_OLED128x64
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
  // Draw Information matrix
  if(high_power_enable)
  {
      display.drawString(0, 0,"H");
  }
  else
  {
      display.drawString(0, 0,"L");    
  }
  display.drawString(10, 0,  "|  Panel");
  display.drawString(50, 0,  "| Battery");
  display.drawString(90, 0,  "| Output");
  display.drawString(0, 12, "V ");
  sprintf(charbuff, "| %2.2f", dashboard.Vpan); display.drawString(10, 12, charbuff);
  sprintf(charbuff, "| %2.2f", dashboard.Vbat); display.drawString(50, 12, charbuff);
  sprintf(charbuff, "| %2.2f", dashboard.Vaux); display.drawString(90, 12, charbuff);
  display.drawString(0, 24, "A ");
  sprintf(charbuff, "| %1.3f", dashboard.Ipan); display.drawString(10, 24, charbuff);
  sprintf(charbuff, "| %1.3f", dashboard.Iin); display.drawString(50, 24, charbuff);
  sprintf(charbuff, "| %1.3f", dashboard.Iout); display.drawString(90, 24, charbuff);
  display.drawString(0, 36, "W ");
  sprintf(charbuff, "| %2.2f", dashboard.Wpan); display.drawString(10, 36, charbuff);
  sprintf(charbuff, "| %2.2f", dashboard.Win); display.drawString(50, 36, charbuff);
  sprintf(charbuff, "| %2.2f", dashboard.Wout); display.drawString(90, 36, charbuff);

  buffTimeData();
  display.drawString(0, 50, charbuff);
  if (dashboard.Wpan > 0.03)
  {
    sprintf(charbuff, "Eff:%2.1f%%", dashboard.efficiency);
    display.drawString(75, 50, charbuff);
  }
  display.fillRect(0, 63, Second * 2, 1); //display seconds progress bar
  display.display();

#endif
}

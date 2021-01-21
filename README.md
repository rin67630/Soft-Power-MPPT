# Soft-Power: the Swiss-Army-Knife MPPT Solar Charge Controller based on simple tinkering modules (Buck DC converters, ESP8266, INA226...)

## The challenge:
The challenge might seem simple: Run a Raspberry Pi or an Arduino, plus a radio transmitter and a few instruments  
on solar power 24/365 in a Scottish climate as a continuous (1s pace) environmental measuring station  
placed in the public domain or others property (which means with limited panel size).

A Raspberry Pi + radio + instruments will need ~150Wh daily, easy with a 100W panel and a 100Ah battery?\
An Arduino + radio + instruments will need ~30Wh daily, easy with a 20W panel and a 20Ah battery?\
... in a sunny region that might work, not in Scotland. 

You must dimension panel and battery to last two weeks cloudy winter weather with barely 5% solar contribution for only a few hours a day!\
Commercial MPPT solar charge controllers will require 40-100mA for themselves, that is up to 31Wh a day- less than what the panel delivers in bad winter days!

## My solution:
So I decided to build my own MPPT solar charge controller, optimized for efficiency and very low quiescent consumption.  
It manages to draw as less as 20mA including WiFi transmission of data to a powerful cloud dashboard.  
The ESP has enough resources left (see my other project SPL-Booster) to manage the measurement as well.
Soft-Power provides MPPT solar charging + networking and reporting abilities to plain DC buck converters, by adding an ESP8266 WiFi microcontroller to it.
Meanwhile the solution has grown to a versatile harware choice of various hardware configurations to match different power requirements/ panel data.

## Dashboard feature list:
These basic reporting and statistic functions will be available.
- battery voltage and current monitoring (with trending in the cloud and download to excel)
- total current to/from Battery and power
- statistics and Coulomb/Ah integration
- logging of events (low/high voltage, cycles, begin / end of full charge)
- energy not harvested (after battery full)
- computation of the internal resistance of the battery
- weather display from openweather.org
- ability to network measures over UDP

Enjoy!\
![grafik](https://user-images.githubusercontent.com/14197155/100760181-c595dd00-33f1-11eb-87bc-8ccab89986ff.png)

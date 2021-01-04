<b>Soft-Power: the Swiss-Army-Knife Solar Charge Controller based on simple tinkering modules (Buck DC converters, ESP8266, INA226...)</b>

The challenge might seem simple: Run a) a Raspberry Pi or b) Arduino + radio + a few instruments on solar power 24/365 in a Scottish climate as an environmental measuring station placed in the public domain / others property (which means with limited panel size).

A Raspberry Pi + radio + instruments will need ~150Wh daily, easy with a 100W panel and a 100Ah battery... 
An Arduino + radio + instruments will need ~30Wh daily, easy with a 20W panel and a 20Ah battery...
... in a sunny region that might work, not in Scotland. 
You must dimension panel and battery to last two weeks cloudy winter weather with barely 5% solar contribution for just 3 hours a day!

Commercial MPPT solar charge controllers will require 40-100mA for themselves -that is up to 31Wh a day- less than what the panel delivers in bad winter days!

So I decided to build my own MPPT solar charge controller, optimized for efficiency and very low quiescent consumption.
It manages to draw als less as 20mA including WiFi trasnsmission of data to a powerful cloud dashboard.

The purpose of this development is to provide networking and reporting abilities to plain DC buck converters, by adding an ESP8266 WiFi microcontroller to it.
 
These basic reporting and statistic functions will be available.
- battery voltage and current monitoring (with trending in the cloud and download to excel)
- total current to/from Battery and power
- statistics and Coulomb/Ah integration
- logging of events (low/high voltage, cycles, begin / end of full charge)
- energy not harvested (after battery full)
- computation of the internal resistance of the battery
- weather display from openweather.org
- ability to network measures over UDP

Enjoy!

![grafik](https://user-images.githubusercontent.com/14197155/100760181-c595dd00-33f1-11eb-87bc-8ccab89986ff.png)

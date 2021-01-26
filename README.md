# Soft-Power: the Swiss-Army-Knife MPPT Solar Charge Controller 
__based on simple tinkering modules (Buck DC converters, ESP8266, INA226...)__

Soft power is a project intending to address a specific niche in the solar charge controller market:  
Providing solar charging services with MPPT strategies to _low and mid-range solar panels_ for powering instrumentation projects off grid, consuming as low as 30mA but 24/365. The specifics of the project are requiring an extremely low quiescent consumption. The concept is suitable for an efficient operation under bad weather conditions, while optimizing the power harvesting from the solar panel.

## The challenge:
The challenge might seem simple: Run a Raspberry Pi or an Arduino, plus a radio transmitter and a few instruments as a continuous no-sleep environmental measuring station
placed in the public domain or others property on solar power 24/365 in a Scottish type climate   

A Raspberry Pi + radio + instruments will need ~150Wh daily... easy with a 100W panel and a 100Ah battery?  
An Arduino + radio + instruments will need ~30Wh daily... easy with a 20W panel and a 20Ah battery?  
In a sunny region that might work, not in Scotland!  
You must dimension panel and battery to last two weeks of cloudy winter weather with barely 5% solar contribution for only a few hours a day! 
 
Commercial MPPT solar charge controllers **will require 60-100mA for themselves**, that is up to 30Wh a day- far less than what the panel delivers in bad winter days!

## My solution:
So I decided to build my own MPPT solar charge controller, optimized for efficiency and very low quiescent consumption.  
It manages to draw as less as 20mA including WiFi transmission of data to a powerful cloud dashboard. 

It includes the charging profiles for various battery chemistries:

1. Flooded lead acid batteries
2. AGM lead acid batteries
3. GEL lead acid batteries
4. LiPo batteries (3s)
5. LiFePo batteries (4s)

The ESP has enough resources left (see my other project SPL-Booster) to manage the measurement as well.

Soft-Power provides MPPT solar charging + networking and reporting abilities to plain DC buck converters, by adding an ESP8266 WiFi microcontroller to it.
Meanwhile the solution has grown to a versatile harware choice of various hardware configurations to match different power requirements/ panel data.
All versions can be wired on a simple prototyping board, without needing a dedicated PCB.

## Dashboard feature list:
![grafik](https://user-images.githubusercontent.com/14197155/100760181-c595dd00-33f1-11eb-87bc-8ccab89986ff.png)
These basic reporting and statistic functions will be available.
- battery voltage and current monitoring (with trending in the cloud and download to excel)
- total current to/from Battery and power
- statistics and Coulomb/Ah integration
- logging of events (low/high voltage, cycles, begin / end of full charge)
- energy not harvested (after battery full)
- computation of the internal resistance of the battery
- weather display from openweather.org
- ability to network measures over UDP  
You can adjust your dashboards online any time ad gusto!

## The candies extra:
The board provides additionally:  
- a convenience DC output switchable and with voltage controlled by software
- two control outputs to switch relay or FET boards
- an I2C port to add sensors
- an analog input port to measure something else  

Enjoy!\


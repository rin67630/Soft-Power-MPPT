<b>Solar-Booster: the Swiss-Army-Knife-for-Solar Charge Controllers</b>

The solution for solar charge controllers owners and those planning especially off-grid small installations to visualize your battery level and get deep reporting: 

Add REAL MPPT (maximum power point tracking) to simple buckconverters and boost them  with elaboate networked display and reporting features...

Especially at the low-power end, market devices tend to be primitive and frequently lack a decent dashboard to supervise the solar process.
The real MPPT devices -beside being expensive- drag too much power for themselves for low-power off grid solutions.

The purpose of this development is to provide networking and reporting abilities to low-end solar charge controllers, by adding a ESP8266 WiFi microcontroller to it.
 

The basic reporting and statistic functions will be available for all types of solar charge controllers.
- battery voltage and current monitoring (with trending in the cloud and download to excel)
- total current to/from Battery and power
- statistics and Coulomb/Ah integration
- logging of events (low/high voltage, cycles, begin / end of full charge)
- energy not harvested (after battery full)
- computation of the internal resistance of the battery
- weather display from openweather.org
- abilty to network measures over UDP

The electronics will provide following convenience functions:
- 5V 1A output ( permanent )
- optionally two independently adjustable voltage outputs 1A (2-12V) switchable by software/dashboard
- optionally two relays switchable by software/dashboard (total power relief strategies, alarming...)

All above functions are available for any SCC irrespective of it's technology.

SCCs with PWM function are usually switching the negative pole (the positive pole is common to panel, battery and output).

SCCs with DC conversion (true or false MPPT) and plain buck converters usually have a common negative pole between panel and battery.
For thes models the swiss army knife will provide additional functionality:

-panel voltage monitoring
-optional panel current, power and conversion efficiency  monitoring.

For plain buck converters with CC/CV potentiometers, the system provides an ellaborated MPPT + battery load optimizsation function (for various chemistries) opon injecting CC/CV corrections to the potentiometers transfoming these cheap devices into fully MPPT enabled SCC, costing ten times as much!

In the first variant, ESP8266 WiFi processor + INA226 power measuring interface + Online Dashboard the total value of the bill of material will be below 20€ (+ casing and connectors used)!

Enjoy!

![grafik](https://user-images.githubusercontent.com/14197155/100760181-c595dd00-33f1-11eb-87bc-8ccab89986ff.png)

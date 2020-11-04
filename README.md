<b>Solar-Booster: the Swiss-Army-Knife-for-Solar Charge Controllers</b>

The solution for solar charge controllers owners and those planning especially off-grid small installtions to visualize your battery level: 

Pimp dumb solar controllers and even add REAL MPPT (maximum power point tracking) to simple buckconverters and boost them  with elaboate networked display and reporting features...

There is a large choice of solar controllers on the market, from pretty cheap to awfully expensive ones. 
Especially at the low-power end, devices tend to be primitive and frequently lack a decent dashboard to supervise the solar process.

The purpose of this development is to provide networking and reporting abilities to low-end solar charge controllers, by adding a ESP8266 WiFi microcontroller to it. 

The basic reporting and statistic functions will be available for all types of solar charge controllers.
- battery voltage and current monitoring (with trending in the cloud and download to excel)
- total current to/from Battery and power
- statistics and Coulomb/Ah integration
- logging of events (low/high voltage, cycles, begin / end of full charge)
- energy not harvested (after battery full)
- computation of the internal resistance of the battery
- weather display from openweather.org

The electronics will provide following convenience functions:
- 5V 1A output ( permanent )
- optionally two independently adjustable voltage outputs 1A (2-12V) switchable by software/dashoboard
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

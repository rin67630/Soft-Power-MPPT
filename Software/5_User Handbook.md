# User Handbook

## Thinger operation.
Thinger.io allows users to change dashboards on the fly. There is no need to install/configure a server, fiddle with databases, configure a MQTT message concept.  
For your convenience and to startup easy, I have provided two powerful dashboards, from the four available to free users.

### Default template dashboard Soft Power Meter
I have provided Soft-Power with a comfortable default template a dashboard.  
![image](https://user-images.githubusercontent.com/14197155/107233248-ab483300-6a22-11eb-8ff1-b0c167e4400e.png)   
This dashboard is organized in 4 Columns and  6 Rows according to following background color conventions:
- Light gray: Weather reports
- Darker gray: Relay control
- Pink: Solar: charger control
- Light green: solar panel measurements
- Light cyan: battery measurements
- Yellow: auxiliary output variable voltage control

#### Column1 light grey block: Weather report
- Outside temperature from openweather.org
- Outside pressure from openweather.org
- Outside humiditys from openweather.org
- Weather description  from openweather.org (clicking on that field opens the weather forecast website)
- Wind speed  from openweather.org (clicking on that field opens the "windy" website)
- Wind direction from openweather.org

#### Column1 mid grey block: Relay control
- Control of the relay operation 1.
- Control of the relay operation 2.

#### Column1 light cyan block: Battery status
- Evaluation of the internal resistance of the battery  
  Balance of the Ah of the previous full day  
  Ongoing balance of the Ah of the current  day

#### Column 2/3  Converter control
- Converter efficiency
- Setpoint from the continuous voltage regulator expressed in mV
  PWM value for the injection 1024 to 0 (more injection means less voltage) under some conditions (t.b.d) you can move the slider and change the PWM  
  High Power Buck enable: under 10W power from the panel, the low-power buck is charging the battery, above the high-power buck converter is on duty.  
  Under some conditions (t.b.d. mainly between 10W and 15W) you can move the slider and switch from one buck converter to the other one. 

#### Column 2 Panel
- Panel voltage
- Panel current
- Panel power

#### Column 3 Battery:
- Battery voltage
- Battery current
- Battery power  
- Historical plot of the last eight hours  
  Green is the battery voltage  
  Blue is the battery current  
  
#### Column 4 auxiliary Output: 
- requested voltage of the auxiliary Output, expressed in mV. 
  PWM value for the injection 1024 to 0 (more injection means less voltage) under some conditions (t.b.d) you can move the slider and change the PWM  
  Auxiliary Output Buck enable
- Auxiliary Output voltage
- Auxiliary Output current
- Auxiliary Output power

### Default template dashboard Soft Power Stats

![image](https://user-images.githubusercontent.com/14197155/107235446-f9f6cc80-6a24-11eb-9073-522d2f5ca252.png)  

The Stats dashboard is organized in three groups:
#### The "midnight" battery status
here is a snapshot of the battery status at a time where she is likely to be idling is taken:
- The voltage difference to the day before ( is an indication, whether the battery is losing or gaining power)
- The voltage at midnight (is an indication of the battery charging state)
- The current amount of Ampere/hour harvested (not a midnight info)
- The amount of Ampere/hour harvested the day before.

#### The Hourly snapshots
Ampere/hour harvested/consumed by each finished hour. Up to the last elapsed hour, a record of the situation today, beyond the record of the situation from yesterday.

#### The last 72 Hour plot
this is a plot of the hourly situation of the battery voltage and the Ampere/hour harvested.
- Green is the voltage
- Grey is the Ampere/hour harvested

You can design yourself further dashboards.

### Data Buckets
Soft-Power reports long-term information in data buckets.  
The information from data buckets can be used to plot trends, can be listed and downloaded e.g. to Excel.
Following data buckets are provided:

#### MIN
This is the data buckets for minute paced information:
- Iaux: the current of the auxiliary output
- Ibat: the current to(-) or from(-) the battery
- Ipan: the current from the panel
- Vaux: the voltage of the auxiliary output
- Vbat: the voltage to(-) or from(-) the battery
- Vpan: the voltage from the panel
- Waux: the current of the auxiliary output
- Wbat: the current to(-) or from(-) the battery
- Wpan: the current from the panel
- efficiency: The converter efficiency ( not the efficiency of the panel )

#### HOUR
This is the data bucket for hourly information:
- Ibat: the current to(-) or from(-) the battery
- Ipan: the current from the panel
- Ohm: the valuation of the internal resistance of the battery
- Vbat: the voltage to(-) or from(-) the battery
- Vpan: the voltage from the panel
- Wbat: the current to(-) or from(-) the battery
- Wpan: the current from the panel
- several weather conditions reported by openweathermaps.org

#### Day
This is the data bucket for a daily summary:
- Bnnh:  (24 columns containing the Ah by hour)
- BAhDay: the total Ah of the day
- BV@0h: the battery voltage at midnight ( time where usually the battery is at rest)
- BV Diff: The difference of the battery voltage at midnight and the day before.

#### EVENT
This is the data bucket to record events:
- Over/undervoltage
- Transition from battery charging states.
- Other errors to be defined...

## optional OLED Display
A small OLED display that can be plugged on to the ESP or integrated in the case cover gives permanently some basic information:  
![image](https://user-images.githubusercontent.com/14197155/107244224-15b2a080-6a2e-11eb-9fbd-6c6ecc99ccb4.png)  
´´´
H Panel | Battry | Output
V 17.30 | 12.43  | 05.11
A 03.21 | 03.76  | 00.03
W 55.53 | 46.73  | 00.16
02.02.2021 17:53 eff. 83%
´´´
The upper left corner displays H or L depending on whether the high-power buck converter is used or the low-power one.  
You then have an matrix of voltage, current, power for the panel, the battery, and auxiliary output.  
Then the date/time indication followed by the conversion efficiency.  
A bar shows the running seconds as a function indicator.  

## Operation on the serial line
The preferred operation -and by far the most powerful- runs in the cloud over Thinger.io.
The precondition is however to have an Internet access. Without that I have provided a fallback operating mode over the serial line.  
You can connect the ESP over its USB port to a terminal program of your computer or of your smart phone.

Upon starting the ESP you will get a boot log with diagnostic messages.

If you never had an Internet connection and have no RTC shield, you will be requested to enter the current date and time .

![image](https://user-images.githubusercontent.com/14197155/107235100-9ff60700-6a24-11eb-9ed8-552b373d9c1a.png)  
t.b.continued.
  




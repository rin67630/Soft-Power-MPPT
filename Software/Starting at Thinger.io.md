# Starting at Thinger.io

Using Thinger.io is not a precondition, but it makes Soft-Power really comfortable and provides a lot of the visibility. 
The following instructions will help you creating an account and the first device at Thinger.io, that is compatible with the Soft-Power example given out of the box.

First you need to register at www.Thinger.io, take note of your username and password.
The recommended username is "SoftPower1" (without the quotes) 
After confirming your registration go to:
https://console.thinger.io/#!/console/ (this will be your main starting point: good to bookmark it!)
The most important feature for a beginning are:
- Dashboards
- Devices
- Data Buckets

First you will need to create a device: Select Devices, then Add Device.
- leave the device type unchanged
- as a device ID I recommend to use "SoftPower" (without the quotes), you must change that for your second device.
- enter whatever you want as a device description
- enter a password as a device credentials (not your password for Thinger.io)
Click on "Add Device"

Then you must enter the for buckets used by Soft-Power: Select Data Buckets, then Add Bucket.
you will need to define the following buckets:
1. EVENT
2. DAY
3. HOUR
4. MIN
for each one, enter exactly the buckets ID. you may enter what you want as a bucket name and Beckett description.
As a data source select " from device write call" out of the drop-down lists.
Click on "Add bucket"  
Finally you must get that picture:  
![image](https://user-images.githubusercontent.com/14197155/106426214-80c80a00-6465-11eb-9a7a-1ead53ddb8f5.png)  

You can finally enter your first dashboard: Select Dashboards, then  Add Dashboard.  
- you may enter any dashboard ID, dashboard name, dashboard description.
Click on Add Dashboard
Then click on the name of your newly created dashboard, you will get that picture:
![image](https://user-images.githubusercontent.com/14197155/106428750-c090f080-6469-11eb-9144-6d397d9651bf.png)  
upon clicking on the right slider you enter the design mode (you can do that anytime from anywhere).  
You may now enter widgets yourself, but for the first dashboard, I can provide a preconfigured powerful dashboard:  
Click on Settings, on the pop-up click on the tab "Developer"  
You will get a small JSON list corresponding to an empty dashboard.  

On a second instance of your browser, open the file:
https://github.com/rin67630/Soft-Power-MPPT/blob/main/Software/Thinger_Dashboard.ino
from that file copy everything **but not the first line and the last line**.  
**your copied content must start and end with a curly brace.**  

**Replace** all the content of the dashboard configuration by the content of your clipboard.  
Click on "save".  
Enjoy your standard Soft-Power dashboard!  
![image](https://user-images.githubusercontent.com/14197155/106634824-751d3600-6580-11eb-932a-027b90c51213.png)
The dashboard is best viewed on a vertical tablet: change the zoom level of your browser to get the best display.

*n.b. this default dashboard is provided for a username "SoftPower1" and a device name "SoftPower".  
If you want to use it for a different user name or a different device name the best is to use the find/replace functionality if the Arduino IDE 
to replace all occurences of the above-mentioned names by your own's before copying the content to Thinger.io.*

** Further design possibilities
You may any time enter the design mode by clicking on the right slider.
every widget has at its upper right corner 3 icons ![image](https://user-images.githubusercontent.com/14197155/106430653-67768c00-646c-11eb-8eee-5a0c796d9060.png)  
corresponding to: duplicate, edit, trash.
e.g. upon clicking on edit the widget you might get something like:  
![image](https://user-images.githubusercontent.com/14197155/106430945-dbb12f80-646c-11eb-9a95-b2874cdfbfeb.png)  
meaning that that widget is getting its information from device resource named measure, using the value Ipan, which will be sampled every 2 seconds.
The corresponding ESP8266 code is defined in the Arduino IDE under c-Setup:
```C++
  thing["measure"] >> [](pson & out)
  {
    out["Ibat"]            = dashboard.Ibat ;
    out["Vbat"]            = dashboard.Vbat ;
    out["Wbat"]            = dashboard.Wbat ;
    out["Ipan"]            = dashboard.Ipan ;
    out["Vpan"]            = dashboard.Vpan ;
    out["Wpan"]            = dashboard.Wpan ;
    out["Iaux"]            = dashboard.Iaux ;
    out["Vaux"]            = dashboard.Vaux ;
    out["Waux"]            = dashboard.Waux ;
    out["ohm"]             = dashboard.internal_resistance ;
    out["efficiency"]      = dashboard.efficiency;
    out["percent_charged"] = dashboard.percent_charged;
  };
``` 
You might also have other widgets getting their data from "device properties".
The corresponding ESP8266 code is defined in the Arduino IDE under c-Setup:
```C++
  pson persistance;
  thing.get_property("persistance", persistance);
  currentInt          = persistance["currentInt"];
  nCurrent            = persistance["nCurrent"];
  AhBat[25]           = persistance["Ah/hour"];
  AhBat[26]           = persistance["Ah/yesterday"];
  voltageDelta        = persistance["voltageDelta"];
  voltageAt0H         = persistance["voltageAt0H"];
  dashboard.internal_resistance       = persistance["resistance"];
  outdoor_temperature = persistance["temperature"];
  outdoor_humidity    = persistance["humidity"];
  outdoor_pressure    = persistance["pressure"];
  wind_speed          = persistance["wind"];
  wind_direction      = persistance["direction"];
```
Device properties are a kind of memory in the cloud, where the ESP can write data and retrieve it.
This is an essential feature to store information that must survive a reset.

Last but not least, widgets can get the information from Data Buckets.
Data buckets are time series information useful to plot longtime trends.
the structure of the data is defined in the Arduino IDE under c-Setup:
e.g. for the data being written every minute:
```C++
  thing["MIN"] >> [](pson & out)
  {
    out["Ibat"]         = dashboard.Ibat ;
    out["Vbat"]         = dashboard.Vbat ;
    out["Wbat"]         = dashboard.Wbat ;
    out["Ipan"]         = dashboard.Ipan ;
    out["Vpan"]         = dashboard.Vpan ;
    out["Wpan"]         = dashboard.Wpan ;
    out["Iaux"]         = dashboard.Iaux ;
    out["Vaux"]         = dashboard.Vaux ;
    out["Waux"]         = dashboard.Waux ;
    out["efficiency"]   = dashboard.efficiency;
  };
```
and the transmission is triggered in the Arduino IDE under c-Wireless:
```C++
#if defined (WRITE_BUCKETS)
  if (triglEvent)   thing.write_bucket("EVENT", "EVENT");
  if (NewDay)       thing.write_bucket("DAY", "DAY");
  if (HourExpiring) thing.write_bucket("HOUR", "HOUR");
  if (NewMinute)    thing.write_bucket("MIN", "MIN");
#endif
```
You have even got more possibilities, but that was the most important ones as a starting manual.
Enjoy your Thinger.io dashboards!

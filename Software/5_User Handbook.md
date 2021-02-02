# User Handbook

##Thinger operation.

### Default template dashboard
I have provided Soft-Power with a comfortable default template a dashboard.  
![image](https://user-images.githubusercontent.com/14197155/106634824-751d3600-6580-11eb-932a-027b90c51213.png)  
This dashboard is organized in 4 Columns and  6 Rows

#### Column1 from top to bottom:
- Control of the relay operation 1.
- Control of the relay operation 2.
- Evaluation of the internal resistance of the battery  
  Balance of the Ah of the previous full day  
  Ongoing balance of the Ah of the current  day
- Outside temperature from openweather.org
- Outside pressure from openweather.org
- Weather description  from openweather.org
- Wind speed  from openweather.org

#### Column 2  from top to bottom (panel, mainly light green background):
- Converter efficiency
- Panel voltage
- Panel current
- Panel power

#### Column 3 from top to bottom (battery, light blue background):
- Setpoint from the continuous voltage regulator expressed in mV
  PWM value for the injection 1024 to 0 (more injection means less voltage) under some conditions (t.b.d) you can move the slider and change the PWM  
  High Power Buck enable: under 10W power from the panel, the low-power buck is charging the battery, above the high-power buck converter is on duty. Under some conditions (t.b.d. mainly between 10W and 15W) you can move the slider and switch from one buck converter to the other one.  
- Battery voltage
- Battery current
- Battery power  
- Historical plot of the last eight hours  
  Green is the battery voltage  
  Blue is the battery current  
  
#### Column 4 from top to bottom (auxiliary output, yellow background): 
- requested voltage of the auxiliary Output, expressed in mV. 
  PWM value for the injection 1024 to 0 (more injection means less voltage) under some conditions (t.b.d) you can move the slider and change the PWM  
  Auxiliary Output Buck enable
- Auxiliary Output voltage
- Auxiliary Output current
- Auxiliary Output power

### Data Buckets
Soft-Power reports long-term information in data buckets
the information from data buckets can be used to plot trends, can be listed and downloaded e.g. to Excel.
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

#### 
  




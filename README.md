# Soft-Power: the high dynamic MPPT Solar Charge Controller 
__based on simple tinkering modules (Buck DC converters, ESP8266, INA226...)__


------------------!!! This project is retired !!!----------------------------------  
I don't follow up that idea any more: the DC-DC moduels, not been designed for solar operation are dying as flees.
  
Please acknowlege that I treid a lot, but fried to much hardware to follow that track further.  
The concept works, but the reality has nor mercy...  

I am currently working on recycling the software to a Report-Only device using PWM controlleers that I found to be at least as good on 18V panels. 
-----------------------------------------------------------------------------------

![image](https://user-images.githubusercontent.com/14197155/108857506-72e05180-75eb-11eb-8731-d5d0d6ecd7af.png)

Everybody can provide grid-connected SCCs for sunny days. 

Soft power is a project intending to address a specific niche under charge controllers:  
Providing solar charging services with MPPT strategies to _low and mid-range solar panels (10 to 200W)_  
to power instrumentation projects off grid, consuming as low as 50mA, but steadily 24/365 without sleep possibility.

## What makes Soft-Power different?
The specifics of the project are requiring an extremely low quiescent consumption. The concept is suitable for an efficient operation under bad weather conditions, while optimizing the power harvesting from the solar panel, even when it produces only a few percent of its nominal power.

## Why is it so important to optimize for bad weather?
During a week wintertime in Northern maritime regions, you frequently get many hundreds cloudy hours with the panel delivering less than 5% of its nominal power, and you may get just a few hours with direct sun irradiance. Both could approximately harvest the same amount of energy, but traditional MPPT solar charge controllers will not be able to handle efficiently the low-power range, frequently harvesting zero, when not even *consuming* power...  
Soft-Power stages two different buck converters, each one being efficient in its own power range 0..15W and 15W..200W.

### Hardware
Additionally, I designed the project hardware in a very versatile way:
It includes the charging profiles for various battery chemistries:

1. Flooded lead acid batteries
2. AGM lead acid batteries
3. GEL lead acid batteries
4. LiPo batteries (3s)
5. LiFePo batteries (4s)

**The candies extra:**   
- an auxiliary DC output switchable and with voltage controlled by software to charge a second smaller battery or just to do neat remote controlled things...
- two control outputs to switch relay or FET boards 
- an I2C port to add sensors
- an analog input port to measure something else  
![image](https://user-images.githubusercontent.com/14197155/105948031-88a13c00-606a-11eb-92d5-1ef73b2c2c20.png)  
The main board is able to handle panels up to 20 W, an optional second converter takes over power up to 200W.  
This split design optimizes efficiency in every power range.  
The result is a solution that has a no-load consumption of ~25mA while providing a full WiFi connectivity.  
The efficiency is ~90% at 1W solar panel harvesting. (commercial MPPT solar chargers are _consuming_ power in that range!)  
The efficiency is ~ 95% at 10W solar panel harvesting and increases to 97% at 100W solar panel harvesting.

Soft-Power can be wired on a simple well described prototyping board, without needing a dedicated PCB. *But I would be grateful, if someone contributes with a PCB file ;-)*  
The BOM cost is < 30 USD.

### Software
Soft-Power provides a powerful cloud-based dashboard:    
![image](https://user-images.githubusercontent.com/14197155/107529012-be8e0680-6bba-11eb-85e3-01bff1225d07.png)   
Provided functions:
- battery voltage and current monitoring (with trending in the cloud and download to excel)
- total current to/from Battery and power
- statistics and Ah integration
- logging of events (low/high voltage, cycles, begin / end of full charge)
- clipping time (after battery full)
- computation of the internal resistance of the battery
- weather display from openweather.org
- ability to network measures over UDP 
- remote control the auxiliary DC output and the relays  
You can adjust your dashboards online any time ad gusto!


You are welcome to discuss with us on our Discord channel: https://discord.gg/NH4gbQUJX8 about Soft-Power.


Enjoy!


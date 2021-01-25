This folder contains the schematics and hardware description of my Soft – Power – MPPT solar charging solution, specialized for efficient low-power operation.
The design uses standard buck converters audited for their efficiency and low no-load current. 

This schematics now contains several possible hardware variants:
1. The preferred design "Soft Power 1xINA3221 w Power Extension", measuring voltage and current for panel, battery, convenience output, the A0 analog input is free for extra usage.
2. A minimal version "Soft Power 1xINA226 Minimum", measuring the battery voltage and current, used as a device power supply.
3. A passive display and logging version "Soft Power 1xINA3221 Passive Logger", used to retrofit existing SCC's with powerful dashboard and logging functions.  
   (which must however have a **common ground** between panel and battery, which is mainly the case for real MPPT devices, but **not** for cheap PWM modules or those just *pretending* to be MPPT)   

All variants use the same Prototype Board layout and provide additionally:  
- a convenience DC output switchable and with voltage controlled by software
- two control outputs to switch relay or FET boards
- an I2C port to add sensors
- an analog input port to measure something else

Further variants, _ will be described in detail later_ just to give an outlook of the conceptual flexibility.  
5. replacing the INA-3221 through 3x INA-226 taking advantage of an increased voltage up to 36V.  
5. reduced with only two INA-226, measuring voltage and current for panel, battery, the A0 analog input measures the convenience output voltage.    
6. modified version 2 to run panels with voltages up to 60Voc, the panel current is measured low.side.  

The "Soft Power 1xINA3221 w Power Extension" can be used for
- Micro-power version with extremely low quiescent current that can handle panels up to 20W (as is, no power buck converter)
- Mid-power version with low quiescent current that can handle panels up to 200W, upon adding a power buck converter to the micropower version.

Don't ask for more power: a High-power version >200W will never be build, commercial stuff covers the requirements.

Enjoy!

**Last but not least:**
I am giving a very detailed on how to solder Soft Power on a protoyping board. It got now very close to become a full blown PCB.  
I just have not time to learn how to handle a PCB CAD and must concentrate on software.  
It would be GREAT, if someone familiar with KiCAD or other ECAD designers would contribute...

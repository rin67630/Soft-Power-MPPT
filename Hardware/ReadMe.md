This folder contains the schematics and hardware description of my Soft – Power – MPPT solar charging solution, specialized for efficient low-power operation.

This schematics now contains several possible hardware variants:
1. The preferred design with one INA-3221, measuring voltage and current for panel, battery, convenience output, the A0 analog input is free for extra usage.
2. A minimal version with only one INA-226, measuring the battery voltage and current, used as a device power supply.
3. A passive display and logging version, used to retrofit existing SCC's with powerful dashboard and logging functions.  
(which must however have a **common ground** between panel and battery, which is mainly the case for real MPPT devices, but **not** for cheap PWM modules or those just *pretending* to be MPPT)   

Further variants, _ will be described in detail later_ just to give an outlook of the conceptual flexibility.  
5. replacing the INA-3221 through 3x INA-226 taking advantage of an increased voltage up to 36V.  
5. reduced with only two INA-226, measuring voltage and current for panel, battery, the A0 analog input measures the convenience output voltage.    
6. modified version 2 to run panels with voltages up to 60Voc, the panel current is measured low.side.  

The schematic 1 can be used for
- Micro-power version with extremely low quiescent current that can handle panels up to 20W (as is, no power buck converter)
- Mid-power version with low quiescent current that can handle panels up to 200W, upon adding a power buck converter to the micropower version.

A High-power version >200W will never be build, commercial stuff covers the requirements.

Enjoy!

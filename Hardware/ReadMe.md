This folder contains the schematics and hardware description of my Soft – Power – MPPT solar charging solution, specialized for efficient low-power operation.

This schematics now contains several possible hardware variants:
1. the preferred design with one INA-3221, measuring voltage and current for panel, battery, convenience output, the A0 analog input is free for extra usage.

Further variants, _that will be described in detail later_ just to give an outlook of the conceptual flexibilty.  
2. replacing the INA-3221 through 3x INA-226 taking advantage of an increased voltage up to 36V.  
3. reduced with only two INA-226, measuring voltage and current for panel, battery, the A0 analog input measures the convenience output voltage.  
4. further reduced with only one INA-226, measuring the battery voltage and current, the A0 analog input measures the panel voltage.  
5. same than 4, just shown without the high power option.  To be part of an integrated device design.  
6. modified version 2 to run panels with voltages up to 60Voc, the panel current is measured low.side.  

All three schematics can be used for
- Micro-power version with extremely low quiescent current that can handle panels up to 20W (as is, no SZBK07 power buck converter)
- Mid-power version with low quiescent current that can handle panels up to 300W, upon adding a SZBK07 power buck converter to the micropower version.

A High-power version >300W will never be build, commercial stuff covers the requirements.

Enjoy!

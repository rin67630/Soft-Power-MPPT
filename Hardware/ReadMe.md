This folder contains the schematics and hardware description of my SoftPower MPPT solar charging solution, specialized in efficient (91% at 1W - 97% at 200w!) extremely low quiescent current operation.
 
The schematics feature several possible hardware configurations to show the conceptual flexibilty:
1. The preferred base design with a single INA-3221, measuring voltage and current for panel, battery and the convenience output. The A0 analog input is still free for extra usage.
2. Version with three Ina-226 (instead of the Ina3221) to take advantage of the higher voltage support of up to 36V.  
3. Version with just two INA-226, measuring voltage and current for panel, battery, the A0 analog input measures the convenience output voltage.  
4. Version with only one INA-226, measuring the battery voltage and current, the A0 analog input measures the panel voltage.  
5. Version same as 4., just shown without the medium power option.  
6. Variation of version 2. to run panels with voltages up to 60Voc, the panel current is measured on the low side.  

Configuration 1 to 5 include efficient (91 to 96%) extremely low quiescent current (7 to 25ma) low-power solutions that can handle panels up to 20W
Configuration 1 to 4 and 6 include efficient (94 to 97%) low quiescent current (34ma) mid-power solutions that can handle panels up to 300W

A High-power solution >300W will never be build since commercial solutions cover that demand already.

Enjoy!

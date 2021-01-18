This folder contains the schematics of hardware build:

This schematic now contains 3 variants
1) the variant with one INA-226, measuring the battery voltage and current, The A0 analog input measures the panel voltage.
2) the preferred variant with one INA-3221, measuring voltage and current for panel, battery, convenience output. The A0 analog input is free for extra usage.
3) the variant with two INA-226, measuring voltage and current for panel, battery, . The A0 analog input measures the convenience output voltage.

All three schematics can be used for

- Micro-power version with extremely low quiescent current that can handle panels up to 20W (as is, no SZBK07 power buck converter)
- Mid-power version with low quiescent current that can handle panels up to 300W, upon adding a SZBK07 power buck converter to the micropower version.
- A High-power versions will never be build, commercial stuff covers the requirements.

Enjoy!

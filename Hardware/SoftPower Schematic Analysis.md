# SoftPower Schematic Analysis

## Aims of the project
Soft power is a project intending to address a specific niche in the solar charge controller market: 
Providing solar charging services with MPPT strategies to _low and mid-range solar panels_ for powering instrumentation projects off grid, consuming as low as 30mA but 24/365.
The specificities of the project are requiring an extremely low quiescent consumption.
The concept is suitable for a very efficient operation under bad weather conditions, while optimizing the power harvesting from the solar panel.
It includes the charging profiles for various battery chemistries:
1. Flooded lead acid batteries
2. AGM lead acid batteries
3. GEL lead acid batteries
4. LiPo batteries (3s)
5. LiFePo batteries (4s)

The project provides furthermore a convenience power output that can be controlled by software between 5V and 12V and can be switched on and off as required.
This output can be used to charge a smaller secondary battery, or just for any other purpose at the discretion of the user.
The project also provides two control lines for relays or FET-modules to switch user loads by software.

Additionally to all above described power management functions, the analog input of the ESP8266 and enough processing capacity of the microcontroller 
remain available to include user-defined measurement functionalities.

## The hardware involved is using:
1. An ESP8266 microcontroller to provide WiFi connectivity, a cloud dashboard, satistics, and optimize the power harvesting from the solar panel and the charging process for 
   various battery chemistries.
2. Several generally available buck converters to provide extremly effective power conversions, using injection into their CV potentiometers to control operation.
3. The usage of generally available modules interconnected through comparatively few connections make it possible to realize the hardware without a PCB, 
   just using a prototyping board.
4. The control board stages a power measurement module INA3221, and three low-power buck converters, and can be used alone for panels up to 20W. 
5. An additional mid-power buck converter can extend the power range to 300W.
6. The whole bill of material should be procured far below 50$.

## Buck converters used:
The buck converter HW813 and optionally the Fine-Red buck converter have been selected because they provide is very low quiescient current, far below 1mA.
The HW813 buck converter is also one of the few providing an "enable" input pad and it can easily be tweaked to get CV injection.
The "Fine" Red buck converter is a plain fixed 5V buck converter, that has the advantage of providing directly a USB connector. 
It can be replaced by a HW813, if the 5 V USB output is not a requirement, so to have three identical modules.

The buck converter SZBK07 is an option to boost the power from 20W to 300W for projects requiring more energy only. 

The buck converters have following functions
- U1 low-power (max 20W) conversion of the panel voltage to battery voltage.
- U3 fixed conversion of the battery voltage to the 5V required by the ESP.
- U7 convenience user power output or secondary battery charge. 
- U6 mid-power _optional_ (max 300W) conversion of the panel voltage to battery voltage.

## ESP8266 microcontroller:
Almost all outputs of the ESP will be used:
- D1 and D2 are providing the I2C functionality used by the power measurement module INA3221.
- D3 and D4 can control up to two relays or two FET modules to control power loads by software.
- D8 enables U7, the convenience user power output.
- D7 enables U6, the mid-power option when the charging power exceeds 15W.
- D0 enables U1, the low-power buck converter when the charging power is less than 15W (D0 has a specificity to be enabled automatically at power on).
- D6 is the PWM-output to control the voltage of the convenience user power output.
- D5 is the PWM-output to control the voltage of either U1 or U6, depending on the charging power.
- A0 ist the 0..3V analog input left  to the user for measuring tasks.

## INA 3221 power measurement module:
The INA 3221 power measurement module provides three independent measurement channels each of them consisting of voltage, current, power measurement.
- channel 1 is used to measure the photovoltaic module
- channel 2 is used to measure the main battery
- channel 3 is used to measure the convenience output/secondary battery.
N.B. The INA 3221 is normally sold with 0,1 Ohm shunts resulting in a measurement range 0..1,5A with an accuracy of 0,5mA, which is fine for the operation up to 20W. 

For the extended power range 300W using a SZBK07 we will have to replace(1) the shunts with 0,01 Ohm shunts resulting in a measurement range 0..15A with an accuracy of 5mA.

(1) the original shunts can be relatively easy unsoldered by adding some tin to both ends, then heating the ends in short sequence and shifting the resistor away 
with the soldering tip.

## Current injection
The technique of current injection is described in document 
https://github.com/rin67630/Soft-Power-MPPT/blob/main/Hardware/About%20CV%20Injection.md.
The bypass filter consists of a 8,2K resistor and a 10 microfarad condenser, the injection current resistor is a 500K trim potentiometer, 
which can be replaced by a fixed resistor, once the project is stable, currently the value is around 100K.

## Connectors
The prototyping board is equipped with following connectors:

**Photovoltaic panel** 
- C1.1 positive.
- C1.2 photovoltaic panel negative.

**SZBK07 (mid-power 300W option)**
- C2.0 Power input negative
- C2.1 Power input positive
- C2.2 Enable
- C2.3 CV Injection
- C2.4 Power output positive

**Main battery**
- C3.1 positive
- C3.2 negative

**Secondary battery or convenience output**
- C4.1 positive
- C4.2 negative

**Relay/FET control**
- C5.1 +5V.
- C5.2 0..3.3V to control first relay
- C5.3 0..3.3V to control second relay
- C5.4 0V.

**User defined measurement input**
- C6.1 0..3.3V analog input.
- C6.2 +5V.
- C6.3 0V.

## Performance
- Quiescent current from the 12V battery: ~25mA, mainly from the WiFi chip, could be reduced to <1mA at night(2)
- Low-Power Efficiency at 1W 92%
- Low-Power Efficiency at 10W 95%
- Mid Power Efficiency at 200W 97%

(2) currently not realized, since my user measurement functions must go on permanently, which are preventing sleep.

## Commissioning
...to be described further, but the most important first:
- The U1 and evtl. U6 buck converters must be set to the float voltage of the battery before starting operations. 
  That way, the concept is fail-safe: without ESP8266 the hardware will charge -and not overcharge- the battery.
- If you use a HW813 as U3, you must set it a +5V you can do that with the trim pot or, better, cut the trace to the trim pot and solder a bridge on the 5V setting.
- U7 should be set at 11v using the trim pot.

Enjoy!






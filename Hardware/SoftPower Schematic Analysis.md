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
1. An ESP8266 microcontroller to provide WiFi connectivity, a cloud dashboard, statistics, and optimize the power harvesting from the solar panel and the charging process for 
   various battery chemistries.
2. Several generally available buck converters to provide extremly effective power conversions, using injection into their CV potentiometers to control operation.
3. The usage of generally available modules interconnected through comparatively few connections make it possible to realize the hardware without a PCB, 
   just using a prototyping board.
4. The control board stages power measurement module INA 226 or INA3221, and three low-power buck converters, and can be used alone for panels up to 20W. 
5. An additional mid-power buck converter can extend the power range to 300W.
6. The whole bill of material should be procured far below 50$.

## Schematic diagrams:
This schematics now contains 4 variants, the three first being suitable with panels vith Voc <= 36V.

- The variant with one INA-226, a simple build intended for 12V systems with 10 to 100W panels, measuring the battery voltage and current, the A0 analog input measures the panel voltage. This variant does not provide an efficiency computation and only estimates the voltage of the convenient output.  
  The INA-226 was historically the first build and still has the advantage of being able to fit panel voltages up to 36V.
  
- The comfort-variant with one INA-3221, measuring voltage, current, power at every stage: panel, battery, convenience output.  
The A0 analog input is left free for an extra usage. This variant is the preferred, and provides all features. It is however limited to panel voltages up to 26V only.

- The variant with two INA-226, measuring voltage and current for panel, battery, the A0 analog input measures the convenience output voltage.  
This variant fits for panels up to 36Voc and just lack the possibility of measuring the current of the convenience output.
  
- A high voltage variant with two INA-226 as defined above. 
For this version we will be using an efficient HW636 buck converter board, that can handle Vin up to 60V. The module has _however an important caveat_: it cannot supply safely more than 20V at the output, else the LT3800 chip _will be destroyed!_. Its trim pot does not prevent that. The very best is to replace the potentiometer by a 20K model to avoid this risk, else just set it counterclockwise to the minimum and increase until the floating battery voltage, typically 13.8V for a lead-acid.   
The higher panel voltage does not allow to use the U1 HW813 buck converter as a low-power tandem either, so that module must not be populated.  
The high panel voltage exceeds also the maximum voltage for the INA226 chip. That leads us also to use the low side current monitoring for the first INA226 and the panel voltage goes over a 2:1 voltage divider before feeding Vbus Pin.  

## Buck converters used:
The buck converter HW813 and optionally the Fine-Red buck converter have been selected because they provide is very low quiescient current, far below 1mA.  
The HW813 buck converter is also one of the few providing an "enable" input pad and it can easily be tweaked to get CV injection.  
The "Fine" Red buck converter is a plain fixed 5V buck converter, that has the advantage of providing directly a USB connector.   
It can be replaced by a HW813, if the 5 V USB output is not a requirement, so to have three identical modules.  

The buck converter SZBK07 is an option to boost the power from 20W to 300W for projects requiring more energy only.  
The buck converters have following functions:
- U1 low-power (max 20W) conversion of the panel voltage to battery voltage.
- U3 fixed conversion of the battery voltage to the 5V required by the ESP.
- U7 convenience user power output or secondary battery charge. 
- U6 mid-power _optional_ (max 300W) conversion of the panel voltage to battery voltage. 
  n.b. the mid-power modueles have usually a low side current shunt: never connect both Vin- and Vout- to GND simultaneously!

## Preparation of the buck converters for injection
None of the buck converters are providing injection from factory. There is a minimum of preparation to use them:
The D-SUN and the HW813 are requiring to solder a wire to a really tiny trim potentiometer. That requires a bit of soldering experience, and a fine tip.
But it is doable, even for an old man with some early signs of Parkinson. 

1) D-SUN module (deprecated, and also the most difficult to solder)
![image](https://user-images.githubusercontent.com/14197155/104938919-0b156600-59b0-11eb-9405-7e87dc7c254f.png)
2) HW813 module (preferred)
![image](https://user-images.githubusercontent.com/14197155/104938984-1f596300-59b0-11eb-8d2a-57a3ed7b8cc6.png)
3) SZBK07 module (only for mid-power option)
![image](https://user-images.githubusercontent.com/14197155/104939054-37c97d80-59b0-11eb-9a48-06a902532046.png)

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

## OLED display option:
The oled display is just nice to have:
You can use two versions:

a) a 64x48 pixel Wemos display hat, that is just a you on the top of the WEMOS D1

b) a 128x64 pixel display, that must be connected separately. 
You need to connect 
-  Vcc to +3.3V
-  SCL to D1
-  SDA to D2
-  GND to GND

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






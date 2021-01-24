# SoftPower Schematic Analysis

## Aims of the project

Soft power is a project intending to address a specific niche in the solar charge controller market: Providing solar charging services with MPPT strategies to _low and mid-range solar panels_ for powering instrumentation projects off grid, consuming as low as 30mA but 24/365. The specifics of the project are requiring an extremely low quiescent consumption. The concept is suitable for an efficient operation under bad weather conditions, while optimizing the power harvesting from the solar panel.

It includes the charging profiles for various battery chemistries:

1. Flooded lead acid batteries
2. AGM lead acid batteries
3. GEL lead acid batteries
4. LiPo batteries (3s)
5. LiFePo batteries (4s)

Instrumentation control is provided by:  
1. A convenience power output that can be controlled by software between 5V and 12V that can switched on and off by software as required. This can be used for any discretionary purpose by the user such as to charge a smaller secondary battery, control devices/track sun...
2. Two control lines for relays or FET-modules to switch user loads by software.
3. The analog input of the ESP8266 and enough processing capacity of the microcontroller remain available to include user-defined measurement functionalities.

## The hardware involved is using:

1. Several generally available buck converters, depending on panel size voltage, controlled by injecting voltage into their CV potentiometers to provide efficient power conversions.
2. An ESP8266 microcontroller to optimize solar panel power harvesting, control the buck converters and the charging process for various battery chemistries; and provide WiFi connectivity and a cloud statistical dashboard.
3. Relatively few connections with power measurement modules and other components make it possible to build the hardware without a PCB, using just a prototyping board.
4. The low cost materials should be procured for far less than $50.

## Schematic diagrams:

Unfortunately, there is no " one size fits all " hardware.  
There is currently no buck converter having at the same time a very low quiescent current, providing high power and being able to manage relatively high input voltage (see next chapter about converters used). For that reason, the design will consist of a base module, containing low-power, very low quiescent current buck converters, able to handling input power up to 20W. That base module can be used alone.  
To handle more power, an optional external buck converter can be added. The software will use the low-power modules in the low-power range and switch over to the more powerful buck converter as a power increases.

The base module has a versatile design. It uses a standard framework, but is offered in several flavors, depending on the INA modules used.

The recommended variant is "SoftPower 1xINA3221", staging a chip able to measure three channels.
It will measure the voltage, the current and the power coming from the solar panel, fed/retrieved from the battery and provided by the convenience output.
The A0 analog input is left free for an extra usage.  
Since the INA3221 module is specified for a maximum of 26 V, this variant is reserved for the "12V class" of panels (Voc=~20V, Vpp=~18V) and "12V" batteries.

The second variant "SoftPower 3xINA226" is functionally identical, the measurements are however realized by three separate INA226 modules, able to handle up to 36V.
with this variant you can use 24V class panels (Voc=~40V, Vpp=~36V) and "24V" batteries. The low power buck converters must be D-SUN.

The third variant "SoftPower 2xINA226" skips the INA226 dedictated to measure the convenience output. The convenience voltage will be measured over A0.
You lose the measure of the convenience current and the A0 analog input is not available anymore for extra usage.  

The 4th variant "SoftPower 1xINA226" skips additionally the INA226 dedictated to measure the panel voltage and power. The panel voltage will be measured over A0.
You lose additionally the measure of the panel current and the monitoring of the conversion efficiency. The voltage of the convenience output is estimated ~5%. 

The 5th schematic diagram "SoftPower Bare minimum Micropower" is the same as above, I just removed the power option for clarity. This is the typical usage for micropower solutions with a solar panel up to 20W.

The 6th variant "SoftPower 3xINA226 Hi Volt" is a special flavor for higher voltage solar panels up to 60 V. It uses a buck converter able to handle that voltage, the higher panel voltage does not allow to use a low power tandem buck converter either, so that module must not be populated. The high panel voltage also exceeds the maximum voltage for the INA226 chip, so low side current monitoring is used for the first INA226 and the panel voltage goes over a 2:1 voltage divider before feeding Vbus Pin. 

## Buck converters used:

The HW613 and D-SUN converter have a very low quiescent current, far below 1mA.
The HW613 buck converter is preferred in almost all respects, it is one of the few providing an "enable" input pad and is more easily tweaked to get CV injection, but it only supports an input voltage up to 24V.
The D-SUN buck converter accepts an input up to 40V which is required for 36Voc panels.

The "Fine" Red buck converter is a plain fixed 5V buck converter with the advantage of an inbuilt USB connector. It fits well under the Wemos module.
If the USB port is not a requirement, the smaller and more efficient HW613 modules can be used instead.

The SZBK07 buck converter is an option to boost the power from 20W to 300W for projects requiring more energy.
The HW636 buck converter is an option to boost the power from 20W to 250W and to manage panels up to 60Voc. 

The buck converters have following functions:

- HW613, D-SUN: low power (up to 20W) conversion of the panel voltage to battery voltage.
- Red one: fixed conversion of the battery voltage to 5V as required by the ESP + offering an USB port.
- HW613, D-SUN: convenience user power output or secondary battery charge.
- SZBK07, HW636: _optional_ mid-power conversion of the panel voltage to battery voltage.
  n.b. the mid-power modules have usually a low side current shunt: never connect both Vin- and Vout- to GND simultaneously!

N.B. High voltage variant: The HW636 is one of the few modules on the market that can handle up to 60V input. _However, it has an important caveat_: it cannot safely supply more than 20V at the output without _destroying the LT3800 chip!_ Sadly, its trimpot does not prevent this. The very best solution is to replace it's 50K potentiometer by a 20K model to avoid this risk. Alternatively, before powering up the module screw the trimpot counterclockwise until a small clicking sound is heard at the minimum, then power it up and increase the voltage to the floating battery voltage, typically 13.8V for a lead-acid battery. This buck converter also has a built-in reverse feed current protection, so an ideal diode is not required.

## Preparation of the modules for injection:

The HW613 and D-SUN require soldering a wire to a really tiny trim potentiometer to allow voltage injection. That requires a bit of soldering experience and a fine tip. It is doable, even for an old man with some early signs of Parkinson.

1. HW613 - preferred for panels up to 24Voc
![image](https://user-images.githubusercontent.com/14197155/104938984-1f596300-59b0-11eb-8d2a-57a3ed7b8cc6.png)
2. D-SUN - for panels up to 40Voc
![image](https://user-images.githubusercontent.com/14197155/104938919-0b156600-59b0-11eb-9405-7e87dc7c254f.png)
3. SZBK07 - mid-power option for up to 300W
![image](https://user-images.githubusercontent.com/14197155/104939054-37c97d80-59b0-11eb-9a48-06a902532046.png)  
4. HW636 - high voltage option for panels up to 60Voc 
![image](https://user-images.githubusercontent.com/14197155/105155131-87bc5780-5b0a-11eb-8179-0464e8d1f992.png)

## ESP8266 microcontroller:

You need to use an ESP8266, model 12E. The best is to use the Wemos D1 mini, which is the most convenient to use, since it has a smaller footprint and provide the ability to stack an OLED display on it.  
![image](https://user-images.githubusercontent.com/14197155/105284419-b1c95480-5bb2-11eb-986b-175e385d049a.png)  
The D1 Mini exists also in the Pro-version, which provides more EEPROM and the possibility to use an external antenna. That more expensive version is recommended but not required.  
I have also made builds using the Lolin Node MCU and they are surely also doable using the Adafruit HUZZAH.

Almost all outputs of the ESP will be used:  
- D1 and D2 are providing the I2C functionality used by the power measurement module INA3221.
- D3 and D4 can control up to two relays or two FET modules to control power loads by software.
- D7 enables the convenience user power output.
- D8 enables the mid-power option when the charging power exceeds 15W.
- D0 enables U1, the low-power buck converter when the charging power is less than 15W (D0 has a specificity to be enabled automatically at power on).
- D6 is the PWM-output to control the voltage of the convenience user power output.
- D5 is the PWM-output to control the voltage of either U1 or U6, depending on the charging power.
- A0 is the 0 to 3V analog input left to the user for measuring tasks, or used to measure the panel voltage or the convenince output.

## OLED display option:

An oled display is nice to have. It adds only ~2 mA to the overall consumption.  
Two versions are supported:
a) The 64x48 pixel Wemos display hat, which conveniently can be just pushed on top of the WEMOS D1  
b) The bigger and more flexible 128x64 pixel display, which must be connected separately by connecting:  
-  Vcc to +3.3V
-  SCL to D1
-  SDA to D2
-  GND to GND

## INA3221 power measurement module:

The INA3221 power measurement module provides three independent measurement channels each of them consisting of voltage, current, power measurement.
- channel 1 is used to measure the photovoltaic module
- channel 2 is used to measure the main battery
- channel 3 is used to measure the convenience output/secondary battery.  
N.B. There are two different versions of INA3221 on the market. You should avoid the pink one, for which all three measurement channels are connected together at V+.  
The right black one is the right one to go, it has independent inputs and is also less expensive:  
![image](https://user-images.githubusercontent.com/14197155/105282377-7e84c680-5bae-11eb-81cc-30ba40c3fb61.png) ![image](https://user-images.githubusercontent.com/14197155/105282569-f94de180-5bae-11eb-9613-98fb4ebb6170.png)
N.B. The INA3221 has a measurement range from 0 to 1.5A with an accuracy of 0.5mA, which is fine for the operation up to 20W.  
For the extended power range up to 200W using a SZBK07 we will have to replace the shunts with 0.01 Ohm shunts resulting in a measurement range from 0 to 15A with an accuracy of 5mA.
If you want to push the SZBK07 to the theoretical maximum of 300W (20A), you can use 0.005 Ohm shunts, I would however recommend and prefer using an external shunt in that case.  


## INA226 power measurement module(s):
The INA226 power measurement module provides only one measurement channel, but they are more versatile.  
They support up to 36V as well can be easily purchased with either 0.1 Ohm or 0.01 Ohm shunts. 
The 0.1 Ohm version can handle a measurement range from 0 to 0.8A with an accuracy of 0.25mA, which is fine for the operation up to 10W.  
The 0.01 Ohm version can handle a measurement range from 0 to 8A with an accuracy of 0.25mA, which is fine for the operation up to 100W.
For an extended power range up to 200W using a SZBK07 we will have to replace the shunts with 0.005 Ohm shunts resulting in a measurement range from 0 to 15A with an accuracy of 5mA.

### Addressing:  
If you use more than one module, you must provide different I2C addresses, by soldering a small tin bridge:  
![image](https://user-images.githubusercontent.com/14197155/105281711-0538a400-5bad-11eb-97eb-b8db0fc177ce.png)  

### Increasing current measuring range:  
The original shunts can be relatively easy unsoldered by generously adding tin to both ends, then heating the ends in short sequence and shifting the resistor away with the soldering tip. You can do it! Even I can, as an old man with beginning Parkinson! 

## Current injection

The technique of current injection is described in document https://github.com/rin67630/Soft-Power-MPPT/blob/main/Hardware/About%20CV%20Injection.md. The bypass filter consists of a 6.8k or 8,2K resistor and a 1 or 10 microfarad condenser, the injection current resistor is a 500K trim potentiometer, which can be replaced by a fixed resistor, once the project is stable, currently the value is around 63K, excepted for the high voltage module which needs 3,3K.  

## Connectors

The prototyping board is equipped with following screw terminals :

**Left connector on INA3221**  
- Panel_in   negative.  
- Panel_in   positive.  
- Power_Output to SZBK Input positive

**Mid connector on INA3221** 
- Power_Input from Ideal Diode positive  
- Battery_Out positive  

**Right connector on INA3221**  
- Convenience output wo (does this mean without?) current monitoring positive  
- Convenience output with current monitoring positive  
- Convenience output negative  


**On Board**  
- Enable to SZBK07  
- CV Injection to SZBK07  

**I2C female header**  
- +3,3V  
- GND  
- SCL  
- SDA  

**2x Relay/FET control male headers**  
- 0 to 3.3V to control first relay  
- 0 to 3.3V to control second relay  
- Gnd.  
- +5V.  

**User defined measurement female header**  
- 0 to 3.3V analog input.  
- 0 to 3.3V to control first relay  
- Gnd  
- +5V.  

**12V Fan connector**

## Performance

- Quiescent current from the 12V battery ~25mA, mainly from the WiFi chip
- Low-Power Efficiency at 1W 92%
- Low-Power Efficiency at 10W 95%
- Mid Power Efficiency at 200W 97%

A reduction to <1mA at night could be realized with a sleep option.  
I do not want it for myself, since my user measurement functions on the same ESP8266 must go on permanently.

## Commissioning

...to be described further, but the most important first:

- The U1 and evtl. U6 buck converters must be set to the float voltage of the battery before starting operations. This is fail-safe, without an operating ESP8266 the hardware will charge _and not overcharge_ the battery.
- If you use a HW813 as U3, you must set it a +5V you can do that with the trim pot or, better, cut the trace to the trim pot and solder a bridge on the 5V setting.
- U7 should be set at 11v using the trim pot.

Enjoy!

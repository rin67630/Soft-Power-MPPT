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

Unfortunately, I cannot provide a " one size fits all " hardware.  
There is currently no buck converter capable of having at the same time a very low quiescent current, high power, and be able to manage relatively high input voltage (see next chapter about converters used). For that reason, the design will consist of a base module, containing low-power, very low quiescent current buck converters, able to handling input power up to about 15 -20W. That base module can be used alone.  
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

The selected low-power buck converters used provide is very low quiescent current, far below 1mA.
The HW813 buck converter is preferred in almost all respects, it is one of the few providing an "enable" input pad and is more easily tweaked to get CV injection, but it only supports an input voltage up to 28V.
The D-SUN buck converter accepts an input up to 40V which is required for 36Voc panels.

The "Fine" Red buck converter is a plain fixed 5V buck converter with the advantage of an inbuilt USB connector. It fits well under the Wemos module.
If 5V USB output is not a requirement, HW813 modules can be used instead to keep all low power modules identical.

The SZBK07 buck converter is an option to boost the power from 20W to 300W for projects requiring more energy.
The HW636 buck converter is an option to manage high-voltage solar panels up to 250W 

The buck converters have following functions:

- low-power (max 20W) conversion of the panel voltage to battery voltage.
- fixed conversion of the battery voltage to the 5V required by the ESP.
- convenience user power output or secondary battery charge.
-  _optional_ mid-power conversion of the panel voltage to battery voltage.
  n.b. the mid-power modules have usually a low side current shunt: never connect both Vin- and Vout- to GND simultaneously!

N.B. High voltage variant: The HW636 buck converter is one of the few modules on the market that can handle 60V input. _However, it has an important caveat_: it cannot safely supply more than 20V at the output without _destroying the LT3800 chip!_ Sadly, its trimpot does not prevent this. The very best solution is to replace it's 50K potentiometer by a 20K model to avoid this risk. Alternatively, before powering up the module screw the trimpot counterclockwise until a small clicking sound is heard at the minimum, then power it up and increase the voltage to the floating battery voltage, typically 13.8V for a lead-acid battery. This buck converter also has a built-in reverse feed current protection, so an ideal diode is not required.

## Preparation of the buck converters for injection:

None of the buck converters allow voltage injection from factory. They must be prepared for use as follows:  
The HW813 and D-SUN require soldering a wire to a really tiny trim potentiometer. That requires a bit of soldering experience, and a fine tip. It is doable, even for an old man with some early signs of Parkinson.

1. HW813 preferred module (for 18V panels)
![image](https://user-images.githubusercontent.com/14197155/104938984-1f596300-59b0-11eb-8d2a-57a3ed7b8cc6.png)
2. D-SUN module (to be used for panels > 26Voc)
![image](https://user-images.githubusercontent.com/14197155/104938919-0b156600-59b0-11eb-9405-7e87dc7c254f.png)
3. SZBK07 module (mid-power option up to 300W)
![image](https://user-images.githubusercontent.com/14197155/104939054-37c97d80-59b0-11eb-9a48-06a902532046.png)  
4. HW636 module (high voltage 60V)
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
- A0 is the 0..3V analog input left to the user for measuring tasks, or used to measure the panel voltage or the convenince output.

## OLED display option:

The oled display is nice to have. It adds only ~2 mA to the overall consumption.  
Two versions are supported:  is
a) A 64x48 pixel Wemos display hat, just push it on the top of the WEMOS D1  
b) a 128x64 pixel display, that must be connected separately by connecting:  
-  Vcc to +3.3V
-  SCL to D1
-  SDA to D2
-  GND to GND

## INA3221 power measurement module:

The INA3221 power measurement module provides three independent measurement channels each of them consisting of voltage, current, power measurement.
- channel 1 is used to measure the photovoltaic module
- channel 2 is used to measure the main battery
- channel 3 is used to measure the convenience output/secondary battery.  
N.B. There are two different versions of INA3221 on the market. You should avoid the left pink one one, for which the tree measurement channels are connected together at V+.  
The right black one is the right one to go, it has independent inputs and is also less expensive:  
![image](https://user-images.githubusercontent.com/14197155/105282377-7e84c680-5bae-11eb-81cc-30ba40c3fb61.png) ![image](https://user-images.githubusercontent.com/14197155/105282569-f94de180-5bae-11eb-9613-98fb4ebb6170.png)  


## INA226 power measurement module(s):
The INA226 power measurement module provides only one measurement channel, but they are more versatile.  
# Addressing:  
If you use more than one module, you must provide different I2C addresses, by soldering a small tin bridge:  
![image](https://user-images.githubusercontent.com/14197155/105281711-0538a400-5bad-11eb-97eb-b8db0fc177ce.png)  
# Increasing current measuring range:  
N.B. The INA boards are normally sold with 0,1 Ohm shunts resulting in a measurement range 0..1,5A with an accuracy of 0,5mA, which is fine for the operation up to 20W.  
For the extended power range 300W using a SZBK07 we will have to replace the shunts with 0,01 Ohm shunts resulting in a measurement range 0..15A with an accuracy of 5mA. The original shunts can be relatively easy unsoldered by generously adding tin to both ends, then heating the ends in short sequence and shifting the resistor away with the soldering tip. You can do it! Even I can, as an old man with beginning Parkinson! 

## Current injection

The technique of current injection is described in document https://github.com/rin67630/Soft-Power-MPPT/blob/main/Hardware/About%20CV%20Injection.md. The bypass filter consists of a 8,2K* resistor and a 10 microfarad* condenser, the injection current resistor is a 500K trim potentiometer, which can be replaced by a fixed resistor, once the project is stable, currently the value is around 63K, excepted for the high voltage module which needs 3,3K.  
* The values are not critical, anything +- 50% will do.

## Connectors

The prototyping board is equipped with following connectors:

**Photovoltaic panel**

- Panel_in   positive.
- Gnd        negative.

**SZBK07 (mid-power 300W option)**

- Inject CV Injection
- Enable 
- Power_Input positive
- Gnd 
- Power_Out positive

**Main battery**

- positive
- negative

**Secondary battery or convenience output**

- positive
- himnegative

**Relay/FET control**

- 0..3.3V to control first relay
- 0..3.3V to control second relay
- Gnd.
- +5V.

**User defined measurement input**

- 0..3.3V analog input.
- Gnd
- +5V.

## Performance

- Quiescent current from the 12V battery: ~25mA, mainly from the WiFi chip, could be reduced to <1mA at night(2)
- Low-Power Efficiency at 1W 92%
- Low-Power Efficiency at 10W 95%
- Mid Power Efficiency at 200W 97%

(2) currently not realized, since my user measurement functions must go on permanently, which are preventing sleep.

## Commissioning

...to be described further, but the most important first:

- The U1 and evtl. U6 buck converters must be set to the float voltage of the battery before starting operations. This is fail-safe, without an operating ESP8266 the hardware will charge _and not overcharge_ the battery.
- If you use a HW813 as U3, you must set it a +5V you can do that with the trim pot or, better, cut the trace to the trim pot and solder a bridge on the 5V setting.
- U7 should be set at 11v using the trim pot.

Enjoy!

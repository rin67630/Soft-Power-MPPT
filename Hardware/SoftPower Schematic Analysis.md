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

## Hardware used

1. Several generally available buck converters, depending on panel size voltage, controlled by injecting voltage into their CV potentiometers to provide efficient power conversions.
2. An ESP8266 microcontroller to optimize solar panel power harvesting, manage the buck converters and the charging process for various battery chemistries; and provide WiFi connectivity and a cloud statistical dashboard.
3. Relatively few connections with power measurement modules and other components make it possible to build the hardware without a PCB, using just a prototyping board.
4. The low cost materials should be procured for far less than $50.

## Schematic diagrams

Unfortunately, I cannot provide a _one size fits all_ hardware. There are no current buck converters capable of having at the same time a very low quiescent current, high power, and be able to manage relatively high input voltage (see next section about converters used). For that reason, the design will consist of a base module, containing low-power, very low quiescent current buck converters, able to handling input power up to about 15 -20W. That base module can be used alone. To handle more power, an optional external buck converter can be added. The software will use the low-power modules in the low-power range and switch over to the more powerful buck converter as a power increases.

The base module has a versatile design. It uses a standard framework offered in several versions, depending on panel and battery voltages determining how different INA power measurement modules are used.

**1. SoftPower 1xINA3221:** This is the recommended version, staging a chip able to measure three channels. It will measure the voltage, the current and the power coming from the solar panel, fed/retrieved from the battery and provided by the convenience output. The A0 analog input is left free for an extra usage. Since the INA3221 module is specified for a maximum of 26V, this variant is reserved for the "12V class" of panels (Voc=~20V, Vpp=~18V) and "12V" batteries.

**2. SoftPower 3xINA226:** Functionally identical to above version with one INA3221 module. Measurements are done with three separate INA226 modules which are able to handle up to 36V. If D-SUN low power buck converters are used this variant allows the use of 24V class panels (Voc=~40V, Vpp=~36V) and "24V" batteries.

**3. SoftPower 2xINA226:** This version skips the INA226 dedictated to measure the convenience output. The convenience voltage will be measured over A0. You lose convenience current measurement and the A0 analog input is no longer available.

**4. SoftPower 1xINA226:** This version also skips the INA226 dedictated to measure the panel voltage and power. The panel voltage will be measured over A0. You also lose panel current measurement and monitoring conversion efficiency. The voltage of the convenience output is estimated ~5%.

**5. SoftPower Bare minimum Micropower:** The same as above with power option removed for clarity. This is the typical usage for micropower solutions with a solar panel up to 20W.

**6. SoftPower 3xINA226 Hi Volt:** This uses a buck converter able to handle higher voltage solar panels up to 60V but the output must not exceed 20V so only "12V" batteries are supported. The higher panel voltage does not allow to use a low power tandem buck converter, so that module must not be populated. Another limitation is the high panel voltage exceeds the maximum voltage for the INA226 chip, so low side current monitoring is used for the first INA226 with the panel voltage going over a 2:1 voltage divider before feeding Vbus Pin.

## Buck converters used

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

**Note:** The HW636 buck converter used in the High Voltage Variant is one of the few modules on the market that can handle 60V input. _However, it has an important caveat_: it cannot safely supply more than 20V at the output without _destroying the LT3800 chip!_ Sadly, its trimpot does not prevent this. The very best solution is to replace it's 50K trimpot by a 20K model to avoid this risk. Alternatively, before powering up the module screw the trimpot counterclockwise until a small clicking sound is heard at the minimum setting, then power it up and increase the voltage to the floating battery voltage, typically 13.8V for a lead-acid battery. This buck converter also has a built-in reverse feed current protection, so an ideal diode is not required.

## Buck converter injection preparation

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

## ESP8266 microcontroller

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

## OLED display option

The oled display is nice to have. It adds only ~2 mA to the overall consumption.
Two versions are supported:
1. 64x48 pixel Wemos display hat, just push it on the top of a WEMOS D1
1. 128x64 pixel display, must be connected separately by connecting:
    -  Vcc to +3.3V
    -  SCL to D1
    -  SDA to D2
    -  GND to GND

## Power measurement

### INA3221 module

The INA3221 power measurement module provides three independent measurement channels each consisting of voltage, current, power measurement.
- channel 1 is used to measure the photovoltaic module
- channel 2 is used to measure the main battery
- channel 3 is used to measure the convenience output/secondary battery.

**Note:** There are two different versions of INA3221 on the market. You should avoid the left one (purple) because the three measurement channels are connected together at V+. The black one on the right is the one to use, it has independent inputs and is also less expensive:
![image](https://user-images.githubusercontent.com/14197155/105282377-7e84c680-5bae-11eb-81cc-30ba40c3fb61.png) ![image](https://user-images.githubusercontent.com/14197155/105282569-f94de180-5bae-11eb-9613-98fb4ebb6170.png)


### INA226 module(s)

The INA226 power measurement module provides only one measurement channel, but two shunt resistor sizes are sold and they are more versatile.

### Addressing

If you use more than one module, you must provide different I2C addresses, by soldering a small tin bridge:
![image](https://user-images.githubusercontent.com/14197155/105281711-0538a400-5bad-11eb-97eb-b8db0fc177ce.png)

### Current measuring range

**Note:** The INA3221 board is normally sold with 0,1 Ohm shunts resulting in a measurement range 0..1,5A with an accuracy of 0,5mA, which is fine for the operation up to 20W. The INA226 is sold with either a 0,1 Ohm or 0,01 Ohm shunt with a measurement range 0..0,8A and 0..8,2A respectively. (Calculated with I = V/R, eg from [INA226 datasheet](https://www.ti.com/lit/ds/symlink/ina226.pdf) VShunt = 81,92mV.)

The original shunts can be relatively easy unsoldered by generously adding tin to both ends, then heating the ends in short sequence and shifting the resistor away with the soldering tip. You can do it! Even I can, as an old man with beginning Parkinson! If the maximum current is greater than the shut will support the shunts on the INA3221 board can be replaced with a 0,01 Ohm shunt resulting in a measurement range 0..15A with an accuracy of 5mA. Alternatively, remove the on-board shunt and use an external shunt sized for the maximum current.

## Current injection

The technique of current injection is described in document https://github.com/rin67630/Soft-Power-MPPT/blob/main/Hardware/About%20CV%20Injection.md. The bypass filter consists of a 8,2K<sup>*</sup> resistor and a 10 microfarad<sup>*</sup> condenser, the injection current resistor is a 500K trim potentiometer, which can be replaced by a fixed resistor, once the project is stable, currently the value is around 63K, excepted for the high voltage module which needs 3,3K.

<sup>*</sup> The values are not critical, anything +/- 50% will do.

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

- Quiescent current from the 12V battery: ~25mA, mainly from the WiFi chip, could be reduced to <1mA at night<sup>*</sup>
- Low-Power Efficiency at 1W 92%
- Low-Power Efficiency at 10W 95%
- Mid Power Efficiency at 200W 97%

<sup>*</sup> Not currently realized since my user measurement functions must go on permanently preventing sleep.

## Commissioning

...to be described further, but the most important first:

- The U1 and evtl. U6 buck converters must be set to the float voltage of the battery before starting operations. This is fail-safe, without an operating ESP8266 the hardware will charge _and not overcharge_ the battery.
- If you use a HW813 as U3, you must set it a +5V you can do that with the trim pot or, better, cut the trace to the trim pot and solder a bridge on the 5V setting.
- U7 should be set at 11v using the trim pot.

Enjoy!

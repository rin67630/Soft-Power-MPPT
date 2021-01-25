# Functional description of "Soft Power 1xINA226 Minimum"

Please confer to the schematic diagram https://github.com/rin67630/Soft-Power-MPPT/blob/main/Hardware/Soft%20Power%201xINA226%20Minimum.pdf  

## Power conversion from panel to battery
The photovoltaic panel is connected over P1,2 to the first buck converter U1 over a blocking diode D1, which prevents reverse current flowing from the battery into the panel, 
and also prevents burning the but converter in case of a short.  
The voltage of the panel goes over the R4 (2 Mohm) resistor, which builds together with the internal resistance of A0 a voltage divisor, providing a measuring range of 0..23V.

This Buck converter is set to the floating voltage of the battery, for a Lead-Acid, 13,8V. There is no hardware current limitation, since the panel is not supposed 
to deliver more current than the battery can take over.
The voltage is controlled over the D3 PWM output of the Wemos D1, which is first smoothed over the low pass filter R1 and C1 to a steady DC voltage, 
that can vary between almost 0 V and 3.3 V.

## Injection
The trim potentiometer RP1 is converting that voltage into a small current that will be injected into the CV potentiometer of the buck converter.
Cf. https://github.com/rin67630/Soft-Power-MPPT/blob/main/Hardware/About%20CV%20Injection.md for a detailed explanation of the injection process.
As explained in that document, there is a neutral voltage, for which the injection will not change the output voltage: 1.2V in the case of the HW613.  
This corresponds to a PWM value of 250. At a PWM value of 0, the voltage will increase, at a PWM value of 1024, the voltage will decrease.
The trim potentiometer should be set to such a value, that at PWM = 0 the maximum voltage of the battery ( in case of FLA 15,5 V equalizing voltage) is reached.
According to that setting, you will also have a minimum voltage reachable at PWM = 1024 that will roughly be around 10V. Please note as these two values.
The PWM values can be changed from the dashboard, explained in the software description.
## Enable
The D0 port of the Wemos D0 enables the U1 converter when HIGH. This is also the initial value of D0 upon booting.
The buck converter can be disabled e.g. if the panel voltage falls below the battery voltage to save power or in case of a overpowering (useful for the power extension version)
The software can provide the MPPT functionality and a current/power limitation upon changing the voltage setpoint more or less above the battery voltage.

## Battery measurement
The output of the buck converter U1 flows over the shunt between IN- to IN+ to the battery. At the opposite, the current provided by the battery will flow at the other direction 
when the battery discharge.
The INA module can measure the current in both directions. A bridge between IN- and VBUS cares for the voltage measurement.  
The INA module provides factory calibrated measurements for voltage, current, power over an I2C bus to the WEMOS D1. An adjustment is not necessary for R100 shunts.
In case of R010 shunts (see procedure to (un)solder the Shunts in document https://github.com/rin67630/Soft-Power-MPPT/blob/main/Hardware/SoftPower%20Prototyping.md) 
the resistance in circuit might differ from the tag value, and a correction must be done in software.

## Power supply for the board
The battery voltage goes moreover to U2, the fixed 5 V converter that provides power to the WEMOS D1 microcontroller. 

## Convenience power supply
The battery voltage goes also to U3 a buck converter that provides an output voltage to be used at the discretion of the user. 
Similar to U1, an injection over R3, C3, RP3 provides a limited possibility to change the voltage of that output. E.g. if the converter is set to 9V, 
the injection will be able to increase that voltage up to ~12 V or to reduce it down to ~5 V.
Please use the procedure described under " injection " to set the trim potentiometer to the right value.

The convenience power supply can also be switched on and off over the enable line controlled by D8.
This is especially useful to prevent deep discharge of the battery, in case of main usage of the battery power from the convenience power supply.

## Relay outputs
The board provides two identical connectors intended to control relay modules or FET Modules.
D5 and D6 control the modules at P7 and P8.
A FET Module is highly recommended, switching low side, in case of taking power direct from the battery. This will prevent deep discharge.

## I2C port
An I2C port is provided at P9. That port can be used to interface additional sensors or provide additional IO.
Please take however in consideration, that an I2C bus should not exceed a lenght of 20-30cm and might be a source of trouble.

## OLED Display
2 types of OLED displays can be used and are supported by software.
1. the Wemos D1 64*48 pixel OLED display that can be plugged on the top of the WEMOS D1
2. 128*64 pixel OLED displays **with I2C interface** that can be operated through the I2C port or plugged on the top of the WEMOS D1, if you build an adapter board.

All hardware is soldered on a 5x7cm prototyping board, which can be used as-is and handle small solar panels between 10W and 20W.
for more power, an additional power Buck converter can be added, to boost the power capacity to approximately 200W.

(here comes soon the description of that addition)




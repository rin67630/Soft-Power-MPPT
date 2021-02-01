#Commissioning Soft-Power hardware

To commission Soft Power and trim the potentiometers you best need an power supply with adjustable voltage and current.
You also need for the first tries something to limit the current from the battery to avoid a disaster if you make a mistake. A 5W car bulb in series with the battery will do.

For the first group of settings we will not plug the ESP.
If you have the high-power option, **please disconnect the + output of the high-power buck converter** and leave the other wires connected.

## Preset the buck converters
We will now trim the buck converter to their default voltage
Give approximately 18 V with a low current limit of ~ 100mA as a panel voltage. ( you may use a small panel, in half shade for that, just be sure that you will have a steady condition and not too much powerful the beginning.  

1. Trim the potentiometer of U1 to get at the battery output the float voltage of your battery (for lead-acid FLA that would have been 13.8V).
2. Be sure that **U2 delivers 5V**, if you haven't configured the presets of a HW613, set to 5V accordingly.
3. Trim the potentiometer of U3 to get at the Aux output a voltage corresponding to the float of your smaller battery, else to 75% of the desired voltage range, which should be at least 2V below the minimum of the main battery.  
4. Set the voltage of the high-power buck converter to the same voltage as U1. (be sure that the SZBK07 high-power buck converter is enabled, the red light must be on)



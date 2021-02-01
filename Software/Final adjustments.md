# Final adjustments
This file describes the procedure to adjust the PWM parameters once your software is installed and you have the Thinger.io dashboard running and operational.

## Set the Low-power injection.
Once you have uploaded the software accordingly configured to your WiFi and Thinger credentials. (cf Commissioning the software.md) and you have your dashboard running
you should run a small calibration procedure to refine the PWM parameters.

Run your Soft-Power from battery to start it, then provide limited power to the panel input (your panel in shade for instance)

Once the ESP has booted (the blue light got on for a second and then lit off), the OLED information appears,  Thinger shows the ESP as being connected, the dashboard is available and responsive.  
Then you can remove the battery voltage, the ESP should continue being powered from its low-power buck converter.

- You should notice the Vbat voltage, which should get roughly the voltage you have set up on the first buck converter U1, during the hardware setup.  

- Else, correct the voltage to be exactly the same that what you had set up using the hardware only.
To do that at the dashboard use the blue slider  
![image](https://user-images.githubusercontent.com/14197155/106478854-f229ac00-64a9-11eb-943e-c67a4a8e8d9e.png)  
Note its PWM value in the software at a0_Parameters at the line #define INJ_NEUTRAL 400.  

- Move the slider to the right maximum. If you have a fixed resistor in place of RP1, just take notice of the voltage in the aO_Parameters of the configuration  
(#define INJ_LP_MAX  15200)  
--if you have a trim pot RP1, adjust it to the equalization voltage of your battery (15.2V for lead acid battery), in the aO_Parameters of the configuration  
(#define INJ_LP_MAX  15200)  

Move the slider to the left minimum and take notice of the voltage (which should be between 10.5V and 11.5V in the aO_Parameters of the configuration (#define INJ_LP_MIN  11040).

## Set the High-power injection.
(you can skip that if you have no high-power extension)
- Move the slider again to the neutral position, where Vbat shows the float voltage of your battery and switch to high-power. If necessary, correct the CV potentiometer of the high-power buck converter to get to the same voltage again.

- Move the slider to the left minimum and adjust the trim pot RP2 to roughly the same voltage than the low power buck, take notice of the voltage in the aO_Parameters of the configuration (#define INJ_HP_MIN  11070).

- Move the slider to the right maximum and take notice of the voltage in in the aO_Parameters of the configuration (#define INJ_HP_MAX  15280).

Reconnect you battery.

You can then recompile the programm to take the new adjustments in account and enjoy your Soft-Power-MPPT. device.
your Soft-Power is now adjusted and ready to use.

Enjoy!



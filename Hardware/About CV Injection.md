A buck converter with a microprocessor can produce a Constant Voltage (CV) as described below.

Practically every buck converter regulates its output voltage over a feedback loop.
The output voltage goes through a resistive divisor into the feedback input of a converter chip. The chip regulates the Pulse Width Modulation (PWM) output in order to keep a constant voltage 
on the feedback input. That constant voltage determined by the chip usually lies between 0.8V and 1.5V.

At a given output voltage, the resistive divisor (usually a trim potentiometer) can be seen as a voltage source with an internal resistance.
If current is fed into or drawn from that voltage source the resulting voltage will increase or decrease respectively.
The effect is the buck converter chip will compensate with an opposite change on the output voltage. 
So feeding some current into the potentiometer will reduce the output voltage, drawing some current from the potentiometer will increase the output voltage.

![injection](https://user-images.githubusercontent.com/14197155/103954043-a18d9000-5143-11eb-96a6-9f30876e3fec.jpg)

Of course, with that technique the output voltage cannot vary from zero to the maximum. By fooling the feedback circuit the overall gain of the feedback loop is also reduced.
In my experience, every buck converter I have tested by injecting current to change the voltage from -100% to +10% was safe and efficient.

By the way, this technique is also used by many modules providing a current limitation functionality. For example, an op amp monitors the output current and injects
voltage into the feedback loop to reduce output voltage as the current increases.

![Typical trim potentiometer on a buck converter](1608728259654.png)

**Image:** Typical buck converter

With a microcontroller the injection technique can be used to do neat things controlling an existing buck converter:
- Digital: A direct digital output 3.3V to 5V over a 1k resistor and a diode can shut down a buck converter. A high signal will increase the feedback voltage in such a way, the chip will virtually stop. 
- Software CV: A PWM digital output followed by a 1KOhm/1microfarad low pass filter and a high-value resistor (approximately 3 times the value of the potentiometer), the output of the converter can be varied approximately +10% -30%, which is also the maximum variation you can reach, to keep the feedback loop working safely and not impact too much the output voltage stability.
- Software CC: The same circuit and a current measurement chip, like an INA226 or ACS712, together with a software feedback loop can provide a kind of
current control. This software loop will however be considerably slower than the analog equivalent describe before and must be processed fast enough. 
- Software MPPT: The same circuit and a double current/voltage measurement by two chips, like INA226 and the above-described software current feedback loop, can provide solar panel maximum power point tracking functionality. 

The importance of the neutral injection point: 

As already mentioned, buck converters have a FB (feedback) voltage by design. The PWM injection circuit will feed current into the voltage potentiometer if it is over the FB voltage, and draw current from the potentiometer if it is below. If the FB voltage were at 1.65V (half of 3.3V), you could increase or decrease the output voltage by the same value. Usually however, the FB voltage is lower (0.8V or 1.2V) which means output voltage can be decreased more than increased. Fortunately, that is also what we need for designing a battery charger.

In software, it is an advantage to know which PWM value will correspond to the FB voltage and be the neutral point, where current is whether fed, nor drawn from the feedback circuit. It is a good practice to initialize the PWM outputs upon booting to that value.

**Caveats:**

The injection technique is safe to use for a limited range of output voltages, ideal for what is required for battery charging and solar controllers.
The software Constant Current (CC) control is too slow to protect the buck controller against inadvertent shorts; small buck converters without currently limitation will burn without notice...

There are several reasons to tweak commercial buck converters and not PWM directly the buck converter functionality in software:
- Efficiency: The PWM signal of most microcontrollers have a fixed frequency around a few KHz. Sure you can operate a buck conversion at that frequency, but it is far from being efficient. The state of the art switching is between 100Khz and 1MHz, requiring much smaller inductors and filter capacitors.
- Safety: The buck converters will be set to generate a safe voltage on their own immediately after power on, right before the microcontroller will have finished booting. The circuit can be designed to work without the microcontroller which is only used to optimize the operation.
- Design: Designing a buck converter is not something to improvise, the PCB must be designed in such a way to reduce the impact of high current pulses onto the feedback circuit and GND traces must be carefully routed. All that has already been taken cared of by the designers of your commercial buck converter and tested to a commercial grade, less sorrows and trouble for you.

Enjoy!

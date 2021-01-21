### Caveat
The software is _still under development_: the display, menu, serial functions and dashboard functionalities are operative.  
The MPPT control loop and the battery loading processes are still missing, since I am still in the process of analyzing the behavior of the hardware, before determining the best algorithm.

# Explanations about the software.
I like software being easy to read, close to naturally language.  
The Arduino IDE is a very accessible development environment, that hides the complexity of C++ language to the beginners.
My code makes also extensive use of compiler directives to determining different options.  
For the sake of clarity I made an extensive use of comments, especially commenting why I realized the code that way.  
I refrained as far as possible to use geek code that requires C++ expertise beyond what an Arduino user with reasonable experience can understand. 
The Arduino IDE provides the possibility to split the code into separate tabs for clarity.
![image](https://user-images.githubusercontent.com/14197155/105344771-a7737e80-5be3-11eb-8d53-a8eb8499e287.png)

## Functional blocks
I used that feature to organize my code in functional blocks:
1. ESP_SwissArmyKnife: comment-only, a short description of the target, license terms.
2. Thinger Dasboard:   comment-only, the JSON content of a dashboard example at thinger.io provided here for convenience.
3. a0_Parameters: options defined by compiler directives. __This will be the main place for users to tamper with.__
4. a1 Libs_Vars: libraries and variables required by the program.
5. b_Functions: the function subroutines used by the program.
6. c_Setup: The setup process that runs once upon booting the ESP
7. d_Menu: The serial menu that can be used to at just parameters and request some reports on the serial line.
8. e_Data: The main processing routine
9. f_Display: The code intended to display current information on the OLED displays
10. g_Serial: The code intended to issue the serial reports called by the menu.
11. h_Wireless: The code to exchange information with the thinger.io Dashboard and other devices
12. k_Loop: The scheduling loop controlling all previous tasks.
13. x_ReadMe: comment-only, mainly for myself contains some syntaxes, that my limited brain tends to forget.
14. y_ParkedCode: comment-only, containing parts of the code intended for further usage. 

The code separation into functional blocks makes it much easier to jump between several tasks.

## Installing the Arduino IDE with ESP support.
https://randomnerdtutorials.com/how-to-install-esp8266-board-arduino-ide/
Then you need a few libraries to run SoftPower:
Start the library manager: Tools/Manage Libraries...
You need 
- ArduinoJson by Benoit Blanchon
- ESP8266...OLED driver, by Thingpulse and Fabrice Weinberg
- INA2xx by Arnd
- thinger.io by Alvaro Luis Bustamente
The other libraries should be already present.

## Download instructions
You can download all the files from the main page of Soft-Power upon clicking on the green Code button and selecting "download Zip".
This will save a file Soft-Power-MPPT-main.zip.
From that compressed file, extract the folder "Software" and copy it into your Arduino working space.
Rename that folder SoftPowerMPPT.

You will now find the project in File/Sketchbook/SoftPowerMPPT and after starting, it you will find all tabs present.

## Required libraries
to be continued...

## Configuration instructions
to be continued...

## Instructions to begin with Tinger.io
to be continued...


Stay tuned!

# Explanations about the software.
I like easy to read, close to naturally language, software.  
The Arduino IDE is very accessible development environment, that hides the complexity of C++ language to the beginners.
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

## Download instructions
to be continued...

Stay tuned!
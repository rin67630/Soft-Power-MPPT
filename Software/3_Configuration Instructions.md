# Configuration instructions
Warning: a few settings must interactivity match between the configuration at Thinger.io and the configuration file in the ESP.
So, if you are not an expert, may I strongly recommend not to change the username, nor to change the HOST_NAME unless you get familiar with the operation of the whole ecosystem.

The software is written in such a way that you can use it just upon defining your options in the folder a0_Parameters.  
If you are not familiar with the code, *this (and eventually Thinger_Dashboard) are the only folder that you should change*:  

## Parameter list
If you have several devices, change the HOST_NAME and let it be "Soft_Power", which must be matching the device name that you created at Thinger.io
The HOST_NAME also matches the device content of the default dashboard.

Then proceed with the hardware configuration:
### Hardware configuration
- #define WEATHER_SOURCE_IS_URL specifies that you get the weather information from an URL, the other options are given in the comment, so you also have the option to  
#define WEATHER_SOURCE_IS_NONE, if you do not want to process weather information.

- #define BATTERY_SOURCE_IS_INA specifies that to get the battery voltage and current from an INA-device, the other options being  
#define BATTERY_SOURCE_IS_UDP to get the battery information from another ESP as a slave device, or  
#define BATTERY_SOURCE_IS_NONE to not process battery information at all ( which only makes sense in my other projects ).

- #define PANEL_SOURCE_IS_A0 specifies that you get the panel voltage over A0 (that would be the case if you only have one INA226), the other options being  
#define PANEL_SOURCE_IS_INA if you are using an INA sensor for the panel (with INA3221 or at least two INA226) or  
#define PANEL_SOURCE_IS_URL to get the battery information from another ESP as a slave device and  
#define PANEL_SOURCE_IS_NONE to not process panel information at all ( which only makes sense in my other projects ).  

- #define CONVENIENCE_SOURCE_IS_A0 specifies that you get the convenience voltage over A0 (that would be the case if you only have one INA226), the other options being  
#define CONVENIENCE_SOURCE_IS_INA if you are using an INA sensor for the convenience  (with INA3221 or at least two INA226) or  
#define CONVENIENCE_SOURCE_IS_URL to get/control the convenience information from another ESP as a slave device and   
#define CONVENIENCE_SOURCE_IS_NONE to not process convenience information at all ( which only makes sense in my other projects or if you decides not to populate the convenience output).  

- #define BATTERY_IS_12V_FLA specifies that you are using a 12 V flooded acid battery, the other options being #define BATTERY_IS_12V_AGM to use a 12 V AGM battery and so on...  
- #define DISPLAY_IS_OLED64x48 define if you are using an OLED display and which one.  
- #define DISPLAY_REVERSED if you're display should be used downunder (by Australians for example ;-)  

### Technical
Do not change this block: (unless you know what you do...)  
- #define THINGER            //(Comment out, if no thinger.io used)
- #define WRITE_BUCKETS      //(Comment out, if this is the second device for Thinger)
- //'define DWITTER          //(Comment out, if no dwitter.io used) 
- #define Console0 Serial    // Port for user inputs  
- #define Console1 Serial    // Port for user output
- #define Console2 Serial1   // Port for midnight report e.g. on thermal printer
- #define Console3 Serial    // Port for boot messages
- #define SERIAL_SPEED  9600 //9600  115200 230400
- //define PUBLISH_REPORT           // Issue events&midnight reports to UDP Port + 1, comment out else
- //#define PUBLISH_BATTERY         // If this is the battery master, comment out else
- #define UDP_TARGET "192.168.1.1"  // IP to forward data
- #define UDP_PORT   4214           // Port to forward data

### Credentials
Enter here your Thinger credentials: user name, device password *not the web password*, device name, if different from "Soft-Power".  
- #define THINGER_USERNAME    "User Name"        // Enter your user Name at Thinger
- #define THINGER_CREDENTIALS "Device password"  // This is the device password that matches the password that you defined in Thinger.io for your device.  
- #define THINGER_DEVICE HOST_NAME

#### WiFi credentials
If you already have successfully used your ESP device in your Wi-Fi network, you can skip that block, else...  

Put two slashes in front of "#define SMARTCONFIG" (this comments out this line) 
Enter your Wi-Fi credentials   
Run the ESP unplugged from Soft-Power connected to an USB  
Compile and upload. 
At the IDE, Tools, start the serial monitor, set to 9600 Baud.
You should see something like that:
´´´
0⸮~?⸮4⸮Ҷ⸮⸮OAqr⸮⸮
ESP-Karajan at work,
Serial @ 9600 Baud
MAC address: D8:F1:5B:11:0E:AC , 
Hostname: Soft-Power
IP address::192.168.188.32
Now is 16:57:29. The Epoch is: 1612195049
Date is Monday, 01 February 2021
Communicating on UDP port: 4214
OTA-Ready
´´´
The first gibberish line is normal.
This is the regular booting report.  
If it get stuck after Serial @ 9600 Baud, your Wi-Fi connection where not successful. 
Correct your credentials and repeat the procedure, until you get an IP.  

Then return to the Arduino IDE, remove the two slashes before the line "#define SMARTCONFIG", 
(you may remove your credentials, they are stored in the ESP and will not be used anymore).  
- #define SMARTCONFIG  // (WiFi Credentials over GogglePlay/Apple App SmartConfig)

Upload the software again, and check, that you get the boot report correctly.

You should have opened a a free account at openweathermap.org, and have noted the map app ID.  
You can also search and call your city, then note its location ID "https://openweathermap.org/city/2928809" (the last number after the slash)  

Enter now these credentials together with your time zone information:  
#define OPEN_WEATHER_MAP_APP_ID      "208085abb5a3859d1e32341d6e1f9079"
#define OPEN_WEATHER_MAP_LOCATION_ID "2820158"
#define OPEN_WEATHER_MAP_LANGUAGE    "en"
#define OPEN_WEATHER_MAP_UNITS       "metric"

// ***Time zones***
#define NTP_SERVER "de.pool.ntp.org"
#define MYTZ TZ_Europe_Paris
#define TZ   1                              // (utc+) TZ in hours

###Electrical parameters

Finally we need to enter the electrical parameters corresponding to your INA hardware:
Enter for each channel  the shunt value in microohm (R100 = 100 000)
Enter approximately the maximum value for your reading (this is only an order of magnitude below the library to optimize the non-floating-point operation)
- #define SHUNT0   100000    // Nominal Shunt resistor value in microOhm
- #define AMPERE0   2        // Chose here about 2x the max expected Amps
- #define SHUNT1   100000    // Nominal Shunt resistor value in microOhm
- #define AMPERE1   2        // Chose here about 2x the max expected Amps 
- #define SHUNT2   100000    // Nominal Shunt resistor value in microOhm
- #define AMPERE2   2        // Chose here about 2x the max expected Amps  
- #define MIN_AMP  -1       
- #define MAX_AMP  +2
- #define MIN_WATT -1
- #define MAX_WATT +20
if you are using shunts on board, that are smaller then R050, you should enter the correction factors for calibration (cf. hardware commissioning instructions, divisor rule of three, increasing factor reduces the display value)
- #define IFACTORP  1000000   // Panel Current correction factor 1000000 is normal,   -"- only used when PAN_SOURCE_IS_INA.
- #define IFACTORB  1000000   // Battery Current correction factor 1000000 is normal,  -1000000 reverses shunt, change value to correct for wrong Amp values  
- #define IFACTORA  1000000   // Aux Out Current correction factor 1000000 is normal,   -"- only used when AUX_SOURCE_IS_INA.
if you are measuring the panel voltage over A0, you should add the the correction factor for the panel voltage:  
- #define PANEL_MAX 23200     // mV panel voltage  (Adjust to match panel voltage, multiplying rule of three, increasing factor increases the display value)

Finally enter your injection factors (cf. hardware commissioning instructions)  
- #define INJ_NEUTRAL 400     //   PWM value that leads to the same voltages than adjusted without ESP.
- #define INJ_HP_MIN  11070   //   Minimum Battery Voltage Setpoint at injection=1024 (in mV)
- #define INJ_HP_MAX  15610   //   Maximum Battery Voltage Setpoint at injection=0  (in mV)
- #define INJ_LP_MIN  11040   //   Minimum Battery Voltage Setpoint at injection=1024 (in mV)
- #define INJ_LP_MAX  15560   //   Maximum Battery Voltage Setpoint at injection=0 (in mV)
- #define INJ_AUX_MIN  2750   //   Minimum Auxiliary Voltage Setpoint at injection=1024 (in mV)
- #define INJ_AUX_MAX  8550   //   Maximum Auxiliary Voltage Setpoint at injection=0 (in mV)

That should be all...  
Compile and enjoy!


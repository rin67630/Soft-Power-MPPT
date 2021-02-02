#define HOST_NAME   "Soft-Power" // n.b: The HOST_NAME must match the device name of Thinger.

//  ***Credentials***  (Adjust to your own values)
// Wifi
#define SMARTCONFIG  // (WiFi Credentials over GogglePlay/Apple App SmartConfig)
// alternatively to Smartconfig App, you can comment out Smartconfig 
// and enter your WiFi credentials to initalize for a new WiFi
//#define ERASE_WIFI_CREDENTIALS 
#define WIFI_SSID            "SSID"
#define WIFI_PASS            "PASS"
#define wifiMaxTries         10
#define wifiRepeatInterval   100
//Thinger
#define THINGER_USERNAME           "SoftPower1"       
#define THINGER_DEVICE_CREDENTIALS "MyVerySecretDevicePassword"    
#define THINGER_DEVICE HOST_NAME    
//Location for weather
#define OPEN_WEATHER_MAP_APP_ID      "208085abb5a3859d1e32341d6e1f9079" 
#define OPEN_WEATHER_MAP_LOCATION_ID "2820158"
#define OPEN_WEATHER_MAP_LANGUAGE    "en"
#define OPEN_WEATHER_MAP_UNITS       "metric"
//Time zone
#define NTP_SERVER "th.pool.ntp.org"
#define MYTZ TZ_Asia_Bangkok
#define TZ   5               // (utc+) TZ in hours

// ***Hardware Configuration***  (Adjust to your own hardware options)
#define WEATHER_SOURCE_IS_URL   //_URL _NONE         Change end accordingly
#define BAT_SOURCE_IS_INA       //_INA _UDP _NONE        Change end accordingly
#define PAN_SOURCE_IS_A0        //_A0 _INA _UDP _NONE   Change end accordingly
#define AUX_SOURCE_IS_NONE      //_A0 _INA  _NONE    Change end accordingly
#define BATTERY_IS_12V_LIFEPO   //_12V_FLA _12V_AGM _12V_GEL _12V_LIFEPO 11V_LIPO
#define DISPLAY_IS_OLED128x64   //_NONE _OLED64x48 _OLED128x64
#define DISPLAY_REVERSED


// ***Electrical parameters***   (Adjust, if you use other shunts than R100)
#define SHUNT0   100000     // Nominal Shunt resistor value in microOhm (Channel 1 of the INA, connected to the battery)
#define AMPERE0   2         // Chose here about 2x the max expected Amps
#define SHUNT1   100000     // Nominal Shunt resistor value in microOhm (Channel 2 of the INA, connected to the panel)
#define AMPERE1   2        // Chose here about 2x the max expected Amps 
#define SHUNT2   100000     // Nominal Shunt resistor value in microOhm (Channel 3 of the INA, connected to the output)
#define AMPERE2   2         // Chose here about 2x the max expected Amps

// ***Calibration***  (Leave as is for a first run)
#define IFACTORP  1000000   // Panel Current correction factor 1000000 is normal,    -"- only used when PAN_SOURCE_IS_INA.
#define IFACTORB  1000000   // Battery Current correction factor 1000000 is normal,  -1000000 reverses shunt, change value to correct for wrong Amp values
#define IFACTORA  1000000   // Aux Out Current correction factor 1000000 is normal,  -"- only used when AUX_SOURCE_IS_INA.
#define PANEL_MAX 23300     // mV panel voltage  (Adjust to match panel voltage),    -only used when PAN_SOURCE_IS_A0.
#define INJ_NEUTRAL 430
#define INJ_HP_MIN  00000   //   Minimum Battery Voltage Setpoint at injection=1024
#define INJ_HP_MAX  00000   //   Maximum Battery Voltage Setpoint at injection=0 
#define INJ_LP_MIN  10000   //   Minimum Battery Voltage Setpoint at injection=1024
#define INJ_LP_MAX  14830   //   Maximum Battery Voltage Setpoint at injection=0 
#define INJ_AUX_MIN  1870   //   Minimum Auxiliary Voltage Setpoint at injection=1024
#define INJ_AUX_MAX  8740   //   Maximum Auxiliary Voltage Setpoint at injection=0 

#define BATT_CAPACITY 12 // Ah

//  ***Communicatin options*** (For geeks only, else leave as it is)
//'define DWITTER               //(Comment out, if no dwitter.io used) 
#define THINGER                 //(Comment out, if no thinger.io used)
#define WRITE_BUCKETS           //(Comment out, if this is the second device for Thinger)
//define PUBLISH_REPORT              // Issue events&midnight reports to UDP Port + 1, comment out else
//#define PUBLISH_BATTERY            // If this is the battery master, comment out else
//#define UDP_TARGET "192.168.188.75"  // IP to forward data
#define UDP_PORT   4214              // Ports to forward/receive data
#define Console0 Serial      // Port for user inputs  
#define Console1 Serial      // Port for user output
#define Console2 Serial1     // Port for midnight report e.g. on thermal printer
#define Console3 Serial      // Port for boot messages
#define SERIAL_SPEED            9600 //9600  115200 230400

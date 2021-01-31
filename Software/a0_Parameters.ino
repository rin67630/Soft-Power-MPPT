#define HOST_NAME   "Soft-Power" // https://github.com/rin67630/Soft-Power-MPPT

// ***Hardware Configuration***
#define WEATHER_SOURCE_IS_URL  //_URL _NONE             Change end accordingly
#define BAT_SOURCE_IS_INA      //_INA _UDP _NONE        Change end accordingly
#define PAN_SOURCE_IS_INA      //_A0 _INA _UDP _NONE    Change end accordingly
#define AUX_SOURCE_IS_INA      //_A0 _INA  _NONE        Change end accordingly
#define BATTERY_IS_12V_FLA     //_12V_FLA _12V_AGM _12V_GEL _12V_LIFEPO 11V_LIPO
#define DISPLAY_IS_OLED128x64  //_NONE _OLED64x48 _OLED128x64
#define DISPLAY_REVERSED

#define THINGER             //(Comment out, if no thinger.io used)
#define WRITE_BUCKETS       //(Comment out, if this is the second device for Thinger)
//'define DWITTER           //(Comment out, if no dwitter.io used) 

#define Console0 Serial      // Port for user inputs  
#define Console1 Serial      // Port for user output
#define Console2 Serial1     // Port for midnight report e.g. on thermal printer
#define Console3 Serial      // Port for boot messages
#define SERIAL_SPEED    9600 //9600  115200 230400

#define THINGER_USERNAME    "User"       
#define THINGER_CREDENTIALS "Device password"    
#define THINGER_DEVICE HOST_NAME

//define PUBLISH_REPORT           // Issue events&midnight reports to UDP Port + 1, comment out else
//#define PUBLISH_BATTERY         // If this is the battery master, comment out else
#define UDP_TARGET "192.168.1.1"  // IP to forward data
#define UDP_PORT   4214           // Port to forward data

//  ***Credentials***
#define SMARTCONFIG  // (WiFi Credentials over GogglePlay/Apple App SmartConfig)
// alternatively to Smartconfig App, you can comment out Smartconfig 
// and enter your credentials to initalize for a new WiFi
#define WIFI_SSID          "SSID"
#define WIFI_PASS          "PASS"
#define wifiMaxTries         10
#define wifiRepeatInterval   100

#define OPEN_WEATHER_MAP_APP_ID      "208085abb5a3859d1e32341d6e1f9079"
#define OPEN_WEATHER_MAP_LOCATION_ID "2820158"
#define OPEN_WEATHER_MAP_LANGUAGE    "en"
#define OPEN_WEATHER_MAP_UNITS       "metric"

// ***Time zones***
#define NTP_SERVER "de.pool.ntp.org"
#define MYTZ TZ_Europe_Paris
#define TZ   1                              // (utc+) TZ in hours

// ***Electrical parameters***
#define SHUNT0   100000    // Nominal Shunt resistor value in microOhm
#define AMPERE0   2        // Chose here about 2x the max expected Amps
#define SHUNT1   100000    // Nominal Shunt resistor value in microOhm
#define AMPERE1   2        // Chose here about 2x the max expected Amps 
#define SHUNT2   100000    // Nominal Shunt resistor value in microOhm
#define AMPERE2   2        // Chose here about 2x the max expected Amps  
#define MIN_AMP  -1       
#define MAX_AMP  +2
#define MIN_WATT -1
#define MAX_WATT +20
#define IFACTORP  1000000   // Panel Current correction factor 1000000 is normal,   -"- only used when PAN_SOURCE_IS_INA.
#define IFACTORB  1000000   // Battery Current correction factor 1000000 is normal,  -1000000 reverses shunt, change value to correct for wrong Amp values
#define IFACTORA  1000000   // Aux Out Current correction factor 1000000 is normal,   -"- only used when AUX_SOURCE_IS_INA.
#define PANEL_MAX 23200     // mV panel voltage  (Adjust to match panel voltage)

#define INJ_NEUTRAL 400

#define INJ_HP_MIN  11070   //   Minimum Battery Voltage Setpoint at injection=1024
#define INJ_HP_MAX  15610   //   Maximum Battery Voltage Setpoint at injection=0 
#define INJ_LP_MIN  11040   //   Minimum Battery Voltage Setpoint at injection=1024
#define INJ_LP_MAX  15560   //   Maximum Battery Voltage Setpoint at injection=0 
#define INJ_AUX_MIN   2750  //   Minimum Auxiliary Voltage Setpoint at injection=1024
#define INJ_AUX_MAX   8550  //   Maximum Auxiliary Voltage Setpoint at injection=0 

#define BATT_CAPACITY 12 // Ah

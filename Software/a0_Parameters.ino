#define HOST_NAME   "SolarSAK" // Solar Swiss Army Knife

// ***Functional Configuration***
#define WEATHER_SOURCE_IS_URL   //_URL _NONE              Change end accordingly
#define BATTERY_SOURCE_IS_INA   //_INA _UDP _NONE         Change end accordingly
#define PANEL_SOURCE_IS_A0      //_INA _UDP _NONE
#define BATTERY_IS_12V_LEAD     //_12V_LEAD _12V_LIFEPO 11V_LIPO

#define THINGER            //(Comment out, if no thinger used)
#define WRITE_BUCKETS      //(Comment out, if this is the second device for Thinger)

#define Console0 Serial      // Port for user inputs  
#define Console1 Serial      // Port for user output
#define Console2 Serial1     // Port for midnight report e.g. on thermal printer
#define Console3 Serial      // Port for boot messages
#define SERIAL_SPEED            9600 //9600  115200 230400


//define PUBLISH_REPORT           // Issue events&midnight reports to UDP Port + 1, comment out else
//#define PUBLISH_BATTERY         // If this is the battery master, comment out else
#define UDP_TARGET "192.168.188.75"  // IP to forward data
#define UDP_PORT   4211           // Port to forwared data


//  ***Credentials***
#define SMARTCONFIG  // (WiFi Credentials over GogglePlay/Apple App SmartConfig)
// alternatively to Smartconfig App, you can comment out Smartconfig 
// and enter your credentials to initalize for a new WiFi
//#define WIFI_SSID          "SSID"
//#define WIFI_PASS          "PASS"
#define wifiMaxTries         30
#define wifiRepeatInterval   100

#define OPEN_WEATHER_MAP_APP_ID      "208085abb5a3859d1e32341d6e1f9079"
#define OPEN_WEATHER_MAP_LOCATION_ID "2820158"
#define OPEN_WEATHER_MAP_LANGUAGE    "en"
#define OPEN_WEATHER_MAP_UNITS       "metric"

#define THINGER_USERNAME    "Thinger User"       
#define THINGER_CREDENTIALS "Device Credentials"    
#define THINGER_DEVICE HOST_NAME     //Device name as defined in first line

// ***Time zones***
#define NTP_SERVER "de.pool.ntp.org"
#define MYTZ TZ_Europe_Paris
#define TZ   1                              // (utc+) TZ in hours

// ***Electrical parameters***
#define SHUNT    10000     // Shunt resistor value in microOhm
#define AMPERE   10        // 10 or 1
#define MIN_VOLT 11.0      // 11.0   9.6
#define MAX_VOLT 14.4      // 14.4  12.8
#define FLOAT    13.8      // Volt
#define ABSORB   14.4      // Volt
#define LOWLIM   11.2      // Volt
#define TRICKLE  0.3       // Ampere
#define MIN_AMP  -1
#define MAX_AMP  +2
#define MIN_WATT -2
#define MAX_WATT +12
#define PANEL_MAX 23200 // mV panel voltage

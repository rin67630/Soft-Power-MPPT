#define DEVICE_NAME   "SoftPowerTest" // n.b: The HOST_NAME must match the device name of Thinger.

//  ***Credentials***  
// WifI: for the very first run with a new ESP or on a new WiFi network 
// remove the // from the next line and provide real SSID and PASS credentials.
#define ERASE_WIFI_CREDENTIALS 
#define WIFI_SSID          "SSID"
#define WIFI_PASS          "Password"
#define wifiMaxTries       20
#define wifiRepeatInterval 500
// after a successful connection, you can revert to the defaults lines again.

//Thinger option
#define THINGER_USERNAME           "USERNAME"       
#define THINGER_DEVICE_CREDENTIALS "Device Credentials"    
#define THINGER_DEVICE DEVICE_NAME   

//Influx option (work in progress)
#define INFLUXDB_URL "https://eu-central-1-1.aws.cloud2.influxdata.com"
#define INFLUXDB_TOKEN "ZON2344MVMpe7ukp7bSOCyjskjlkjlkjlOP6W-qLftp7lkjhlkjhcOBQKiv0Tz1aDrszK6wwgoIaH4WAV9GcQ=="
#define INFLUXDB_ORG "your@email"
#define INFLUXDB_BUCKET "SoftPower Bucket"

//Location for weather
#define OPEN_WEATHER_MAP_APP_ID      "Openweathermapps ID" 
#define OPEN_WEATHER_MAP_LOCATION_ID "Location"
#define OPEN_WEATHER_MAP_LANGUAGE    "en"
#define OPEN_WEATHER_MAP_UNITS       "metric"
//Time zone
#define NTP_SERVER "de.pool.ntp.org"
#define TZ TZ_Europe_Berlin

// ***Hardware Configuration***  (Adjust to your own hardware options)
#define WEATHER_SOURCE_IS_URL   //_URL _NONE         Change end accordingly
#define BAT_SOURCE_IS_INA       //_INA _UDP _NONE        Change end accordingly
#define PAN_SOURCE_IS_INA       //_A0 _INA _UDP _NONE   Change end accordingly
#define AUX_SOURCE_IS_INA       //_A0 _INA _UDP _NONE    Change end accordingly
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
#define IFACTORP   1000000   // Panel   Current correction factor 1000000 is normal,   -"- only used when PAN_SOURCE_IS_INA.
#define IFACTORB   1000000   // Battery Current correction factor 1000000 is normal,  -1000000 reverses shunt, change value to correct for wrong Amp values
#define IFACTORA   1000000   // Aux Out Current correction factor 1000000 is normal,   -"- only used when AUX_SOURCE_IS_INA.
#define PANEL_MAX  23300     // mV panel voltage  (Adjust to match panel voltage)
#define INJ_NEUTRAL 424
#define INJ_HP_MIN  11130   //   Minimum Battery Voltage Setpoint at injection=1024
#define INJ_HP_MAX  15600   //   Maximum Battery Voltage Setpoint at injection=0 
#define INJ_LP_MIN  11240   //   Minimum Battery Voltage Setpoint at injection=1024
#define INJ_LP_MAX  15600   //   Maximum Battery Voltage Setpoint at injection=0 
#define INJ_AUX_MIN  2780   //   Minimum Auxiliary Voltage Setpoint at injection=1024
#define INJ_AUX_MAX  8560   //   Maximum Auxiliary Voltage Setpoint at injection=0 

#define BATT_CAPACITY 120 // Ah

//  ***Communicatin options*** (For geeks only, else leave as it is)
//#define INFLUX             //(Comment out, if no Influx is used) 
//#define THINGER            //(Comment out, if no thinger.io used)
//#define WRITE_BUCKETS      //(Comment out, if this is the second device for Thinger)
//#define PUBLISH_REPORT     // Issue events&midnight reports to UDP Port + 1, comment out else
#define REPORT_TARGET "192.168.188.00"  // IP to forward Report
//#define UDP_MASTER         // If this is the  master of a slave ESP
#define UDP_SLAVE             // If this is the  master of a slave ESP
#define DATA_TARGET   "192.168.188.00"  // IP to forward data
#define UDP_PORT   4214      // Ports to forward/receive data
#define Console0 Serial      // Port for user inputs  
#define Console1 Serial      // Port for user output
#define Console2 Serial1     // Port for midnight report e.g. on thermal printer
#define Console3 Serial      // Port for periodic messages
#define Console4 Serial      // Port for boot messages
#define SERIAL_SPEED            9600 //9600  115200 230400
//#define _DEBUG_            // to get deep diagnosis information over the serial line.

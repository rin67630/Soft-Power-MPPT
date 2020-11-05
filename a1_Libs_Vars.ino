// *** libraries***
#include <Wire.h>          // Libs for I2C
#include <INA.h>           // Zanshin INA Library
#include <ArduinoJson.h>   // Libs for Webscraping
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <ESP8266WiFi.h>   // default from Espressif
#include <ESP8266HTTPClient.h>
#include <TZ.h>            // default from Espressif
#include <FS.h>
#if defined(THINGER)
#include <ThingerESP8266.h>
//#include <ThingerConsole.h>
#endif
#include <EEPROM.h>

// ESP8266 Lolin / D1 /Witty (see definitions for other boards in Parked code)
#define SCL 5           // D1 GPIO05 for I2C (Wire) System Clock
#define SDA 4           // D2 GPIO04 for I2C (Wire) System Data
#define RST 0           // GPIO0

#define RELAY1     D3   // GPIO12
#define RELAY2     D4   // GPIO02
#define DC_OUT1   D6   // GPIO12
#define DC_OUT2   D7   // GPIO13
#define CC_CONTR   D0   // GPIO14 PWM output to control MPPT
#define CV_CONTR   D5   // GPIO14 PWM output to control MPPT (Option)

// Test outputs, not used operatively
#define STDLED     D4   // GPIO02 (& Console2 TX)
#define REDLED     D8   // GPIO15
#define GRNLED     D6   // GPIO12
#define BLULED     D7   // GPIO13

// Concatenate URLs
#define OPEN_WEATHER_MAP_URL  "http://api.openweathermap.org/data/2.5/weather?id=" OPEN_WEATHER_MAP_LOCATION_ID "&appid=" OPEN_WEATHER_MAP_APP_ID "&units=" OPEN_WEATHER_MAP_UNITS "&lang="  OPEN_WEATHER_MAP_LANGUAGE
//#define OPEN_WEATHER_MAP_URL   "http://api.openweathermap.org/data/2.5/weather?id=2928810&appid=208085abb5a3859d1e32341d6e1f9079&lang=de&units=metric"
#define DFLD_URL "http://api.dfld.de/noise/dfld.de/" DFLD_REGION "/" DFLD_STATION 
//#define DFLD_URL "http://api.dfld.de/noise/dfld.de/004/020"

//***Variables for Time***
tm*        timeinfo;                 //localtime returns a pointer to a tm struct static int Second;
time_t     Epoch;
time_t     now;
byte Second;
long SecondOfDay;
byte GracePause;
long MillisMem;
byte Minute;
byte Hour;
byte Day;
byte Month;
unsigned int Year;
byte Weekday;
char DayName[12];
char MonthName[12];
char Time[10];
char Date[12];
byte slice;
boolean Each6S;
boolean NewMinute;
boolean MinuteExpiring;
boolean NewHour;
boolean HourExpiring;
boolean NewDay;
boolean DayExpiring;

// ***Variables for Menu***
byte    inbyte;
byte    displayPage;
byte    displaySubPage;
byte    serialPage;
byte    serialPageMem;
byte    wirelessPage;
boolean serialDay;
boolean serialHur;
boolean serialMin;
boolean serialSec;
boolean SerialEvent;
boolean triglEvent;

static IPAddress ip;
static IPAddress remip;

//***Payload Variables***
// INA226
byte devicesFound =      0; ///< Number of INAs found
float ina1_current;
float ina1_voltage;
float ina1_shunt;
float ina1_power;
float current1 ;
float voltage1 ;
float ina2_current;
float ina2_voltage;
float ina2_shunt;
float ina2_power;
float current2 ;
float voltage2 ;
float delta_current;
float delta_voltage;
float percent_charged = 50;
float voltageAt0H ;
float voltageDelta ;
float currentInt = 0;
int   nCurrent;
float AhBat[31];
int CC_value;
int corrCC;
int CV_value;
boolean Relay1_value;
boolean Relay2_value;
boolean DC_Out1_value;
boolean DC_Out2_value;

struct battery {
float current ;
float voltage ;
float power = 0;
float ohm   = 0;
float panel ;
} battery;
char batteryPayload[sizeof(battery)];  //  Array of characters as image of the structure for UDP xmit/rcv

//Weather
float outdoor_temperature;
float outdoor_humidity;
float outdoor_pressure;
float wind_speed;
int   wind_direction;
int   cloudiness;
String weather_summary;
long  sunrise;
long  sunset;

//Sound level from URL
String  JSONpayload;
byte    wifiConnectCounter;

//*** Buffers ***
static char charbuff[80];    //Char buffer for many functions

int A0Raw;
boolean trigEvent;
String eventTime;

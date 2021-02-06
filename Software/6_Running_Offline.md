#Off-line operation
Soft-Power works nominally interconnected with a powerful cloud dashboard at Thinger.io.  
In situations, where new network is available, a fallback operating mode without network is possible.

In that case it is strongly recommended to monitor the boot process with a serial terminal set at 9600 Baud.
You can use the built in serial monitor of the Arduino IDE or use any terminal program e.g. Simple USB Terminal on your Android phone.

This is an example of the boot protocol with an unsuccessful connection
'''
ESP-Karajan at work,Serial @ 9600 Baud
Trying to connect

mode : sta(d8:f1:5b:11:0e:ac)
add if0

.RSSI: 31 dBm
.RSSI: 31 dBm
.RSSI: 31 dBm
.RSSI: 31 dBm
.RSSI: 31 dBm
scandone
state: 0 -> 2 (b0)
.RSSI: 31 dBm
state: 2 -> 3 (0)
state: 3 -> 5 (10)
add 0
aid 1
cnt 
.RSSI: -51 dBm
.RSSI: -50 dBm
.RSSI: -52 dBm
.RSSI: -53 dBm
.RSSI: -52 dBm
.RSSI: -52 dBm
state: 5 -> 2 (2a0)
rm 0
.RSSI: 31 dBm
.RSSI: 31 dBm
reconnect
state: 2 -> 0 (0)
scandone
state: 0 -> 2 (b0)
state: 2 -> 3 (0)
state: 3 -> 5 (10)
add 0
aid 1
cnt 
.RSSI: -50 dBm
.RSSI: -50 dBm
.RSSI: -50 dBm
.RSSI: -51 dBm
.RSSI: -51 dBm
.

Bad SSID or PASS?
state: 5 -> 0 (0)
rm 0
del if0
usl
mode : null
force slp enable,type: 2
fpm open,type:2 0

Running offline, back in the 70's
Now is Thursday, 01 January 1970 08:00:18. Epoch =     28818

Please enter date & time (dd/mm/yyyy hh:mm:ss) in the serial monitor, followed by [return]
'''
At that stage you are required to enter the date and time over the serial monitor, Soft-Power with answer with:
'''
I have understood 6/2/2021 22:53:0
Epoch = 1612648380
Welcome back in the present!, Menu ready to listen
'''
From now on your system is operative.
You will then be able to answer your first menu command:
Type "T" [return]
The system replies with:
Sat Feb  6 22:54:01 2021 

## Menu system

The Software provides a simple “single character” command-line menu over the USB serial line.  
Commands are given by a single character and executed over [return].  
Commands are stackable: you can give several characters then [return]; all commands will be executed in sequence.  
Example: U+++ 	means: Apply Defaults and Increase Injection by 3 steps.

Usually an upper case letter sets the function and the lower case reset the function.

### Control actions
- 'Z':  //Reset the ESP device
- 'U':  //Apply Injection Defaults (Unchanged)
- '+':  //Increase Injection by 1step   /     '-':   //Reduce Offset by 1Step
- '?':  //List parameters
- '~':  //List WLAN / Radio settings.

### Control Display
control the information displayed on the OLED screen.
- '0': //Display mode 0  ...  '3': //Display mode 3

### Periodical reports over the USB serial line

- 'P': //Periodical Reports on 		'p': //Periodical Reports off
#### Options for periodical reports:
- 'D':  //Day Report  		'd':  //no Day Report
- 'H':  //Hour Report		  'h':  //no Hour Report
- 'M': //Minute Report*		'm':  //no Minute Report     (Battery)
- 'S':  //Second Report*	's':  //no Second Report     
- 'E':  //Event Report		'e':  //no Event Report
* these reports are designed to produce Arduino serial Plotter compatible results.

- Example1 : PDHmsE 	means: Print Daily, Hourly, no minute, no second, Events 
- Example 2: p 		means: stop printing reports.
- Example 3: P 		means: resume printing reports with last options
- Example 4: Sd		means: now with Second reports without Daily reports.

One shot reports
n.b. these reports stop periodical reports, resume with “P” to return to periodical printing.

'B':  // Battery Report by 24h * 
'b':  // Battery Report (Actual measurements) *
‘W’: // Weather report
 
## Report examples

### Minute Hour Day and Events
#### Menu command MHEP:
08:55:59.490 -> Bat_Volt-10:1.928 Bat_Watt:-0.593 Bat_Level:7.200   
08:56:59.461 -> Bat_Volt-10:1.927 Bat_Watt:-0.593 Bat_Level:7.200   
08:57:59.462 -> Bat_Volt-10:1.926 Bat_Watt:-0.593 Bat_Level:7.200   
08:58:59.502 -> Bat_Volt-10:1.925 Bat_Watt:-0.593 Bat_Level:7.200   
08:59:59.489 -> BatAhBat:0.000  WindSpeed:0 Direction:107  
08:59:59.536 -> Bat_Volt-10:1.924 Bat_Watt:-0.593 Bat_Level:7.200   
09:00:59.478 -> Bat_Volt-10:1.923 Bat_Watt:-0.593 Bat_Level:7.200   
09:01:59.466 -> Bat_Volt-10:1.922 Bat_Watt:-0.593 Bat_Level:7.200  

#### Menu command B:*
'''
Battery History :
 Hour   |   00   |   01   |   02   |   03   |   04   |   05   |   06   |   07   |   08   |   09   |   10   |   11   |
 Bat Ah | -0.045 | -0.047 | -0.048 | -0.048 | -0.048 | -0.048 | -0.048 | -0.049 | -0.049 | +0.000 | +0.000 | +0.000 |
 Hour   |   12   |   13   |   14   |   15   |   16   |   17   |   18   |   19   |   20   |   21   |   22   |   23   |
 Bat Ah | +0.000 | +0.000 | +0.000 | +0.000 | +0.000 | +0.000 | +0.000 | +0.000 | -0.044 | -0.044 | -0.044 | -0.044 |

* with battery management, see Chapter x
'''

## Ongoing reporting:
You can enable ongoing event + midnight summary reporting:

PKTime: (Peak Time of the event)
Leq4:   (Level equivalent for the time defined by max-10dB to  max-10dB on the other side)
t10:       (time defined by max-10dB to  max-10dB on the other side)
Leq3::   (Level equivalent for the time above threshold)
t AT:      (Time above threshold)

NAT|PKTime  |PKdB|Leq4|t10|Leq3|tAT|
…
 15|21:52:29|74.7|70.5|026|70.1|057|
 01|22:01:33|74.6|71.2|017|70.3|043|
 02|22:03:44|71.2|67.3|019|66.7|045|
 03|22:13:46|72.3|69.2|026|68.9|055|
 04|22:16:25|71.8|69.3|021|68.8|048|
 05|22:28:19|69.3|66.7|024|66.7|048|
 
Daily Report for Tuesday, 15 September 2020 
Hour|  Ah    |
00  | -0.427 |
01  | -0.391 |
02  | -0.385 |
03  | -0.399 |
04  | -0.388 |
05  | -0.379 |
06  | -0.379 |
07  | -0.025 |
08  | -0.290 |
09  | -0.219 |
10  | +0.116 |
11  | +1.050 |
12  | +1.594 |
13  | +1.824 |
14  | +1.392 |
15  | +1.080 |
16  | +1.091 |
17  | +1.023 |
18  | +0.290 |
19  | -0.142 |
20  | -0.494 |
21  | -0.461 |
22  | -0.430 |
23  | -0.407 |
Extra hours cf. Man.
25  | -0.407 |
26  | +4.651 |
27  | +4.651 |
28  | +0.000 |
29  | +0.000 |
'''

These reports will be standard wise routed over the Serial USB connection to the serial monitor of the Arduino IDE.  

They can also be configured to be issued   
- to Serial1 on pin D4 (GPIO2) and from there be forwarded to e.g. a thermal receipt printer or over an UART-USB converter to another USB-port of a host computer for reporting.  
- to a UDP network port and be dumped on the host computer in a log file.  

##Graphical reporting:
over the menu command "ESP" (nomen est omen)  you can issue a one second paced report that provides data in a format suitable for serial plotting.  
Over the Ardunio Serial Plotter you can get a graphical output of the battery evolution history:  

The plotter and reporting abilities of the Arduino IDE are however, limited and you can only have one output at a time.


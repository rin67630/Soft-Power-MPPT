# Operation on the serial line
The preferred operation -and by far the most powerful- runs in the cloud over Thinger.io.  
The precondition is however to have an Internet access. Without that I have provided a fallback operating mode over the serial line.   
The serial line is also the way to go upon problems with connecting to your dashboard.  
For that, you can connect the ESP over its USB port to a terminal program of your computer or of your smart phone.  

# Bootlog

## Successful
Upon starting the ESP you will get a boot log with diagnostic messages:  
```
0⸮~?⸮4⸮Ҷ⸮⸮OAqr⸮⸮

ESP-Karajan at work,Serial @ 9600 Baud
Trying to connect

state: 5 -> 0 (0)
rm 0
del if0
usl
mode : null
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
aid 5
cnt 

connected with [SSID], channel 1
dhcp client start...
ip:192.168.188.32,mask:255.255.255.0,gw:192.168.188.1
.RSSI: -53 dBm
OTA Ready
 MAC address: D8:F1:5B:11:0E:AC
Hostname: ESP-110EAC 
UDP ports: 4214, 4215
Now is Monday, 08 February 2021 21:42:32. Epoch =1612816952

pm open,type:2 0
```
_n.b.  
the gibberish first line is normal after a reboot._

Many lines are automatically generated, in between you however get interesting information:  
- RSSI: 31 dBm is generally the indication, that the connection on that frequency failed  
  RSSI: -53 dBm is a realistic radio level  
- ip:192.168.188.32 is a valuable information over the IP of your device.  
- Hostname: ESP-110EAC (not matching the hostname of your upload) means the Router has refused the host name, the reason for that is very probably,  
  that you already have another device with the same hostname in the network.  
- you only get the UDP ports listed if the operation was successful.  
- You only get the current date, if the ESP was able to reach the NTP server.  

## Unsuccessful
this is an example of an unsuccessful Wi-Fi connection attempt.  
```
ESP-Karajan at work,
Serial @ 9600 Baud
mode : sta(3c:61:05:d1:53:ce) + softAP(3e:61:05:d1:53:ce)
add if0

.....scandone
no wifihot found, reconnect after 1s
reconnect
.....SSID or PASS?
scandone
del if0
mode : softAP(3e:61:05:d1:53:ce)
running offline, back in the 70's
RSSI: 31 dBm
Now is 00:00:12. The Epoch is:         12
Date is Thursday, 01 January 1970
I need the date(dd/mm/yyyy) and time(hh:mm:ss)
```
In that case "no wifihot found" means, the SSID wifihot was not detected.  
Else it would list the router and attempt several connections, giving up after the third attempt, if your password does not match  
Another example with an existing SSID, but the wrong credentials:  
```
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
```
If the connection fails AND you never had an Internet connection and have no RTC shield, you will be requested to enter the current date and time, which is essential for proper operation of Soft-Power's statistic reports.  
You must then enter the date and time manually in order to proceed.  

The system answers with:  
```
I have understood 5/2/2021 18:48:0
Now is 18:48:00. The Epoch is: 1612464480
Date is Thursday, 05 January 2021
```
Now, your serial port is ready to receive commands.

In order to put the maximum of functionality into scarce memory of the microcontroller, there is no verbose menu.  
Instead you have a choice of single character commands, from which you can however enter several in one line, they will be executed in sequence.  

## One-shot reports

'S' Issues a status report, e.g.:  
```
Daily Report for 
Sunday, 07 February 2021 
Hour|   Ah   |    V   |    W   |
00  | +0.000 | +0.000 | +0.000 |
01  | +0.000 | +0.000 | +0.000 |
02  | +0.000 | +0.000 | +0.000 |
03  | +0.000 | +0.000 | +0.000 |
04  | +0.000 | +0.000 | +0.000 |
05  | +0.000 | +0.000 | +0.000 |
06  | +0.000 | +0.000 | +0.000 |
07  | +0.000 | +0.000 | +0.000 |
08  | +0.000 | +0.000 | +0.000 |
09  | +0.000 | +0.000 | +0.000 |
10  | +0.000 | +0.000 | +0.000 |
11  | +0.000 | +0.000 | +0.000 |
12  | +0.000 | +0.000 | +0.000 |
13  | +0.000 | +0.000 | +0.000 |
14  | +0.000 | +0.000 | +0.000 |
15  | +0.000 | +0.000 | +0.000 |
16  | +0.000 | +0.000 | +0.000 |
17  | +0.000 | +0.000 | +0.000 |
18  | +0.000 | +0.000 | +0.000 |
19  | +0.000 | +0.000 | +0.000 |
20  | +0.000 | +0.000 | +0.000 |
21  | +0.000 | +0.000 | +0.000 |
22  | +0.000 | +0.000 | +0.000 |
23  | +0.000 | +0.000 | +0.000 |
Extra hours 25:H-1, 26:today, 27:D-1, 28:D-2..
25  | +0.000 | +0.000 | +0.000 |
26  | +0.000 | +0.000 | +0.000 |
27  | +0.000 | +0.000 | +0.000 |
28  | +0.000 | +0.000 | +0.000 |
29  | +0.000 | +0.000 | +0.000 |
30  | +0.000 | +0.000 | +0.000 |
```
'T' Returns the time
```
Mon Feb  8 22:09:11 2021
```
'~' returns a radio report
```
WiFi Plot :
Mode: STA
PHY mode: N
Channel: 1
AP id: 0
Status: 5
Auto connect: 1
SSID (10): [SSID]
Passphrase (8): [Password]
BSSID set: 0
```
's~' issues the same report, but followed with a signal strength line every second, so you can follow where you get the best (less negative) signal:  
```
RSSI:-88 dBm
RSSI:-88 dBm
RSSI:-88 dBm
RSSI:-88 dBm
```
In the example above, we already have used 's' an extender mentioning that you want to get a periodical report.  

## Periodical reports
Periodical reports can be printed every second, every minute, every hour, and even every day.  
They can also be used in the serial plotter from the Arduino IDE to generate time series graphs.  

### Setting the pace for periodical reports
The pace is given with a low case extender:  
's', 'm', 'h', 'd' staying for every second, minutely, hourly, daily.  
Once the pace for periodical reports is given, it stays valid for every report called after, until another pace is choosen or a '#' stop command is entered.  

### Periodical reports
currently the following periodical reports are available (more to come)
- 'E' Energy plot  
```
Ah:+00.000 Panel:-9.640 V-10:02.552 Amp:-0.029 Watt:-00.358
Ah:+00.000 Panel:-9.640 V-10:02.552 Amp:-0.029 Watt:-00.358
Ah:+00.000 Panel:-9.640 V-10:02.552 Amp:-0.029 Watt:-00.358
Ah:+00.000 Panel:-9.640 V-10:02.552 Amp:-0.029 Watt:-00.358
```
The same plot called from Arduino's IDE serial plotter:  
![image](https://user-images.githubusercontent.com/14197155/107235100-9ff60700-6a24-11eb-9ed8-552b373d9c1a.png) 
_n.b.  
The serial plotter of the Arduino IDE has only one Y-Axis range. In order to optimize the presentation, panel and battery voltages are issued -10 V: 3V means 13V..._


- 'W' Weather plot
```
Temp:-07.2 Hum:73.0 Press:1002 WindSpeed:5.7 Direction:50
Temp:-07.2 Hum:73.0 Press:1002 WindSpeed:5.7 Direction:50
Temp:-07.2 Hum:73.0 Press:1002 WindSpeed:5.7 Direction:50
Temp:-07.2 Hum:73.0 Press:1002 WindSpeed:5.7 Direction:50
```
### Control commands
From the serial menu, you can control several operations of Soft-Power.  
- '+' or '-' increases or decreases in small steps the setpoint of the battery voltage
- '>' or '<' increases or decreases in coarse steps the setpoint of the battery voltage
- A0 stops the auxiliary output
- A3.3 starts the auxiliary output at 3.3V (or any of the voltage specified up to 9.0V)
- R10 or R11 or R20 or R21 respectively stops or start relay 1 or relay 2.

### Display control commands
You will be able to control which information is displayed on the OLED Display:  
- '0' switch of the display
- '1' current energy display
- '2' Ah display ( current and the last two hours ) (to come soon)
- '3' Ah display ( scanning the last day ) (to come soon)
- '4' and '5' (to come soon)


t.b.continued.
  


#Off-line operation
Soft-Power works nominally interconnected with a powerful cloud dashboard at Thinger.io.  
In situations, where new network is available, a fallback operating mode without network is possible.

In that case it is strongly recommended to monitor the boot process with a serial terminal set at 9600 Baud.
You can use the built in serial monitor of the Arduino IDE or use any terminal program e.g. Simple USB Terminal on your Android phone.

This is an example of the boot protocol with an unsuccessful connection
´´´´
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
´´´
At that stage you are required to enter the date and time over the serial monitor, Soft-Power with answer with:
´´´
I have understood 6/2/2021 22:53:0
Epoch = 1612648380
Welcome back in the present!, Menu ready to listen
´´´
From now on your system is operative.
You will then be able to answer your first menu command:
Type "T" [return]
The system replies with:
Sat Feb  6 22:54:01 2021 


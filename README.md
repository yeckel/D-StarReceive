# D-StarReceive
Simple D-Star reception for TTGO T-Beam ESP32 SX1278 written with Platformio

* <del> Current version receives a short D-Star transmission and dumps it in hex format into terminal.
* It uses sx127x FSK Continuous Mode, PreambleDetect and SyncAddress on DIO0, Dclk(DIO1) and Data(DIO2)
* D-Star ending frame is caught by local configurable shift register
* Decodes D-Star RF Header, 20 characters message and a text payload

Cool D-Star info sources:
[kb9mwr](https://www.qsl.net/kb9mwr/projects/dv/dstar/)
[Slow data](https://www.qsl.net/kb9mwr/projects/dv/dstar/Slow%20Data.pdf)


Example output:
```
Nb errors:1
Checking crc: 1

RF Header:0x0 0x0 0x0 DIRECT  DIRECT  CQCQCQ  OK1CHP  705 0x89 $0x0 
TTATATATATATATAAAAAAAAAAAUC
GPSData size: 84 val:D-STAR newbe        PI705,DSTAR*:!4946.70N/01329.43E-/A=001182Playing with ic-705
Headersize: 0 val:
MSGsize: 20 val:D-STAR newbe        


Nb errors:1
Checking crc: 1

RF Header:0x0 0x0 0x0 DIRECT  DIRECT  CQCQCQ  OK1CHP  705 0x89 $0x0 
TATATATAAAAAAAAAAAAAAHC
GPSData size: 84 val:$$CRCD8C8,OK1CHP-1>API705,DSTAR*:!4946.70N/01329.43E-/A=001183Playing with ic-705
Headersize: 5 val:DI
MSGsize: 20 val:D-STAR newbe
```

# TODO
* <del> Decode D-Star header
* <del> Decode GPS coord?
* Send same data to serial and BT as IC-705 does (images, text messages)
* Use SX1278 AFC (automatic frequency correction) to correct XTAL offset and thermal drifft
* ?DV Fast data?

## Notes
* D-Star SMS message is transmitted in format: ```$$Msg,OK1CHP,OK1LOL,001172ahoj 0xA2, 0xD, 0x0``` no clue what that 001172 means
* D-Star Image block is transmitted as ```$$Pic,OK1CHP,OK1LOL,0111 0xEF, 0x80, 0x9, 0x7,_Z 0xEF, 0x8D,aQ@ 0x1F, 0xEF,g 0xD``` 
All those ICOM extensions are sent as a message type 0x30 and are thus dumped directly into serial port

The official ICOM app RS-MS1A for Android could be used to communicate via Bluetooth (model Others) It's then receiving and sending the data from serial or bluetooth port. ```$$Msg,OK1CHP,OK1LOL,001172ahoj  0xC2, 0xD, 0x0,``` 

Picture 160x120 (19200px) is sent with 10x8 (80) blocks with 25% quality -> 240px/block, one block has 18bytes but 4 of them (0xEF, 0x80, 0x9, 0x7) represents the format. (??,??,column,row)
  * 0111 0xEF, 0x80, 0x09, 0x7  ---25%, 160x120
  * 0212 0x01, 0x09, 0x07 --- 50%, 160x120
  * 0313 0x02, 0x09, 0x07,--- 75%, 160x120
  * 0414 0x12, 0x27, 0x1D,--- 25%, 640x480 

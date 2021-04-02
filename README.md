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

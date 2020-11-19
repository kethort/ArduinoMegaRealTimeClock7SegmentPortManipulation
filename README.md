# port-manipulation-arduino-mega-rtc
Arduino Mega with Real Time Clock and 7 Segment Display using Port Manipulation

## Wiring
https://www.allaboutcircuits.com/projects/interface-a-seven-segment-display-to-an-arduino/

https://howtomechatronics.com/tutorials/arduino/arduino-ds3231-real-time-clock-tutorial/

### INFO
This example uses a 4 panel 7 segment LCD from manufacturer MakerHawk.

The display pins are common cathode for digit selector pins 1-4. 
The display decimal point shares the common cathode of each digit. 
There are individual anode pins for segments A-G and the decimal point.

The sketch uses PORTK for the LCD LED segments (A - G) and
PORTF for switching between the panels.

### DS3231 Library
http://www.rinkydinkelectronics.com/library.php?id=73

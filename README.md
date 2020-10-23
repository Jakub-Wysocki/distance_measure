# distance_measure
## About
Simple program that measures distance using HC-SR04 ultrasonic sensor after clicking button on 4x4 keyboard. This project uses Arduino Uno witch ATmega328P microprocessor and it is written in clear C.

## Pinout

The project is using small 420 slots breadboard.

### Sensor singal HC-SR04 connection:
Vcc - Arduino 5V via breadboard
Gnd - Arduino GND via breadboard
Echo - D8 (PB0) (ICP1)
Trigger - D9 (PB1)

### Arduino Uno R3:
PD0 - LCD D4
PD1 - LCD D5
PD2 - LCD D6
PD3 - LCD D7
PD4 - LCD E
PD5 - LCD RS via breadbord

PB0 - Sensor Echo pin. Input Capture Module Pin
PB1  - Sensor Trigger 

### LCD display 16x2:

VSS - Arduino 5V via breadboard
VDD - Arduino GND via breadboard
V0 - 10kOhms potentiometer
RS - PD5 via breadbord
RW - Arduino GND via breadboard
E - PD4 via breadbord
D0 - D3 unused
D4 - Arduino PD0
D5 - Arduino PD1
D6 - Arduino PD2
D7 - Arduino PD3
Anode - Arduino 5V via breadboard
Katode - Arduino GND via 220Ohms resistor via breadboard


## Known Bugs
Value of the some measurement is incorrect. The incorrect measurement is in the region of -350cm. 
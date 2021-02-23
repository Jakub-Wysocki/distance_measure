# distance_measure
## About
Simple program that measures distance using HC-SR04 ultrasonic sensor. This project uses Arduino Uno witch ATmega328P microprocessor and it is written in clear C.

## Pinout

The project is using small 420 slots breadboard.

### Sensor singal HC-SR04 connection:
Vcc - Arduino 5V via breadboard <br />
Gnd - Arduino GND via breadboard <br />
Echo - D8 (PB0) (ICP1) <br />
Trigger - D9 (PB1) <br />

### Arduino Uno R3:
PD0 - LCD D4 <br />
PD1 - LCD D5 <br />
PD2 - LCD D6 <br />
PD3 - LCD D7 <br />
PD4 - LCD E <br />
PD5 - LCD RS via breadbord <br />

PB0 - Sensor Echo pin. Input Capture Module Pin <br />
PB1  - Sensor Trigger <br />

### LCD display 16x2:

VSS - Arduino GND via breadboard <br />
VDD - Arduino 5V via breadboard <br />
V0 - 10kOhms potentiometer <br />
RS - PD5 via breadbord <br />
RW - Arduino GND via breadboard <br />
E - PD4 via breadbord <br />
D0 - D3 unused <br />
D4 - Arduino PD0 <br />
D5 - Arduino PD1 <br />
D6 - Arduino PD2 <br />
D7 - Arduino PD3 <br />
Anode - Arduino 5V via breadboard <br />
Katode - Arduino GND via 220Ohms resistor via breadboard <br />


## Known Bugs
Value of the some measurement is incorrect. The incorrect measurement is in the region of -350cm. 

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "dist_measure.h"
#include "lcd.h"

volatile float t_start = 0.0, t_stop = 0.0, temp = 0.0;
int temp_int = 0;

int main(void)
{
  DDRB &= 0b11111110;//echo - recive signal, PB0
  DDRB |= 0b00100010; //trigger send signal, PB1
  Serial.begin(9600);
  Init(); //initialize LCD
  char tekst[] = "Odleglosc: ";
  
  setTimer1();
  
  while(true) //dlaczego wstawienie tu funckji delay() powoduje zapętlenie całego main?
  {
    genImpulse();
    _delay_ms(50);
    sendText(tekst);
    temp_int = (int)temp;
    sendChar((unsigned char)temp_int);
    Serial.println(temp);
    _delay_ms(300);
    Init();
    _delay_ms(10);
  }
  
}
ISR(TIMER1_CAPT_vect) //input capture interrupt
{
  
  if((TCCR1B & 0b01000000) == 0b01000000) //if rising edge is set
  {
    t_start = ICR1; //save time
    TCCR1B &= 0b10111111; //change edge to falling
    TIFR1 |= 0b00100000;//clear Input Capture Flag
  }
  else if ((TCCR1B & 0b01000000) != 0b01000000) //faling edge
  {
    t_stop = ICR1;
    TCCR1B |= (1 << ICES1);
    temp = ((t_stop - t_start)*0.5)/58;
    TIFR1 |= 0b00100000; //clear Input Capture Flag
  }
  
}
ISR(TIMER1_COMPA_vect) //interrupt when distance is too large. 
{
  sendChar('<');
  sendChar('2');
  sendChar('0');
  sendChar('0');
}

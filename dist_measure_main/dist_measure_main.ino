#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "dist_measure.h"
#include "lcd.h"

volatile float t_start = 0.0, t_stop = 0.0, distance = 0.0;

int main(void)
{
  DDRB &= 0b11111110;//echo - recive signal, PB0
  DDRB |= 0b00100010; //trigger send signal, PB1
  Init(); //initialize LCD
  setTimer1();
  
  while(1)
  {
    genImpulse();
    _delay_ms(50);
    display_lcd((int)distance);
    _delay_ms(1000);
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
    distance = ((t_stop - t_start)*0.5)/58;
    TIFR1 |= 0b00100000; //clear Input Capture Flag
  }
  
}
ISR(TIMER1_COMPA_vect) //interrupt when distance is too large. 
{
 //nothing
}

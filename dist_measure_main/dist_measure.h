#ifndef DIST_MEASURE_H
#define DIST_MEASURE_H

void setTimer1() //initalize the timer1 in CTC mode. Set global interruption flag, init 
{
  sei(); //enable interrupts
  TCCR1A = 0; //clear registers
  TCCR1B = 0;
  TCNT1 = 0;
  ICR1 = 0;

  TIFR1 &= 0b11011111; //clear Input Capture Flag
  OCR1A = 62500; //1 cycle is 0.5us. OCR1A is max value in CTC (Mode 4) 
  TCCR1B |= (1 << WGM12); //Set CTC mode 4
  TCCR1B |= (1 << CS11);  // Set prescaler to 8 
  TCCR1B |= (1 << ICES1) | (1 << ICNC1);  // Set Input Capture Mode on rising edge and the Noise Canceler
  TIMSK1 |= (1 << OCIE1A) | (1 << ICIE1); // Output Compare Match A Interrupt Enable, and Input capture interrupt

}
void genImpulse() //function generates 15us impulse to start the measurement. The impulse is porceded by 10us low state, to avoid errors
{
  DDRB |= 0b00000010; //set PB0 to output
  short ctr = TCNT1;
  
  PORTB &= 0b11111101; //set output to 0
  while((TCNT1-ctr) <= 20) //Wait 10us
  
  PORTB |= 0b00000010;//set pin 10 to high
  while((TCNT1-ctr-20) <= 30) //wait 15us
  
  PORTB &= 0b11111101; //set output to 0

}

#endif
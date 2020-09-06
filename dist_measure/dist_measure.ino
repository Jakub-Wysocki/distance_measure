#include <util/delay.h>

unsigned short t_start = 0, t_stop = 0, temp = 0;

void SetupTimer1() {
  noInterrupts();
  
  //Clear registers
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  OCR1A = 46400; //Count up to 46400. 1 cycle is 0.5uS. Should I add additional clock cycles? Noice canceler is turned off. 
  TCCR1B |= (1 << WGM12); // Set CTC mode
  TCCR1B |= (1 << CS11);  // Set prescaler to 8
  TCCR1B |= (1 << ICES1);  // Set Input Capture Mode on rising edge
  TIMSK1 |= (1 << OCIE1A) | (1 << ICIE1); // Output Compare Match A Interrupt Enable, and Input capture interrupt
  interrupts();
}
void GenerateImpulse()
{ 
  TCNT1 = 0; //Reset cou  nter. 
  
  PORTB |= 0b00000010; //Start signal

  while( TCNT1 <= 20); //Wait until impulse is generated. 20 cycles are equal to 10uS.
      
  PORTB &= 0b11111101; //Finish signal

}
ISR(TIMER1_CAPT_vect) //input capture 
{
  if(1) //if rising edge is set
  {
    t_start = ICR1;

    //set to falling edge
    
  }
  else
  {
     t_stop = ICR1;
     //set to rising edge

     Serial.print(((t_stop - t_start)*0.5)/0.58);
    
  }
    
  
    //Serial.print("Hello!");
}
int main(void)
{
  DDRB |= 0b00000010;
  Serial.begin(9600);
  SetupTimer1();  

  while(1)
  {
    GenerateImpulse();
    
  }

  return 0;
}

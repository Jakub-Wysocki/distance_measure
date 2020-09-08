#include <util/delay.h>

unsigned short t_start = 0, t_stop = 0;
float temp = 0;

void SetupTimer1() {
  noInterrupts();
  
  //Clear registers
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  ICR1 = 0;

  OCR1A = 62500; //1 cycle is 0.5uS. Should I add additional clock cycles?  
  TCCR1B |= (1 << WGM12); // Set CTC mode
  TCCR1B |= (1 << CS11);  // Set prescaler to 8 
  TCCR1B |= (1 << ICES1) | (1 << ICNC1);  // Set Input Capture Mode on rising edge and the Noise Canceler
  TIMSK1 |= (1 << OCIE1A) | (1 << ICIE1); // Output Compare Match A Interrupt Enable, and Input capture interrupt
  interrupts();
}
void GenerateImpulse()
{ 
  TCNT1 = 0; //Reset counter. 

  PORTB &= 0b11111101; //Set output to LOW
  while(TCNT1 <= 10); //Wait 3uS. Noice canceler delay 4 clocks. It is 2uS. 
  
  PORTB |= 0b00000010; //Start signal

  while(TCNT1 <= 34); //Wait until impulse is generated. 20 cycles are equal to 10uS.
      
  PORTB &= 0b11111101; //Finish signal

}
ISR(TIMER1_CAPT_vect) //input capture interrupt.
{

  if((TCCR1B &= 0b01000000)  == 0b01000000) //if rising edge is set
  {
    t_start = ICR1;
    Serial.println(t_start);
    TCCR1B &= 0b10111111; //set to falling edge
    
  }
  else //if falling edge is set
  {
     t_stop = ICR1;
     TCCR1B |= (1 << ICES1); //set to rising edge
     Serial.println(t_stop);
     temp = (((float)t_stop - (float)t_start)*0.5)/58.0;
  }
  
}
ISR(TIMER1_OVF_vect) //interrupt when ditance is too large. 
{
  Serial.println("Too large!\n");
  Serial.println(temp);
  temp = 999;
}
int main(void)
{
  DDRB |= 0b00000010; //Set pin to output
  Serial.begin(9600);
  SetupTimer1();  

  GenerateImpulse();
  _delay_ms(100);
  Serial.println(temp);

  while(1)
  {
    //delay somehow
  }


}

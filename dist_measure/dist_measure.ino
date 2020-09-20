#include <util/delay.h>

float t_start = 0, t_stop = 0, temp = 0;

void SetupTimer1() {
  sei();
  //Clear registers
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  ICR1 = 0;

  OCR1A = 62500; //1 cycle is 0.5us. OCR1A is max value in CTC (Mode 4)  
  TCCR1B |= (1 << WGM12); // Set CTC mode 4
  TCCR1B |= (1 << CS11);  // Set prescaler to 8 
  TCCR1B |= (1 << ICES1) | (1 << ICNC1);  // Set Input Capture Mode on rising edge and the Noise Canceler
  TIMSK1 |= (1 << OCIE1A) | (1 << ICIE1); // Output Compare Match A Interrupt Enable, and Input capture interrupt
  
}
void GenerateImpulse()
{ 
  TCNT1 = 0; //Reset counter. 
  
  PORTB &= 0b11111011; //Set output to LOW
  while(TCNT1<= 20); //Wait 3uS. Noice canceler delay 4 clocks
  
  PORTB |= 0b00000100; //Start signal

  while(TCNT1 <= 100); //Wait until impulse is generated. 20 cycles are equal to 10uS.
      
  PORTB &= 0b11111011; //Finish signal

  Serial.println(TCNT1); //Aprox. 36 clocks
  

}
ISR(TIMER1_CAPT_vect) //input capture interrupt.
{

  if((TCCR1B &= 0b01000000)  == 0b01000000) //if rising edge is set
  {
    t_start = ICR1; //is reading ok?
    Serial.println("Naroslo");
    TCCR1B &= 0b10111111; //set to falling edge
    
    
  }
  else//if falling edge is set
  {
     t_stop = ICR1;
     TCCR1B |= (1 << ICES1); //set to rising edge
     Serial.println("Opadlo");
     temp = ((t_stop - t_start)*0.5)/58.0;
     Serial.println(temp);
  }
  
}
ISR(TIMER1_OVF_vect) //interrupt when ditance is too large. 
{
  Serial.println("Too large!\n");
  temp = 999;
  Serial.println(temp);
}
int main(void)
{
  DDRB |= 0b00000100; //Set pin 10 to output
  DDRB &= 0b11111110; //set pin 8 to input
  Serial.begin(9600);
  SetupTimer1();
  GenerateImpulse();

   while(1)
  {
    Serial.println(t_start);
    _delay_ms(100);
  }

}

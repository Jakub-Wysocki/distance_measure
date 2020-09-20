float t_start = 0.0, t_stop = 0.0, temp = 0.0;

void setTimer1();
void genImpulse();
int main(void)
{
  DDRB &= 0b11111110;//echo - recive signal, PB0
  DDRD |= 0b00100000; //trigger send signal, PD5
  Serial.begin(9600);
  setTimer1();

  Serial.println("9");

  while(true) //dlaczego wstawienie tu funckji delay() powoduje zapętlenie całego main?
  {
    genImpulse();
    Serial.println("1");
  }
  
}
ISR(TIMER1_CAPT_vect) //input capture interrupt
{

  
  if((TCCR1B &= 0b01000000) == 0b01000000) //if rising edge is set
  {
    Serial.println(TCNT1);
    t_start = ICR1; //save time
    TCCR1B &= 0b10111111; //change edge to falling
    TIFR1 &= 0b11011111;
  }
  else //faling edge
  {
    Serial.println(TCNT1);
    t_stop = ICR1;
    TCCR1B |= (1 << ICES1);
    temp = ((t_stop - t_start)*0.5)/58;
    Serial.println(temp);
    TIFR1 &= 0b11011111;
  }
  
}
void setTimer1()
{
  sei();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  ICR1 = 0;
  
  OCR1A = 62500; //1 cycle is 0.5us. OCR1A is max value in CTC (Mode 4) 
  TCCR1B |= (1 << WGM12); //Set CTC mode 4
  TCCR1B |= (1 << CS11);  // Set prescaler to 8 
  TCCR1B |= (1 << ICES1) | (1 << ICNC1);  // Set Input Capture Mode on rising edge and the Noise Canceler
  TIMSK1 |= (1 << OCIE1A) | (1 << ICIE1); // Output Compare Match A Interrupt Enable, and Input capture interrupt
  Serial.println("2");

}
void genImpulse()
{
  short ctr = TCNT1;
  
  PORTD &= 0b11011111; //set output to 0
  while((TCNT1-ctr) <= 20) //Wait 10us
  
  PORTB |= 0b00100000;//set pin 10 to high
  while((TCNT1-ctr-20) <= 30) //wait 15us
  
  PORTB &= 0b11011111; //set output to 0
  Serial.println("3");

}
ISR(TIMER1_OVF_vect) //interrupt when ditance is too large. 
{
  Serial.println("Too large!\n");
  temp = 999;
  Serial.println(temp);
}

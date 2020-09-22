#include <util/delay.h>

//RS PD2
//E PD3
//D4-D7 PD4-PD7

void sendInstruction(unsigned char data)
{
  DDRD |= 0b11111100; //leave PD0 and PD1 as it was, set other pins to output
  PORTD &= 0b11111011; //set RS to 0, because this is instruction
  PORTD |= 0b00001000; //set E to 1

  PORTD = ((PORTD & 0b11110000) |  (data >> 4));
  PORTD &= 0b11110111; //set E to 0
  _delay_us(300);
  PORTD |= 0b00001000; //set E to 1

  PORTD = ((PORTD & 0b11110000) |  (data & 0b00001111));
  PORTD &= 0b11110111; //set E to 0
  _delay_us(300);
  PORTD |= 0b00001000; //set E to 1

}
void sendChar(unsigned char data)
{
  DDRD |= 0b11111100;
  PORTD |= 0b00001100; //set E = 1 and RS = 1

  PORTD = ((PORTD & 0b11110000) |  (data >> 4));
  PORTD &= 0b11110111; //set E to 0
  _delay_us(300);
  PORTD |= 0b00001000; //set E to 1

  PORTD = ((PORTD & 0b11110000) |  (data & 0b00001111));
  PORTD &= 0b11110111; //set E to 0
  _delay_us(300);
  PORTD |= 0b00001000; //set E to 1

}
void sendText(char* str)
{
  for(int i = 0; *(str+i) != 0; i++)
    sendChar(*(str+i));

}
void Init()
{
  sendInstruction(0x33);
  sendInstruction(0x32);
  sendInstruction(0x28);
  sendInstruction(0x08);
  sendInstruction(0x01);
  sendInstruction(0x06);
  sendInstruction(0x0F);

}

#include <stdio.h>

void sendChar(unsigned char data)
{
  DDRD = 0b00111111;
  PORTD |= 0b00110000; //RS = 1 i E = 1
  PORTD = ((PORTD & 0b11110000) | ((data>>4) & 0b00001111)); 
  PORTD &= 0b11101111; //E = 0
  _delay_loop_2(5000);
  PORTD |= 0b00010000; //E = 1
  PORTD = ((PORTD & 0b11110000) | (data & 0b00001111)); 
  PORTD &= 0b11101111; //E = 0
  _delay_loop_2(5000);
  PORTD |= 0b00010000; //E = 1
}
void sendInstruction(unsigned char data)
{
  DDRD = 0b00111111;
  PORTD &= 0b11011111; //RS = 0
  PORTD |= 0b00010000; //E = 1
  PORTD = ((PORTD & 0b11110000) | ((data>>4) & 0b00001111)); 
  PORTD &= 0b11101111; //E = 0
  _delay_loop_2(25000);
  PORTD |= 0b00010000; //E = 1
  PORTD = ((PORTD & 0b11110000) | (data & 0b00001111)); 
  PORTD &= 0b11101111; //E = 0
  _delay_loop_2(25000);
  PORTD |= 0b00010000; //E = 1
}
void Init(void)
{
  sendInstruction(0x33);
  sendInstruction(0x32);
  sendInstruction(0x28);
  sendInstruction(0x08);
  sendInstruction(0x01);
  sendInstruction(0x06);
  sendInstruction(0x0F);
}
void sendText(char* str)
{
  for(int i = 0; *(str+i) != 0; i++)
    sendChar(*(str+i));
}
void display_lcd(int distance)
{ 
  sendInstruction(0x01);
  char tekst[] = "Odleglosc: ";
  sendText(tekst);
  char dist_char[4];
  sprintf(dist_char, "%d", distance);
  
  sendInstruction(0xC0); //Druga linia
  _delay_ms(20);
  sendText(dist_char);
  _delay_ms(20);

}

#ifndef LCD_H
#define LCD_H

#include <stdio.h>

void sendChar(unsigned char data) //function send data to the lcd
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
void sendInstruction(unsigned char data) //function takes instruction and loads it to lcd screen
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
void Init(void) //function takes no argument, initialize lcd 2x16 screen
{
  sendInstruction(0x33);
  sendInstruction(0x32);
  sendInstruction(0x28);
  sendInstruction(0x08);
  sendInstruction(0x01);
  sendInstruction(0x06);
  sendInstruction(0x0F);
}
void sendText(char* str) //function accepts string as an argument, and display it on the screen
{
  if(str == NULL)
    return;

  for(int i = 0; *(str+i) != 0; i++)
    sendChar(*(str+i));
}
void display_lcd(int distance) //function accepts distance as an argument, changes type to char and initlise display
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

#endif
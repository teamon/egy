#include "sumo.h"

// Inicjalizacja USATRu
void usart_init() {
  // Nadawanie i odbiór
  UCSRB = 0x18; 
  // asynchronicznie 8N1
  UCSRC = 0x86;  
  // konfiguracja prędkości
  UBRRH = 0;
  UBRRL = (F_CPU/(USART_SPEED*16))-1;  
}

// Wysłanie bajtu na RS
void usart_write_byte(unsigned char byte) {
  // sprawdzenie zezwolenia
  while (!(UCSRA & (1<<5)));
  // wysłanie
  UDR = byte;
}

// Wysłanie łańcucha znaków na RS
void usart_write_string(char *string) {
  while (*string != '\0')
  {
    usart_write_byte(*string);
    string++;
  }
}

// Wysłanie łańcucha znaków z pamięci programu
void usart_write_progmem_string(const char *string) {
  char sign;
  sign = pgm_read_byte(string);
  while (sign != '\0')
  {
    usart_write_byte(sign);
    string++;
    sign = pgm_read_byte(string);
  }
}


// Wysłanie liczby na RS
void usart_write_number(long number)
{
  unsigned char i,j,k;
  long a,b;
  a=1000000000;
  b=999999999;
  
  // wysłanie znaku '-'
  if (number < 0)
    usart_write_byte('-');
  
  for (i=0;i<10;i++)
  {
    j = (number / a) % 10;
    if ((number > b) || (i == 9)) 
    {
      // zamiana na znak
      switch(j)
      {
        case 0:
          k='0';
          break;  
        case 1:
          k='1';
          break;
        case 2:
          k='2';
          break;
        case 3:
          k='3';
          break; 
        case 4:
          k='4';
          break;  
        case 5:
          k='5';
          break;
        case 6:
          k='6';
          break;
        case 7:
          k='7';
          break; 
        case 8:
          k='8';
          break;  
        case 9:
          k='9';
          break;
        default:
          k='0';
      }
      usart_write_byte(k);
    }
    a /= 10;
    b /= 10;
  }
}

// Odbieranie bajtu z ES
// funkcja zwraca 0 jeśli nic nie przyszło
unsigned char usart_read_byte() {
  if (UCSRA & (1<<7))
    return UDR;
  else
    return 0;
}



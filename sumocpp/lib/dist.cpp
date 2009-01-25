#include "sumo.h"

// Numer aktualnie przetwarzanego portu
volatile unsigned char dist_p=1; 

// Wyniki przetwarzania na poszczególnych kanałach
volatile unsigned char dist1=0;   
volatile unsigned char dist2=0; 
volatile unsigned char dist3=0; 
volatile unsigned char dist4=0;  
volatile unsigned char dist5=0; 
volatile unsigned char dist6=0; 

// Funkcja inicjalizująca czujniki odległości
// UWAGA: zajmuje przetwornik AC
void dist_init()
{
  // Inicjalizacja portu
  DIST_DDR &= ~((1<<DIST1_PIN) | (1<<DIST2_PIN) | (1<<DIST3_PIN) | (1<<DIST4_PIN) | (1<<DIST5_PIN) | (1<<DIST6_PIN));
  DIST_POTR &= ~((1<<DIST1_PIN) | (1<<DIST2_PIN) | (1<<DIST3_PIN) | (1<<DIST4_PIN) | (1<<DIST5_PIN) | (1<<DIST6_PIN));
  
  // Konfiguracja przetwornika i przerwań
  ADMUX = 0x60; //01100000
  ADCSRA = 0xcd; //11001101
  
  // inicjalizacja numeru czujnika
  dist_p=1;
  sei();
}


unsigned char dist1_value() { return dist1; }
unsigned char dist2_value() { return dist2; }
unsigned char dist3_value() { return dist3; }
unsigned char dist4_value() { return dist4; }
unsigned char dist5_value() { return dist5; }
unsigned char dist6_value() { return dist6; }

// Procedura przerwania od przetwornika AC
SIGNAL (SIG_ADC)
{
  switch (dist_p)
  {
    case 1:
      dist1 = ADCH;
      ADMUX = 0x60 + DIST2_PIN;
      break;
    case 2:
      dist2 = ADCH;
      ADMUX = 0x60 + DIST3_PIN;
      break;
    case 3:
      dist3 = ADCH;
      ADMUX = 0x60 + DIST4_PIN;
      break;
    case 4:
      dist4 = ADCH;
      ADMUX = 0x60 + DIST5_PIN;
      break;
    case 5:
      dist5 = ADCH;
      ADMUX = 0x60 + DIST6_PIN;
      break;
    case 6:
      dist6 = ADCH;
      ADMUX = 0x60 + DIST1_PIN;
      break;
    default:
      dist_p = 6;
      break;
  }
  
  dist_p++;
  if (dist_p > 6)
    dist_p = 1;
  
  ADCSRA |= 0x40;
  
}


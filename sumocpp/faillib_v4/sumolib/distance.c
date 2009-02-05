/**
 * Funkcje obsługi czujników odległości
 */

#include "sumolib.h"

/**
 * Numer aktualnie przetwarzanego portu
 */
volatile unsigned char dist_p=1; 

/**
 * Wyniki przetwarzania na poszczególnych kanałach
 */
volatile unsigned char dist1=0;   
volatile unsigned char dist2=0; 
volatile unsigned char dist3=0; 
volatile unsigned char dist4=0;  
volatile unsigned char dist5=0; 
volatile unsigned char dist6=0; 
volatile unsigned char dist7=0; 
volatile unsigned char dist8=0; 


/**
 * Funkcja inicjalizująca czujniki odległości
 */
void dist_init()
{
	// Inicjalizacja portu
	DIST_DDR &= ~((1<<DIST1_PIN) | (1<<DIST2_PIN) | (1<<DIST3_PIN) | (1<<DIST4_PIN) | (1<<DIST5_PIN) | (1<<DIST6_PIN) | (1<<DIST7_PIN) | (1<<DIST8_PIN));
	DIST_POTR &= ~((1<<DIST1_PIN) | (1<<DIST2_PIN) | (1<<DIST3_PIN) | (1<<DIST4_PIN) | (1<<DIST5_PIN) | (1<<DIST6_PIN) | (1<<DIST7_PIN) | (1<<DIST8_PIN));
	
	// Konfiguracja przetwornika i przerwań
	ADMUX = 0x60; //01100000
	ADCSRA = 0xcd; //11001101
	
	// inicjalizacja numeru czujnika
	dist_p=1;
	sei();
}


/**
 * Funkcja zwraca przetworzoną wartość z czujnika 1
 */
inline unsigned char dist1_value() {
	return dist1;		
}

/**
 * Funkcja zwraca przetworzoną wartość z czujnika 2
 */
inline unsigned char dist2_value() {
	return dist2;		
}

/**
 * Funkcja zwraca przetworzoną wartość z czujnika 3
 */
inline unsigned char dist3_value() {
	return dist3;		
}

/**
 * Funkcja zwraca przetworzoną wartość z czujnika 4
 */
inline unsigned char dist4_value() {
	return dist4;		
}

/**
 * Funkcja zwraca przetworzoną wartość z czujnika 5
 */
inline unsigned char dist5_value() {
	return dist5;		
}

/**
 * Funkcja zwraca przetworzoną wartość z czujnika 6
 */
inline unsigned char dist6_value() {
	return dist6;		
}

/**
 * Funkcja zwraca przetworzoną wartość z czujnika 7
 */
inline unsigned char dist7_value() {
	return dist7;		
}

/**
 * Funkcja zwraca przetworzoną wartość z czujnika 8
 */
inline unsigned char dist8_value() {
	return dist8;		
}


/**
 * Procedura przerwania od przetwornika AC
 */
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
			ADMUX = 0x60 + DIST7_PIN;
			break;
		case 7:
			dist7 = ADCH;
			ADMUX = 0x60 + DIST8_PIN;
			break;
		case 8:
			dist8 = ADCH;
			ADMUX = 0x60 + DIST1_PIN;
			break;
		default:
			dist_p = 8;
			break;
	}
	
	dist_p++;
	if (dist_p > 8)
		dist_p = 1;
	
	ADCSRA |= 0x40;
	
}


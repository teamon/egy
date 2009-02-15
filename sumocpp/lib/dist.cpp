#include "sumo.h"

// Numer aktualnie przetwarzanego portu
volatile unsigned char dist_p = 0;
volatile unsigned char values[6];
volatile unsigned char prevs[6];
volatile double p[6];

// Funkcja inicjalizująca czujniki odległości
// UWAGA: zajmuje przetwornik AC
void dist_init(){
	// Inicjalizacja portu
	DIST_DDR &= ~((1<<DIST1_PIN) | (1<<DIST2_PIN) | (1<<DIST3_PIN) | (1<<DIST4_PIN) | (1<<DIST5_PIN) | (1<<DIST6_PIN));
	DIST_POTR &= ~((1<<DIST1_PIN) | (1<<DIST2_PIN) | (1<<DIST3_PIN) | (1<<DIST4_PIN) | (1<<DIST5_PIN) | (1<<DIST6_PIN));
	
	// Konfiguracja przetwornika i przerwań
	ADMUX = 0x60; //01100000
	ADCSRA = 0xcd; //11001101
	
	// inicjalizacja numeru czujnika
	dist_p = 1;
	sei();
}

unsigned char dist(char id){
	return values[id];
}

void kalman(int i, int k){
	double P_ = p[k] + KQ;
	double K = P_/(P_+KR);
	values[k] = prevs[k]+K*(i-prevs[k]);
	p[k] = (1 - K)*P_;
	prevs[k] = values[k];
}

// Procedura przerwania od przetwornika AC
SIGNAL (SIG_ADC){
	//values[dist_p] = ADCH;
	kalman(ADCH, dist_p);
	if (dist_p == 5) ADMUX = 0x60;
	else ADMUX = 0x60 + (dist_p + 1);
		
	dist_p++;
	if (dist_p > 5) dist_p = 0;
	
	ADCSRA |= 0x40;
}


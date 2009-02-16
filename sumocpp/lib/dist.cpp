#include "sumo.h"

// Numer aktualnie przetwarzanego portu
volatile unsigned char dist_p = 0;
int values[6];
// double p[6];

// Funkcja inicjalizująca czujniki odległości
// UWAGA: zajmuje przetwornik AC
void dist_init(){
	// Inicjalizacja portu
	DIST_DDR &= ~((1<<DIST1_PIN) | (1<<DIST2_PIN) | (1<<DIST3_PIN) | (1<<DIST4_PIN) | (1<<DIST5_PIN) | (1<<DIST6_PIN));
	DIST_POTR &= ~((1<<DIST1_PIN) | (1<<DIST2_PIN) | (1<<DIST3_PIN) | (1<<DIST4_PIN) | (1<<DIST5_PIN) | (1<<DIST6_PIN));
	
	// Konfiguracja przetwornika i przerwań
	ADMUX = 0x60; //01100000
	ADCSRA = 0xcd; //11001101
	
	// for(dist_p=0; dist_p < 6; dist_p++) {
	// 	values[dist_p] = 0;
	// 	// p[dist_p] = 1;
	// }
	
	// inicjalizacja numeru czujnika
	dist_p = 1;
	
	sei();
}

int dist(char id){
	return values[id];
}

// void kalman(int i, char k){
// 	i = 50
// 	double P_ = p[k] + KQ;
// 	double K = P_/(P_+KR);
// 	i = i+0;
// 	values[k] = values[k]+K*(i-values[k]);
//     p[k] = (1 - K)*P_;
// }

// Procedura przerwania od przetwornika AC
SIGNAL (SIG_ADC){
	values[dist_p] = ADCH;
	if (dist_p == 5) ADMUX = 0x60;
	else ADMUX = 0x60 + (dist_p + 1);
		
	dist_p++;
	if (dist_p > 5) dist_p = 0;
	
	ADCSRA |= 0x40;
}


#include "sumo.h"

// Numer aktualnie przetwarzanego portu
volatile unsigned char dist_p = 0;
volatile unsigned char values[8];
double P[6];
int Dist[2][3];

// Funkcja inicjalizująca czujniki odległości
// UWAGA: zajmuje przetwornik AC
void dist_init(){}

unsigned char dist(char id){
	return values[id];
}

void kalmanize(){
	for(int k=0; k < 6; k++) {
		int i = values[k];		
		double P_ = P[k] + KQ;
		double K = P_/(P_+KR);
		Dist[k/3][k%3] = Dist[k/3][k%3]+K*(i-Dist[k/3][k%3]);
		P[k] = (1 - K)*P_;
	}
}

// Procedura przerwania od przetwornika AC
// SIGNAL (SIG_ADC)
// {
// 	values[dist_p] = ADCH;
// 	if (dist_p == 7) ADMUX = 0x60;
// 	else ADMUX = 0x60 + (dist_p + 1);
// 		
// 	dist_p++;
// 	if (dist_p > 7) dist_p = 0;
// 	
// 	ADCSRA |= 0x40;
// }


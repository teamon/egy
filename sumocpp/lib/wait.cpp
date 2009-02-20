#include "sumo.h"

// Czeka podaną ilość sekund
void wait_s(int s) {
	int i;
	unsigned char j;
	for (i=0; i<s; i++) {
		// obliczanie sekundy
		for (j=0; j<100; j++)
			_delay_ms(10);
	}
}

// Czeka podaną ilość milisekund
void wait_ms(int ms) {
	int i;
	for (i=0; i<ms; i++) {
		_delay_ms(1);
	}
}

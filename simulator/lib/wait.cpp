#include "sumo.h"
#include <unistd.h>

// Czeka podaną ilość sekund
void wait_s(int s) {
	sleep(s);
}

// Czeka podaną ilość milisekund
void wait_ms(int ms) {
	usleep(ms*1000);
}

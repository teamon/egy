#include "sumo.h"

/// Inicjalizacja czujników podłoża
void ground_init() {}

char Ground[4];
// Wykrywa białe podłoże (linię) pod czujnikiem 1
unsigned char ground1_detected() {
	return Ground[0];
}

// Wykrywa białe podłoże (linię) pod czujnikiem 2
unsigned char ground2_detected() {
	return Ground[1];
}

// Wykrywa białe podłoże (linię) pod czujnikiem 3
unsigned char ground3_detected() {
	return Ground[2];
}

// Wykrywa białe podłoże (linię) pod czujnikiem 4
unsigned char ground4_detected() {
	return Ground[3];
}
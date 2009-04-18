#include "sumo.h"

unsigned char Switch[2];
// Inicjalizacja przycisków
void switch_init() {}

// Sprawdzenie, czy przycisk 1 naciśnięty
unsigned char switch1_pressed() {
	return Switch[0];
}

// Sprawdzenie, czy przycisk 2 naciśnięty
unsigned char switch2_pressed() {
	return Switch[1];
}

// Czekanie na naciśnięcie przycisku 1
void wait_switch1() {
	while(1);
}

// Czekanie na naciśnięcie przycisku 2
void wait_switch2() {
	while(1);
}

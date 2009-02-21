/**
 * Funkcje do obsługi przycisków
 */

#include "sumolib.h"

/**
 * Inicjalizacja przycisków
 */
void switch_init() {
	// przycisk 1
	clr(SWITCH1_DDR, SWITCH1_PIN);
	setb(SWITCH1_PORT, SWITCH1_PIN);
	// przycisk 2
	clr(SWITCH2_DDR, SWITCH2_PIN);
	setb(SWITCH2_PORT, SWITCH2_PIN);
	
}

/**
 * Sprawdzenie, czy przycisk 1 naciśnięty
 * 0 - nie 
 * 1 - tak
 */
unsigned char switch1_pressed() {
	if (bit_is_clear(SWITCH1_PINPORT, SWITCH1_PIN))
	 	return 1;
	else
		return 0;
}

/**
 * Sprawdzenie, czy przycisk 2 naciśnięty
 * 0 - nie 
 * 1 - tak
 */
unsigned char switch2_pressed() {
	if (bit_is_clear(SWITCH2_PINPORT, SWITCH2_PIN))
		return 1;
	else
		return 0;
}

/**
 * Czekanie na naciśnięcie przycisku 1
 */
void wait_switch1() {
	while(bit_is_set(SWITCH1_PINPORT, SWITCH1_PIN));
}

/**
 * Czekanie na naciśnięcie przycisku 2
 */
void wait_switch2() {
	while(bit_is_set(SWITCH2_PINPORT, SWITCH2_PIN));
}


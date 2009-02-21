/**
 * Funkcje obsługi czujników podłoża
 */

#include "sumolib.h"

/**
 * Inicjalizacja czujników podłoża
 */
void ground_init() {
	clr(GROUND_DDR, GROUND1_PIN);
	clr(GROUND_DDR, GROUND2_PIN);
	clr(GROUND_DDR, GROUND3_PIN);
	clr(GROUND_DDR, GROUND4_PIN);
	clr(GROUND_PORT, GROUND1_PIN);
	clr(GROUND_PORT, GROUND2_PIN);
	clr(GROUND_PORT, GROUND3_PIN);
	clr(GROUND_PORT, GROUND4_PIN);
	setb(GROUND_PWM_DDR, GROUND_PWM);
	setb(GROUND_PWN_PORT, GROUND_PWM);
}

/**
 * Wykrywa białe podłoże (linię) pod czujnikiem 1
 * Zwraca:
 * 1 - podłoże jasne
 * 0 - podłoże ciemne
 * Wartości będą zanegowane, jeśli zostanie to ustawione w konfiguracji
 */
unsigned char ground1_detected() {
	// Normalne działanie
	if (!GROUND_NEGATE) {
		if (bit_is_clear(GROUND_PINPORT, GROUND1_PIN))
			return 1;
		else
			return 0;
	}
	// Zanegowane wartości
	else {
		if (bit_is_clear(GROUND_PINPORT, GROUND1_PIN))
			return 0;
		else
			return 1;
	}
}


/**
 * Wykrywa białe podłoże (linię) pod czujnikiem 2
 * Zwraca:
 * 1 - podłoże jasne
 * 0 - podłoże ciemne
 * Wartości będą zanegowane, jeśli zostanie to ustawione w konfiguracji
 */
unsigned char ground2_detected() {
	// Normalne działanie
	if (!GROUND_NEGATE) {
		if (bit_is_clear(GROUND_PINPORT, GROUND2_PIN))
			return 1;
		else
			return 0;
	}
	// Zanegowane wartości
	else {
		if (bit_is_clear(GROUND_PINPORT, GROUND2_PIN))
			return 0;
		else
			return 1;
	}
}


/**
 * Wykrywa białe podłoże (linię) pod czujnikiem 3
 * Zwraca:
 * 1 - podłoże jasne
 * 0 - podłoże ciemne
 * Wartości będą zanegowane, jeśli zostanie to ustawione w konfiguracji
 */
unsigned char ground3_detected() {
	// Normalne działanie
	if (!GROUND_NEGATE) {
		if (bit_is_clear(GROUND_PINPORT, GROUND3_PIN))
			return 1;
		else
			return 0;
	}
	// Zanegowane wartości
	else {
		if (bit_is_clear(GROUND_PINPORT, GROUND3_PIN))
			return 0;
		else
			return 1;
	}
}


/**
 * Wykrywa białe podłoże (linię) pod czujnikiem 4
 * Zwraca:
 * 1 - podłoże jasne
 * 0 - podłoże ciemne
 * Wartości będą zanegowane, jeśli zostanie to ustawione w konfiguracji
 */
unsigned char ground4_detected() {
	// Normalne działanie
	if (!GROUND_NEGATE) {
		if (bit_is_clear(GROUND_PINPORT, GROUND4_PIN))
			return 1;
		else
			return 0;
	}
	// Zanegowane wartości
	else {
		if (bit_is_clear(GROUND_PINPORT, GROUND4_PIN))
			return 0;
		else
			return 1;
	}
}



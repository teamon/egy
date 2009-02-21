/**
 * Funkcje do obsługi diod led
 */

#include "sumolib.h"

unsigned int led_state = 0x00;
unsigned int last_led_state = 0xff;

/**
 * Funkcja inicjalizujaca sterownik diod
 */
void sled_init() {
	setb(SLED_SDI_DDR,SLED_SDI_PIN);
	clr(SLED_SDI_PORT,SLED_SDI_PIN);

	setb(SLED_CLK_DDR,SLED_CLK_PIN);
	clr(SLED_CLK_PORT,SLED_CLK_PIN);

	setb(SLED_LE_DDR,SLED_LE_PIN);
	clr(SLED_LE_PORT,SLED_LE_PIN);
	
	sled_send();
	
}


/**
 * Funkcja wysyła dane do sterownika diod
 */
void sled_send() {

	// sprawdzanie czy cos sie zmienilo
	if (led_state != last_led_state) {
	
		int i;
		// rejestr tymczasowy
		unsigned int reg = led_state;
		
		// przesuniecie bitowe
		reg = reg >> 8;
	
		// wyslanie danych do rejestru
		for (i=0; i<16; i++) {

			// zapis wartosci
			if (reg & 0x01)
				setb(SLED_SDI_PORT,SLED_SDI_PIN);
			else
				clr(SLED_SDI_PORT,SLED_SDI_PIN);

			// opoznienie
			sled_delay();

			// zbocze rosnace zegara
			setb(SLED_CLK_PORT,SLED_CLK_PIN);

			// opoznienie
			sled_delay();

			// zbocze opadajace zegara
			clr(SLED_CLK_PORT,SLED_CLK_PIN);

			// przesuniecie
			reg = reg >> 1;
		}

		// opoznienie
		sled_delay();
		
		// zbocze opadajace zatrzasku
		//clr(SLED_LE_PORT,SLED_LE_PIN);
		setb(SLED_LE_PORT,SLED_LE_PIN);

		// opoznienie
		sled_delay();
		
		// zbocze rosnace zatrzasku
		//setb(SLED_LE_PORT,SLED_LE_PIN);
		clr(SLED_LE_PORT,SLED_LE_PIN);
	
		// aktualizowanie 
		last_led_state = led_state;
	}
	
}

/**
 * Funkcja ustawia wartosci diod
 */
void sled_set(unsigned int value) {
	led_state = value;
	led_state = led_state << 8;
	sled_send();
}

/*
 * Zapal diode led 1
 */
void sled8_on() {
	setb(led_state, 8);
	sled_send();
}

/*
 * Zgas diode led 1
 */
void sled8_off() {
	clr(led_state, 8);
	sled_send();
}

/*
 * Zapal diode led 2
 */
void sled7_on() {
	setb(led_state, 9);
	sled_send();
}

/*
 * Zgas diode led 2
 */
void sled7_off() {
	clr(led_state, 9);
	sled_send();
}

/*
 * Zapal diode led 3
 */
void sled6_on() {
	setb(led_state, 10);
	sled_send();
}

/*
 * Zgas diode led 3
 */
void sled6_off() {
	clr(led_state, 10);
	sled_send();
}

/*
 * Zapal diode led 4
 */
void sled5_on() {
	setb(led_state, 11);
	sled_send();
}

/*
 * Zgas diode led 4
 */
void sled5_off() {
	clr(led_state, 11);
	sled_send();
}

/*
 * Zapal diode led 5
 */
void sled4_on() {
	setb(led_state, 12);
	sled_send();
}

/*
 * Zgas diode led 5
 */
void sled4_off() {
	clr(led_state, 12);
	sled_send();
}

/*
 * Zapal diode led 6
 */
void sled3_on() {
	setb(led_state, 13);
	sled_send();
}

/*
 * Zgas diode led 6
 */
void sled3_off() {
	clr(led_state, 13);
	sled_send();
}

/*
 * Zapal diode led 7
 */
void sled2_on() {
	setb(led_state, 14);
	sled_send();
}

/*
 * Zgas diode led 7
 */
void sled2_off() {
	clr(led_state, 14);
	sled_send();
}

/*
 * Zapal diode led 8
 */
void sled1_on() {
	setb(led_state, 15);
	sled_send();
}

/*
 * Zgas diode led 8
 */
void sled1_off() {
	clr(led_state, 15);
	sled_send();
}


/**
 * Funkcja opozniajaca
 */
void sled_delay() {
	volatile unsigned char i;
	for (i=0; i<10; i++);
}




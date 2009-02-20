#include "sumo.h"

unsigned int led_state = 0x00;
unsigned int last_led_state = 0xff;

// Funkcja inicjalizująca sterownik diod
void led_init() {
	setb(LED_SDI_DDR,LED_SDI_PIN);
	clr(LED_SDI_PORT,LED_SDI_PIN);

	setb(LED_CLK_DDR,LED_CLK_PIN);
	clr(LED_CLK_PORT,LED_CLK_PIN);

	setb(LED_LE_DDR,LED_LE_PIN);
	clr(LED_LE_PORT,LED_LE_PIN);

	led_send();
}

// Wysylanie danych do sterownika
void led_send() {
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
			if (reg & 0x01) setb(LED_SDI_PORT,LED_SDI_PIN);
			else clr(LED_SDI_PORT,LED_SDI_PIN);
			// opoznienie
			led_delay();
			// zbocze rosnace zegara
			setb(LED_CLK_PORT,LED_CLK_PIN);
			// opoznienie
			led_delay();
			// zbocze opadajace zegara
			clr(LED_CLK_PORT,LED_CLK_PIN);
			// przesuniecie
			reg = reg >> 1;
		}

		// opoznienie
		led_delay();
		// zbocze opadajace zatrzasku
		//clr(LED_LE_PORT,LED_LE_PIN);
		setb(LED_LE_PORT,LED_LE_PIN);
		// opoznienie
		led_delay();
		// zbocze rosnace zatrzasku
		//setb(LED_LE_PORT,LED_LE_PIN);
		clr(LED_LE_PORT,LED_LE_PIN);
		// aktualizowanie 
		last_led_state = led_state;
	}
}

// Funkcja ustawia wartosci diod
void led_set(unsigned int value) {
	led_state = value;
	led_state = led_state << 8;
	led_send();
}

void led_delay() {
	volatile unsigned char i;
	for (i=0; i<10; i++);
}

void led1_on() {
	setb(led_state, 1);
	led_send();
}
void led1_off() {
	clr(led_state, 1);
	led_send();
}
void led2_on() {
	setb(led_state, 2);
	led_send();
}
void led2_off() {
	clr(led_state, 2);
	led_send();
}
void led3_on() {
	setb(led_state, 3);
	led_send();
}
void led3_off() {
	clr(led_state, 3);
	led_send();
}
void led4_on() {
	setb(led_state, 4);
	led_send();
}
void led4_off() {
	clr(led_state, 4);
	led_send();
}
void led5_on() {
	setb(led_state, 5);
	led_send();
}
void led5_off() {
	clr(led_state, 5);
	led_send();
}
void led6_on() {
	setb(led_state, 6);
	led_send();
}
void led6_off() {
	clr(led_state, 6);
	led_send();
}
void led7_on() {
	setb(led_state, 7);
	led_send();
}
void led7_off() {
	clr(led_state, 7);
	led_send();
}
void led8_on() {
	setb(led_state, 8);
	led_send();
}
void led8_off() {
	clr(led_state, 8);
	led_send();
}

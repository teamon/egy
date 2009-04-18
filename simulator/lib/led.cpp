#include "sumo.h"

unsigned int led_state = 0x00;
unsigned int last_led_state = 0xff;

// Funkcja inicjalizująca sterownik diod
void led_init() {}

// Wysylanie danych do sterownika
void led_send() {}

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

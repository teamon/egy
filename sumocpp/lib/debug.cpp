#include "sumo.h"

void send_ground_state_on_usart(){
	usart_write_progmem_string(PSTR("2:1:"));
	if (ground1_detected()) usart_write_byte('2');
	else usart_write_byte('1');
	usart_write_byte('\n');
	
	usart_write_progmem_string(PSTR("2:2:"));
	if (ground2_detected()) usart_write_byte('2');
	else usart_write_byte('1');
	usart_write_byte('\n');
	
	usart_write_progmem_string(PSTR("2:3:"));
	if (ground3_detected()) usart_write_byte('2');
	else usart_write_byte('1');
	usart_write_byte('\n');
	
	usart_write_progmem_string(PSTR("2:4:"));
	if (ground4_detected()) usart_write_byte('2');
	else usart_write_byte('1');
	usart_write_byte('\n');
}

void send_distance_state_on_usart(){
	// leds_negate();
	usart_write_progmem_string(PSTR("4:1:"));
	usart_write_number((int)dist(0));
	usart_write_byte('\n');
	
	usart_write_progmem_string(PSTR("4:2:"));
	usart_write_number((int)dist(1));
	usart_write_byte('\n');
	
	usart_write_progmem_string(PSTR("4:3:"));
	usart_write_number((int)dist(2));
	usart_write_byte('\n');
	
	usart_write_progmem_string(PSTR("4:4:"));
	usart_write_number((int)dist(3));
	usart_write_byte('\n');
	
	usart_write_progmem_string(PSTR("4:5:"));
	usart_write_number((int)dist(4));
	usart_write_byte('\n');
	
	usart_write_progmem_string(PSTR("4:6:"));
	usart_write_number((int)dist(5));
	usart_write_byte('\n');
}

unsigned char progressVal = 1;
// 1 2 4 8 12 32 64 128
void progress(){	
	led1_on();
	led_send(progressVal);
	if (progressVal == 128) progressVal = 1;
	else progressVal *= 2;
}

void debug(){
	progress();
	send_ground_state_on_usart();
	send_distance_state_on_usart();
}
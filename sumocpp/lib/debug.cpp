#include "sumo.h"

void reset(){
	asm("cli"); 
	asm("jmp 0"); 
}

void led_grd(){
	if (ground1_detected()) {
		led1_on();
	} else {
		led1_off();
	}
	// czujnik GRD 2
	if (ground2_detected()) {
		led2_on();
	} else {
		led2_off();
	}
	// czujnik GRD 3
	if (ground3_detected()) {
		led3_on();
	} else {
		led3_off();
	}
	// czujnik GRD 4
	if (ground4_detected()) {
		led4_on();
	} else {
		led4_off();
	}
}

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
	for(int k=0; k < 6; k++) {
		usart_write_progmem_string(PSTR("4:"));
		usart_write_number(k+1);
		usart_write_progmem_string(PSTR(":"));
		//usart_write_number(Dist[k/3][k%3]);
		usart_write_number(dist(k));
		usart_write_byte('\n');
	}
}

unsigned char progressVal = 1;
void progress(){
	if (progressVal == 8) progressVal = 1;
	else progressVal++;
	led_set(1 << progressVal);
}

void countdown(char val){
	led_set((1<<(val-1))*(val>0));
}

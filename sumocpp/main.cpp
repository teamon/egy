/*
	G - ground
	D - distance
	M - motor
	----------------------
	| G2	D1	D2	D3	G3 |
	|										|
	|										|
	| M1							M2 |
	|										|
	|										|
	| G5	D4	D5	D6	G7 |
	----------------------
*/

#include "lib/sumo.h"
#include "lib/motor.h"
#include "lib/queue.h"

#define ITIME 50
#define DEBUG 1

Queue queue;
//Move move;

void reset(){
	asm("cli"); 
	asm("jmp 0"); 
}

void reverse(){
	Motor tmp = motor_left;
	motor_left = motor_right;
	motor_right = tmp;
}

void init(){
	led_init();
	motor_init();
	switch_init();
	ground_init();
	dist_init();
	servo_init();
	if(DEBUG) usart_init();
}

int main(){
	init();
	leds_on();
	
	if(!DEBUG) wait_s(5); // regulaminowy czas
	
	for (;;){
		if (usart_read_byte() == '!'){
			usart_write_progmem_string(PSTR("Bonjour\n"));
			break;
		}
	
		wait_ms(ITIME);
	}
	
	for(;;){
		if(DEBUG) debug();
		if (usart_read_byte() == '*') reset();
				
		// if(switch1_pressed()){
		//	 leds_negate();
		//	 wait_ms(1000);
		//	 reset();
		// }
		
		// if(queue.head){
		//	 move = queue.pop(ITIME);
		//	 motor_left.set_power(move.left);
		//	 motor_right.set_power(move.right);
		// } else{
		//	 // serczin` und killin` !
		//	 motor_left.set_power(0);
		//	 motor_right.set_power(0);
		// }
		// 
		wait_ms(ITIME);
	}
}


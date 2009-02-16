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

//Motor motor[2];
bool mleft = 0, mright = 1;

int Dist[6];
double p[6];
void kalmanize(){
	for(int k=0; k < 6; k++) {
		int i = dist(k);
		
		double P_ = p[k] + KQ;
		double K = P_/(P_+KR);
		Dist[k] = Dist[k]+K*(i-Dist[k]);
		p[k] = (1 - K)*P_;
	}
}

void reverse(){
	//motory
	mleft = !mleft;
	mright = !mright;
	
	//disty
	
	//groundy
	
}

void setup(){
	led_init();
	motor_init();
	switch_init();
	ground_init();
	dist_init();
	servo_init();
	if(DEBUG) usart_init();
	
	leds_on();
}

unsigned char ticks = 0;
bool odliczanie = false;
bool hold = false;
bool preLoop(){
	if (DEBUG){
		if (usart_read_byte() == '!'){
			usart_write_progmem_string(PSTR("Bonjour\n"));
			return true;
		}
	}else {
		if (switch1_pressed() && !hold){
			odliczanie = !odliczanie;
			ticks = 0;
			hold = true;
		}else if(!switch1_pressed())
			hold = false;
		
		ticks += odliczanie;
		if (ticks >= 5000/ITIME) return true;
	}
	return false;
}

void loop(){
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
}

int main(){
	setup();
	
	while(!preLoop()) wait_ms(ITIME);
	
	for(;;){
		loop();
		wait_ms(ITIME);
	}
}


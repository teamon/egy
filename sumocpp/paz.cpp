/*
	G - ground
	D - distance
	M - motor
	----------------------
	| G-2	D-1	D-2	G-3 |
	|										|
	|										|
	| M-1						M-2 |
	|										|
	|										|
	| G-5		 D-3		G-7 |
	----------------------
*/

#include "lib/sumo.h"
#include "lib/motor.h"
#include "lib/queue.h"

#define PI 3.1415
#define REV_ITER 20
#define ITERATION_TIME 50
#define ROZSTAW 7.5

char escape_grd = 0;	
char grd;

Motor motor1 = Motor(&OCR1A, &MOTOR1_DIR_PORT, MOTOR1_DIR_PIN);
Motor motor2 = Motor(&OCR1B, &MOTOR2_DIR_PORT, MOTOR2_DIR_PIN);

Queue queue;
Move move;

void straight(char val){
	queue.push(val, val, 5);
} 

void turn(double angle){
	if(angle >= 0){
		queue.push(50, 30, angle * 10);
	} else{
		queue.push(30, 50, -1 * angle * 10);
	}
}

void escape(char grd){
	switch (grd){
		case 6: //lapia oba z gory
		default:
			straight(20);
			turn(1/2.0);
			break;
		case 35: //lapia oba z dolu
			straight(-20);
			break;
		case 21: //lapia oba z prawej
			turn(1/2.0);
			break;
		case 10: //lapia oba z lewej
			turn(-1/2.0);
			break;
		case 2:
			turn(1/2.0);
			break;
		case 3:
			turn(1/2.0);
			break;
	}
}

int main(){
	led_init();
	motor_init();
	switch_init();
	ground_init();
	dist_init();
	leds_on();
	
	while(switch1_pressed()==0){
		if(ground1_detected()) led1_on();
		else led1_off();
		if(ground2_detected()) led2_on();
		else led2_off();
		if(ground3_detected()) led3_on();
		else led3_off();
		if(ground4_detected()) led4_on();
		else led4_off();
	}

	
	for(;;){
		// ground debug
		if(ground1_detected()) led1_on();
		else led1_off();
		if(ground2_detected()) led2_on();
		else led2_off();
		if(ground3_detected()) led3_on();
		else led3_off();
		if(ground4_detected()) led4_on();
		else led4_off();
		
		
		grd = ground();	 
		
		if(grd != 1 && grd != escape_grd){
			queue.clear();
			escape_grd = grd;
			escape(grd);
		}
		
		if(queue.head){
			queue.head->move.time--;
			Move move = queue.head->move;
			if(move.time == 0){
				escape_grd = 0;
				queue.pop();
				move = queue.head->move;
			}
			
			motor1.set_power(move.m1);
			motor2.set_power(move.m2);
			
			if(escape == 0){
				// search & destroy
			}
		} else{
			queue.push(50, 30, 10);
		}
		
		wait_ms(50);
	}
}

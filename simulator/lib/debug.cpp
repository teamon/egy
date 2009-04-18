#include "sumo.h"

void reset(){}

void led_grd(){}

void send_ground_state_on_usart(){}

void send_distance_state_on_usart(){}

unsigned char progressVal = 1;
void progress(){
	if (progressVal == 8) progressVal = 0;
	else progressVal++;
	led_set(1 << progressVal);
}

void countdown(char val){}

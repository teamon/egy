#include "sumo.h"


// tak na szybko wjebany kalman
int v[6];
double p[6];

void kalman_init(){
	for(int i=0; i < 6; i++) {
		v[i] = 0;
		p[i] = 1;
	}
}

void reset(){
	asm("cli"); 
	asm("jmp 0"); 
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
	
	
	// zrobmy sobie kalmana
	for(int k=0; k < 6; k++) {
		int i = dist(k);
		
		double P_ = p[k] + KQ;
		double K = P_/(P_+KR);
		v[k] = v[k]+K*(i-v[k]);
		p[k] = (1 - K)*P_;
	}
		
	
	// tuuuu na dole zbiera z tablicy v[x] 
	// leds_negate();
	usart_write_progmem_string(PSTR("4:1:"));
	usart_write_number((int)v[0]);
	usart_write_byte('\n');
	
	usart_write_progmem_string(PSTR("4:2:"));
	usart_write_number((int)v[1]);
	usart_write_byte('\n');
	
	usart_write_progmem_string(PSTR("4:3:"));
	usart_write_number((int)v[2]);
	usart_write_byte('\n');
	
	usart_write_progmem_string(PSTR("4:4:"));
	usart_write_number((int)v[3]);
	usart_write_byte('\n');
	
	usart_write_progmem_string(PSTR("4:5:"));
	usart_write_number((int)v[4]);
	usart_write_byte('\n');
	
	usart_write_progmem_string(PSTR("4:6:"));
	usart_write_number((int)v[5]);
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
	
	unsigned char c = usart_read_byte();
	while (c!=0){
		if(c=='*') reset();
		
		/*else if (c == '~'){ //motor
			char lp = usart_read_byte();
			char sign_c = usart_read_byte();
			char sign;
			switch (sign_c){
				case 'f': 
					sign = 1;
					break;
				case 'b':
					sign = -1;
					break;
				case 'n':
					sign=0;
					break;
			}
			char power = usart_read_byte();
			power *= sign;
			SetMotor(lp, power);
		}*/
		
		c = usart_read_byte();
	}
}
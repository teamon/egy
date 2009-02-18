#include "sumo.h"

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
	for(int k=0; k < 6; k++) {
		usart_write_progmem_string(PSTR("4:"));
		usart_write_number(k+1);
		usart_write_progmem_string(PSTR(":"));
		usart_write_number(Dist[k/3][k%3]);
		usart_write_byte('\n');
	}
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
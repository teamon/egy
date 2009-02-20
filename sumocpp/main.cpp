/*
  G - ground
  D - distance
  M - motor
  ----------------------
  | G2  D1  D2  D3  G3 |
  |                    |
  |                    |
  | M1              M2 |
  |                    |
  |                    |
  | G5  D4  D5  D6  G7 |
  ----------------------
*/

#include "lib/sumo.h"
#include "lib/motor.h"
#include "lib/queue.h"

#define ITIME 50
#define DEBUG 1

Queue queue;
Move move;

void init(){
  led_init();
  motor_init();
  switch_init();
  ground_init();
  dist_init();
  servo_init();
  if(DEBUG) usart_init();
}

int main() {
  init();
  led8_on();
    
  for (;;){
	progress();
    usart_write_progmem_string(PSTR("4:5:"));
	usart_write_number(dist(4));
	usart_write_byte('\n');
    wait_ms(100);
  }  
}


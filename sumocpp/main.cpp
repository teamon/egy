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
#define MAX_POWER 50 // tak zeby nie zjarac serw :p
#define DEBUG 1

Queue queue;
Move move;
Motor motor1;
Motor motor2;

void reset() 
{
  asm("cli"); 
  asm("jmp 0"); 
}

// debug itp
unsigned char progressVal = 1;
void progress(){  
  led_send(progressVal);
  if (progressVal == 128) progressVal = 1;
  else progressVal *= 2;
}
// 1 2 4 8 12 32 64 128

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

void send_distance_state_on_usart() {
  usart_write_progmem_string(PSTR("4:1:"));
  usart_write_number((int)dist1_value());
  usart_write_byte('\n');

  usart_write_progmem_string(PSTR("4:2:"));
  usart_write_number((int)dist2_value());
  usart_write_byte('\n');

  usart_write_progmem_string(PSTR("4:3:"));
  usart_write_number((int)dist3_value());
  usart_write_byte('\n');

  usart_write_progmem_string(PSTR("4:4:"));
  usart_write_number((int)dist4_value());
  usart_write_byte('\n');

  usart_write_progmem_string(PSTR("4:5:"));
  usart_write_number((int)dist5_value());
  usart_write_byte('\n');

  usart_write_progmem_string(PSTR("4:6:"));
  usart_write_number((int)dist6_value());
  usart_write_byte('\n');
}

void debug(){
  progress();
  send_ground_state_on_usart();
	send_distance_state_on_usart();
}

void init(){
  led_init();
  motor_init();
  switch_init();
  ground_init();
  dist_init();
  servo_init();
  if(DEBUG) usart_init();

  motor1 = Motor(&OCR1A, &MOTOR1_DIR_PORT, MOTOR1_DIR_PIN, MAX_POWER);
  motor2 = Motor(&OCR1B, &MOTOR2_DIR_PORT, MOTOR2_DIR_PIN, MAX_POWER);
}

int main() {
  init();
  leds_on();
  
  if(!DEBUG) wait_s(5); // regulaminowy czas
  
  for(;;){
    if(DEBUG) debug();
        
    if(switch1_pressed()){
      leds_negate();
      wait_ms(1000);
      reset();
    }
    
    if(queue.head){
      move = queue.pop(ITIME);
      motor1.set_power(move.m1);
      motor2.set_power(move.m2);
    } else {
      // leds_off();
      // szukanie
      
      motor1.set_power(0);
      motor2.set_power(0);
    }
    wait_ms(ITIME);
  }
}


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

void reset() 
{
  asm("cli"); 
  asm("jmp 0"); 
}

// debug itp progress powinien dzialac
unsigned char progressVal = 0;
void progress(){
  if (progressVal == 8) progressVal = 0;
  else progressVal++;
  led_set(1 << progressVal);
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

void send_distance_state_on_usart() {
  for(char i=0 ; i<8 ; ++i){
    usart_write_progmem_string(PSTR("4:"));
    usart_write_number(i);
    usart_write_progmem_string(PSTR(":"));
    usart_write_number((int)dist(0));
    usart_write_byte('\n');
  }
}

void debug(){
  progress();
  send_ground_state_on_usart();
  send_distance_state_on_usart();
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

int main() {
  init();
  led8_on();
  
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
    if (usart_read_byte() == '!') reset();
        
    // if(switch1_pressed()){
    //   leds_negate();
    //   wait_ms(1000);
    //   reset();
    // }
    
    // if(queue.head){
    //   move = queue.pop(ITIME);
    //   motor_left.set_power(move.left);
    //   motor_right.set_power(move.right);
    // } else {
    //   // serczin` und killin` !
    //   motor_left.set_power(0);
    //   motor_right.set_power(0);
    // }
    // 
    wait_ms(ITIME);
  }
}


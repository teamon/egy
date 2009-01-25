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

// debug itp

unsigned char progressVal = 1;
void progress(){  
  led_send(progressVal);
  if (progressVal*2 > 63) progressVal = 1;
  else progressVal *= 2;
}

void debug(){
  progress();
  
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
  
  wait_s(5); // regulaminowy czas

  for(;;){
    if(DEBUG) debug();
        
    if(switch1_pressed()){
      leds_negate();
    }
    
    if(queue.head){
      move = queue.pop(ITIME);
      motor1.set_power(move.m1);
      motor2.set_power(move.m2);
    } else {
      leds_off();
      // szukanie
      motor1.set_power(0);
      motor2.set_power(0);
    }
    wait_ms(ITIME);
  }
}


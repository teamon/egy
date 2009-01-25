#include "sumo.h"
#include "motor.h"

Motor motor_left;
Motor motor_right;
  
Motor::Motor(volatile uint16_t* reg, volatile uint8_t* port, unsigned char pin){
  REG = reg;
  DIR_PORT = port;
  DIR_PIN = pin;
}

void Motor::stop(){
  *REG = 0;
}

void Motor::set_power(char p){
  char dir = p; /// albo p/abs(p);
  p = abs(p);
  if(p > MOTOR_MAX_POWER) p = MOTOR_MAX_POWER;
  *REG = p * 10;
  
  if(dir > 0) clr(*DIR_PORT, DIR_PIN); // do przodu
  else if(dir < 0) setb(*DIR_PORT, DIR_PIN); // do tylu
}

void motor_init() {
  setb(MOTOR1_PWM_DDR, MOTOR1_PWM_PIN);
  setb(MOTOR2_PWM_DDR, MOTOR2_PWM_PIN);
  setb(MOTOR1_DIR_DDR, MOTOR1_DIR_PIN);
  setb(MOTOR2_DIR_DDR, MOTOR2_DIR_PIN);
  
  // ustawienie rejestrów
  TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(WGM11) | _BV(WGM10);
  TCCR1A |= _BV(COM1A0);
  TCCR1A |= _BV(COM1B0);
  
  OCR1A = 0;
  OCR1B = 0;
  TCCR1B = 0x00; 
  TCCR1B |= PWM_PRESCALLER_CONFIG;
  
  clr(MOTOR1_DIR_PORT, MOTOR1_DIR_PIN);
  clr(MOTOR2_DIR_PORT, MOTOR2_DIR_PIN);

  motor_left = Motor(&OCR1A, &MOTOR1_DIR_PORT, MOTOR1_DIR_PIN);
  motor_right = Motor(&OCR1B, &MOTOR2_DIR_PORT, MOTOR2_DIR_PIN);
}


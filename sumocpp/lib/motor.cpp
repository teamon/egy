#include "sumo.h"
#include "motor.h"

Motor motor[2];

Motor::Motor(volatile uint16_t* reg, volatile uint8_t* port, unsigned char pin){
	REG = reg;
	DIR_PORT = port;
	DIR_PIN = pin;
	
	reverse = false;
}

void Motor::stop(){
	*REG = 0;
}

void Motor::setPower(char p){
	if (reverse)
		p = -p;
/*
jezeli przy reverse==1 wrzucam p do przodu to power = -p
gdy potem leci fikumiku() to reverse == 0 i getPower() zwraca power = -p
gdy potem dostane taki sam power tzn. -p to ponizsza implikacja spowoduje
wyjscie z funkcji, czyli wszystko ok :)
*/	
	if (p == getPower()) return;
	power = p;
	char dir = p; /// albo p/abs(p);
	p = mabs(p);
	if(p > MOTOR_MAX_POWER) p = MOTOR_MAX_POWER;
	*REG = p * 10;
	
	if(dir > 0) clr(*DIR_PORT, DIR_PIN); // do przodu
	else if(dir < 0) setb(*DIR_PORT, DIR_PIN); // do tylu
	else stop();
}

char Motor::getPower(){
	return (reverse)?-power:power;
}

void motor_init(){
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

	motor[0] = Motor(&OCR1A, &MOTOR1_DIR_PORT, MOTOR1_DIR_PIN);
	motor[1] = Motor(&OCR1B, &MOTOR2_DIR_PORT, MOTOR2_DIR_PIN);
}


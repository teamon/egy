#include "sumo.h"
#include "motor.h"

Motor motor[2];
	
Motor::Motor(){
	reverse = false;
	power = 0;
}

void Motor::stop(){
	power = 0;
}

void Motor::setPower(char p){
	power = p;
}

char Motor::getPower(){
	return (reverse)?-power:power;
}

void motor_init() {
	motor[0] = Motor();
	motor[1] = Motor();
}


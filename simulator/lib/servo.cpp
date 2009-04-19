#include "sumo.h"

// licznik
volatile unsigned char counter = 0;

// Konfiguracja serwomechanizmów
// 0 - serwo wyłączone
// 1 - serwo stoi
// 2 - serwo obraca się w przód
// 3 - serwo obraca się w tył
// 4 - kalibracja serwa
volatile unsigned char servo1 = 0;
volatile unsigned char servo2 = 0;
volatile unsigned char servo3 = 0;
volatile unsigned char servo4 = 0;

// Inicjalizacja serwomechanizmów 1-2
// UWAGA: zajmuje timer0
void servo_init() {
	servo1 = 1;
	servo2 = 1;
	servo3 = 1;
	servo4 = 1;
}

void servo1_forward() {	servo1 = 2; }
void servo2_forward() {	servo2 = 2; }
void servo3_forward() {	servo3 = 2; }
void servo4_forward() {	servo4 = 2; }

void servo1_backward() {	servo1 = 3; }
void servo2_backward() {	servo2 = 3; }
void servo3_backward() {	servo3 = 3; }
void servo4_backward() {	servo4 = 3; }

void servo1_stop() { servo1 = 1; }
void servo2_stop() { servo2 = 1; }
void servo3_stop() { servo3 = 1; }
void servo4_stop() { servo4 = 1; }

void servo1_calibrate() { servo1 = 4; }
void servo2_calibrate() { servo2 = 4; }
void servo3_calibrate() { servo3 = 4; }
void servo4_calibrate() { servo4 = 4; }


// Obsługa przerwania od timera 0
// SIGNAL (SIG_OVERFLOW0)
// {
// 	TCNT0 = TIMER0_BEGIN_VALUE;
// 
// 	// dla 17 milisekundy
// 	if (counter == (34)) {
// 		if(servo1 > 1) setb(SERVO1_PORT,SERVO1_PIN);
// 		if(servo2 > 1) setb(SERVO2_PORT,SERVO2_PIN);
// 		if(servo3 > 1) setb(SERVO3_PORT,SERVO3_PIN);
// 		if(servo4 > 1) setb(SERVO4_PORT,SERVO4_PIN);
// 	}
// 
// 	// dla 18 milisekundy
// 	if (counter == (36)) {	
// 		if(servo1 == 2) clr(SERVO1_PORT,SERVO1_PIN);
// 		if(servo2 == 2) clr(SERVO2_PORT,SERVO2_PIN);
// 		if(servo3 == 2) clr(SERVO3_PORT,SERVO3_PIN);
// 		if(servo4 == 2) clr(SERVO4_PORT,SERVO4_PIN);
// 	}
// 
// 	// dla 18,5 milisekundy
// 	if (counter == (37)) {	
// 		if(servo1 == 4) clr(SERVO1_PORT,SERVO1_PIN);
// 		if(servo2 == 4) clr(SERVO2_PORT,SERVO2_PIN);
// 		if(servo3 == 4) clr(SERVO3_PORT,SERVO4_PIN);
// 		if(servo4 == 4) clr(SERVO4_PORT,SERVO3_PIN);
// 	}
// 
// 	// dla 19 milisekundy
// 	if (counter == (38)) {
// 		if(servo1 > 0) clr(SERVO1_PORT,SERVO1_PIN);
// 		if(servo2 > 0) clr(SERVO2_PORT,SERVO2_PIN);
// 		if(servo3 > 0) clr(SERVO3_PORT,SERVO3_PIN);
// 		if(servo4 > 0) clr(SERVO4_PORT,SERVO4_PIN);
// 	}
// 
// 	counter++;
// 	if (counter==40) counter=0;
// }

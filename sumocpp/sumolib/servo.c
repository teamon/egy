/**
 * Funkcje do sterowania serwomechanizmami
 */

#include "sumolib.h"

// licznik
volatile unsigned char counter=0;

/**
 * Konfiguracja serwomechanizmów
 * 0 - serwo wyłączone
 * 1 - serwo stoi
 * 2 - serwo obraca się w przód
 * 3 - serwo obraca się w tył
 * 4 - kalibracja serwa
 */
volatile unsigned char servo1=0;
volatile unsigned char servo2=0;
volatile unsigned char servo3=0;
volatile unsigned char servo4=0;


/**
 * Inicjalizacja serwomechanizmów 1-4
 * UWAGA: zajmuje timer0
 */
void servo_init() {
	
	// Włączenie przerwania od timera 0
	TIMSK = _BV(TOIE0);
	// konfiguracja preskalera
	TCNT0 = TIMER0_BEGIN_VALUE;
	// konfiguracja timera
	TCCR0 = T0_CONF;
	sei();
	
	// Konfiguracja portów
	setb(SERVO1_DDR, SERVO1_PIN);
	setb(SERVO2_DDR, SERVO2_PIN);
	setb(SERVO3_DDR, SERVO3_PIN);
	setb(SERVO4_DDR, SERVO4_PIN);
	clr(SERVO1_PORT, SERVO1_PIN);
	clr(SERVO2_PORT, SERVO2_PIN);
	clr(SERVO3_PORT, SERVO3_PIN);
	clr(SERVO4_PORT, SERVO4_PIN);
	
	// logiczne włączenie serw
	servo1=1;
	servo2=1;
	servo3=1;
	servo4=1;
	
}


/**
 * Uruchomienie serwomechanizmu 1
 * obroty w przód
 */
void servo1_forward() {
	if (!SERVO1_DIR_NEGATE)
		servo1 = 2;
	else 
		servo1 = 3;
}

/**
 * Uruchomienie serwomechanizmu 2
 * obroty w przód
 */
void servo2_forward() {
	if (!SERVO2_DIR_NEGATE)
		servo2 = 2;
	else 
		servo2 = 3;
}

/**
 * Uruchomienie serwomechanizmu 3
 * obroty w przód
 */
void servo3_forward() {
	if (!SERVO3_DIR_NEGATE)
		servo3 = 2;
	else 
		servo3 = 3;
}

/**
 * Uruchomienie serwomechanizmu 4
 * obroty w przód
 */
void servo4_forward() {
	if (!SERVO4_DIR_NEGATE)
		servo4 = 2;
	else 
		servo4 = 3;
}


/**
 * Uruchomienie serwomechanizmu 1
 * obroty w tył
 */
void servo1_backward() {
	if (!SERVO1_DIR_NEGATE)
		servo1 = 3;
	else 
		servo1 = 2;
}

/**
 * Uruchomienie serwomechanizmu 2
 * obroty w tył
 */
void servo2_backward() {
	if (!SERVO2_DIR_NEGATE)
		servo2 = 3;
	else 
		servo2 = 2;
}

/**
 * Uruchomienie serwomechanizmu 3
 * obroty w tył
 */
void servo3_backward() {
	if (!SERVO3_DIR_NEGATE)
		servo3 = 3;
	else 
		servo3 = 2;
}

/**
 * Uruchomienie serwomechanizmu 4
 * obroty w tył
 */
void servo4_backward() {
	if (!SERVO4_DIR_NEGATE)
		servo4 = 3;
	else 
		servo4 = 2;
}


/**
 * Zatrzymanie serwomechanizmu 1
 */
void servo1_stop() {
	servo1 = 1;
}

/**
 * Zatrzymanie serwomechanizmu 2
 */
void servo2_stop() {
	servo2 = 1;
}

/**
 * Zatrzymanie serwomechanizmu 3
 */
void servo3_stop() {
	servo3 = 1;
}

/**
 * Zatrzymanie serwomechanizmu 4
 */
void servo4_stop() {
	servo4 = 1;
}

/**
 * Kalibracja serwomechanizmu 1
 */
void servo1_calibrate() {
	servo1 = 4;
}

/**
 * Kalibracja serwomechanizmu 2
 */
void servo2_calibrate() {
	servo2 = 4;
}

/**
 * Kalibracja serwomechanizmu 3
 */
void servo3_calibrate() {
	servo3 = 4;
}

/**
 * Kalibracja serwomechanizmu 4
 */
void servo4_calibrate() {
	servo4 = 4;
}

/**
 * Obsługa przerwania od timera 0
 */
SIGNAL (SIG_OVERFLOW0)
{
	 TCNT0 = TIMER0_BEGIN_VALUE;

	 // dla 17 milisekundy
	 if (counter == (34)) {
        if(servo1 > 1) 
        	setb(SERVO1_PORT,SERVO1_PIN);
        if(servo2 > 1) 
        	setb(SERVO2_PORT,SERVO2_PIN);
        if(servo3 > 1) 
        	setb(SERVO3_PORT,SERVO3_PIN);
        if(servo4 > 1)
        	setb(SERVO4_PORT,SERVO4_PIN);
    }
   
	// dla 18 milisekundy
    if (counter == (36)) {  
       if(servo1 == 2)
    	   clr(SERVO1_PORT,SERVO1_PIN);
       if(servo2 == 2)
    	   clr(SERVO2_PORT,SERVO2_PIN);
       if(servo3 == 2)
    	   clr(SERVO3_PORT,SERVO3_PIN);
       if(servo4 == 2)
    	   clr(SERVO4_PORT,SERVO4_PIN);
    }

   // dla 18,5 milisekundy
   if (counter == (37)) {  
      if(servo1 == 4)
    	  clr(SERVO1_PORT,SERVO1_PIN);
      if(servo2 == 4)
    	  clr(SERVO2_PORT,SERVO2_PIN);
      if(servo3 == 4)
    	  clr(SERVO3_PORT,SERVO3_PIN);
      if(servo4 == 4)
    	  clr(SERVO4_PORT,SERVO4_PIN);
   }
  
   // dla 19 milisekundy
   if (counter == (38)) {
	   if(servo1 > 0) 
		   clr(SERVO1_PORT,SERVO1_PIN);
	   if(servo2 > 0) 
		   clr(SERVO2_PORT,SERVO2_PIN);
	   if(servo3 > 0) 
		   clr(SERVO3_PORT,SERVO3_PIN);
	   if(servo4 > 0) 
		   clr(SERVO4_PORT,SERVO4_PIN);
   }
   
   counter++;
   if (counter==40) 
	   counter=0;
	 
}


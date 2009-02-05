/**
 * Funkcje do sterowania silnikiem prądu stałego
 */

#include "sumolib.h"

// moc silnika 1
unsigned int motor1_power_config = 0;
// moc silnika 2
unsigned int motor2_power_config = 0;

/**
 * Inicjalizacja prostej obsługi silników
 */
void motor_init() {
	setb(MOTOR1_PWM_DDR, MOTOR1_PWM_PIN);
	setb(MOTOR2_PWM_DDR, MOTOR2_PWM_PIN);
	setb(MOTOR1_DIR_DDR, MOTOR1_DIR_PIN);
	setb(MOTOR2_DIR_DDR, MOTOR2_DIR_PIN);
	
	// ustawienie rejestrów
	TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(WGM11) | _BV(WGM10);
	if (MOTOR1_PWM_NEGATE) {
		TCCR1A |= _BV(COM1A0);
	}
	if (MOTOR2_PWM_NEGATE) {
		TCCR1A |= _BV(COM1B0);
	}
	OCR1A = 0;
	OCR1B = 0;
	TCCR1B = 0x00; 
	TCCR1B |= PWM_PRESCALLER_CONFIG;
	
	// ustawienie stanów początkowych wyjść DIR
	if (!MOTOR1_DIR_NEGATE)
		clr(MOTOR1_DIR_PORT, MOTOR1_DIR_PIN);
	else
		setb(MOTOR1_DIR_PORT, MOTOR1_DIR_PIN);
	
	if (!MOTOR2_DIR_NEGATE)
		clr(MOTOR2_DIR_PORT, MOTOR2_DIR_PIN);
	else
		setb(MOTOR2_DIR_PORT, MOTOR2_DIR_PIN);
	
	// ustawianie mocy
	motor1_set_power(MOTOR1_DEFAULT_POWER);
	motor2_set_power(MOTOR2_DEFAULT_POWER);
	
}

/**
 * Ustawia moc silnika 1 wyrażoną w %
 */
void motor1_set_power(unsigned char power) {
	if (power < MOTOR1_MAX_POWER) {
		motor1_power_config = power * 10;
	} else {
		motor1_power_config = MOTOR1_MAX_POWER * 10;
	}
}

/**
 * Ustawia moc silnika 2 wyrażoną w %
 */
void motor2_set_power(unsigned char power) {
	if (power < MOTOR2_MAX_POWER) {
		motor2_power_config = power * 10;
	} else {
		motor2_power_config = MOTOR2_MAX_POWER * 10;
	}
}

/**
 * Zatrzymanie silnika 1
 */
void motor1_stop() {
	OCR1B = 0;
}

/**
 * Zatrzymanie silnika 2
 */
void motor2_stop() {
	OCR1A = 0;
}

/**
 * Uruchomienie silnika 1
 * obroty w przód
 */
void motor1_forward() {
	// zatrzymanie silnika
	motor1_stop();
	
	// opóźnienie	
	if (MOTOR1_DELAY > 0) {
		wait_ms(MOTOR1_DELAY);
	} else {
		wait_ms(1);
	}
	
	// ustawienie kierunku
	if (!MOTOR1_DIR_NEGATE)
		clr(MOTOR1_DIR_PORT, MOTOR1_DIR_PIN);
	else
		setb(MOTOR1_DIR_PORT, MOTOR1_DIR_PIN);

	// opóźnienie	
	if (MOTOR1_DELAY > 0) {
		wait_ms(MOTOR1_DELAY);
	} else {
		wait_ms(1);
	}
	
	// uruchomienie silnika
	OCR1B = motor1_power_config;
}

/**
 * Uruchomienie silnika 2
 * obroty w przód
 */
void motor2_forward() {
	// zatrzymanie silnika
	motor2_stop();
	
	// opóźnienie
	if (MOTOR2_DELAY > 0) {
		wait_ms(MOTOR2_DELAY);
	} else {
		wait_ms(1);
	}
	
	// ustawienie kierunku
	if (!MOTOR2_DIR_NEGATE)
		clr(MOTOR2_DIR_PORT, MOTOR2_DIR_PIN);
	else
		setb(MOTOR2_DIR_PORT, MOTOR2_DIR_PIN);
	
	// opóźnienie
	if (MOTOR2_DELAY > 0) {
		wait_ms(MOTOR2_DELAY);
	} else {
		wait_ms(1);
	}	
	
	// uruchomienie silnika
	OCR1A = motor2_power_config;
}


/**
 * Uruchomienie silnika 1
 * obroty w tył
 */
void motor1_backward() {
	// zatrzymanie silnika
	motor1_stop();
	
	// opóźnienie	
	if (MOTOR1_DELAY > 0) {
		wait_ms(MOTOR1_DELAY);
	} else {
		wait_ms(1);
	}
	
	// ustawienie kierunku
	if (!MOTOR1_DIR_NEGATE)
		setb(MOTOR1_DIR_PORT, MOTOR1_DIR_PIN);
	else
		clr(MOTOR1_DIR_PORT, MOTOR1_DIR_PIN);

	// opóźnienie	
	if (MOTOR1_DELAY > 0) {
		wait_ms(MOTOR1_DELAY);
	} else {
		wait_ms(1);
	}	
	
	// uruchomienie silnika
	OCR1B = motor1_power_config;
}

/**
 * Uruchomienie silnika 2
 * obroty w tył
 */
void motor2_backward() {
	// zatrzymanie silnika
	motor2_stop();
	
	// opóźnienie	
	if (MOTOR2_DELAY > 0) {
		wait_ms(MOTOR2_DELAY);
	} else {
		wait_ms(1);
	}

	// ustawienie kierunku
	if (!MOTOR2_DIR_NEGATE)
		setb(MOTOR2_DIR_PORT, MOTOR2_DIR_PIN);
	else
		clr(MOTOR2_DIR_PORT, MOTOR2_DIR_PIN);
	
	// opóźnienie
	if (MOTOR2_DELAY > 0) {
		wait_ms(MOTOR2_DELAY);
	} else {
		wait_ms(1);
	}	
	
	// uruchomienie silnika
	OCR1A = motor2_power_config;
}

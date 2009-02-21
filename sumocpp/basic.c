/**
 * Program podstawowy robota minisumo
 */

// dołączenie biblioteki
#include "sumolib/sumolib.h"

// deklaracje funkcji
// funkcja inicjalizująca procesor i podzespoły elektroniczne
void initialization();
// funkcja wysyłająca stan czujników na diody
void send_sensors_state_on_leds();
// funkcja wysyłająca stan czujników na port szeregowy
void send_sensors_state_on_usart();
// funkcja podejmująca decyzję, jaki ruch wykonać
void choose_move();
// funkcja wysyłająca na port szeregowy informacje o aktualnym manewrze
void send_move_on_usart();
// funkcja ustawia ruch
void set_move(unsigned char move, unsigned char iteration_number);
// funkcja wykonująca manewr
void execute_move();

// wartości stałe
// próg widzenia czujnika odległości 1 - lewy przedni
#define DIST1_RANGE 35
// próg widzenia czujnika odległości 2 - prawy przedni
#define DIST2_RANGE 35
// próg widzenia czujnika odległości 3 - tylny
#define DIST3_RANGE 45
// czas trwania jednej iteracji w ms
#define ITERATION_TIME 50
// ilość iteracji pomiędzy wysyłaniem stanów czujników na port szeregowy
#define NUMBER_OF_ITERATIONS_FOR_USART 10
// moc silników używana podczas szukania przeciwnika
#define SEARCHING_POWER 50
// moc silników używana podczas ataku
#define ATTACK_POWER 60
// ilość iteracji namierzania celu
#define TIME_FOR_SEARCH_TARGET 30
// ilość iteracji ucieczki od linii po prostej
#define TIME_FOR_ESCAPE_STRAIGHT 200
// ilość iteracji ucieczki od linii w bok
#define TIME_FOR_ESCAPE_ON_SIDE 10
// ilość iteracji obrotu
#define TIME_FOR_ROTATE 70
// ilość iteracji ataku
#define TIME_FOR_ATTACK 10
// minimalna losowa ilość iteracji
#define RANDOM_MIN_TIME 10
// maksymalna losowa ilość iteracji
#define RANDOM_MAX_TIME 50


// zdefiniowane stałe
// rodzaje ruchów
#define MOVE_STOP 0
#define MOVE_FORWARD 1
#define MOVE_BACKWARD 2
#define MOVE_RIGHT_FORWARD 3
#define MOVE_RIGHT_BACKWARD 4
#define MOVE_LEFT_FORWARD 5
#define MOVE_LEFT_BACKWARD 6
#define MOVE_ROTATION_RIGHT 7
#define MOVE_ROTATION_LEFT 8
#define MOVE_ATTACK 9



// zmienne globalne
// ilość iteracji które minęły od ostatniego wysłania informacji na port szeregowy
unsigned char iteration_number_for_usart = 0;
// aktualnie wykonywany ruch
unsigned char actual_move = MOVE_STOP;
// ilość iteracji do końca ruchu
unsigned char iteration_number_to_end_move = 0;

// program główny
int main() {
	
	// inicjalizacja
	initialization();
	
	// wystawienie sygnału kalibrującego serwa
	servo3_calibrate();
	
	// wysłanie informacji na port szeregowy (RS-232)
	usart_write_progmem_string(PSTR("ZASILANIE WLACZONE\n\r"));
	usart_write_progmem_string(PSTR("OCZEKIWANIE NA NACISNIECIE PRZYCISKU\n\r"));
	
	
	// pętla oczekiwania na naciśnięcie przycisku
	while((switch1_pressed() == 0) && (switch2_pressed() == 0)) {
		// wysyłanie stanów czujników na doidy
		send_sensors_state_on_leds();
		// wysyłanie stanów czujników na port szeregowy
		if (iteration_number_for_usart >= NUMBER_OF_ITERATIONS_FOR_USART) {
			iteration_number_for_usart = 0;
			send_sensors_state_on_usart();
		}
		iteration_number_for_usart++;
		// opóźnienie
		wait_ms(ITERATION_TIME);
	}
	
	// jeśli został naciśnięty przycisk 
	// wysłanie informacji na port szeregowy (RS-232)
	usart_write_progmem_string(PSTR("ROZPOCZECIE ODLICZANIA\n\r"));
	// wygaszenie diod
	sled_set(0x00);
	// odliczanie 
	sled1_on();
	usart_write_progmem_string(PSTR("5\n\r"));
	wait_s(1);
	sled2_on();
	usart_write_progmem_string(PSTR("4\n\r"));
	wait_s(1);
	sled3_on();
	usart_write_progmem_string(PSTR("3\n\r"));
	wait_s(1);
	sled4_on();
	usart_write_progmem_string(PSTR("2\n\r"));
	wait_s(1);
	sled5_on();
	usart_write_progmem_string(PSTR("1\n\r"));
	wait_s(1);
	
	// gaszenie diod 
	sled_set(0x00);
	// zapalenie diody 8 (trwa walka)
	sled8_on();
	// wysłanie informacji na port szeregowy (RS-232)
	usart_write_progmem_string(PSTR("ROZPOCZECIE WALKI\n\r"));
	
	
	for(;;) {
		// podjęcie decyzji o ruchu
		choose_move();
		// wykonanie ruchu
		execute_move();
		
		// wysyłanie stanów czujników na doidy
		send_sensors_state_on_leds();
		// wysyłanie stanów czujników i wykonywanego ruchu na port szeregowy
		if (iteration_number_for_usart >= NUMBER_OF_ITERATIONS_FOR_USART) {
			iteration_number_for_usart = 0;
			send_sensors_state_on_usart();
			send_move_on_usart();
		}
		iteration_number_for_usart++;
		
		// opóźnienie
		wait_ms(ITERATION_TIME);
	}
	
}


// funkcja inicjalizująca procesor i podzespoły elektroniczne
void initialization() {
	// inicjalizacja generatora liczb pseudolosowych
	random_init();
	// inicjalizacja diod swiecących
	sled_init();
	// inicjalizacja przycisków
	switch_init();
	// inicjalizacja transmisji szeregowej
	usart_init();
	// inicjalizacja czujników podłoża
	ground_init();
	// inicjalizacja czujników odległości
	dist_init();
	// inicjalizacja obsługi serwomechanizmów (SRV1, SRV2)
	servo_init();
	// inicjalizacja obsługi silników DC
	motor_init();
}


// funkcja wysyłająca stan czujników na diody
void send_sensors_state_on_leds() {
	// sprawdzanie stanów czujników podłoża i zapalanie odpowiednich diod
	// jeśli czujnik wykrył linię to zapal diodę
	// czujnik GRD 1
	if (ground1_detected()) {
		sled1_on();
	} else {
		sled1_off();
	}
	// czujnik GRD 2
	if (ground2_detected()) {
		sled2_on();
	} else {
		sled2_off();
	}
	// czujnik GRD 3
	if (ground3_detected()) {
		sled3_on();
	} else {
		sled3_off();
	}
	// czujnik GRD 4
	if (ground4_detected()) {
		sled4_on();
	} else {
		sled4_off();
	}
	// sprawdzanie stanów czujników odległości i zapalanie odpowiednich diod
	// czujnik DIST 1
	if (dist1_value() >= DIST1_RANGE) {
		sled5_on();
	} else {
		sled5_off();
	}
	// czujnik DIST 2
	if (dist2_value() >= DIST2_RANGE) {
		sled6_on();
	} else {
		sled6_off();
	}
	// czujnik DIST 3
	if (dist3_value() >= DIST3_RANGE) {
		sled7_on();
	} else {
		sled7_off();
	}
}

// funkcja wysyłająca stan czujników na port szeregowy
void send_sensors_state_on_usart() {
	// sprawdzanie stanów czujników podłoża i wysyłanie ich na port szeregowy
	// czujnik GRD 1
	if (ground1_detected()) {
		usart_write_progmem_string(PSTR("GRD1:1 "));
	} else {
		usart_write_progmem_string(PSTR("GRD1:0 "));
	}
	// czujnik GRD 2
	if (ground2_detected()) {
		usart_write_progmem_string(PSTR("GRD2:1 "));
	} else {
		usart_write_progmem_string(PSTR("GRD2:0 "));
	}
	// czujnik GRD 3
	if (ground3_detected()) {
		usart_write_progmem_string(PSTR("GRD3:1 "));
	} else {
		usart_write_progmem_string(PSTR("GRD3:0 "));
	}
	// czujnik GRD 4
	if (ground4_detected()) {
		usart_write_progmem_string(PSTR("GRD4:1 "));
	} else {
		usart_write_progmem_string(PSTR("GRD4:0 "));
	}
	// sprawdzanie stanów czujników podłoża i wysyłanie ich na port szeregowy
	// czujnik DIST 1
	usart_write_progmem_string(PSTR("DIST1: "));
	usart_write_number(dist1_value());
	// czujnik DIST 3		
	usart_write_progmem_string(PSTR(" DIST2: "));
	usart_write_number(dist2_value());
	// czujnik DIST 3		
	usart_write_progmem_string(PSTR(" DIST3: "));
	usart_write_number(dist3_value());
	// wysyłanie znaku końca linii
	usart_write_progmem_string(PSTR("\n\r"));
}

// funkcja podejmująca decyzję, jaki ruch wykonać
void choose_move() {
	//jeśli którykolwiek czujnik podłoża coś wykrył
	if(ground1_detected() || ground2_detected() || ground3_detected() || ground4_detected())
	{	
		// sprawdź czy dwa przednie - linia z przodu
		if (ground1_detected() && ground2_detected()) {
			set_move(MOVE_BACKWARD, TIME_FOR_ESCAPE_STRAIGHT);
			usart_write_progmem_string(PSTR("UCIECZKA OD LINII Z PRZODU\n\r"));
			return;
		}
		// sprawdź czy dwa tylne - linia z tyłu
		if (ground3_detected() && ground4_detected()) {
			set_move(MOVE_FORWARD, TIME_FOR_ESCAPE_STRAIGHT);
			usart_write_progmem_string(PSTR("UCIECZKA OD LINII Z TYLU\n\r"));
			return;
		}
		// linia z przodu po lewej
		if (ground1_detected()) {
			set_move(MOVE_RIGHT_BACKWARD, TIME_FOR_ESCAPE_ON_SIDE);
			usart_write_progmem_string(PSTR("UCIECZKA OD LINII Z PRZODU PO LEWEJ\n\r"));
			return;
		}
		// linia z przodu po prawej
		if (ground2_detected()) {
			set_move(MOVE_LEFT_BACKWARD, TIME_FOR_ESCAPE_ON_SIDE);
			usart_write_progmem_string(PSTR("UCIECZKA OD LINII Z PRZODU PO PRAWEJ\n\r"));			
			return;
		}	
		// linia z tyłu po lewej
		if (ground3_detected()) {
			set_move(MOVE_RIGHT_FORWARD, TIME_FOR_ESCAPE_ON_SIDE);
			usart_write_progmem_string(PSTR("UCIECZKA OD LINII Z TYLU PO LEWEJ\n\r"));
			return;
		}
		// linia z tyłu po prawej
		if (ground4_detected()) {
			set_move(MOVE_LEFT_FORWARD, TIME_FOR_ESCAPE_ON_SIDE);
			usart_write_progmem_string(PSTR("UCIECZKA OD LINII Z TYLU PO PRAWEJ\n\r"));
			return;
		}
	}
	//jeśli którykolwiek czujnik odległości coś wykrył
	else if (dist1_value() > DIST1_RANGE || dist2_value() > DIST2_RANGE || dist3_value() > DIST3_RANGE){
		// przeciwnik na wprost, atak
		if (dist1_value() > DIST1_RANGE && dist2_value() > DIST2_RANGE) {
			set_move(MOVE_ATTACK, TIME_FOR_ATTACK);
			usart_write_progmem_string(PSTR("ATAKAKOWANIE PRZECIWNIKA NA WPROST\n\r"));
			return;
		}
		// przeciwnik po lewej
		if (dist1_value() > DIST1_RANGE ) {
			set_move(MOVE_LEFT_FORWARD, TIME_FOR_SEARCH_TARGET);
			usart_write_progmem_string(PSTR("NAMIERZANIE PRZECIWNIKA PO LEWEJ\n\r"));
			return;
		}	
		// przeciwnik po prawej
		if (dist2_value() > DIST2_RANGE ) {
			set_move(MOVE_RIGHT_FORWARD, TIME_FOR_SEARCH_TARGET);
			usart_write_progmem_string(PSTR("NAMIERZANIE PRZECIWNIKA PO PRAWEJ\n\r"));
			return;
		}	
		// przeciwnik z tyłu
		if (dist3_value() > DIST3_RANGE ) {
			set_move(MOVE_ROTATION_RIGHT, TIME_FOR_ROTATE);
			usart_write_progmem_string(PSTR("NAMIERZANIE PRZECIWNIKA Z TYLU\n\r"));			
			return;			
		}	
		
	}
	// jeśli żaden czujnik nic nie wykrył
	else {
		// jeśli manewr został zakończony
		if (actual_move == MOVE_STOP) {
			unsigned char random_move = random(8) + 1;
			unsigned char iteration_number = RANDOM_MIN_TIME + random(RANDOM_MAX_TIME - RANDOM_MIN_TIME);
			set_move(random_move, iteration_number);
			usart_write_progmem_string(PSTR("LOSOWANIE RUCHU\n\r"));		
		}
	}

}

// funkcja wysyłająca na port szeregowy informacje o aktualnym manewrze
void send_move_on_usart() {
	usart_write_progmem_string(PSTR("RUCH: "));
	// wysyłanie aktualnie wykonywanego ruchu
	switch (actual_move) {
		case MOVE_STOP:
			usart_write_progmem_string(PSTR("STOP\n\r"));
			break;
		case MOVE_FORWARD:
			usart_write_progmem_string(PSTR("JAZDA DO PRZODU\n\r"));
			break;	
		case MOVE_BACKWARD:
			usart_write_progmem_string(PSTR("JAZDA DO TYLU\n\r"));
			break;
		case MOVE_LEFT_FORWARD:
			usart_write_progmem_string(PSTR("SKRET W LEWO\n\r"));
			break;
		case MOVE_RIGHT_FORWARD:
			usart_write_progmem_string(PSTR("SKRET W PRAWO\n\r"));
			break;	
		case MOVE_LEFT_BACKWARD:
			usart_write_progmem_string(PSTR("COFANIE W LEWO\n\r"));
			break;
		case MOVE_RIGHT_BACKWARD:
			usart_write_progmem_string(PSTR("COFANIE W PRAWO\n\r"));
			break;
		case MOVE_ROTATION_LEFT:
			usart_write_progmem_string(PSTR("OBROT W LEWO\n\r"));
			break;	
		case MOVE_ROTATION_RIGHT:
			usart_write_progmem_string(PSTR("OBROT W PRAWO\n"));
			break;			
			
		default:
			break;
	}
	
}

// funkcja ustawia ruch
void set_move(unsigned char move, unsigned char iteration_number) {
	actual_move = move;
	iteration_number_to_end_move = iteration_number;
}

// funkcja wykonująca manewr
void execute_move() {
	// sprawdzanie czy manewr powinien się skończyć
	if (iteration_number_to_end_move == 0) {
		actual_move = MOVE_STOP;
	}
	
	switch (actual_move) {
		case MOVE_STOP:
			servo1_stop();
			servo2_stop();
			motor1_stop();
			motor2_stop();
			break;
		case MOVE_FORWARD:
			servo1_forward();
			servo2_backward();
			motor1_set_power(SEARCHING_POWER);
			motor2_set_power(SEARCHING_POWER);
			motor1_forward();
			motor2_forward();
			break;	
		case MOVE_BACKWARD:
			servo1_backward();
			servo2_forward();
			motor1_set_power(SEARCHING_POWER);
			motor2_set_power(SEARCHING_POWER);
			motor1_backward();
			motor2_backward();
			break;	
		case MOVE_RIGHT_FORWARD:
			servo1_forward();
			servo2_stop();
			motor1_set_power(SEARCHING_POWER);
			motor2_set_power(SEARCHING_POWER);
			motor1_forward();
			motor2_stop();
			break;
		case MOVE_RIGHT_BACKWARD:
			servo1_backward();
			servo2_stop();
			motor1_set_power(SEARCHING_POWER);
			motor2_set_power(SEARCHING_POWER);
			motor1_backward();
			motor2_stop();
			break;	
		case MOVE_LEFT_FORWARD:
			servo1_stop();
			servo2_backward();
			motor1_set_power(SEARCHING_POWER);
			motor2_set_power(SEARCHING_POWER);
			motor1_stop();
			motor2_forward();
			break;
		case MOVE_LEFT_BACKWARD:
			servo1_stop();
			servo2_forward();
			motor1_set_power(SEARCHING_POWER);
			motor2_set_power(SEARCHING_POWER);
			motor1_stop();
			motor2_backward();
			break;
		case MOVE_ROTATION_RIGHT:
			servo1_forward();
			servo2_forward();
			motor1_set_power(SEARCHING_POWER);
			motor2_set_power(SEARCHING_POWER);
			motor1_forward();
			motor2_backward();
			break;	
		case MOVE_ROTATION_LEFT:
			servo1_backward();
			servo2_backward();
			motor1_set_power(SEARCHING_POWER);
			motor2_set_power(SEARCHING_POWER);
			motor1_backward();
			motor2_forward();
			break;	
		case MOVE_ATTACK:
			servo1_forward();
			servo2_backward();
			motor1_set_power(ATTACK_POWER);
			motor2_set_power(ATTACK_POWER);
			motor1_forward();
			motor2_forward();
			break;	
		default:
			break;
	}
	
	// dekrementacja ilości pozostałych taktów
	if (iteration_number_to_end_move > 0) {
		iteration_number_to_end_move--;
	}
}


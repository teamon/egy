/**
 * Plik konfiguracyjny biblioteki
 * 
 */

/**
 * Opis wyprowadzeń procesora
 * 
 * PORTA
 * 		0 - DIST1 - czujnik odległości
 * 		1 - DIST2 - czujnik odległości
 * 		2 - DIST3 - czujnik odległości
 * 		3 - DIST4 - czujnik odległości
 * 		4 - AIN1 - wejscie analogowe
 * 		5 - AIN2 - wejscie analogowe
 * 		6 - AIN3 - wejście analogowe
 * 		7 - AIN4 - wejście analogowe
 * 
 * PORTB
 * 		0 - GROUND1 - czujnik podłoża
 * 		1 - GROUND2 - czujnik podłoża
 * 		2 - GROUND3 - czujnik podłoża
 * 		3 - GROUND4 - czujnik podłoża
 * 		4 - SLED_LE - wyjscie sterownika diod
 * 		5 - MOSI - używany do programowania
 * 		6 - MISO - używany do programowania
 * 		7 - SCK - używany do programowania
 * 
 * PORTC
 * 		0 - M1_DIR - kierunek obrotów silnika
 * 		1 - M2_DIR - kierunek obrotów silnika
 * 		2 - SERVO1 - wyjśćie serwomechanizmu
 * 		3 - SERVO2 - wyjśćie serwomechanizmu
 * 		4 - SERVO3 - wyjśćie serwomechanizmu
 * 		5 - SERVO4 - wyjśćie serwomechanizmu
 * 		6 - SLED_CLK - wyjśćie sterownika diod
 * 		7 - SLED_SDI - wyjśćie sterownika diod
 * 
 * PORTD
 * 		0 - RXD - port szeregowy
 * 		1 - TXD - port szeregowy
 * 		2 - SWITCH1 - przycisk
 * 		3 - SWITCH2 - przycisk
 * 		4 - M1_PWM - start/stop silnika
 * 		5 - M2_PWM - start/stop silnika
 * 		6 - SIG - sygnał do wykorzystania
 * 		7 - GRD_PWM - regulacja mocy diod czujników podłoża
 * 
 */



#ifndef SUMOCONFIG_H_
#define SUMOCONFIG_H_

/**
 * Częstotliwość kwarcu
 */
#define F_CPU 7372800L

/**
 * Prędkość transmisji po RSie
 */
#define USART_SPEED 9600L


/**
 * Port wyjścia PWM silnika 1
 */
#define MOTOR1_PWM_PORT PORTD

/**
 * Rejestr kierunku portu wyjścia PWM silnika 1
 */
#define MOTOR1_PWM_DDR DDRD

/**
 * Linia portu wyjścia PWM silnika 1
 */
#define MOTOR1_PWM_PIN 5

/** 
 * Negacja stanu aktywnego silnika 1
 * 0 - brak negacji
 * 1 - negacja
 */
#define MOTOR1_PWM_NEGATE 1

/**
 * Opóźnienie pomiędzy przełączaniem kierunków ruchu silnika 1
 * podawane w ms
 * Uwaga: musi być większe od 0
 */
#define MOTOR1_DELAY 2

/**
 * Maksymalna moc silnika 1 wyrażona w % 
 */
#define MOTOR1_MAX_POWER 100

/**
 * Domyślna moc silnika 1 wyrażona w % 
 */
#define MOTOR1_DEFAULT_POWER 30

/**
 * Port wyjścia kierunku silnika 1
 */
#define MOTOR1_DIR_PORT PORTC

/**
 * Rejestr kierunku portu wyjścia kierunku silnika 1
 */
#define MOTOR1_DIR_DDR DDRC

/**
 * Linia portu wyjścia kierunku silnika 1
 */
#define MOTOR1_DIR_PIN 1

/** 
 * Negacja kierunku ruchu silnika 1
 * 0 - brak negacji
 * 1 - negacja
 */
#define MOTOR1_DIR_NEGATE 0



/**
 * Port wyjścia PWM silnika 2
 */
#define MOTOR2_PWM_PORT PORTD

/**
 * Rejestr kierunku portu wyjścia PWM silnika 2
 */
#define MOTOR2_PWM_DDR DDRD

/**
 * Linia portu wyjścia PWM silnika 2
 * (musi być wyjście kanału PWM)
 */
#define MOTOR2_PWM_PIN 4

/** 
 * Negacja stanu aktywnego silnika 2
 * 0 - brak negacji
 * 1 - negacja
 */
#define MOTOR2_PWM_NEGATE 1

/**
 * Opóźnienie pomiędzy przełączaniem kierunków ruchu silnika 2
 * podawane w ms
 * Uwaga: musi być większe od 0
 */
#define MOTOR2_DELAY 2

/**
 * Maksymalna moc silnika 2 wyrażona w % 
 */
#define MOTOR2_MAX_POWER 100

/**
 * Domyślna moc silnika 2 wyrażona w % 
 */
#define MOTOR2_DEFAULT_POWER 30

/**
 * Port wyjścia kierunku silnika 2
 */
#define MOTOR2_DIR_PORT PORTC

/**
 * Rejestr kierunku portu wyjścia kierunku silnika 2
 */
#define MOTOR2_DIR_DDR DDRC

/**
 * Linia portu wyjścia kierunku silnika 2
 */
#define MOTOR2_DIR_PIN 0

/** 
 * Negacja kierunku ruchu silnika 2
 * 0 - brak negacji
 * 1 - negacja
 */
#define MOTOR2_DIR_NEGATE 0



/**
 * Port serwomechanozmu 1
 */
#define SERVO1_PORT PORTC

/**
 * Rejestr kierunku portu serwomechanozmu 1
 */
#define SERVO1_DDR DDRC

/**
 * Linia portu serwomechanozmu 1
 */
#define SERVO1_PIN 3

/** 
 * Negacja kierunku ruchu serwomechanizmu 1
 * 0 - brak negacji
 * 1 - negacja
 */
#define SERVO1_DIR_NEGATE 0


/**
 * Port serwomechanozmu 2
 */
#define SERVO2_PORT PORTC

/**
 * Rejestr kierunku portu serwomechanozmu 2
 */
#define SERVO2_DDR DDRC

/**
 * Linia portu serwomechanozmu 1
 */
#define SERVO2_PIN 2

/** 
 * Negacja kierunku ruchu serwomechanizmu 2
 * 0 - brak negacji
 * 1 - negacja
 */
#define SERVO2_DIR_NEGATE 0


/**
 * Port serwomechanozmu 3
 */
#define SERVO3_PORT PORTC

/**
 * Rejestr kierunku portu serwomechanozmu 3
 */
#define SERVO3_DDR DDRC

/**
 * Linia portu serwomechanozmu 3
 */
#define SERVO3_PIN 5

/** 
 * Negacja kierunku ruchu serwomechanizmu 3
 * 0 - brak negacji
 * 1 - negacja
 */
#define SERVO3_DIR_NEGATE 0


/**
 * Port serwomechanozmu 4
 */
#define SERVO4_PORT PORTC

/**
 * Rejestr kierunku portu serwomechanozmu 4
 */
#define SERVO4_DDR DDRC

/**
 * Linia portu serwomechanozmu 4
 */
#define SERVO4_PIN 4

/** 
 * Negacja kierunku ruchu serwomechanizmu 4
 * 0 - brak negacji
 * 1 - negacja
 */
#define SERVO4_DIR_NEGATE 0


/**
 * Port czujników odległości
 * (musi być port z wejściami analogowymi)
 */
#define DIST_POTR PORTA

/**
 * Rejestr kierunku portu czujników odległości
 */
#define DIST_DDR DDRA

/**
 * Linie czujników odległości
 */
#define DIST1_PIN 0
#define DIST2_PIN 1
#define DIST3_PIN 2
#define DIST4_PIN 3
#define DIST5_PIN 4
#define DIST6_PIN 5
#define DIST7_PIN 6
#define DIST8_PIN 7


/**
 * Port czujników podłoża
 */
#define GROUND_PORT PORTB

/**
 * Rejestr kierunku portu czujników podłaża
 */
#define GROUND_DDR DDRB

/**
 * Rejestr wejściowy portu czujników podłaża
 */
#define GROUND_PINPORT PINB

/**
 * Linie czujników podłoża
 */
#define GROUND1_PIN 0
#define GROUND2_PIN 1
#define GROUND3_PIN 2
#define GROUND4_PIN 3

/**
 * Negacja wartości zwracanej przez funkcje wykrywające podloże
 * 0 - brak negacji
 * 1 - negacja
 */
#define GROUND_NEGATE 0

/**
 * Port mocy czujników podłoża
 */
#define GROUND_PWN_PORT PORTD

/**
 * Rejestr kierunku portu mocy czujników podłaża
 */
#define GROUND_PWM_DDR DDRD


/**
 * Linia portu mocy czujników podłoża
 */
#define GROUND_PWM 7



/**
 * Port przycisku 1
 */
#define SWITCH1_PORT PORTD

/**
 * Rejestr kierunku portu przycisku 1
 */
#define SWITCH1_DDR PORTD

/**
 * Rejestr wejściowy portu przycisku 1
 */
#define SWITCH1_PINPORT PIND

/**
 * linia portu przycisku 1
 */
#define SWITCH1_PIN 2

/**
 * Port przycisku 2
 */
#define SWITCH2_PORT PORTD

/**
 * Rejestr kierunku portu przycisku 2
 */
#define SWITCH2_DDR PORTD

/**
 * Rejestr wejściowy portu przycisku 2
 */
#define SWITCH2_PINPORT PIND

/**
 * linia portu przycisku 2
 */
#define SWITCH2_PIN 3



/**
 * Port danych sterownika diod LED
 */
#define SLED_SDI_PORT PORTC

/**
 * Rejestr kierunku portu danych sterownika diod LED
 */
#define SLED_SDI_DDR DDRC

/**
 * Linia portu danych sterownika diod LED
 */
#define SLED_SDI_PIN 7


/**
 * Port danych sterownika diod LED
 */
#define SLED_CLK_PORT PORTC

/**
 * Rejestr kierunku portu danych sterownika diod LED
 */
#define SLED_CLK_DDR DDRC

/**
 * Linia portu danych sterownika diod LED
 */
#define SLED_CLK_PIN 6


/**
 * Port zatrzasku sterownika diod LED
 */
#define SLED_LE_PORT PORTB

/**
 * Rejestr kierunku portu zatrzasku sterownika diod LED
 */
#define SLED_LE_DDR DDRB

/**
 * Linia portu zatrzasku sterownika diod LED
 */
#define SLED_LE_PIN 4


#endif /*SUMOCONFIG_H_*/

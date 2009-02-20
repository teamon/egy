#ifndef SUMO_H_
#define SUMO_H_

//kalman
#define KR 0.05
#define KQ 0.0003

/* Opis wyprowadzeń procesora
 *
 * PORTA
 *	 0 - DIST1 - czujnik odległości
 *	 1 - DIST2 - czujnik odległości
 *	 2 - DIST3 - czujnik odległości
 *	 3 - DIST4 - czujnik odległości
 *	 4 - AIN1 - wejscie analogowe
 *	 5 - AIN2 - wejscie analogowe
 *	 6 - AIN3 - wejście analogowe
 *	 7 - AIN4 - wejście analogowe
 * 
 * PORTB
 *	 0 - GROUND1 - czujnik podłoża
 *	 1 - GROUND2 - czujnik podłoża
 *	 2 - GROUND3 - czujnik podłoża
 *	 3 - GROUND4 - czujnik podłoża
 *	 4 - LED_LE - wyjscie sterownika diod
 *	 5 - MOSI - używany do programowania
 *	 6 - MISO - używany do programowania
 *	 7 - SCK - używany do programowania
 * 
 * PORTC
 *	 0 - M1_DIR - kierunek obrotów silnika
 *	 1 - M2_DIR - kierunek obrotów silnika
 *	 2 - SERVO1 - wyjśćie serwomechanizmu
 *	 3 - SERVO2 - wyjśćie serwomechanizmu
 *	 4 - SERVO3 - wyjśćie serwomechanizmu
 *	 5 - SERVO4 - wyjśćie serwomechanizmu
 *	 6 - LED_CLK - wyjśćie sterownika diod
 *	 7 - LED_SDI - wyjśćie sterownika diod
 *	
 * PORTD
 *	 0 - RXD - port szeregowy
 *	 1 - TXD - port szeregowy
 *	 2 - SWITCH1 - przycisk
 *	 3 - SWITCH2 - przycisk
 *	 4 - M1_PWM - start/stop silnika
 *	 5 - M2_PWM - start/stop silnika
 *	 6 - SIG - sygnał do wykorzystania
 *	 7 - GRD_PWM - regulacja mocy diod czujników podłoża
 *
 */



// Częstotliwość kwarcu
#define F_CPU 7372800L
// Prędkość transmisji po RSie
#define USART_SPEED 4800L


// Port wyjścia PWM silnika 1
#define MOTOR1_PWM_PORT PORTD
// Rejestr kierunku portu wyjścia PWM silnika 1
#define MOTOR1_PWM_DDR DDRD
// Linia portu wyjścia PWM silnika 1
#define MOTOR1_PWM_PIN 4
// Port wyjścia kierunku silnika 1
#define MOTOR1_DIR_PORT PORTC
// Rejestr kierunku portu wyjścia kierunku silnika 1
#define MOTOR1_DIR_DDR DDRC
// Linia portu wyjścia kierunku silnika 1
#define MOTOR1_DIR_PIN 0


// Port wyjścia PWM silnika 2
#define MOTOR2_PWM_PORT PORTD
// Rejestr kierunku portu wyjścia PWM silnika 2
#define MOTOR2_PWM_DDR DDRD
// Linia portu wyjścia PWM silnika 2
#define MOTOR2_PWM_PIN 5
// Port wyjścia kierunku silnika 2
#define MOTOR2_DIR_PORT PORTC
// Rejestr kierunku portu wyjścia kierunku silnika 2
#define MOTOR2_DIR_DDR DDRC
// Linia portu wyjścia kierunku silnika 2
#define MOTOR2_DIR_PIN 1


// Port serwomechanozmu 1
#define SERVO1_PORT PORTC
// Rejestr kierunku portu serwomechanozmu 1
#define SERVO1_DDR DDRC
// Linia portu serwomechanozmu 1
#define SERVO1_PIN 2

// Port serwomechanozmu 2
#define SERVO2_PORT PORTC
// Rejestr kierunku portu serwomechanozmu 2
#define SERVO2_DDR DDRC
// Linia portu serwomechanozmu 1
#define SERVO2_PIN 3

// Port serwomechanozmu 3
#define SERVO3_PORT PORTC
// Rejestr kierunku portu serwomechanozmu 3
#define SERVO3_DDR DDRC
// Linia portu serwomechanozmu 3
#define SERVO3_PIN 4

// Port serwomechanozmu 4
#define SERVO4_PORT PORTC
// Rejestr kierunku portu serwomechanozmu 4
#define SERVO4_DDR DDRC
// Linia portu serwomechanozmu 4
#define SERVO4_PIN 5


// Port czujników odległości
// (musi być port z wejściami analogowymi)
#define DIST_POTR PORTA
// Rejestr kierunku portu czujników odległości
#define DIST_DDR DDRA
// Linie czujników odległości
#define DIST1_PIN 0
#define DIST2_PIN 1
#define DIST3_PIN 2
#define DIST4_PIN 3
#define DIST5_PIN 4
#define DIST6_PIN 5
#define DIST7_PIN 6
#define DIST8_PIN 7


// Port czujników podłoża
// (musi być port z wejściami analogowymi)
#define GROUND_PORT PORTB
// Rejestr kierunku portu czujników podłaża
#define GROUND_DDR DDRB
// Rejestr wejściowy portu czujników podłaża
#define GROUND_PINPORT PINB
// Linie czujników podłoża
#define GROUND1_PIN 0
#define GROUND2_PIN 1
#define GROUND3_PIN 2
#define GROUND4_PIN 3
// Port mocy czujników podłoża
#define GROUND_PWN_PORT PORTD
// Rejestr kierunku portu mocy czujników podłaża
#define GROUND_PWM_DDR DDRD
// Linia portu mocy czujników podłoża
#define GROUND_PWM 7


// Port przycisku 1
#define SWITCH1_PORT PORTD
// Rejestr kierunku portu przycisku 1
#define SWITCH1_DDR PORTD
// Rejestr wejściowy portu przycisku 1
#define SWITCH1_PINPORT PIND
// linia portu przycisku 1
#define SWITCH1_PIN 2

// Port przycisku 2
#define SWITCH2_PORT PORTD
// Rejestr kierunku portu przycisku 2
#define SWITCH2_DDR PORTD
// Rejestr wejściowy portu przycisku 2
#define SWITCH2_PINPORT PIND
// linia portu przycisku 2
#define SWITCH2_PIN 3


// Port danych sterownika diod LED
#define LED_SDI_PORT PORTC
// Rejestr kierunku portu danych sterownika diod LED
#define LED_SDI_DDR DDRC
// Linia portu danych sterownika diod LED
#define LED_SDI_PIN 7
// Port danych sterownika diod LED
#define LED_CLK_PORT PORTC
// Rejestr kierunku portu danych sterownika diod LED
#define LED_CLK_DDR DDRC
// Linia portu danych sterownika diod LED
#define LED_CLK_PIN 6
// Port zatrzasku sterownika diod LED
#define LED_LE_PORT PORTB
// Rejestr kierunku portu zatrzasku sterownika diod LED
#define LED_LE_DDR DDRB
// Linia portu zatrzasku sterownika diod LED
#define LED_LE_PIN 4


// Wartość preskalera timera0
#define T0_PRESCALER 256
// Konfiguracja timera0
#define T0_CONF _BV(CS02)
// Wartość początkowa dla timera0 używanego do sterowania serwomechanizmami
#define TIMER0_BEGIN_VALUE (unsigned char) (255-((0.0005)*(F_CPU/T0_PRESCALER)))
// Wartość preskalera dla PWM
// 0x01 - preskaler=1
// 0x02 - preskaler=8
// 0x03 - preskaler=64
// 0x04 - preskaler=256
// 0x05 - preskaler=1024
#define PWM_PRESCALLER_CONFIG 0x02

#define MOTOR_MAX_POWER 50 // tak zeby nie zjarac serw :p


#include "macro.h"
#include "queue.h"

#include <avr/io.h>
#include <avr/iom32.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include <ctype.h>
#include <stdlib.h>

// lib/led.cpp
void led_init();
void led_send();
void led_set(unsigned int value);
void led1_on();
void led1_off();
void led2_on();
void led2_off();
void led3_on();
void led3_off();
void led4_on();
void led4_off();
void led5_on();
void led5_off();
void led6_on();
void led6_off();
void led7_on();
void led7_off();
void led8_on();
void led8_off();
void led_delay();

// lib/wait.cpp
void wait_s(int s);
void wait_ms(int ms);

// lib/motor.cpp
void motor_init();

// lib/switch.cpp
void switch_init();
unsigned char switch1_pressed();
unsigned char switch2_pressed();
void wait_switch1();
void wait_switch2();

// lib/ground.cpp
void ground_init();
unsigned char ground1_detected();
unsigned char ground2_detected();
unsigned char ground3_detected();
unsigned char ground4_detected();

// lib/dist.cpp
void dist_init();
unsigned char dist(char id);
void kalmanize();
extern int Dist[2][3];


// lib/servo.cpp
void servo_init();
void servo1_forward();
void servo2_forward();
void servo3_forward();
void servo4_forward();
void servo1_backward();
void servo2_backward();
void servo3_backward();
void servo4_backward();
void servo1_stop();
void servo2_stop();
void servo3_stop();
void servo4_stop();
void servo1_calibrate();
void servo2_calibrate();
void servo3_calibrate();
void servo4_calibrate();

// lib/usart.cpp
void usart_init();
void usart_write_byte(unsigned char byte);
void usart_write_string(char *string);
void usart_write_number(long number);
void usart_write_progmem_string(const char *string);
unsigned char usart_read_byte();

//lib/debug.cpp
void reset();
void send_ground_state_on_usart();
void send_distance_state_on_usart();
void progress();
//void debug();

#endif

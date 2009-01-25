#ifndef SUMO_H_
#define SUMO_H_

// Opis wyprowadzeń procesora
// 
// PORTA
//     0 - DIST1 - czujnik odległości
//     1 - DIST2 - czujnik odległości
//     2 - DIST3 - czujnik odległości
//     3 - DIST4 - czujnik odległości
//     4 - DIST5 - czujnik odległości
//     5 - DIST6 - czujnik odległości
//     6 - SERVO1 - wejście serwomechanizmu
//     7 - SERVO2 - wejście serwomechanizmu
// 
// PORTB
//     0 - GROUND1 - czujnik podłoża
//     1 - GROUND2 - czujnik podłoża
//     2 - GROUND3 - czujnik podłoża
//     3 - GROUND4 - czujnik podłoża
//     4 - LEDS - dioda świecąca
//     5 - MOSI - używany do programowania
//     6 - MISO - używany do programowania
//     7 - SCK - używany do programowania
// 
// PORTC
//     0 - LED1 - dioda świecąca
//     1 - LED2 - dioda świecąca
//     2 - LED3 - dioda świecąca
//     3 - LED4 - dioda świecąca
//     4 - LED5 - dioda świecąca
//     5 - LED6 - dioda świecąca
//     6 - LED7/SERVO4 - dioda świecąca/wejście serwomechanizmu
//     7 - LED8/SERVO3 - dioda świecąca/wejście serwomechanizmu
// 
// PORTD
//     0 - RXD - RS232
//     1 - TXD - RS232
//     2 - SWITCH1 - przycisk
//     3 - SWITCH2 - przycisk
//     4 - M1_PWM - start/stop silnika
//     5 - M2_PWM - start/stop silnika
//     6 - M1_DIR - kierunek obrotów silnika
//     7 - M2_DIR - kierunek obrotów silnika
// 


// Częstotliwość kwarcu
#define F_CPU 7372800L
// Prędkość transmisji po RSie
#define USART_SPEED 9600L


// Port wyjścia PWM silnika 1
#define MOTOR1_PWM_PORT PORTD
// Rejestr kierunku portu wyjścia PWM silnika 1
#define MOTOR1_PWM_DDR DDRD
// Linia portu wyjścia PWM silnika 1
#define MOTOR1_PWM_PIN 4
// Port wyjścia kierunku silnika 1
#define MOTOR1_DIR_PORT PORTD
// Rejestr kierunku portu wyjścia kierunku silnika 1
#define MOTOR1_DIR_DDR DDRD
// Linia portu wyjścia kierunku silnika 1
#define MOTOR1_DIR_PIN 7


// Port wyjścia PWM silnika 2
#define MOTOR2_PWM_PORT PORTD
// Rejestr kierunku portu wyjścia PWM silnika 2
#define MOTOR2_PWM_DDR DDRD
// Linia portu wyjścia PWM silnika 2
#define MOTOR2_PWM_PIN 5
// Port wyjścia kierunku silnika 2
#define MOTOR2_DIR_PORT PORTD
// Rejestr kierunku portu wyjścia kierunku silnika 2
#define MOTOR2_DIR_DDR DDRD
// Linia portu wyjścia kierunku silnika 2
#define MOTOR2_DIR_PIN 6


// Port serwomechanozmu 1
#define SERVO1_PORT PORTA
// Rejestr kierunku portu serwomechanozmu 1
#define SERVO1_DDR DDRA
// Linia portu serwomechanozmu 1
#define SERVO1_PIN 6

// Port serwomechanozmu 2
#define SERVO2_PORT PORTA
// Rejestr kierunku portu serwomechanozmu 2
#define SERVO2_DDR DDRA
// Linia portu serwomechanozmu 1
#define SERVO2_PIN 7

// Port serwomechanozmu 3
#define SERVO3_PORT PORTC
// Rejestr kierunku portu serwomechanozmu 3
#define SERVO3_DDR DDRC
// Linia portu serwomechanozmu 3
#define SERVO3_PIN 6

// Port serwomechanozmu 4
#define SERVO4_PORT PORTC
// Rejestr kierunku portu serwomechanozmu 4
#define SERVO4_DDR DDRC
// Linia portu serwomechanozmu 4
#define SERVO4_PIN 7


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


// Port specjalnej diody LED
#define LEDS_PORT PORTB
// Rejestr kierunku portu specjalnej diody LED
#define LEDS_DDR DDRB
// Linia diody specjalnej
#define LEDS_PIN 4
// Port diagnostycznych diod LED
#define LED_PORT PORTC
// Rejestr kierunku portu diagnostycznych diod LED
#define LED_DDR DDRC

// Linie poszczególnych diod
#define LED1_PIN 0
#define LED2_PIN 1
#define LED3_PIN 2
#define LED4_PIN 3
#define LED5_PIN 4
#define LED6_PIN 5
#define LED7_PIN 6
#define LED8_PIN 7

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
void led_send(unsigned char value);

// lib/wait.cpp
void wait_s(int s);
void wait_ms(int ms);

// lib/motor.cpp
void motor_init();
void motors(Move move);

// lib/switch.cpp
void switch_init();
unsigned char switch1_pressed();
unsigned char switch2_pressed();
void wait_switch1();
void wait_switch2();

// lib/ground.cpp
void ground_init();
unsigned char ground();
unsigned char ground1_detected();
unsigned char ground2_detected();
unsigned char ground3_detected();
unsigned char ground4_detected();

// lib/dist.cpp
void dist_init();
unsigned char dist1_value();
unsigned char dist2_value();
unsigned char dist3_value();
unsigned char dist4_value();
unsigned char dist5_value();
unsigned char dist6_value();

// lib/servo.cpp
void servo_init();
void servo1_forward();
void servo2_forward();
void servo1_backward();
void servo2_backward();
void servo1_stop();
void servo2_stop();
void servo1_calibrate();
void servo2_calibrate();

// lib/usart.cpp
void usart_init();
void usart_write_byte(unsigned char byte);
void usart_write_string(char *string);
void usart_write_string_from_progmem(const char *string);
void usart_write_number(long number);
unsigned char usart_read_byte();

#endif

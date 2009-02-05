/**
 * Nagłówek biblioteki sumolib
 */

#ifndef SUMOLIB_H_
#define SUMOLIB_H_

// Plik konfiguracyjny
#include "../sumoconfig.h"

// Wczytanie makr
#include "macro.h"

// Biblioteki standatdowe
#include <avr/io.h>
#include <avr/iom32.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include <ctype.h>


// Stałe obliczane

/**
 * Wartość preskalera timera0
 */
#define T0_PRESCALER 256

/**
 * Konfiguracja timera0
 */
#define T0_CONF _BV(CS02)

/**
 * Wartość początkowa dla timera0 
 * używanego do sterowania serwomechanizmami
 */
#define TIMER0_BEGIN_VALUE (unsigned char) (255-((0.0005)*(F_CPU/T0_PRESCALER)))

/**
 * Wartość preskalera dla PWM
 * 0x01 - preskaler=1
 * 0x02 - preskaler=8
 * 0x03 - preskaler=64
 * 0x04 - preskaler=256
 * 0x05 - preskaler=1024
 */
#define PWM_PRESCALLER_CONFIG 0x02

// Deklaracje funkcji:

/**
 * Funkcja inicjalizujaca sterownik diod
 */
void sled_init();

/**
 * Funkcja wysyła dane do sterownika diod
 */
void sled_send();

/**
 * Funkcja ustawia wartosci diod
 */
void sled_set(unsigned int value);

/*
 * Zapal diode led 1
 */
void sled1_on();

/*
 * Zgas diode led 1
 */
void sled1_off();

/*
 * Zapal diode led 2
 */
void sled2_on();

/*
 * Zgas diode led 2
 */
void sled2_off();

/*
 * Zapal diode led 3
 */
void sled3_on();

/*
 * Zgas diode led 3
 */
void sled3_off();

/*
 * Zapal diode led 4
 */
void sled4_on();

/*
 * Zgas diode led 4
 */
void sled4_off();

/*
 * Zapal diode led 5
 */
void sled5_on();

/*
 * Zgas diode led 5
 */
void sled5_off();

/*
 * Zapal diode led 6
 */
void sled6_on();

/*
 * Zgas diode led 6
 */
void sled6_off();

/*
 * Zapal diode led 7
 */
void sled7_on();

/*
 * Zgas diode led 7
 */
void sled7_off();

/*
 * Zapal diode led 8
 */
void sled8_on();

/*
 * Zgas diode led 8
 */
void sled8_off();

/**
 * Funkcja opozniajaca
 */
void sled_delay();




/**
 * Inicjalizacja przycisków
 */
void switch_init();

/**
 * Sprawdzenie, czy przycisk 1 naciśnięty
 * 0 - nie 
 * 1 - tak
 */
unsigned char switch1_pressed();

/**
 * Sprawdzenie, czy przycisk 2 naciśnięty
 * 0 - nie 
 * 1 - tak
 */
unsigned char switch2_pressed();

/**
 * Czekanie na naciśnięcie przycisku 1
 */
void wait_switch1();

/**
 * Czekanie na naciśnięcie przycisku 2
 */
void wait_switch2();


/**
 * Inicjalizacja czujników podłoża
 */
void ground_init();

/**
 * Wykrywa białe podłoże (linię) pod czujnikiem 1
 * Zwraca:
 * 1 - podłoże jasne
 * 0 - podłoże ciemne
 * Wartości będą zanegowane, jeśli zostanie to ustawione w konfiguracji
 */
unsigned char ground1_detected();

/**
 * Wykrywa białe podłoże (linię) pod czujnikiem 2
 * Zwraca:
 * 1 - podłoże jasne
 * 0 - podłoże ciemne
 * Wartości będą zanegowane, jeśli zostanie to ustawione w konfiguracji
 */
unsigned char ground2_detected();

/**
 * Wykrywa białe podłoże (linię) pod czujnikiem 3
 * Zwraca:
 * 1 - podłoże jasne
 * 0 - podłoże ciemne
 * Wartości będą zanegowane, jeśli zostanie to ustawione w konfiguracji
 */
unsigned char ground3_detected();

/**
 * Wykrywa białe podłoże (linię) pod czujnikiem 4
 * Zwraca:
 * 1 - podłoże jasne
 * 0 - podłoże ciemne
 * Wartości będą zanegowane, jeśli zostanie to ustawione w konfiguracji
 */
unsigned char ground4_detected();

/**
 * Funkcja inicjalizująca czujniki odległości
 * UWAGA: zajmuje przetwornik AC
 */
void dist_init();

/**
 * Funkcja zwraca przetworzoną wartość z czujnika 1
 */
inline unsigned char dist1_value();

/**
 * Funkcja zwraca przetworzoną wartość z czujnika 2
 */
inline unsigned char dist2_value();

/**
 * Funkcja zwraca przetworzoną wartość z czujnika 3
 */
inline unsigned char dist3_value();

/**
 * Funkcja zwraca przetworzoną wartość z czujnika 4
 */
inline unsigned char dist4_value();

/**
 * Funkcja zwraca przetworzoną wartość z czujnika 5
 */
inline unsigned char dist5_value();

/**
 * Funkcja zwraca przetworzoną wartość z czujnika 6
 */
inline unsigned char dist6_value();

/**
 * Funkcja zwraca przetworzoną wartość z czujnika 7
 */
inline unsigned char dist7_value();

/**
 * Funkcja zwraca przetworzoną wartość z czujnika 8
 */
inline unsigned char dist8_value();

/**
 * Inicjalizacja serwomechanizmów 1-4
 * UWAGA: zajmuje timer0
 */
void serwo_init();

/**
 * Uruchomienie serwomechanizmu 1
 * obroty w przód
 */
void servo1_forward();

/**
 * Uruchomienie serwomechanizmu 2
 * obroty w przód
 */
void servo2_forward();

/**
 * Uruchomienie serwomechanizmu 3
 * obroty w przód
 */
void servo3_forward();

/**
 * Uruchomienie serwomechanizmu 4
 * obroty w przód
 */
void servo4_forward();

/**
 * Uruchomienie serwomechanizmu 1
 * obroty w tył
 */
void servo1_backward();

/**
 * Uruchomienie serwomechanizmu 2
 * obroty w tył
 */
void servo2_backward();

/**
 * Uruchomienie serwomechanizmu 3
 * obroty w tył
 */
void servo3_backward();

/**
 * Uruchomienie serwomechanizmu 4
 * obroty w tył
 */
void servo4_backward();

/**
 * Zatrzymanie serwomechanizmu 1
 */
void servo1_stop();

/**
 * Zatrzymanie serwomechanizmu 2
 */
void servo2_stop();

/**
 * Zatrzymanie serwomechanizmu 3
 */
void servo3_stop();

/**
 * Zatrzymanie serwomechanizmu 4
 */
void servo4_stop();

/**
 * Kalibracja serwomechanizmu 1
 */
void servo1_calibrate();

/**
 * Kalibracja serwomechanizmu 2
 */
void servo2_calibrate();

/**
 * Kalibracja serwomechanizmu 3
 */
void servo3_calibrate();

/**
 * Kalibracja serwomechanizmu 4
 */
void servo4_calibrate();

/**
 * Inicjalizacja prostej obsługi silników
 */
void motor_init();

/**
 * Ustawia moc silnika 1 wyrażoną w %
 */
void motor1_set_power(unsigned char power);

/**
 * Ustawia moc silnika 2 wyrażoną w %
 */
void motor2_set_power(unsigned char power);

/**
 * Zatrzymanie silnika 1
 */
void motor1_stop();

/**
 * Zatrzymanie silnika 2
 */
void motor2_stop();

/**
 * Uruchomienie silnika 1
 * obroty w przód
 */
void motor1_forward();

/**
 * Uruchomienie silnika 2
 * obroty w przód
 */
void motor1_forward();

/**
 * Uruchomienie silnika 1
 * obroty w tył
 */
void motor1_backward();

/**
 * Uruchomienie silnika 2
 * obroty w tył
 */
void motor1_backward();

/**
 * Inicjalizacja USATRu
 */
void usart_init();

/**
 * Wysłanie bajtu na RS
 */
void usart_write_byte(unsigned char byte);

/**
 * Wysłanie łańcucha znaków na RS
 */
void usart_write_string(char *string);

/**
 * Wysłanie łańcucha znaków z pamięci programu
 */
void usart_write_string_from_progmem(const char *string);

/**
 * Wysłanie liczby na RS
 */
void usart_write_number(long number);

/**
 * Odbieranie bajtu z ES
 * funkcja zwraca 0 jeśli nic nie przyszło
 */
unsigned char usart_read_byte();


/**
 * Czeka podaną ilość sekund
 */
void wait_s(int s);

/**
 * Czeka podaną ilość milisekund
 */
void wait_ms(int ms);

/**
 * Inicjalizuje prace generatoea liczb pseudolosowych
 */
void random_init();

/*
 * Zwraca liczbę z podanego zakresu
 */
char random (char range);












#endif /*SUMOLIB_H_*/

#include "sumo.h"

// Inicjalizacja USATRu
void usart_init() {}

// Wysłanie bajtu na RS
void usart_write_byte(unsigned char byte) {}

// Wysłanie łańcucha znaków na RS
void usart_write_string(char *string) {}

// Wysłanie łańcucha znaków z pamięci programu
void usart_write_progmem_string(const char *string) {}


// Wysłanie liczby na RS
void usart_write_number(long number){}

// Odbieranie bajtu z ES
// funkcja zwraca 0 jeśli nic nie przyszło
unsigned char usart_read_byte() {}




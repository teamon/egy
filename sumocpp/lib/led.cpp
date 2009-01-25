#include "sumo.h"

// Funkcja inicjalizująca diody 1-8 i diodę S
void led_init() {
  LED_DDR |= 0xff;
  LED_PORT |= 0xff;
  
  setb(LEDS_DDR,LEDS_PIN);
  setb(LEDS_PORT,LEDS_PIN);
}

// Funkcja wysyła na port diod 1-8 wartość
void led_send(unsigned char value) {
  LED_PORT = ~value;
}
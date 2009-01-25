#include "sumo.h"

// Inicjalizacja przycisków
void switch_init() {
  // przycisk 1
  clr(SWITCH1_DDR, SWITCH1_PIN);
  setb(SWITCH1_PORT, SWITCH1_PIN);
  // przycisk 2
  clr(SWITCH2_DDR, SWITCH2_PIN);
  setb(SWITCH2_PORT, SWITCH2_PIN);
}

// Sprawdzenie, czy przycisk 1 naciśnięty
unsigned char switch1_pressed() {
  return bit_is_clear(SWITCH1_PINPORT, SWITCH1_PIN);
}

// Sprawdzenie, czy przycisk 2 naciśnięty
unsigned char switch2_pressed() {
  return bit_is_clear(SWITCH2_PINPORT, SWITCH2_PIN);
}

// Czekanie na naciśnięcie przycisku 1
void wait_switch1() {
  while(bit_is_set(SWITCH1_PINPORT, SWITCH1_PIN));
}

// Czekanie na naciśnięcie przycisku 2
void wait_switch2() {
  while(bit_is_set(SWITCH2_PINPORT, SWITCH2_PIN));
}

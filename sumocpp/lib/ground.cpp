#include "sumo.h"

/// Inicjalizacja czujników podłoża
void ground_init() {
  clr(GROUND_DDR, GROUND1_PIN);
  clr(GROUND_DDR, GROUND2_PIN);
  clr(GROUND_DDR, GROUND3_PIN);
  clr(GROUND_DDR, GROUND4_PIN);
  clr(GROUND_PORT, GROUND1_PIN);
  clr(GROUND_PORT, GROUND2_PIN);
  clr(GROUND_PORT, GROUND3_PIN);
  clr(GROUND_PORT, GROUND4_PIN);
}

unsigned char ground(){
  unsigned char out=1;
  if (ground1_detected()) out*=2; // przod lewy
  if (ground2_detected()) out*=3; // przod prawy
  if (ground3_detected()) out*=5; // tyl lewy
  if (ground4_detected()) out*=7; // tyl prawy
  return out;
}

// Wykrywa białe podłoże (linię) pod czujnikiem 1
unsigned char ground1_detected() {
  return bit_is_clear(GROUND_PINPORT, GROUND1_PIN);
}

// Wykrywa białe podłoże (linię) pod czujnikiem 2
unsigned char ground2_detected() {
  return bit_is_clear(GROUND_PINPORT, GROUND2_PIN);
}

// Wykrywa białe podłoże (linię) pod czujnikiem 3
unsigned char ground3_detected() {
  return bit_is_clear(GROUND_PINPORT, GROUND3_PIN);
}

// Wykrywa białe podłoże (linię) pod czujnikiem 4
unsigned char ground4_detected() {
  return bit_is_clear(GROUND_PINPORT, GROUND4_PIN);
}
/**
 * Funkcje do obs�ugi losowania
 */
 
 #include "sumolib.h";
 
 /**
  * Inicjalizuje prace generatoea liczb pseudolosowych
  */
 void random_init() {
	TCCR2 = _BV(CS20);
 }
 
 
/*
 * Zwraca liczb� z podanego zakresu
 */
char random (char range) {
	if (range > 0)
		return (TCNT2 % range);
	else
		return TCNT2;
}
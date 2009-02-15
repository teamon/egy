#include "sumo.h"

// Numer aktualnie przetwarzanego portu
volatile unsigned char k = 0;

// kalman
// #define N 40
// #define K 6
// #define D 6
// #define R 0.05
// #define Q 0.0003

// float distance[K][N];
// float kalman[K];
// float P[K][N];

// void kal(int i, int k){
//   int pre = (i == 0) ? 0 : i-1;
//   float P_ = P[k][pre] + Q;
//   float A = P_ / (P_ + R);
//   kalman[k][i] = kalman[k][pre] + A * (distance[k][i] - kalman[k][pre]);
//   P[k][i] = (1 - K) * P_;
// }

// Funkcja inicjalizująca czujniki odległości
// UWAGA: zajmuje przetwornik AC
void dist_init()
{
  // Inicjalizacja portu
  DIST_DDR &= ~((1<<DIST1_PIN) | (1<<DIST2_PIN) | (1<<DIST3_PIN) | (1<<DIST4_PIN) | (1<<DIST5_PIN) | (1<<DIST6_PIN));
  DIST_POTR &= ~((1<<DIST1_PIN) | (1<<DIST2_PIN) | (1<<DIST3_PIN) | (1<<DIST4_PIN) | (1<<DIST5_PIN) | (1<<DIST6_PIN));
  
  // Konfiguracja przetwornika i przerwań
  ADMUX = 0x60; //01100000
  ADCSRA = 0xcd; //11001101
  
  // inicjalizacja numeru czujnika
  k = 1;
  sei();
}

unsigned char dist(char id){
  return id;
  // return kalman[id];
}

// Procedura przerwania od przetwornika AC
// SIGNAL (SIG_ADC)
// {
//   char val = ADCH;
//   
//   kalman[k] = val; //tmp
//   // kalman
//   // int i;
//   // 
//   // for(i=1; i<N; ++i) {
//   //   distance[k][i-1] = distance[k][i];
//   //   kalman[k][i-1] = kalman[k][i];
//   //   P[k][i-1] = P[k][i];
//   // }
//   // 
//   // distance[k][N-1] = val;
//   // kalman[k][N-1] = val;
//   // P[k][N-1] = 1;
//   
//   // kal(N-1, k);
//   
//   // eof
// 
//   if (k == 5) ADMUX = 0x60;
//   else ADMUX = 0x60 + (k + 1);
//     
//   k++;
//   if (k > 5) k = 0;
//   
//   ADCSRA |= 0x40;
// }


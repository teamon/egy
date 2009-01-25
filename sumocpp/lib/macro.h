#ifndef MACRO_H_
#define MACRO_H_

// Ustawia bit w bajcie
#define setb(byte,bit) byte |= (1 << bit)
// Zeruje bit w bajcie
#define clr(byte,bit) byte &= ~(1 << bit)
// Neguje bit w bajcie
#define cpl(byte,bit) byte ^= (1 << bit)
// Zapis do pamięci eeprom
#define eeprom_write(adr,dane) eeprom_write_byte ((uint8_t*)adr, dane)
// Odczyt z pamięci eeprom
#define eeprom_read(adr) eeprom_read_byte ((uint8_t*)adr)

// Zapalanie poszczególnych diod
#define led1_on() clr(LED_PORT,LED1_PIN)
#define led2_on() clr(LED_PORT,LED2_PIN)
#define led3_on() clr(LED_PORT,LED3_PIN)
#define led4_on() clr(LED_PORT,LED4_PIN)
#define led5_on() clr(LED_PORT,LED5_PIN)
#define led6_on() clr(LED_PORT,LED6_PIN)
#define led7_on() clr(LED_PORT,LED7_PIN)
#define led8_on() clr(LED_PORT,LED8_PIN)
#define leds_on() clr(LEDS_PORT,LEDS_PIN)

// Gaszenie poszczególnych diod
#define led1_off() setb(LED_PORT,LED1_PIN)
#define led2_off() setb(LED_PORT,LED2_PIN)
#define led3_off() setb(LED_PORT,LED3_PIN)
#define led4_off() setb(LED_PORT,LED4_PIN)
#define led5_off() setb(LED_PORT,LED5_PIN)
#define led6_off() setb(LED_PORT,LED6_PIN)
#define led7_off() setb(LED_PORT,LED7_PIN)
#define led8_off() setb(LED_PORT,LED8_PIN)
#define leds_off() setb(LEDS_PORT,LEDS_PIN)

// Zmiana stanu poszczególnych diod
#define led1_negate() cpl(LED_PORT,LED1_PIN)
#define led2_negate() cpl(LED_PORT,LED2_PIN)
#define led3_negate() cpl(LED_PORT,LED3_PIN)
#define led4_negate() cpl(LED_PORT,LED4_PIN)
#define led5_negate() cpl(LED_PORT,LED5_PIN)
#define led6_negate() cpl(LED_PORT,LED6_PIN)
#define led7_negate() cpl(LED_PORT,LED7_PIN)
#define led8_negate() cpl(LED_PORT,LED8_PIN)
#define leds_negate() cpl(LEDS_PORT,LEDS_PIN)

#endif
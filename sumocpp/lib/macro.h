#ifndef MACRO_H_
#define MACRO_H_

#define mabs(x) ((x<0)?-(x):x)
#define inrange(x, from, to) (x>=from && x<=to)
#define min(x, y) ((x<=y)?x:y)
#define max(x, y) ((x>=y)?x:y)
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


#endif
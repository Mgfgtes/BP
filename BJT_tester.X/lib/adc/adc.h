/**
 * ADC knihovna pro AVR64DA28
 * 
 * Jednoducha knihovna pro 12-bitovy AD prevodnik integrovany v AVR64DA28
 */
#ifndef ADC_H
#define ADC_H

#include <avr/io.h>
#include <stdint.h>

/**
 * Inicializace AD prevodniku s interni referenci 1.024V
 */
void ADC_init(void);

/**
 * Cteni hodnoty z AD prevodniku
 * 
 * @param channel Kanal, ze ktereho se bude cist
 * @return Hodnota namerena z AD prevodniku (12-bit)
 */
uint16_t ADC_read(uint8_t channel);

#endif // ADC_H
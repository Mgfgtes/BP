/**
 * ADC knihovna pro AVR64DA28 - Implementace
 * 
 * Jednoducha knihovna pro 12-bitovy AD prevodnik integrovany v AVR64DA28
 */

#include "adc.h"

void ADC_init(void) {
    // Nastaveni reference na interni napajeci napeti
    VREF.ADC0REF = VREF_REFSEL_VDD_gc;
    
    // Nastaveni rozliseni na 12 bitu
    ADC0.CTRLA = ADC_RESSEL_12BIT_gc;
    
    // Nastaveni hodin pro AD prevodnik
    ADC0.CTRLC = ADC_PRESC_DIV16_gc; // Delic frekvence
    
    // Zapnuti AD prevodniku
    ADC0.CTRLA |= ADC_ENABLE_bm;
}

uint16_t ADC_read(uint8_t channel) {
    // Vyber kanalu
    ADC0.MUXPOS = channel;
    
    // Spusteni prevodu
    ADC0.COMMAND = ADC_STCONV_bm;
    
    // Cekani na dokonceni prevodu
    while (!(ADC0.INTFLAGS & ADC_RESRDY_bm));
    
    // Navrat hodnoty
    return ADC0.RES;
}
/**
 * AVR64DA28 UART knihovna - Implementace
 * 
 * Jednoduchá knihovna pro komunikaci p?es UART rozhraní na mikrokontroléru AVR64DA28
 * Podporuje základní nastavení a p?enos dat
 */

#include "uart.h"

/**
 * Inicializace UART0
 * 
 * @param baud_rate Hodnota baudrate z enum uart_baud_t
 */
void uart0_init(uart_baud_t baud_rate) {
    // Nastavení pin? pro TX (PA0) a RX (PA1)
    PORTA.DIRSET = PIN0_bm;  // TX jako výstup
    PORTA.DIRCLR = PIN1_bm;  // RX jako vstup
    
    // Nastavení baudrate
    USART0.BAUD = baud_rate;
    
    // Povolení vysíla?e a p?ijíma?e
    USART0.CTRLB = USART_TXEN_bm | USART_RXEN_bm;
    
    // Formát dat: 8 bit?, bez parity, 1 stop bit
    USART0.CTRLC = USART_CHSIZE_8BIT_gc;
}

/**
 * Odeslání jednoho bajtu p?es UART
 * 
 * @param data Bajt k odeslání
 */
void uart0_send_byte(uint8_t data) {
    // ?ekání na uvoln?ní vysílacího bufferu
    while (!(USART0.STATUS & USART_DREIF_bm));
    
    // Odeslání bajtu
    USART0.TXDATAL = data;
}

/**
 * Odeslání ?et?zce p?es UART
 * 
 * @param str ?et?zec k odeslání
 */
void uart0_send_string(const char* str) {
    while(*str) {
        uart0_send_byte(*str++);
    }
}

/**
 * P?íjem jednoho bajtu p?es UART
 * 
 * @return P?ijatý bajt
 */
uint8_t uart0_receive_byte(void) {
    // ?ekání na p?íjem dat
    while (!(USART0.STATUS & USART_RXCIF_bm));
    
    // Vrácení p?ijatého bajtu
    return USART0.RXDATAL;
}

/**
 * Kontrola, zda jsou k dispozici data k p?e?tení
 * 
 * @return 1 pokud jsou data k dispozici, jinak 0
 */
uint8_t uart0_data_available(void) {
    return (USART0.STATUS & USART_RXCIF_bm) ? 1 : 0;
}

/**
 * P?íjem ?et?zce p?es UART s ?asovým limitem
 * 
 * @param buffer Buffer pro ulo?ení p?ijatých dat
 * @param max_length Maximální délka bufferu
 * @param timeout Po?et cykl? pro timeout (0 = bez timeoutu)
 * @return Po?et p?ijatých znak?
 */
uint16_t uart0_receive_string(char* buffer, uint16_t max_length, uint16_t timeout) {
    uint16_t count = 0;
    uint16_t timer = 0;
    
    while(count < max_length - 1) {
        if (uart0_data_available()) {
            buffer[count] = uart0_receive_byte();
            
            // Kontrola ukon?ení ?et?zce
            if (buffer[count] == '\n' || buffer[count] == '\r') {
                buffer[count] = '\0';
                return count;
            }
            
            count++;
            timer = 0;
        } else {
            if (timeout > 0) {
                timer++;
                if (timer >= timeout) {
                    break;
                }
            }
        }
    }
    
    buffer[count] = '\0';
    return count;
}

/**
 * Inicializace UART1 (druhý UART kanál na jiných pinech)
 * 
 * @param baud_rate Hodnota baudrate z enum uart_baud_t
 */
void uart1_init(uart_baud_t baud_rate) {
    // Nastavení pin? pro TX (PC0) a RX (PC1)
    PORTC.DIRSET = PIN0_bm;  // TX jako výstup
    PORTC.DIRCLR = PIN1_bm;  // RX jako vstup
    
    // Nastavení baudrate
    USART1.BAUD = baud_rate;
    
    // Povolení vysíla?e a p?ijíma?e
    USART1.CTRLB = USART_TXEN_bm | USART_RXEN_bm;
    
    // Formát dat: 8 bit?, bez parity, 1 stop bit
    USART1.CTRLC = USART_CHSIZE_8BIT_gc;
}


/**
 * Odeslání jednoho bajtu p?es UART1
 * 
 * @param data Bajt k odeslání
 */
void uart1_send_byte(uint8_t data) {
    // ?ekání na uvoln?ní vysílacího bufferu
    while (!(USART1.STATUS & USART_DREIF_bm));
    
    // Odeslání bajtu
    USART1.TXDATAL = data;
}

/**
 * Odeslání ?et?zce p?es UART
 * 
 * @param str ?et?zec k odeslání
 */
void uart1_send_string(const char* str) {
    while(*str) {
        uart1_send_byte(*str++);
    }
}

/**
 * P?íjem jednoho bajtu p?es UART1
 * 
 * @return P?ijatý bajt
 */
uint8_t uart1_receive_byte(void) {
    // ?ekání na p?íjem dat
    while (!(USART1.STATUS & USART_RXCIF_bm));
    
    // Vrácení p?ijatého bajtu
    return USART1.RXDATAL;
}

/**
 * Kontrola, zda jsou k dispozici data k p?e?tení
 * 
 * @return 1 pokud jsou data k dispozici, jinak 0
 */
uint8_t uart1_data_available(void) {
    return (USART1.STATUS & USART_RXCIF_bm) ? 1 : 0;
}

/**
 * P?íjem ?et?zce p?es UART s ?asovým limitem
 * 
 * @param buffer Buffer pro ulo?ení p?ijatých dat
 * @param max_length Maximální délka bufferu
 * @param timeout Po?et cykl? pro timeout (0 = bez timeoutu)
 * @return Po?et p?ijatých znak?
 */
uint16_t uart1_receive_string(char* buffer, uint16_t max_length, uint16_t timeout) {
    uint16_t count = 0;
    uint16_t timer = 0;
    
    while(count < max_length - 1) {
        if (uart1_data_available()) {
            buffer[count] = uart1_receive_byte();
            
            // Kontrola ukon?ení ?et?zce
            if (buffer[count] == '\n' || buffer[count] == '\r') {
                buffer[count] = '\0';
                return count;
            }
            
            count++;
            timer = 0;
        } else {
            if (timeout > 0) {
                timer++;
                if (timer >= timeout) {
                    break;
                }
            }
        }
    }
    
    buffer[count] = '\0';
    return count;
}
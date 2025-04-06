/**
 * AVR64DA28 UART knihovna - Implementace
 * 
 * Jednoduch� knihovna pro komunikaci p?es UART rozhran� na mikrokontrol�ru AVR64DA28
 * Podporuje z�kladn� nastaven� a p?enos dat
 */

#include "uart.h"

/**
 * Inicializace UART0
 * 
 * @param baud_rate Hodnota baudrate z enum uart_baud_t
 */
void uart0_init(uart_baud_t baud_rate) {
    // Nastaven� pin? pro TX (PA0) a RX (PA1)
    PORTA.DIRSET = PIN0_bm;  // TX jako v�stup
    PORTA.DIRCLR = PIN1_bm;  // RX jako vstup
    
    // Nastaven� baudrate
    USART0.BAUD = baud_rate;
    
    // Povolen� vys�la?e a p?ij�ma?e
    USART0.CTRLB = USART_TXEN_bm | USART_RXEN_bm;
    
    // Form�t dat: 8 bit?, bez parity, 1 stop bit
    USART0.CTRLC = USART_CHSIZE_8BIT_gc;
}

/**
 * Odesl�n� jednoho bajtu p?es UART
 * 
 * @param data Bajt k odesl�n�
 */
void uart0_send_byte(uint8_t data) {
    // ?ek�n� na uvoln?n� vys�lac�ho bufferu
    while (!(USART0.STATUS & USART_DREIF_bm));
    
    // Odesl�n� bajtu
    USART0.TXDATAL = data;
}

/**
 * Odesl�n� ?et?zce p?es UART
 * 
 * @param str ?et?zec k odesl�n�
 */
void uart0_send_string(const char* str) {
    while(*str) {
        uart0_send_byte(*str++);
    }
}

/**
 * P?�jem jednoho bajtu p?es UART
 * 
 * @return P?ijat� bajt
 */
uint8_t uart0_receive_byte(void) {
    // ?ek�n� na p?�jem dat
    while (!(USART0.STATUS & USART_RXCIF_bm));
    
    // Vr�cen� p?ijat�ho bajtu
    return USART0.RXDATAL;
}

/**
 * Kontrola, zda jsou k dispozici data k p?e?ten�
 * 
 * @return 1 pokud jsou data k dispozici, jinak 0
 */
uint8_t uart0_data_available(void) {
    return (USART0.STATUS & USART_RXCIF_bm) ? 1 : 0;
}

/**
 * P?�jem ?et?zce p?es UART s ?asov�m limitem
 * 
 * @param buffer Buffer pro ulo?en� p?ijat�ch dat
 * @param max_length Maxim�ln� d�lka bufferu
 * @param timeout Po?et cykl? pro timeout (0 = bez timeoutu)
 * @return Po?et p?ijat�ch znak?
 */
uint16_t uart0_receive_string(char* buffer, uint16_t max_length, uint16_t timeout) {
    uint16_t count = 0;
    uint16_t timer = 0;
    
    while(count < max_length - 1) {
        if (uart0_data_available()) {
            buffer[count] = uart0_receive_byte();
            
            // Kontrola ukon?en� ?et?zce
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
 * Inicializace UART1 (druh� UART kan�l na jin�ch pinech)
 * 
 * @param baud_rate Hodnota baudrate z enum uart_baud_t
 */
void uart1_init(uart_baud_t baud_rate) {
    // Nastaven� pin? pro TX (PC0) a RX (PC1)
    PORTC.DIRSET = PIN0_bm;  // TX jako v�stup
    PORTC.DIRCLR = PIN1_bm;  // RX jako vstup
    
    // Nastaven� baudrate
    USART1.BAUD = baud_rate;
    
    // Povolen� vys�la?e a p?ij�ma?e
    USART1.CTRLB = USART_TXEN_bm | USART_RXEN_bm;
    
    // Form�t dat: 8 bit?, bez parity, 1 stop bit
    USART1.CTRLC = USART_CHSIZE_8BIT_gc;
}


/**
 * Odesl�n� jednoho bajtu p?es UART1
 * 
 * @param data Bajt k odesl�n�
 */
void uart1_send_byte(uint8_t data) {
    // ?ek�n� na uvoln?n� vys�lac�ho bufferu
    while (!(USART1.STATUS & USART_DREIF_bm));
    
    // Odesl�n� bajtu
    USART1.TXDATAL = data;
}

/**
 * Odesl�n� ?et?zce p?es UART
 * 
 * @param str ?et?zec k odesl�n�
 */
void uart1_send_string(const char* str) {
    while(*str) {
        uart1_send_byte(*str++);
    }
}

/**
 * P?�jem jednoho bajtu p?es UART1
 * 
 * @return P?ijat� bajt
 */
uint8_t uart1_receive_byte(void) {
    // ?ek�n� na p?�jem dat
    while (!(USART1.STATUS & USART_RXCIF_bm));
    
    // Vr�cen� p?ijat�ho bajtu
    return USART1.RXDATAL;
}

/**
 * Kontrola, zda jsou k dispozici data k p?e?ten�
 * 
 * @return 1 pokud jsou data k dispozici, jinak 0
 */
uint8_t uart1_data_available(void) {
    return (USART1.STATUS & USART_RXCIF_bm) ? 1 : 0;
}

/**
 * P?�jem ?et?zce p?es UART s ?asov�m limitem
 * 
 * @param buffer Buffer pro ulo?en� p?ijat�ch dat
 * @param max_length Maxim�ln� d�lka bufferu
 * @param timeout Po?et cykl? pro timeout (0 = bez timeoutu)
 * @return Po?et p?ijat�ch znak?
 */
uint16_t uart1_receive_string(char* buffer, uint16_t max_length, uint16_t timeout) {
    uint16_t count = 0;
    uint16_t timer = 0;
    
    while(count < max_length - 1) {
        if (uart1_data_available()) {
            buffer[count] = uart1_receive_byte();
            
            // Kontrola ukon?en� ?et?zce
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
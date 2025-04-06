/**
 * AVR64DA28 UART knihovna - Hlavi?kov� soubor
 * 
 * Jednoduch� knihovna pro komunikaci p?es UART rozhran� na mikrokontrol�ru AVR64DA28
 * Podporuje z�kladn� nastaven� a p?enos dat
 */

#ifndef UART_H
#define UART_H

#include <avr/io.h>
#include <stdint.h>

/**
 * Nastaven� baudrate pro UART komunikaci
 * 
 * Pro 16MHz oscil�tor:
 * 9600   - 1666
 * 19200  - 833
 * 38400  - 416
 * 57600  - 277
 * 115200 - 138
 */
typedef enum {
    BAUD_9600 = 1666,
    BAUD_19200 = 833,
    BAUD_38400 = 416,
    BAUD_57600 = 277,
    BAUD_115200 = 138
} uart_baud_t;

/* Funkce pro UART0 */

/**
 * Inicializace UART0
 * 
 * @param baud_rate Hodnota baudrate z enum uart_baud_t
 */
void uart0_init(uart_baud_t baud_rate);

/**
 * Odesl�n� jednoho bajtu p?es UART0
 * 
 * @param data Bajt k odesl�n�
 */
void uart0_send_byte(uint8_t data);

/**
 * Odesl�n� ?et?zce p?es UART0
 * 
 * @param str ?et?zec k odesl�n�
 */
void uart0_send_string(const char* str);

/**
 * P?�jem jednoho bajtu p?es UART0
 * 
 * @return P?ijat� bajt
 */
uint8_t uart0_receive_byte(void);

/**
 * Kontrola, zda jsou k dispozici data k p?e?ten� p?es UART0
 * 
 * @return 1 pokud jsou data k dispozici, jinak 0
 */
uint8_t uart0_data_available(void);

/**
 * P?�jem ?et?zce p?es UART0 s ?asov�m limitem
 * 
 * @param buffer Buffer pro ulo?en� p?ijat�ch dat
 * @param max_length Maxim�ln� d�lka bufferu
 * @param timeout Po?et cykl? pro timeout (0 = bez timeoutu)
 * @return Po?et p?ijat�ch znak?
 */
uint16_t uart0_receive_string(char* buffer, uint16_t max_length, uint16_t timeout);





/* Funkce pro UART1 */

/**
 * Inicializace UART1 (druh� UART kan�l na jin�ch pinech)
 * 
 * @param baud_rate Hodnota baudrate z enum uart_baud_t
 */
void uart1_init(uart_baud_t baud_rate);

/**
 * Odesl�n� jednoho bajtu p?es UART1
 * 
 * @param data Bajt k odesl�n�
 */
void uart1_send_byte(uint8_t data);

/**
 * Odesl�n� ?et?zce p?es UART1
 * 
 * @param str ?et?zec k odesl�n�
 */
void uart1_send_string(const char* str);

/**
 * P?�jem jednoho bajtu p?es UART1
 * 
 * @return P?ijat� bajt
 */
uint8_t uart1_receive_byte(void);

/**
 * Kontrola, zda jsou k dispozici data k p?e?ten� p?es UART1
 * 
 * @return 1 pokud jsou data k dispozici, jinak 0
 */
uint8_t uart1_data_available(void);

/**
 * P?�jem ?et?zce p?es UART1 s ?asov�m limitem
 * 
 * @param buffer Buffer pro ulo?en� p?ijat�ch dat
 * @param max_length Maxim�ln� d�lka bufferu
 * @param timeout Po?et cykl? pro timeout (0 = bez timeoutu)
 * @return Po?et p?ijat�ch znak?
 */
uint16_t uart1_receive_string(char* buffer, uint16_t max_length, uint16_t timeout);

#endif // UART_H
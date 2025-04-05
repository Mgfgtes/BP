/**
 * AVR64DA28 UART knihovna - Hlavi?kový soubor
 * 
 * Jednoduchá knihovna pro komunikaci p?es UART rozhraní na mikrokontroléru AVR64DA28
 * Podporuje základní nastavení a p?enos dat
 */

#ifndef UART_H
#define UART_H

#include <avr/io.h>
#include <stdint.h>

/**
 * Nastavení baudrate pro UART komunikaci
 * 
 * Pro 16MHz oscilátor:
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
 * Odeslání jednoho bajtu p?es UART0
 * 
 * @param data Bajt k odeslání
 */
void uart0_send_byte(uint8_t data);

/**
 * Odeslání ?et?zce p?es UART0
 * 
 * @param str ?et?zec k odeslání
 */
void uart0_send_string(const char* str);

/**
 * P?íjem jednoho bajtu p?es UART0
 * 
 * @return P?ijatý bajt
 */
uint8_t uart0_receive_byte(void);

/**
 * Kontrola, zda jsou k dispozici data k p?e?tení p?es UART0
 * 
 * @return 1 pokud jsou data k dispozici, jinak 0
 */
uint8_t uart0_data_available(void);

/**
 * P?íjem ?et?zce p?es UART0 s ?asovým limitem
 * 
 * @param buffer Buffer pro ulo?ení p?ijatých dat
 * @param max_length Maximální délka bufferu
 * @param timeout Po?et cykl? pro timeout (0 = bez timeoutu)
 * @return Po?et p?ijatých znak?
 */
uint16_t uart0_receive_string(char* buffer, uint16_t max_length, uint16_t timeout);





/* Funkce pro UART1 */

/**
 * Inicializace UART1 (druhý UART kanál na jiných pinech)
 * 
 * @param baud_rate Hodnota baudrate z enum uart_baud_t
 */
void uart1_init(uart_baud_t baud_rate);

/**
 * Odeslání jednoho bajtu p?es UART1
 * 
 * @param data Bajt k odeslání
 */
void uart1_send_byte(uint8_t data);

/**
 * Odeslání ?et?zce p?es UART1
 * 
 * @param str ?et?zec k odeslání
 */
void uart1_send_string(const char* str);

/**
 * P?íjem jednoho bajtu p?es UART1
 * 
 * @return P?ijatý bajt
 */
uint8_t uart1_receive_byte(void);

/**
 * Kontrola, zda jsou k dispozici data k p?e?tení p?es UART1
 * 
 * @return 1 pokud jsou data k dispozici, jinak 0
 */
uint8_t uart1_data_available(void);

/**
 * P?íjem ?et?zce p?es UART1 s ?asovým limitem
 * 
 * @param buffer Buffer pro ulo?ení p?ijatých dat
 * @param max_length Maximální délka bufferu
 * @param timeout Po?et cykl? pro timeout (0 = bez timeoutu)
 * @return Po?et p?ijatých znak?
 */
uint16_t uart1_receive_string(char* buffer, uint16_t max_length, uint16_t timeout);

#endif // UART_H
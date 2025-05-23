/**
 * AVR64DA28 UART knihovna
 * 
 * Jednoducha knihovna pro komunikaci pres UART rozhraní na mikrokontroleru AVR64DA28
 * Podporuje zakladní nastavení a prenos dat
 */

#ifndef UART_H
#define UART_H

#include <avr/io.h>
#include <stdint.h>

/**
 * Nastavení baudrate pro UART komunikaci
 * 
 * Pro 16MHz:
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
 * Odeslani jednoho bajtu pres UART0
 * 
 * @param data Bajt k odeslani
 */
void uart0_send_byte(uint8_t data);

/**
 * Odeslani retezce pees UART0
 * 
 * @param str retezec k odeslani
 */
void uart0_send_string(const char* str);

/**
 * Prijem jednoho bajtu pres UART0
 * 
 * @return Prijaty bajt
 */
uint8_t uart0_receive_byte(void);

/**
 * Kontrola, zda jsou k dispozici data k precteni pres UART0
 * 
 * @return 1 pokud jsou data k dispozici, jinak 0
 */
uint8_t uart0_data_available(void);

/**
 * Prijem retezce pres UART0 s casovym limitem
 * 
 * @param buffer Buffer pro ulorení prijatych dat
 * @param max_length Maximalni delka bufferu
 * @param timeout Pocet cyklu pro timeout (0 = bez timeoutu)
 * @return Pocet prijatych znaku
 */
uint8_t uart0_receive_string(char* buffer, uint8_t max_length);





/* Funkce pro UART1 */

/**
 * Inicializace UART1 (druhy UART kanal na jinych pinech)
 * 
 * @param baud_rate Hodnota baudrate z enum uart_baud_t
 */
void uart1_init(uart_baud_t baud_rate);

/**
 * Odeslani jednoho bajtu pres UART1
 * 
 * @param data Bajt k odeslani
 */
void uart1_send_byte(uint8_t data);

/**
 * Odeslani retezce pres UART1
 * 
 * @param str retezec k odeslani
 */
void uart1_send_string(const char* str);

/**
 * Prijem jednoho bajtu pres UART1
 * 
 * @return Prijaty bajt
 */
uint8_t uart1_receive_byte(void);

/**
 * Kontrola, zda jsou k dispozici data k prectene pres UART1
 * 
 * @return 1 pokud jsou data k dispozici, jinak 0
 */
uint8_t uart1_data_available(void);

/**
 * Vyprazdneni prijimaciho bufferu
 * 
 * @param buffer
 * @param max_length
 * @return 
 */
void uart1_clear_receive_buffer();

/**
 * Prijem retezce pres UART1
 * 
 * @param buffer Buffer pro ulorení prijatych dat
 * @param max_length Maximalni delka bufferu
 * @param timeout Maximalni pocet opakovani
 * @return Pocet prijatych znaku
 */
uint8_t uart1_receive_string(char* buffer, uint8_t max_length, uint8_t timeout);

#endif // UART_H
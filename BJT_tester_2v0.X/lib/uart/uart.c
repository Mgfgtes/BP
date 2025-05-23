/**
 * AVR64DA28 UART knihovna - Implementace
 * 
 * Jednoducha knihovna pro komunikaci pres UART rozhrani na mikrokontroleru AVR64DA28
 * Podporuje zakladní nastaveni a prenos dat
 */

#include "uart.h"

/**
 * Inicializace UART0
 * 
 * @param baud_rate Hodnota baudrate z enum uart_baud_t
 */
void uart0_init(uart_baud_t baud_rate) {
    // Nastaveni pinu pro TX (PA0) a RX (PA1)
    PORTA.DIRSET = PIN0_bm;  // TX jako vystup
    PORTA.DIRCLR = PIN1_bm;  // RX jako vstup
    
    // Nastaveni baudrate
    USART0.BAUD = baud_rate;
    
    //Povoleni preruseni
    USART0.CTRLA = USART_RXCIE_bm;
    
    // Povoleni vysilace a prijimace
    USART0.CTRLB = USART_TXEN_bm | USART_RXEN_bm;
    
    // Format dat: 8 bit, bez parity, 1 stop bit
    USART0.CTRLC = USART_CHSIZE_8BIT_gc;
}

/**
 * Odeslani jednoho bajtu pres UART
 * 
 * @param data Bajt k odeslani
 */
void uart0_send_byte(uint8_t data) {
    // Cekani na uvolneni vysilaciho bufferu
    while (!(USART0.STATUS & USART_DREIF_bm));
    
    // Odeslani bajtu
    USART0.TXDATAL = data;
}

/**
 * Odeslani retezce pres UART
 * 
 * @param str retezec k odeslani
 */
void uart0_send_string(const char* str) {
    while(*str) {
        uart0_send_byte(*str++);
    }
}

/**
 * Prijem jednoho bajtu pres UART
 * 
 * @return Prijaty bajt
 */
uint8_t uart0_receive_byte(void) {
    // Cekani na prijem dat
    while (!(USART0.STATUS & USART_RXCIF_bm));
    
    // Vraceni prijateho bajtu
    return USART0.RXDATAL;
}

/**
 * Kontrola, zda jsou k dispozici data k precteni
 * 
 * @return 1 pokud jsou data k dispozici, jinak 0
 */
uint8_t uart0_data_available(void) {
    return (USART0.STATUS & USART_RXCIF_bm) ? 1 : 0;
}

/**
 * Prijem retezce pres UART
 * 
 * @param buffer Buffer pro ulozeni prijatych dat
 * @param max_length Maximalni delka bufferu
 * @return Pocet prijatych znaku
 */
uint8_t uart0_receive_string(char* buffer, uint8_t max_length) {
    uint8_t count = 0;
    
    while (count < max_length - 1) {
        if (uart0_data_available()){
            buffer[count]=uart0_receive_byte();
            if(buffer[count]==0) return count;
            count++;
        } 
    }
    
    buffer[count] = 0;
    return count;
}

/**
 * Inicializace UART1 (druhy UART kanal na jinych pinech)
 * 
 * @param baud_rate Hodnota baudrate z enum uart_baud_t
 */
void uart1_init(uart_baud_t baud_rate) {
    // Nastaveni pinu pro TX (PC0) a RX (PC1)
    PORTC.DIRSET = PIN0_bm;  // TX jako vystup
    PORTC.DIRCLR = PIN1_bm;  // RX jako vstup
    
    // Nastaveni baudrate
    USART1.BAUD = baud_rate;
    
    //Povoleni preruseni
    USART1.CTRLA = USART_RXCIE_bm;
    
    // Povoleni vysilace a prijimace
    USART1.CTRLB |= USART_TXEN_bm | USART_RXEN_bm;
    
    // Format dat: 8 bit, bez parity, 1 stop bit
    USART1.CTRLC = USART_CHSIZE_8BIT_gc;
}


/**
 * Odeslani jednoho bajtu pres UART1
 * 
 * @param data Bajt k odeslani
 */
void uart1_send_byte(uint8_t data) {
    // Cekani na uvolneni vysilaciho bufferu
    while (!(USART1.STATUS & USART_DREIF_bm));
    
    // Odeslani bajtu
    USART1.TXDATAL = data;
}

/**
 * Odeslání retezce pres UART
 * 
 * @param str retezec k odeslani
 */
void uart1_send_string(const char* str) {
    while(*str) {
        uart1_send_byte(*str++);
    }
}

/**
 * Kontrola, zda jsou k dispozici data k precteni
 * 
 * @return 1 pokud jsou data k dispozici, jinak 0
 */
uint8_t uart1_data_available(void) {
    if(USART1.STATUS & USART_RXCIF_bm) return 1;
    return 0;
}

/**
 * Prijem jednoho bajtu pres UART1
 * 
 * @return Prijaty bajt
 */
uint8_t uart1_receive_byte(void) {
    // Cekani na prijem dat
    while (!(USART1.STATUS & USART_RXCIF_bm));
    
    // Vraceni prijateho bajtu
    return USART1.RXDATAL;
}

/**
 * Vyprazdneni prijimaciho bufferu
 * 
 * @param buffer
 * @param max_length
 * @return 
 */
void uart1_clear_receive_buffer(){
    while (uart1_data_available()) {
        uart1_receive_byte();
    }
}

/**
 * Prijem retezce pres UART
 * 
 * @param buffer Buffer pro ulozeni prijatych dat
 * @param max_length Maximalni delka bufferu
 * @param timeout Maximalni pocet opakovani
 * @return Pocet prijatých znaku
 */
uint8_t uart1_receive_string(char* buffer, uint8_t max_length, uint8_t timeout) {
    uint8_t count = 0;
    uint8_t t = 0;
    
    while ((count < max_length - 1)&&(t < timeout)) {
        if (uart1_data_available()){
            buffer[count]=uart1_receive_byte();
            if(buffer[count]==0) return count;
            count++;
            t = 0;
        }
        else{
            t++;
        }
    }
    
    buffer[count] = 0;
    return count;
}
/*
 * File:   main.c
 * Author: mate2
 *
 * Created on 18. dubna 2025, 17:24
 */

#define F_CPU 16000000UL
#define MCP4728_ADDRESS 0x61

#include <xc.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>

#include "../lib/uart/uart.h"
#include "../lib/i2c/i2c.h"
#include "../lib/DA_converter_MCP4728A1/mcp4728a1.h"

typedef enum {
    START,
    CH1_TESTING,
    CH2_TESTING,
    CH3_TESTING
        
} device_status_t;

volatile device_status_t status;

int main(void) {
    //Nastaveni hodinoveho signalu na 16 MHz a vypnuti 32,768 kHz oscilatoru.
    CLKCTRL.OSCHFCTRLA = CLKCTRL_FRQSEL_16M_gc;
    CLKCTRL.MCLKCTRLA = CLKCTRL_CLKSEL_OSCHF_gc;
    CLKCTRL.XOSC32KCTRLA &= 0
    
    //Oprava na desce -> nastavení HiZ na PIN1
    PORTA.DIRCLR = PIN1_bm;
    
    //Inicializace seriovych sbernic
    uart1_init(BAUD_9600);
    uart1_clear_receive_buffer();
    sei();
    i2c_init(I2C_NORMAL_MODE_100KHZ);
    
    uart1_send_string("t0.txt=\"INITIALIZING\"");
    uart1_send_byte(0xff);
    uart1_send_byte(0xff);
    uart1_send_byte(0xff);
    
    _delay_ms(250);
    
    if (mcp4728_init(MCP4728_ADDRESS) != I2C_OK) {
        // Chyba inicializace
        uart1_send_string("t0.txt=\"I2C INIT ERROR\"");
        uart1_send_byte(0xff);
        uart1_send_byte(0xff);
        uart1_send_byte(0xff);
    }
    
    while (status != START) {}
    
    
    
    return 0;
}

ISR(USART1_RXC_vect){
    char string[10];
    
    uart1_receive_string(string, 10);
    
    if(strcmp(string, "cmd_start")) status = START;
}
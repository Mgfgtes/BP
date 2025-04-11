/*
 * File:   main.c
 * Author: mate2
 *
 * Created on 5. dubna 2025, 13:26
 */

#define F_CPU 16000000UL

#include <xc.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "../lib/uart/uart.h"
#include "../lib/i2c/i2c.h"
#include "../lib/DA_converter_MCP4728A1/mcp4728a1.h"

#include <stdio.h>

/*ISR(USART1_RXC_vect){
    uint8_t string[10];
    
    
    uint8_t i=0;
    
    //while (i<10) {
        
    //    if (uart1_data_available()){
    //        string[i]=uart1_receive_byte();
    //        if(string[i]==0) break;
    //        i++;
    //    }
        
    //}
    
    uart1_receive_string(&string[0], 10,20);
    
    uart1_send_string("t0.txt=\"");
    uart1_send_string(&string[0]);
    uart1_send_string("\"");
    uart1_send_byte(0xff);
    uart1_send_byte(0xff);
    uart1_send_byte(0xff);
}*/

int main(void) {  
    //cli();
    
    CLKCTRL.OSCHFCTRLA = CLKCTRL_FRQSEL_16M_gc;
    CLKCTRL.MCLKCTRLA = CLKCTRL_CLKSEL_OSCHF_gc;
    
    uart1_init(BAUD_9600);
    i2c_init(I2C_NORMAL_MODE_100KHZ);
    
    //_delay_ms(500);
    
    uart1_send_string("t0.txt=\"OK\"");
    uart1_send_byte(0xff);
    uart1_send_byte(0xff);
    uart1_send_byte(0xff);
    
    _delay_ms(500);
    
    if (mcp4728_init(MCP4728_DEFAULT_ADDRESS) != I2C_OK) {
        // Chyba inicializace - nap?�klad blik�n� LED pro indikaci chyby
        while (1) {
            uart1_send_string("t0.txt=\"I2C ERROR\"");
            uart1_send_byte(0xff);
            uart1_send_byte(0xff);
            uart1_send_byte(0xff);
        }
    }
    
    mcp4728_set_channel(MCP4728_CHANNEL_A, 2048, 
                        MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, 
                        MCP4728_PD_NORMAL);
    
    
    uart1_send_string("t0.txt=\"V_SET\"");
    uart1_send_byte(0xff);
    uart1_send_byte(0xff);
    uart1_send_byte(0xff);
    
    //sei();
    //uint8_t str[10];
    //uint8_t t = 1;
    
    
    while (1) {
        /*_delay_ms(1000);
        uart1_send_string("t0.txt=\"");
        sprintf(str, "%d", t);
        uart1_send_string(str);
        uart1_send_string(" s\"");
        uart1_send_byte(0xff);
        uart1_send_byte(0xff);
        uart1_send_byte(0xff);
        t++;*/
        
    }
    return 0;
}

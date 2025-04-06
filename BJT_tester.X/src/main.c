/*
 * File:   main.c
 * Author: mate2
 *
 * Created on 5. dubna 2025, 13:26
 */
#define F_CPU 16000000UL

#include <xc.h>
#include "../lib/uart/uart.h"
#include <util/delay.h>

int main(void) {
    
    uart1_init(BAUD_9600);
    
    uart1_send_string("t0.txt=\"OK\"");
    uart1_send_byte(0xff);
    uart1_send_byte(0xff);
    uart1_send_byte(0xff);
    
    _delay_ms(500);
    
    uint8_t string[10]={1,1,1,1,1,1,1,1,1,0};
    uint8_t i=0;
    
    USART1_RXDATAL=0;
    USART1_RXDATAH &= 0xFE;
    
    while (i<10) {
        uart1_send_string("t0.txt=\"wait\"");
        
        uart1_send_byte(0xff);
        uart1_send_byte(0xff);
        uart1_send_byte(0xff);
        _delay_ms(500);
        if (uart1_data_available()){
            string[i]=uart1_receive_byte();
            if(string[i]==0) break;
            i++;
        }
        
        _delay_ms(500);
    }

    
    uart1_send_string("t0.txt=\"");
    uart1_send_string(string);
    uart1_send_string("\"");
    uart1_send_byte(0xff);
    uart1_send_byte(0xff);
    uart1_send_byte(0xff);
    _delay_ms(500);
    
    return 0;
}

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
#include <avr/interrupt.h>

ISR(USART1_RXC_vect){
    uint8_t string[10]={1,1,1,1,1,1,1,1,1,0};
    uint8_t i=0;
    
    
    while (i<10) {
        
        if (uart1_data_available()){
            string[i]=uart1_receive_byte();
            if(string[i]==0) break;
            i++;
        }
    
    }
    
    uart1_send_string("t0.txt=\"");
    uart1_send_string(string);
    uart1_send_string("\"");
    uart1_send_byte(0xff);
    uart1_send_byte(0xff);
    uart1_send_byte(0xff);
    _delay_ms(2000);
}

int main(void) {  
    uart1_init(BAUD_9600);
    
    _delay_ms(500);
    
    uart1_send_string("t0.txt=\"OK\"");
    uart1_send_byte(0xff);
    uart1_send_byte(0xff);
    uart1_send_byte(0xff);
    
    sei();
    
    _delay_ms(1000);
     
    while (1) {

    }

    
    return 0;
}

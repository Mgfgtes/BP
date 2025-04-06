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
    
    _delay_ms(2000);
    
    uart1_send_string("t0.txt=\"OK\"");
    uart1_send_byte(0xff);
    uart1_send_byte(0xff);
    uart1_send_byte(0xff);
    
    char string[10];
    uart1_receive_string(string,10,0);
    
    uart1_send_string("t0.txt=\"");
    uart1_send_string(string);
    uart1_send_string("\"");
    uart1_send_byte(0xff);
    uart1_send_byte(0xff);
    uart1_send_byte(0xff);
    
    return 0;
}

/*
 * File:   main.c
 * Author: mate2
 *
 * Created on 5. dubna 2025, 13:26
 */
#define F_CPU 16000000

#include <xc.h>
#include "../lib/uart.h"
#include <util/delay.h>

int main(void) {
    
    uart1_init(BAUD_9600);
    
    _delay_ms(3000);
    
    uart1_send_string("t0.txt=\"OK\"");
    uart1_send_byte(0xff);
    uart1_send_byte(0xff);
    uart1_send_byte(0xff);
    
    return 0;
}

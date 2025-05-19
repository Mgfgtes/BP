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
#include "../lib/adc/adc.h"
#include <stdio.h>

ISR(USART1_RXC_vect){
    char string[10];
    
    
    /*uint8_t i=0;
    
    while (i<10) {
        
        if (uart1_data_available()){
            string[i]=uart1_receive_byte();
            if(string[i]==0) break;
            i++;
        }
        
    }*/
    
    uart1_receive_string(string, 10);
    
    uart1_send_string("t0.txt=\"");
    uart1_send_string(string);
    uart1_send_string("\"");
    uart1_send_byte(0xff);
    uart1_send_byte(0xff);
    uart1_send_byte(0xff);
}

void nextion_send_string(const char* str){
    uart1_send_string(str);
    uart1_send_byte(0xff);
    uart1_send_byte(0xff);
    uart1_send_byte(0xff);
}

uint16_t measure_I_uA(uint8_t INA_CH){
    //Zmereni napeti kanalu D z DA prevodiku
    VREF.ADC0REF = VREF_REFSEL_1V024_gc;
    
    uint16_t VREF_mV_corrigated = (ADC_read(7)*1024)/4096;
    
    //Nastaveni reference na vystup DA prevodniku z kanalu D
    VREF.ADC0REF = VREF_REFSEL_VREFA_gc;
    
                //I = ((((VREF/Rozliseni)*ADC_read())/INA_GAIN)/Rb)*1000000   [uA]
                //I = (VREF*ADC_read()*1000000)/(Rb*INA_GAIN*Rozliseni)       [uA] 
                //I = (VREF_mV*ADC_read()*1000)/(0,2*50*4096)                 [uA]
                //I = (VREF_mV*ADC_read()*1000)/40960                         [uA]
    uint16_t I = (VREF_mV_corrigated*ADC_read(INA_CH))/40960;
    
    return I;
}

uint16_t measure_I_mA(uint8_t INA_CH){
    //Nastaveni reference na vystup DA prevodniku z kanalu D
    VREF.ADC0REF = VREF_REFSEL_1V024_gc;
    
                //I = ((((VREF/Rozliseni)*ADC_read())/INA_GAIN)/Rb)*1000   [mA]
                //I = (VREF*ADC_read()*1000)/(Rb*INA_GAIN*Rozliseni)       [mA] 
                //I = (VREF_mV*ADC_read(2))/(0,2*50*4096)                  [mA]
                //I = (1024*ADC_read(2)*)/40960                            [mA]
    uint16_t I = (1024*ADC_read(INA_CH))/40960;
    
    return I;
}

int main(void) {  
    //cli();
    
    CLKCTRL.OSCHFCTRLA = CLKCTRL_FRQSEL_16M_gc;
    CLKCTRL.MCLKCTRLA = CLKCTRL_CLKSEL_OSCHF_gc;
    
    uart1_init(BAUD_9600);
    
    PORTA.DIRCLR = PIN1_bm;
    i2c_init(I2C_NORMAL_MODE_100KHZ);
    
    _delay_ms(500);
    
    uart1_send_string("t0.txt=\"OK\"");
    uart1_send_byte(0xff);
    uart1_send_byte(0xff);
    uart1_send_byte(0xff);
    
    _delay_ms(500);
    
    if (mcp4728_init(0x61) != I2C_OK) {
        // Chyba inicializace
        uart1_send_string("t0.txt=\"I2C INIT ERROR\"");
        uart1_send_byte(0xff);
        uart1_send_byte(0xff);
        uart1_send_byte(0xff);
    }
    
    _delay_ms(10);
    
    mcp4728_set_channel(MCP4728_CHANNEL_A, 2048, 
                        MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, 
                        MCP4728_PD_NORMAL);
    
    _delay_ms(10);
    
    mcp4728_set_channel(MCP4728_CHANNEL_B, 2340, 
                        MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, 
                        MCP4728_PD_NORMAL);
    
    _delay_ms(10);
    
    mcp4728_set_channel(MCP4728_CHANNEL_C, 2048, 
                        MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, 
                        MCP4728_PD_NORMAL);
    
    _delay_ms(10);
    
    
    uart1_clear_receive_buffer();
    sei(); 
    
    
    uint8_t str[10];
    //uint8_t t = 1;
    
    
    
    
    
    //mereni proudu
    ADC_init();
    
    //VREF=100mV
    mcp4728_set_channel(MCP4728_CHANNEL_D, 100, MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL);
    //VREF.ADC0REF = VREF_REFSEL_VREFA_gc;
    //VREF.ADC0REF = VREF_REFSEL_1V024_gc;
    
    /*uint16_t Ib = ((((0.1/4096)*ADC_read(2))/50)/0.2)*1000;
                 //((((VREF/Rozliseni)*ADC_read(2))/INA_GAIN)/Rb)*1000000 [uA]*/
                 //(VREF*ADC_read(2))/(Rb*INA_GAIN*Rozliseni)
                 //(VREF*ADC_read(2))/(0,2*50*4096)
                 //(VREF*ADC_read(2))/40960
    //uint16_t Ib = (1024000*ADC_read(2))/40960;
    
    uint16_t Ib = measure_I_uA(2);
    
    sprintf(str, "%d", Ib);
    
    uart1_send_string("t0.txt=\"");
    uart1_send_string(str);
    uart1_send_string("\"");
    uart1_send_byte(0xff);
    uart1_send_byte(0xff);
    uart1_send_byte(0xff);
    
    
    //PORTA.DIRSET = PIN6_bm;
    
    while (1) {
        //_delay_ms(1000);
        
        //PORTA.OUTTGL = PIN6_bm;
        
        /*
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

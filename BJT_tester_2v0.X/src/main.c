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
#include <stdio.h>

#include "../lib/uart/uart.h"
#include "../lib/i2c/i2c.h"
#include "../lib/DA_converter_MCP4728A1/mcp4728a1.h"
#include "../lib/adc/adc.h"

typedef enum {
    RUN,
    IDLE
} device_status_t;

typedef enum {
    NPN,
    PNP
} BJTPolarity;

typedef struct {
    BJTPolarity polarity; // polarita tranzistoru (NPN nebo PNP)
    uint8_t base_channel;       // kanal pripojeny na baie (0-2)
    uint16_t h21;        // zesileni tranzistoru
} BJT;

volatile device_status_t status;
BJT tested_BJT;

void nextion_send_string(const char* str){
    uart1_send_string(str);
    uart1_send_byte(0xff);
    uart1_send_byte(0xff);
    uart1_send_byte(0xff);
}

int main(void) {
    //Nastaveni hodinoveho signalu na 16 MHz a vypnuti 32,768 kHz oscilatoru.
    CLKCTRL.OSCHFCTRLA = CLKCTRL_FRQSEL_16M_gc;
    CLKCTRL.MCLKCTRLA = CLKCTRL_CLKSEL_OSCHF_gc;
    CLKCTRL.XOSC32KCTRLA &= 0;
    
    //Oprava na desce -> nastavení HiZ na PIN1
    PORTA.DIRCLR = PIN1_bm;
    
    //Inicializace seriovych sbernic
    uart1_init(BAUD_9600);
    uart1_clear_receive_buffer();
    
    nextion_send_string("t0.txt=\"INITIALIZING...\"");
    
    i2c_init(I2C_NORMAL_MODE_100KHZ);
    
    
    sei();
    
    if (mcp4728_init(MCP4728_ADDRESS) != I2C_OK) {
        // Chyba inicializace
        nextion_send_string("t0.txt=\"I2C INIT ERROR\"");
    }
    
    //Nastaveni offsetu  
    uint16_t da_val[4]={2048, 2048, 2048, 0};
        
    if (mcp4728_set_channel(MCP4728_CHANNEL_A, da_val[0], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
        // Chyba nastaveni napeti na kanalu
        nextion_send_string("t0.txt=\"ERROR CHA SET\"");
    }
    if (mcp4728_set_channel(MCP4728_CHANNEL_B, da_val[1], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
        // Chyba nastaveni napeti na kanalu
        nextion_send_string("t0.txt=\"ERROR CHB SET\"");
    }
    if (mcp4728_set_channel(MCP4728_CHANNEL_C, da_val[2], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
        // Chyba nastaveni napeti na kanalu
        nextion_send_string("t0.txt=\"ERROR CHC SET\"");
    }

    
    nextion_send_string("page start_menu");
    
    //cekani na stisknuti start
    while (status != RUN) {}
    
    
    //Kontrola zda není NPN
    for (int i = 0; i < 3; i++) {
        
        //offset
        da_val[0]= 2048;
        da_val[1]= 2048;
        da_val[2]= 2048;
        
        //Zvyseni napeti na vystupu jednoho zesilovace o 0,7V -> 0,7/2,4=0,292 -> 2048+292 = 2340
        da_val[i]= 2340;
        
        if (mcp4728_set_channel(MCP4728_CHANNEL_A, da_val[0], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
            // Chyba nastaveni napeti na kanalu
            nextion_send_string("t0.txt=\"ERROR CHA SET\"");
        }
        if (mcp4728_set_channel(MCP4728_CHANNEL_B, da_val[1], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
            // Chyba nastaveni napeti na kanalu
            nextion_send_string("t0.txt=\"ERROR CHB SET\"");
        }
        if (mcp4728_set_channel(MCP4728_CHANNEL_C, da_val[2], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
            // Chyba nastaveni napeti na kanalu
            nextion_send_string("t0.txt=\"ERROR CHC SET\"");
        }
        
        //Mereni proudu dalsimi dvema kanaly
        //Nastaveni reference
        VREF.ADC0REF = VREF_REFSEL_1V024_gc;
        
        //Proud vetsi nez 250uA
        if ((i==0) && (ADC_read(4)>10) && (ADC_read(3)>10)) {
            tested_BJT.base_channel = 0;
            tested_BJT.polarity = NPN;
            break;
        }
        if ((i==1) && (ADC_read(4)>10) && (ADC_read(1)>10)) {
            tested_BJT.base_channel = 1;
            tested_BJT.polarity = NPN;
            break;
        }
        if ((i==2) && (ADC_read(3)>10) && (ADC_read(1)>10)) {
            tested_BJT.base_channel = 2;
            tested_BJT.polarity = NPN;
            break;
        }
        
    }

    
    //Kontrola zda není PNP
    for (int i = 0; i < 3; i++) {
        
        //offset
        da_val[0]= 2048;
        da_val[1]= 2048;
        da_val[2]= 2048;
        
        //Snizeni napeti na vystupu jednoho zesilovace o 0,7V -> 0,7/2,4=0,292 -> 2048-292 = 1756
        da_val[i]= 1756;
        
        if (mcp4728_set_channel(MCP4728_CHANNEL_A, da_val[0], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
            // Chyba nastaveni napeti na kanalu
            nextion_send_string("t0.txt=\"ERROR CHA SET\"");
        }
        if (mcp4728_set_channel(MCP4728_CHANNEL_B, da_val[1], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
            // Chyba nastaveni napeti na kanalu
            nextion_send_string("t0.txt=\"ERROR CHB SET\"");
        }
        if (mcp4728_set_channel(MCP4728_CHANNEL_C, da_val[2], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
            // Chyba nastaveni napeti na kanalu
            nextion_send_string("t0.txt=\"ERROR CHC SET\"");
        }
        
        //Mereni proudu dalsimi dvema kanaly
        //Nastaveni reference
        VREF.ADC0REF = VREF_REFSEL_1V024_gc;
        
        //Proud vetsi nez 250uA
        if ((i==0) && (ADC_read(5)>10) && (ADC_read(2)>10)) {
            tested_BJT.base_channel = 0;
            tested_BJT.polarity = PNP;
            break;
        }
        if ((i==1) && (ADC_read(5)>10) && (ADC_read(0)>10)) {
            tested_BJT.base_channel = 1;
            tested_BJT.polarity = PNP;
            break;
        }
        if ((i==2) && (ADC_read(2)>10) && (ADC_read(0)>10)) {
            tested_BJT.base_channel = 2;
            tested_BJT.polarity = PNP;
            break;
        }

        
    }
    
    
    
    
    
    //Mereni h21
    
    //VREF=10mV
    mcp4728_set_channel(MCP4728_CHANNEL_D, 10, MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL);
    VREF.ADC0REF = VREF_REFSEL_VREFA_gc;
    
    if (tested_BJT.polarity == NPN) {
        
        if (tested_BJT.base_channel==0) {
            //Nastav 100uA na 0,2 Ohm rezistoru
            //0,2*100e-6= 20uV
            //Merici zesilovac *50 -> 20e-6*50=1mV
            //Rozliseni: VREF/2^12 = (0,01/4096)
            //Vystup ADC: pozadovana hodnota/rozliseni = 1e-3/(0,01/4096)=409,6
            while (ADC_read(0)<410) {
                da_val[0]++;
                if (mcp4728_set_channel(MCP4728_CHANNEL_A, da_val[0], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                    // Chyba nastaveni napeti na kanalu
                    nextion_send_string("t0.txt=\"ERROR CHA SET\"");
                }
            }

            da_val[1] = 4096;
            da_val[2] = 0;

            if (mcp4728_set_channel(MCP4728_CHANNEL_B, da_val[1], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                // Chyba nastaveni napeti na kanalu
                nextion_send_string("t0.txt=\"ERROR CHA SET\"");
            }
            if (mcp4728_set_channel(MCP4728_CHANNEL_C, da_val[2], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                // Chyba nastaveni napeti na kanalu
                nextion_send_string("t0.txt=\"ERROR CHA SET\"");
            }

            tested_BJT.h21= ADC_read(2)/ADC_read(0);

            da_val[1] = 0;
            da_val[2] = 4096;

            if (mcp4728_set_channel(MCP4728_CHANNEL_B, da_val[1], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                // Chyba nastaveni napeti na kanalu
                nextion_send_string("t0.txt=\"ERROR CHA SET\"");
            }
            if (mcp4728_set_channel(MCP4728_CHANNEL_C, da_val[2], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                // Chyba nastaveni napeti na kanalu
                nextion_send_string("t0.txt=\"ERROR CHA SET\"");
            }

            if (ADC_read(5)/ADC_read(0)>tested_BJT.h21) tested_BJT.h21 = ADC_read(5)/ADC_read(0);
        } else if(tested_BJT.base_channel == 1) {
            //Nastav 100uA na 0,2 Ohm rezistoru
            //0,2*100e-6= 20uV
            //Merici zesilovac *50 -> 20e-6*50=1mV
            //Rozliseni: VREF/2^12 = (0,01/4096)
            //Vystup ADC: pozadovana hodnota/rozliseni = 1e-3/(0,01/4096)=409,6
            while (ADC_read(2)<410) {
                da_val[1]++;
                if (mcp4728_set_channel(MCP4728_CHANNEL_B, da_val[1], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                    // Chyba nastaveni napeti na kanalu
                    nextion_send_string("t0.txt=\"ERROR CHA SET\"");
                }
            }

            da_val[0] = 4096;
            da_val[2] = 0;

            if (mcp4728_set_channel(MCP4728_CHANNEL_A, da_val[0], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                // Chyba nastaveni napeti na kanalu
                nextion_send_string("t0.txt=\"ERROR CHA SET\"");
            }
            if (mcp4728_set_channel(MCP4728_CHANNEL_C, da_val[2], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                // Chyba nastaveni napeti na kanalu
                nextion_send_string("t0.txt=\"ERROR CHA SET\"");
            }

            tested_BJT.h21= ADC_read(0)/ADC_read(2);

            da_val[0] = 0;
            da_val[2] = 4096;

            if (mcp4728_set_channel(MCP4728_CHANNEL_A, da_val[0], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                // Chyba nastaveni napeti na kanalu
                nextion_send_string("t0.txt=\"ERROR CHA SET\"");
            }
            if (mcp4728_set_channel(MCP4728_CHANNEL_C, da_val[2], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                // Chyba nastaveni napeti na kanalu
                nextion_send_string("t0.txt=\"ERROR CHA SET\"");
            }

            if (ADC_read(5)/ADC_read(2)>tested_BJT.h21) tested_BJT.h21 = ADC_read(5)/ADC_read(2);
        }else if(tested_BJT.base_channel==2) {
            //Nastav 100uA na 0,2 Ohm rezistoru
            //0,2*100e-6= 20uV
            //Merici zesilovac *50 -> 20e-6*50=1mV
            //Rozliseni: VREF/2^12 = (0,01/4096)
            //Vystup ADC: pozadovana hodnota/rozliseni = 1e-3/(0,01/4096)=409,6
            while (ADC_read(0)<410) {
                da_val[0]++;
                if (mcp4728_set_channel(MCP4728_CHANNEL_C, da_val[2], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                    // Chyba nastaveni napeti na kanalu
                    nextion_send_string("t0.txt=\"ERROR CHA SET\"");
                }
            }

            da_val[0] = 4096;
            da_val[1] = 0;

            if (mcp4728_set_channel(MCP4728_CHANNEL_A, da_val[0], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                // Chyba nastaveni napeti na kanalu
                nextion_send_string("t0.txt=\"ERROR CHA SET\"");
            }
            if (mcp4728_set_channel(MCP4728_CHANNEL_B, da_val[1], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                // Chyba nastaveni napeti na kanalu
                nextion_send_string("t0.txt=\"ERROR CHA SET\"");
            }

            tested_BJT.h21= ADC_read(0)/ADC_read(5);

            da_val[0] = 0;
            da_val[1] = 4096;

            if (mcp4728_set_channel(MCP4728_CHANNEL_A, da_val[0], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                // Chyba nastaveni napeti na kanalu
                nextion_send_string("t0.txt=\"ERROR CHA SET\"");
            }
            if (mcp4728_set_channel(MCP4728_CHANNEL_B, da_val[1], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                // Chyba nastaveni napeti na kanalu
                nextion_send_string("t0.txt=\"ERROR CHA SET\"");
            }

            if (ADC_read(2)/ADC_read(5)>tested_BJT.h21) tested_BJT.h21 = ADC_read(2)/ADC_read(5);
        }

    } else if(tested_BJT.polarity==PNP){
        if (tested_BJT.base_channel == 0) {
            
        } else if (tested_BJT.base_channel == 1) {
            
        } else if (tested_BJT.base_channel == 2) {
            
        }

    }

    
    
    
    
    
    
    
    
    
    
    //Odeslani h21 do displeje
    char h21_str[10];
    sprintf(h21_str, "%d", tested_BJT.h21);
    nextion_send_string("t0.txt=\"\"");
    nextion_send_string(h21_str);
    nextion_send_string("\"");
    
    status = IDLE;
    
    return 0;
}

ISR(USART1_RXC_vect){
    char string[10];
    
    uart1_receive_string(string, 10);
    
    if(strcmp(string, "cmd_start")) status = RUN;
}
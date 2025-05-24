/*
 * File:   main.c
 * Author: mate2
 *
 * Created on 18. dubna 2025, 17:24
 */

#define F_CPU 16000000UL

#define MCP4728_ADDRESS 0x61
#define INA_CH_A_F 0
#define INA_CH_A_R 1
#define INA_CH_B_F 2
#define INA_CH_B_R 3
#define INA_CH_C_F 5
#define INA_CH_C_R 4

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
    FAULTY,
    NPN,
    PNP
} BJTPolarity;

typedef struct {
    BJTPolarity polarity; // polarita tranzistoru (NPN nebo PNP)
    mcp4728_channel_t base_channel;       // kanal pripojeny na bazi (0-2)
    uint16_t h21;        // zesileni tranzistoru
    uint16_t Ib_uA;
    uint16_t Ic_mA;
} BJT;

void nextion_send_string(const char* str){
    uart1_send_string(str);
    uart1_send_byte(0xff);
    uart1_send_byte(0xff);
    uart1_send_byte(0xff);
}

uint16_t measure_I_uA(uint8_t INA_CH){
    //Zmereni napeti kanalu D z DA prevodiku
    VREF.ADC0REF = VREF_REFSEL_1V024_gc;
    
    volatile uint32_t VREF_mV_corrigated = ADC_read(7);
    VREF_mV_corrigated = VREF_mV_corrigated *1024;
    VREF_mV_corrigated = VREF_mV_corrigated /4096;
    
    //Nastaveni reference na vystup DA prevodniku z kanalu D
    VREF.ADC0REF = VREF_REFSEL_VREFA_gc;
    
                //I = ((((VREF/Rozliseni)*ADC_read())/INA_GAIN)/Rb)*1000000   [uA]
                //I = (VREF*ADC_read()*1000000)/(Rb*INA_GAIN*Rozliseni)       [uA] 
                //I = (VREF_mV*ADC_read()*1000)/(0,2*50*4096)                 [uA]
                //I = (VREF_mV*ADC_read()*1000)/40960                         [uA]
    volatile uint32_t I = ADC_read(INA_CH);
    I = I * VREF_mV_corrigated * 1000;
    I = I / 40960;
    
    return I;
}

uint16_t measure_I_mA(uint8_t INA_CH){
    //Nastaveni reference na vystup DA prevodniku z kanalu D
    VREF.ADC0REF = VREF_REFSEL_1V024_gc;
    
                //I = ((((VREF/Rozliseni)*ADC_read())/INA_GAIN)/Rb)*1000   [mA]
                //I = (VREF*ADC_read()*1000)/(Rb*INA_GAIN*Rozliseni)       [mA] 
                //I = (VREF_mV*ADC_read(2))/(0,2*50*4096)                  [mA]
                //I = (1024*ADC_read(2)*)/40960                            [mA]
    volatile uint32_t I = ADC_read(INA_CH);
    I = I * 1024;
    I = I /40960;
    
    return I;
}

//Globalni promenna status
volatile device_status_t status;

int main(void) {
    //Nastaveni hodinoveho signalu na 16 MHz a vypnuti 32,768 kHz oscilatoru.
    CLKCTRL.OSCHFCTRLA = CLKCTRL_FRQSEL_16M_gc;
    CLKCTRL.MCLKCTRLA = CLKCTRL_CLKSEL_OSCHF_gc;
    CLKCTRL.XOSC32KCTRLA &= 0;
    
    //Oprava na desce -> nastavení HiZ na PIN1
    PORTA.DIRCLR = PIN1_bm;
    
    // Nastaveni pinu PD0-5 jako vstupy pro ADC
    PORTD.DIRCLR = PIN0_bm | PIN1_bm | PIN2_bm | PIN3_bm | PIN4_bm | PIN5_bm;
    
    // Nastaveni pinu PD7 jako vstup pro VREF
    PORTD.DIRCLR = PIN7_bm;
    
    //Inicializace AD prevodniku
    ADC_init();
    
    //Inicializace seriovych sbernic a vyprazdneni prijimaciho i vysilaciho bufferu
    uart1_init(BAUD_9600);
    uart1_clear_receive_buffer();
    nextion_send_string("");
    
    nextion_send_string("t0.txt=\"INITIALIZING...\"");
    
    i2c_init(I2C_NORMAL_MODE_100KHZ);
    
    _delay_ms(200);
    
    sei();
    
    //Kontola dostupnosti DA prevodniku
    if (mcp4728_init(MCP4728_ADDRESS) != I2C_OK) {
        // Chyba inicializace
        nextion_send_string("t0.txt=\"I2C DA CONV INIT ERROR\"");
    }
    
    //Prechod na stranku se startovacim tlacitkem
    nextion_send_string("page Start_menu");
    
    while (1) {
        status = IDLE;
        //Struct pro ukladani parametru tranzistoru
        volatile BJT tested_BJT;
        tested_BJT.h21 = 0;
        tested_BJT.polarity = FAULTY;
        
        //Nastaveni offsetu a 100mV reference !Kanál C chyba zesílení!
        volatile uint16_t da_val[4]={2048, 2048, 1900, 100};

        if (mcp4728_set_channel(MCP4728_CHANNEL_A, da_val[0], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
            // Chyba nastaveni napeti na kanalu
            nextion_send_string("t0.txt=\"ERROR CHA SET\"");
        }
        _delay_ms(10);
        if (mcp4728_set_channel(MCP4728_CHANNEL_B, da_val[1], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
            // Chyba nastaveni napeti na kanalu
            nextion_send_string("t0.txt=\"ERROR CHB SET\"");
        }
        _delay_ms(10);
        if (mcp4728_set_channel(MCP4728_CHANNEL_C, da_val[2], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
            // Chyba nastaveni napeti na kanalu
            nextion_send_string("t0.txt=\"ERROR CHC SET\"");
        }
        _delay_ms(10);
        if (mcp4728_set_channel(MCP4728_CHANNEL_D, da_val[3], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
            // Chyba nastaveni napeti na kanalu
            nextion_send_string("t0.txt=\"ERROR CHD SET\"");
        }
        _delay_ms(10);
        
        uart1_clear_receive_buffer();
        //Cekani na stisknuti start
        while (status != RUN) {_delay_us(1);}
        

        //Kontrola zda není NPN
        for (int i = 0; i < 3; i++) {

            //offset
            da_val[0]= 2048;
            da_val[1]= 2048;
            da_val[2]= 1900;

            //Zvyseni napeti na vystupu jednoho zesilovace 
            da_val[i] += 550;

            if (mcp4728_set_channel(MCP4728_CHANNEL_A, da_val[0], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                // Chyba nastaveni napeti na kanalu
                nextion_send_string("t0.txt=\"ERROR CHA SET\"");
            }
            _delay_ms(10);
            if (mcp4728_set_channel(MCP4728_CHANNEL_B, da_val[1], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                // Chyba nastaveni napeti na kanalu
                nextion_send_string("t0.txt=\"ERROR CHB SET\"");
            }
            _delay_ms(10);
            if (mcp4728_set_channel(MCP4728_CHANNEL_C, da_val[2], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                // Chyba nastaveni napeti na kanalu
                nextion_send_string("t0.txt=\"ERROR CHC SET\"");
            }
            _delay_ms(10);

            //Mereni proudu dalsimi dvema kanaly
            //Proud vetsi nez 100uA kvuli sum
            if (i==0) {
                volatile uint32_t I1,I2;
                I1 = measure_I_uA(INA_CH_B_R);
                I2 = measure_I_uA(INA_CH_C_R);
                
                if((I1 > 100) && (I2 > 100)){
                    //Osetreni prepsani vadnym tranzistorem
                    if(tested_BJT.polarity != FAULTY){
                        tested_BJT.polarity = FAULTY;
                        break;
                    }
                    tested_BJT.base_channel = MCP4728_CHANNEL_A;
                    tested_BJT.polarity = NPN;
                    
                }
                
            }
            if (i==1) {
                volatile uint32_t I1,I2;
                I1 = measure_I_uA(INA_CH_A_R);
                I2 = measure_I_uA(INA_CH_C_R);
                
                if((I1 > 100) && (I2 > 100)){
                    //Osetreni prepsani vadnym tranzistorem
                    if(tested_BJT.polarity != FAULTY){
                        tested_BJT.polarity = FAULTY;
                        break;
                    }
                    tested_BJT.base_channel = MCP4728_CHANNEL_B;
                    tested_BJT.polarity = NPN;
                    break;
                }
                
            }
            if (i==2) {
                volatile uint32_t I1,I2;
                I1 = measure_I_uA(INA_CH_A_R);
                I2 = measure_I_uA(INA_CH_B_R);
                
                if((I1 > 100) && (I2 > 100)){
                    //Osetreni prepsani vadnym tranzistorem
                    if(tested_BJT.polarity != FAULTY){
                        tested_BJT.polarity = FAULTY;
                        break;
                    }
                    tested_BJT.base_channel = MCP4728_CHANNEL_C;
                    tested_BJT.polarity = NPN;
                    break;
                }
                
            }

        }


        //Kontrola zda není PNP
        for (int i = 0; i < 3; i++) {

            //offset
            da_val[0]= 2048;
            da_val[1]= 2048;
            da_val[2]= 1900;

            //Snizeni napeti na vystupu jednoho zesilovace
            da_val[i] -= 550;

            if (mcp4728_set_channel(MCP4728_CHANNEL_A, da_val[0], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                // Chyba nastaveni napeti na kanalu
                nextion_send_string("t0.txt=\"ERROR CHA SET\"");
            }
            _delay_ms(10);
            if (mcp4728_set_channel(MCP4728_CHANNEL_B, da_val[1], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                // Chyba nastaveni napeti na kanalu
                nextion_send_string("t0.txt=\"ERROR CHB SET\"");
            }
            _delay_ms(10);
            if (mcp4728_set_channel(MCP4728_CHANNEL_C, da_val[2], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                // Chyba nastaveni napeti na kanalu
                nextion_send_string("t0.txt=\"ERROR CHC SET\"");
            }
            _delay_ms(10);
            

            //Mereni proudu dalsimi dvema kanaly
            //Proud vetsi nez 100uA
            if ((i==0) && (measure_I_uA(INA_CH_B_F)>100) && (measure_I_uA(INA_CH_C_F)>100)) {
                tested_BJT.base_channel = MCP4728_CHANNEL_A;
                tested_BJT.polarity = PNP;
                break;
            }
            if ((i==1) && (measure_I_uA(INA_CH_A_F)>100) && (measure_I_uA(INA_CH_C_F)>100)) {
                tested_BJT.base_channel = MCP4728_CHANNEL_B;
                tested_BJT.polarity = PNP;
                break;
            }
            if ((i==2) && (measure_I_uA(INA_CH_A_F)>100) && (measure_I_uA(INA_CH_B_F)>100)) {
                tested_BJT.base_channel = MCP4728_CHANNEL_C;
                tested_BJT.polarity = PNP;
                break;
            }


        }


        
        

        //MERENI h21

        
        if (tested_BJT.polarity == NPN) {

            if (tested_BJT.base_channel==MCP4728_CHANNEL_A) {
                //Kolektor na kanalu B
                da_val[0] = 0;
                da_val[1] = 4096;
                da_val[2] = 0;
                
                if (mcp4728_set_channel(MCP4728_CHANNEL_A, da_val[0], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                // Chyba nastaveni napeti na kanalu
                nextion_send_string("t0.txt=\"ERROR CHA SET\"");
                }
                _delay_ms(10);
                if (mcp4728_set_channel(MCP4728_CHANNEL_B, da_val[1], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                    // Chyba nastaveni napeti na kanalu
                    nextion_send_string("t0.txt=\"ERROR CHB SET\"");
                }
                _delay_ms(10);
                if (mcp4728_set_channel(MCP4728_CHANNEL_C, da_val[2], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                    // Chyba nastaveni napeti na kanalu
                    nextion_send_string("t0.txt=\"ERROR CHC SET\"");
                }
                _delay_ms(10);
                
                //Nastav zhruba 100uA bazi
                while (measure_I_uA(INA_CH_A_F)<100) {
                    da_val[0]++;
                    if (mcp4728_set_channel(MCP4728_CHANNEL_A, da_val[0], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                        // Chyba nastaveni napeti na kanalu
                        nextion_send_string("t0.txt=\"ERROR CHA SET\"");
                    }
                    
                }

                tested_BJT.Ib_uA = measure_I_uA(INA_CH_A_F);

                tested_BJT.Ic_mA = measure_I_mA(INA_CH_B_F);

                //Kolektor na kanalu C
                da_val[0] = 0;
                da_val[1] = 0;
                da_val[2] = 4096;
                
                if (mcp4728_set_channel(MCP4728_CHANNEL_A, da_val[0], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                // Chyba nastaveni napeti na kanalu
                nextion_send_string("t0.txt=\"ERROR CHA SET\"");
                }
                _delay_ms(10);
                if (mcp4728_set_channel(MCP4728_CHANNEL_B, da_val[1], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                    // Chyba nastaveni napeti na kanalu
                    nextion_send_string("t0.txt=\"ERROR CHB SET\"");
                }
                _delay_ms(10);
                if (mcp4728_set_channel(MCP4728_CHANNEL_C, da_val[2], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                    // Chyba nastaveni napeti na kanalu
                    nextion_send_string("t0.txt=\"ERROR CHC SET\"");
                }
                _delay_ms(10);
                
                while (measure_I_uA(INA_CH_A_F)<100) {
                    da_val[0]++;
                    if (mcp4728_set_channel(MCP4728_CHANNEL_A, da_val[0], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                        // Chyba nastaveni napeti na kanalu
                        nextion_send_string("t0.txt=\"ERROR CHA SET\"");
                    }
                    
                }

                if(tested_BJT.Ic_mA < measure_I_mA(INA_CH_C_F)){
                    tested_BJT.Ic_mA = measure_I_mA(INA_CH_C_F);
                }

                tested_BJT.h21= tested_BJT.Ic_mA / (tested_BJT.Ib_uA * 1000);

            } else if(tested_BJT.base_channel == MCP4728_CHANNEL_B) {
                //Kolektor na kanalu A
                da_val[0] = 4096;
                da_val[1] = 0;
                da_val[2] = 0;

                if (mcp4728_set_channel(MCP4728_CHANNEL_A, da_val[0], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                    // Chyba nastaveni napeti na kanalu
                    nextion_send_string("t0.txt=\"ERROR CHA SET\"");
                }
                _delay_ms(10);
                if (mcp4728_set_channel(MCP4728_CHANNEL_B, da_val[1], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                    // Chyba nastaveni napeti na kanalu
                    nextion_send_string("t0.txt=\"ERROR CHB SET\"");
                }
                _delay_ms(10);
                if (mcp4728_set_channel(MCP4728_CHANNEL_C, da_val[2], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                    // Chyba nastaveni napeti na kanalu
                    nextion_send_string("t0.txt=\"ERROR CHC SET\"");
                }
                _delay_ms(10);
                
                //Nastav 100uA na bazi
                while (measure_I_uA(INA_CH_B_F)<100) {
                    da_val[1]++;
                    if (mcp4728_set_channel(MCP4728_CHANNEL_B, da_val[1], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                        // Chyba nastaveni napeti na kanalu
                        nextion_send_string("t0.txt=\"ERROR CHB SET\"");
                    }
                    
                }

                tested_BJT.Ib_uA = measure_I_uA(INA_CH_B_F);

                tested_BJT.Ic_mA = measure_I_mA(INA_CH_A_F);

                //Kolektor na kanalu C
                da_val[0] = 0;
                da_val[1] = 0;
                da_val[2] = 4096;

                if (mcp4728_set_channel(MCP4728_CHANNEL_A, da_val[0], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                    // Chyba nastaveni napeti na kanalu
                    nextion_send_string("t0.txt=\"ERROR CHA SET\"");
                }
                _delay_ms(10);
                if (mcp4728_set_channel(MCP4728_CHANNEL_B, da_val[1], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                    // Chyba nastaveni napeti na kanalu
                    nextion_send_string("t0.txt=\"ERROR CHB SET\"");
                }
                _delay_ms(10);
                if (mcp4728_set_channel(MCP4728_CHANNEL_C, da_val[2], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                    // Chyba nastaveni napeti na kanalu
                    nextion_send_string("t0.txt=\"ERROR CHC SET\"");
                }
                _delay_ms(10);
                
                //Nastav 100uA na bazi
                while (measure_I_uA(INA_CH_B_F)<100) {
                    da_val[1]++;
                    if (mcp4728_set_channel(MCP4728_CHANNEL_B, da_val[1], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                        // Chyba nastaveni napeti na kanalu
                        nextion_send_string("t0.txt=\"ERROR CHB SET\"");
                    }
                    
                }

                if(tested_BJT.Ic_mA < measure_I_mA(INA_CH_C_F)){
                    tested_BJT.Ic_mA = measure_I_mA(INA_CH_C_F);
                }

                tested_BJT.h21= tested_BJT.Ic_mA / (tested_BJT.Ib_uA * 1000);

            }else if(tested_BJT.base_channel==MCP4728_CHANNEL_C) {
                //Kolektor na kanalu A
                da_val[0] = 4096;
                da_val[1] = 0;
                da_val[2] = 0;

                if (mcp4728_set_channel(MCP4728_CHANNEL_A, da_val[0], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                    // Chyba nastaveni napeti na kanalu
                    nextion_send_string("t0.txt=\"ERROR CHA SET\"");
                }
                _delay_ms(10);
                if (mcp4728_set_channel(MCP4728_CHANNEL_B, da_val[1], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                    // Chyba nastaveni napeti na kanalu
                    nextion_send_string("t0.txt=\"ERROR CHB SET\"");
                }
                _delay_ms(10);
                if (mcp4728_set_channel(MCP4728_CHANNEL_C, da_val[2], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                    // Chyba nastaveni napeti na kanalu
                    nextion_send_string("t0.txt=\"ERROR CHC SET\"");
                }
                _delay_ms(10);
                
                //Nastav 100uA na bazi
                while (measure_I_uA(INA_CH_C_F)<100) {
                    da_val[2]++;
                    if (mcp4728_set_channel(MCP4728_CHANNEL_C, da_val[2], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                        // Chyba nastaveni napeti na kanalu
                        nextion_send_string("t0.txt=\"ERROR CHC SET\"");
                    }
                    
                }

                tested_BJT.Ib_uA = measure_I_uA(INA_CH_C_F);

                tested_BJT.Ic_mA = measure_I_mA(INA_CH_A_F);

                //Kolektor na kanalu B
                da_val[0] = 0;
                da_val[1] = 4096;
                da_val[2] = 0;

                if (mcp4728_set_channel(MCP4728_CHANNEL_A, da_val[0], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                    // Chyba nastaveni napeti na kanalu
                    nextion_send_string("t0.txt=\"ERROR CHA SET\"");
                }
                _delay_ms(10);
                if (mcp4728_set_channel(MCP4728_CHANNEL_B, da_val[1], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                    // Chyba nastaveni napeti na kanalu
                    nextion_send_string("t0.txt=\"ERROR CHB SET\"");
                }
                _delay_ms(10);
                if (mcp4728_set_channel(MCP4728_CHANNEL_C, da_val[2], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                    // Chyba nastaveni napeti na kanalu
                    nextion_send_string("t0.txt=\"ERROR CHC SET\"");
                }
                _delay_ms(10);
                
                //Nastav 100uA na bazi
                while (measure_I_uA(INA_CH_C_F)<100) {
                    da_val[2]++;
                    if (mcp4728_set_channel(MCP4728_CHANNEL_C, da_val[2], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                        // Chyba nastaveni napeti na kanalu
                        nextion_send_string("t0.txt=\"ERROR CHC SET\"");
                    }
                    
                }

                if(tested_BJT.Ic_mA < measure_I_mA(INA_CH_B_F)){
                    tested_BJT.Ic_mA = measure_I_mA(INA_CH_B_F);
                }

                tested_BJT.h21= tested_BJT.Ic_mA / (tested_BJT.Ib_uA * 1000);
            }

        } else if(tested_BJT.polarity==PNP){
            if (tested_BJT.base_channel == MCP4728_CHANNEL_A) {
                //Kolektor na kanalu B
                da_val[0] = 4096;
                da_val[1] = 4096;
                da_val[2] = 0;

                if (mcp4728_set_channel(MCP4728_CHANNEL_A, da_val[0], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                    // Chyba nastaveni napeti na kanalu
                    nextion_send_string("t0.txt=\"ERROR CHA SET\"");
                }
                _delay_ms(10);
                if (mcp4728_set_channel(MCP4728_CHANNEL_B, da_val[1], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                    // Chyba nastaveni napeti na kanalu
                    nextion_send_string("t0.txt=\"ERROR CHB SET\"");
                }
                _delay_ms(10);
                if (mcp4728_set_channel(MCP4728_CHANNEL_C, da_val[2], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                    // Chyba nastaveni napeti na kanalu
                    nextion_send_string("t0.txt=\"ERROR CHC SET\"");
                }
                _delay_ms(10);
                
                //Nastav 100uA na bazi
                while (measure_I_uA(INA_CH_A_R)<100) {
                    da_val[0]--;
                    if (mcp4728_set_channel(MCP4728_CHANNEL_A, da_val[0], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                        // Chyba nastaveni napeti na kanalu
                        nextion_send_string("t0.txt=\"ERROR CHA SET\"");
                    }
                    
                }

                tested_BJT.Ib_uA = measure_I_uA(INA_CH_A_R);

                tested_BJT.Ic_mA = measure_I_mA(INA_CH_B_F);

                //Kolektor na kanalu C
                da_val[0] = 4096;
                da_val[1] = 0;
                da_val[2] = 4096;

                if (mcp4728_set_channel(MCP4728_CHANNEL_A, da_val[0], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                    // Chyba nastaveni napeti na kanalu
                    nextion_send_string("t0.txt=\"ERROR CHA SET\"");
                }
                _delay_ms(10);
                if (mcp4728_set_channel(MCP4728_CHANNEL_B, da_val[1], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                    // Chyba nastaveni napeti na kanalu
                    nextion_send_string("t0.txt=\"ERROR CHB SET\"");
                }
                _delay_ms(10);
                if (mcp4728_set_channel(MCP4728_CHANNEL_C, da_val[2], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                    // Chyba nastaveni napeti na kanalu
                    nextion_send_string("t0.txt=\"ERROR CHC SET\"");
                }
                _delay_ms(10);
                
                //Nastav 100uA na bazi
                while (measure_I_uA(INA_CH_A_R)<100) {
                    da_val[0]--;
                    if (mcp4728_set_channel(MCP4728_CHANNEL_A, da_val[0], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                        // Chyba nastaveni napeti na kanalu
                        nextion_send_string("t0.txt=\"ERROR CHA SET\"");
                    }
                    
                }

                if(tested_BJT.Ic_mA < measure_I_mA(INA_CH_C_F)){
                    tested_BJT.Ic_mA = measure_I_mA(INA_CH_C_F);
                }

                tested_BJT.h21= tested_BJT.Ic_mA / (tested_BJT.Ib_uA * 1000);

            } else if (tested_BJT.base_channel == MCP4728_CHANNEL_B) {
                //Kolektor na kanalu A
                da_val[0] = 4096;
                da_val[1] = 4096;
                da_val[2] = 0;

                if (mcp4728_set_channel(MCP4728_CHANNEL_A, da_val[0], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                    // Chyba nastaveni napeti na kanalu
                    nextion_send_string("t0.txt=\"ERROR CHA SET\"");
                }
                _delay_ms(10);
                if (mcp4728_set_channel(MCP4728_CHANNEL_B, da_val[1], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                    // Chyba nastaveni napeti na kanalu
                    nextion_send_string("t0.txt=\"ERROR CHB SET\"");
                }
                _delay_ms(10);
                if (mcp4728_set_channel(MCP4728_CHANNEL_C, da_val[1], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                    // Chyba nastaveni napeti na kanalu
                    nextion_send_string("t0.txt=\"ERROR CHC SET\"");
                }
                _delay_ms(10);
                
                //Nastav 100uA na bazi
                while (measure_I_uA(INA_CH_B_R)<100) {
                    da_val[1]--;
                    if (mcp4728_set_channel(MCP4728_CHANNEL_B, da_val[1], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                        // Chyba nastaveni napeti na kanalu
                        nextion_send_string("t0.txt=\"ERROR CHB SET\"");
                    }
                    
                }

                tested_BJT.Ib_uA = measure_I_uA(INA_CH_B_R);

                tested_BJT.Ic_mA = measure_I_mA(INA_CH_A_F);

                //Kolektor na kanalu C
                da_val[0] = 0;
                da_val[1] = 4096;
                da_val[2] = 4096;

                if (mcp4728_set_channel(MCP4728_CHANNEL_A, da_val[0], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                    // Chyba nastaveni napeti na kanalu
                    nextion_send_string("t0.txt=\"ERROR CHA SET\"");
                }
                _delay_ms(10);
                if (mcp4728_set_channel(MCP4728_CHANNEL_B, da_val[1], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                    // Chyba nastaveni napeti na kanalu
                    nextion_send_string("t0.txt=\"ERROR CHB SET\"");
                }
                _delay_ms(10);
                if (mcp4728_set_channel(MCP4728_CHANNEL_C, da_val[2], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                    // Chyba nastaveni napeti na kanalu
                    nextion_send_string("t0.txt=\"ERROR CHC SET\"");
                }
                _delay_ms(10);
                
                //Nastav 100uA na bazi
                while (measure_I_uA(INA_CH_B_R)<100) {
                    da_val[1]--;
                    if (mcp4728_set_channel(MCP4728_CHANNEL_B, da_val[1], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                        // Chyba nastaveni napeti na kanalu
                        nextion_send_string("t0.txt=\"ERROR CHB SET\"");
                    }
                    
                }

                if(tested_BJT.Ic_mA < measure_I_mA(INA_CH_C_F)){
                    tested_BJT.Ic_mA = measure_I_mA(INA_CH_C_F);
                }

                tested_BJT.h21= tested_BJT.Ic_mA / (tested_BJT.Ib_uA * 1000);
                
            } else if (tested_BJT.base_channel == MCP4728_CHANNEL_C) {
                //Kolektor na kanalu A
                da_val[0] = 4096;
                da_val[1] = 0;
                da_val[2] = 4096;

                if (mcp4728_set_channel(MCP4728_CHANNEL_A, da_val[0], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                    // Chyba nastaveni napeti na kanalu
                    nextion_send_string("t0.txt=\"ERROR CHA SET\"");
                }
                _delay_ms(10);
                if (mcp4728_set_channel(MCP4728_CHANNEL_B, da_val[1], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                    // Chyba nastaveni napeti na kanalu
                    nextion_send_string("t0.txt=\"ERROR CHB SET\"");
                }
                _delay_ms(10);
                if (mcp4728_set_channel(MCP4728_CHANNEL_C, da_val[2], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                    // Chyba nastaveni napeti na kanalu
                    nextion_send_string("t0.txt=\"ERROR CHC SET\"");
                }
                _delay_ms(10);
                
                //Nastav 100uA na bazi
                while (measure_I_uA(INA_CH_C_R)<100) {
                    da_val[2]--;
                    if (mcp4728_set_channel(MCP4728_CHANNEL_C, da_val[2], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                        // Chyba nastaveni napeti na kanalu
                        nextion_send_string("t0.txt=\"ERROR CHC SET\"");
                    }
                    
                }

                tested_BJT.Ib_uA = measure_I_uA(INA_CH_C_R);

                tested_BJT.Ic_mA = measure_I_mA(INA_CH_A_F);

                //Kolektor na kanalu B
                da_val[0] = 0;
                da_val[1] = 4096;
                da_val[2] = 4096;

                if (mcp4728_set_channel(MCP4728_CHANNEL_A, da_val[0], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                    // Chyba nastaveni napeti na kanalu
                    nextion_send_string("t0.txt=\"ERROR CHA SET\"");
                }
                _delay_ms(10);
                if (mcp4728_set_channel(MCP4728_CHANNEL_B, da_val[1], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                    // Chyba nastaveni napeti na kanalu
                    nextion_send_string("t0.txt=\"ERROR CHB SET\"");
                }
                _delay_ms(10);
                if (mcp4728_set_channel(MCP4728_CHANNEL_C, da_val[2], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                    // Chyba nastaveni napeti na kanalu
                    nextion_send_string("t0.txt=\"ERROR CHC SET\"");
                }
                _delay_ms(10);
                
                //Nastav 100uA na bazi
                while (measure_I_uA(INA_CH_C_R)<100) {
                    da_val[2]--;
                    if (mcp4728_set_channel(MCP4728_CHANNEL_C, da_val[2], MCP4728_VREF_INTERNAL, MCP4728_GAIN_2X, MCP4728_PD_NORMAL)) {
                        // Chyba nastaveni napeti na kanalu
                        nextion_send_string("t0.txt=\"ERROR CHC SET\"");
                    }
                    
                }

                if(tested_BJT.Ic_mA < measure_I_mA(INA_CH_B_F)){
                    tested_BJT.Ic_mA = measure_I_mA(INA_CH_B_F);
                }

                tested_BJT.h21= tested_BJT.Ic_mA / (tested_BJT.Ib_uA * 1000);

            }

        }


        //Odeslani h21 do displeje
        char h21_str[10];
        sprintf(h21_str, "%d", tested_BJT.h21);
        uart1_send_string("n0.val=");
        uart1_send_string(h21_str);
        uart1_send_byte(0xff);
        uart1_send_byte(0xff);
        uart1_send_byte(0xff);
        
        if (tested_BJT.polarity==NPN) {
            nextion_send_string("t0.txt=\"NPN\"");
        } else if(tested_BJT.polarity==PNP){
            nextion_send_string("t0.txt=\"PNP\"");
        } else {
            nextion_send_string("t0.txt=\"FAULTY OR UNRECOGNISED\"");
        }
        
    }

    
    return 0;
}

ISR(USART1_RXC_vect){
    char string[10];
    
    uart1_receive_string(string, 10, 20);
    
    if(strcmp(string, "cmd_start")) status = RUN;
}
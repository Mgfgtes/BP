/**
 * AVR64DA28 I2C knihovna - Implementace
 * 
 * Jednoducha knihovna pro komunikaci pres I2C rozhrani na mikrokontroleru AVR64DA28
 * I2C je pripojeno na piny PA3 (SCL) a PA2 (SDA)
 */

#ifndef F_CPU
# define F_CPU 16000000UL
#endif

#include "i2c.h"

// Konstanty pro casovy limit
#define I2C_TIMEOUT_COUNT 65535  // Pocet cyklu pro timeout
#define I2C_RETRY_COUNT 3      // Pocet pokusu pri chybe

i2c_status_t i2c_init(i2c_freq_t freq) {
    // Konfigurace pinu - SDA (PA2) a SCL (PA3) jako vstupy
    PORTA.DIRCLR = PIN2_bm | PIN3_bm;
       
    // Inicializace TWI0 jako master
    TWI0.MCTRLA = !TWI_ENABLE_bm;          // Docasne vypnuti pro konfiguraci
    TWI0.MBAUD = (F_CPU / (2 * freq)) - 5;  // Nastaveni rychlosti
    TWI0.MSTATUS = TWI_BUSSTATE_IDLE_gc;  // Vynulovani stavu sbernice
    TWI0.MCTRLA = TWI_ENABLE_bm;  // Povoleni TWI master
    
    return I2C_OK;
}

i2c_status_t i2c_write(uint8_t slave_addr, const uint8_t *data, uint8_t len) {
    uint8_t retry_count = 0;
    
    do {
        // Nastaveni adresy a smer (zapis)
        TWI0.MADDR = (slave_addr << 1) | 0;
        
        // Cekani na dokonceni prenosu adresy
        uint16_t timeout_counter = 0;
        while (!(TWI0.MSTATUS & (TWI_WIF_bm | TWI_RIF_bm))) {
            if (++timeout_counter > I2C_TIMEOUT_COUNT) {
                return I2C_ERROR_TIMEOUT;
            }
            
            // Kontrola chyby sbernice
            if (TWI0.MSTATUS & TWI_BUSERR_bm) {
                TWI0.MSTATUS = TWI_BUSSTATE_IDLE_gc;
                retry_count++;
                _delay_ms(1);
                break;
            }
        }
        
        // Kontrola NACK po adrese
        if (TWI0.MSTATUS & TWI_RXACK_bm) {
            TWI0.MCTRLB = TWI_MCMD_STOP_gc;
            return I2C_ERROR_NACK;
        }
        
        // Prenos dat
        for (uint8_t i = 0; i < len; i++) {
            TWI0.MDATA = data[i];
            
            // Cekani na dokonceni prenosu bajtu
            timeout_counter = 0;
            while (!(TWI0.MSTATUS & TWI_WIF_bm)) {
                if (++timeout_counter > I2C_TIMEOUT_COUNT) {
                    return I2C_ERROR_TIMEOUT;
                }
                
                // Kontrola chyby sbernice
                if (TWI0.MSTATUS & TWI_BUSERR_bm) {
                    TWI0.MSTATUS = TWI_BUSSTATE_IDLE_gc;
                    retry_count++;
                    _delay_ms(1);
                    break;
                }
            }
            
            // Kontrola NACK po datech
            if (TWI0.MSTATUS & TWI_RXACK_bm) {
                TWI0.MCTRLB = TWI_MCMD_STOP_gc;
                return I2C_ERROR_NACK;
            }
        }
        
        // Poslani STOP
        TWI0.MCTRLB = TWI_MCMD_STOP_gc;
        return I2C_OK;
        
    } while (retry_count < I2C_RETRY_COUNT);
    
    return I2C_ERROR_BUS;
}

i2c_status_t i2c_read(uint8_t slave_addr, uint8_t *data, uint8_t len) {
    uint8_t retry_count = 0;
    
    do {
        // Nastaveni adresy a smer (cteni)
        TWI0.MADDR = (slave_addr << 1) | 1;
        
        // Cekani na dokonceni prenosu adresy
        uint16_t timeout_counter = 0;
        while (!(TWI0.MSTATUS & (TWI_WIF_bm | TWI_RIF_bm))) {
            if (++timeout_counter > I2C_TIMEOUT_COUNT) {
                return I2C_ERROR_TIMEOUT;
            }
            
            // Kontrola chyby sbernice
            if (TWI0.MSTATUS & TWI_BUSERR_bm) {
                TWI0.MSTATUS = TWI_BUSSTATE_IDLE_gc;
                retry_count++;
                _delay_ms(1);
                break;
            }
        }
        
        // Kontrola NACK po adrese
        if (TWI0.MSTATUS & TWI_RXACK_bm) {
            TWI0.MCTRLB = TWI_MCMD_STOP_gc;
            return I2C_ERROR_NACK;
        }
        
        // Cteni dat
        for (uint8_t i = 0; i < len; i++) {
            // Cekani na prijeti bajtu
            timeout_counter = 0;
            while (!(TWI0.MSTATUS & TWI_RIF_bm)) {
                if (++timeout_counter > I2C_TIMEOUT_COUNT) {
                    return I2C_ERROR_TIMEOUT;
                }
                
                // Kontrola chyby sbernice
                if (TWI0.MSTATUS & TWI_BUSERR_bm) {
                    TWI0.MSTATUS = TWI_BUSSTATE_IDLE_gc;
                    retry_count++;
                    _delay_ms(1);
                    break;
                }
            }
            
            // Cteni prijateho bajtu
            data[i] = TWI0.MDATA;
            
            // Poslani ACK (nebo NACK pro posledni bajt)
            if (i == len - 1) {
                TWI0.MCTRLB = TWI_ACKACT_bm | TWI_MCMD_STOP_gc;  // NACK + STOP
            } else {
                TWI0.MCTRLB = TWI_MCMD_RECVTRANS_gc;  // ACK + pokracovani
            }
        }
        
        return I2C_OK;
        
    } while (retry_count < I2C_RETRY_COUNT);
    
    return I2C_ERROR_BUS;
}

bool i2c_device_available(uint8_t address) {
    // Zkusime odeslat pouze adresu
    TWI0.MADDR = (address << 1) | 0;
    
    // Cekani na dokonceni prenosu adresy
    uint16_t timeout_counter = 0;
    while (!(TWI0.MSTATUS & (TWI_WIF_bm | TWI_RIF_bm))) {
        if (++timeout_counter > I2C_TIMEOUT_COUNT) {
            TWI0.MCTRLB = TWI_MCMD_STOP_gc;
            return false;
        }
        
        // Kontrola chyby sbernice
        if (TWI0.MSTATUS & TWI_BUSERR_bm) {
            TWI0.MSTATUS = TWI_BUSSTATE_IDLE_gc;
            TWI0.MCTRLB = TWI_MCMD_STOP_gc;
            return false;
        }
    }
    
    // Zkontrolujeme, zda jsme dostali ACK
    bool device_present = !(TWI0.MSTATUS & TWI_RXACK_bm);
    
    // Poslani STOP
    TWI0.MCTRLB = TWI_MCMD_STOP_gc;
    
    return device_present;
}

uint8_t i2c_scan(uint8_t *devices, uint8_t max_devices) {
    uint8_t found_devices = 0;
    
    // Prohledani adres 1-127 (0 je adresa pro broadcast)
    for (uint8_t addr = 1; addr < 128 && found_devices < max_devices; addr++) {
        if (i2c_device_available(addr)) {
            devices[found_devices++] = addr;
        }
    }
    
    return found_devices;
}
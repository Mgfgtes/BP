/**
 * AVR64DA28 I2C knihovna - Implementace
 * 
 * Jednoduchá knihovna pro komunikaci p?es I2C rozhraní na mikrokontroléru AVR64DA28
 * I2C je p?ipojeno na piny PA1 (SDA) a PA2 (SCL)
 */

#include "i2c.h"
#include <util/delay.h>

#define I2C_TIMEOUT 10000    // Timeout v iteracích
#define F_CPU 16000000UL     // Frekvence CPU (16 MHz)

/**
 * Inicializace I2C rozhraní
 * 
 * @param freq Frekvence I2C sb?rnice
 * @return I2C_OK pokud byla inicializace úsp??ná
 */
i2c_status_t i2c_init(i2c_freq_t freq) {
    // Nastavení pin? pro I2C (PA1 = SDA, PA2 = SCL)
    PORTA.DIRCLR = PIN1_bm;  // SDA jako vstup
    PORTA.DIRCLR = PIN2_bm;  // SCL jako vstup
    
    // Povolení pull-up rezistor?
    PORTA.PIN1CTRL |= PORT_PULLUPEN_bm;
    PORTA.PIN2CTRL |= PORT_PULLUPEN_bm;
    
    // Výb?r pinu pro SDA
    TWI0.MADDR = 0;  // Resetování adresy Master
    TWI0.MCTRLA = 0; // Resetování ?ídícího registru
    TWI0.MSTATUS = TWI_RIF_bm | TWI_WIF_bm; // Vy?i?t?ní p?íznak?
    
    // Výpo?et hodnoty registru MBAUD pro po?adovanou frekvenci
    // BAUD = (F_CPU / (2 * freq)) - 5
    uint8_t baud = (F_CPU / (2 * freq)) - 5;
    
    // Nastavení rychlosti I2C
    TWI0.MBAUD = baud;
    
    // Povolení TWI rozhraní jako Master
    TWI0.MCTRLA = TWI_ENABLE_bm;
    
    // Nastavení stavu Smart mode
    TWI0.MCTRLB = TWI_MCMD_RECVTRANS_gc;
    
    return I2C_OK;
}

/**
 * ?ekání na dokon?ení I2C operace s timeoutem
 * 
 * @return Návratový kód operace
 */
static i2c_status_t i2c_wait_for_completion(void) {
    uint16_t timeout = 0;
    
    // ?ekání na dokon?ení operace (RIF nebo WIF)
    while (!(TWI0.MSTATUS & (TWI_RIF_bm | TWI_WIF_bm))) {
        _delay_us(1);
        timeout++;
        if (timeout >= I2C_TIMEOUT) {
            return I2C_ERROR_TIMEOUT;
        }
    }
    
    // Kontrola chyb
    if (TWI0.MSTATUS & TWI_BUSERR_bm) {
        return I2C_ERROR_BUS;
    }
    
    if (TWI0.MSTATUS & TWI_ARBLOST_bm) {
        return I2C_ERROR_BUS;
    }
    
    if (!(TWI0.MSTATUS & TWI_RXACK_bm)) {
        // RXACK = 0 znamená, ?e slave za?ízení poslalo ACK
        return I2C_OK;
    } else {
        // RXACK = 1 znamená, ?e slave za?ízení poslalo NACK
        return I2C_ERROR_NACK;
    }
}

/**
 * Za?átek I2C p?enosu
 * 
 * @param address 7-bitová adresa za?ízení
 * @param read P?íznak ?tení (true) nebo zápisu (false)
 * @return Návratový kód operace
 */
i2c_status_t i2c_start(uint8_t address, bool read) {
    // Kontrola, zda není sb?rnice zaneprázdn?na
    if (TWI0.MSTATUS & TWI_BUSSTATE_BUSY_gc) {
        return I2C_ERROR_BUSY;
    }
    
    // Nastavení adresy Master - adresa za?ízení a typ operace (R/W)
    TWI0.MADDR = (address << 1) | (read ? 1 : 0);
    
    // ?ekání na dokon?ení operace
    return i2c_wait_for_completion();
}

/**
 * Ukon?ení I2C p?enosu
 */
void i2c_stop(void) {
    // Odeslání STOP podmínky
    TWI0.MCTRLB = TWI_MCMD_STOP_gc;
}

/**
 * Odeslání bajtu p?es I2C
 * 
 * @param data Bajt k odeslání
 * @return Návratový kód operace
 */
i2c_status_t i2c_write(uint8_t data) {
    // Odeslání dat
    TWI0.MDATA = data;
    
    // ?ekání na dokon?ení operace
    return i2c_wait_for_completion();
}

/**
 * ?tení bajtu p?es I2C s mo?ností ukon?ení p?enosu
 * 
 * @param data Ukazatel na místo pro ulo?ení p?ijatého bajtu
 * @param ack P?íznak, zda poslat ACK (true) nebo NACK (false) po p?ijetí
 * @return Návratový kód operace
 */
i2c_status_t i2c_read(uint8_t *data, bool ack) {
    i2c_status_t status;
    
    // ?ekání na dokon?ení p?edchozí operace
    status = i2c_wait_for_completion();
    if (status != I2C_OK) {
        return status;
    }
    
    // P?e?tení dat
    *data = TWI0.MDATA;
    
    // Nastavení ACK/NACK
    if (ack) {
        // Poslat ACK, pokra?ovat v p?enosu
        TWI0.MCTRLB = TWI_ACKACT_ACK_gc | TWI_MCMD_RECVTRANS_gc;
    } else {
        // Poslat NACK, ukon?it p?enos
        TWI0.MCTRLB = TWI_ACKACT_NACK_gc | TWI_MCMD_RECVTRANS_gc;
    }
    
    return I2C_OK;
}

/**
 * Zápis více bajt? do I2C za?ízení
 * 
 * @param address Adresa za?ízení
 * @param reg Registr, do kterého zapisujeme
 * @param data Ukazatel na data k odeslání
 * @param len Po?et bajt? k odeslání
 * @return Návratový kód operace
 */
i2c_status_t i2c_write_bytes(uint8_t address, uint8_t reg, const uint8_t *data, uint8_t len) {
    i2c_status_t status;
    
    // Zahájení p?enosu (zápis)
    status = i2c_start(address, false);
    if (status != I2C_OK) {
        i2c_stop();
        return status;
    }
    
    // Odeslání adresy registru
    status = i2c_write(reg);
    if (status != I2C_OK) {
        i2c_stop();
        return status;
    }
    
    // Odeslání v?ech bajt?
    for (uint8_t i = 0; i < len; i++) {
        status = i2c_write(data[i]);
        if (status != I2C_OK) {
            i2c_stop();
            return status;
        }
    }
    
    // Ukon?ení p?enosu
    i2c_stop();
    
    return I2C_OK;
}

/**
 * ?tení více bajt? z I2C za?ízení
 * 
 * @param address Adresa za?ízení
 * @param reg Registr, ze kterého ?teme
 * @param data Ukazatel na místo pro ulo?ení p?ijatých dat
 * @param len Po?et bajt? k p?ijetí
 * @return Návratový kód operace
 */
i2c_status_t i2c_read_bytes(uint8_t address, uint8_t reg, uint8_t *data, uint8_t len) {
    i2c_status_t status;
    
    // Zahájení p?enosu (zápis)
    status = i2c_start(address, false);
    if (status != I2C_OK) {
        i2c_stop();
        return status;
    }
    
    // Odeslání adresy registru
    status = i2c_write(reg);
    if (status != I2C_OK) {
        i2c_stop();
        return status;
    }
    
    // Zahájení p?enosu (?tení)
    status = i2c_start(address, true);
    if (status != I2C_OK) {
        i2c_stop();
        return status;
    }
    
    // ?tení bajt?
    for (uint8_t i = 0; i < len; i++) {
        // Poslední bajt obdr?í NACK, ostatní ACK
        status = i2c_read(&data[i], (i < len - 1));
        if (status != I2C_OK) {
            i2c_stop();
            return status;
        }
    }
    
    // Ukon?ení p?enosu
    i2c_stop();
    
    return I2C_OK;
}

/**
 * Zápis jednoho bajtu do I2C za?ízení
 * 
 * @param address Adresa za?ízení
 * @param reg Registr, do kterého zapisujeme
 * @param data Hodnota k zápisu
 * @return Návratový kód operace
 */
i2c_status_t i2c_write_byte(uint8_t address, uint8_t reg, uint8_t data) {
    return i2c_write_bytes(address, reg, &data, 1);
}

/**
 * ?tení jednoho bajtu z I2C za?ízení
 * 
 * @param address Adresa za?ízení
 * @param reg Registr, ze kterého ?teme
 * @param data Ukazatel na místo pro ulo?ení p?ijatého bajtu
 * @return Návratový kód operace
 */
i2c_status_t i2c_read_byte(uint8_t address, uint8_t reg, uint8_t *data) {
    return i2c_read_bytes(address, reg, data, 1);
}

/**
 * Zji?t?ní, zda za?ízení odpovídá na dané adrese
 * 
 * @param address Adresa za?ízení
 * @return true pokud za?ízení odpovídá, jinak false
 */
bool i2c_device_available(uint8_t address) {
    i2c_status_t status = i2c_start(address, false);
    i2c_stop();
    
    return (status == I2C_OK);
}

/**
 * Skenování I2C sb?rnice pro nalezení p?ipojených za?ízení
 * 
 * @param devices Pole pro ulo?ení nalezených adres
 * @param max_devices Maximální po?et za?ízení k nalezení
 * @return Po?et nalezených za?ízení
 */
uint8_t i2c_scan(uint8_t *devices, uint8_t max_devices) {
    uint8_t count = 0;
    
    // Skenování celého adresního prostoru (7-bit adresy: 0x08-0x77)
    for (uint8_t address = 0x08; address <= 0x77; address++) {
        if (i2c_device_available(address)) {
            if (count < max_devices) {
                devices[count] = address;
            }
            count++;
        }
    }
    
    return count;
}
/**
 * AVR64DA28 I2C knihovna - Implementace
 * 
 * Jednoduch� knihovna pro komunikaci p?es I2C rozhran� na mikrokontrol�ru AVR64DA28
 * I2C je p?ipojeno na piny PA1 (SDA) a PA2 (SCL)
 */

#include "i2c.h"
#include <util/delay.h>

#define I2C_TIMEOUT 10000    // Timeout v iterac�ch
#define F_CPU 16000000UL     // Frekvence CPU (16 MHz)

/**
 * Inicializace I2C rozhran�
 * 
 * @param freq Frekvence I2C sb?rnice
 * @return I2C_OK pokud byla inicializace �sp??n�
 */
i2c_status_t i2c_init(i2c_freq_t freq) {
    // Nastaven� pin? pro I2C (PA1 = SDA, PA2 = SCL)
    PORTA.DIRCLR = PIN1_bm;  // SDA jako vstup
    PORTA.DIRCLR = PIN2_bm;  // SCL jako vstup
    
    // Povolen� pull-up rezistor?
    PORTA.PIN1CTRL |= PORT_PULLUPEN_bm;
    PORTA.PIN2CTRL |= PORT_PULLUPEN_bm;
    
    // V�b?r pinu pro SDA
    TWI0.MADDR = 0;  // Resetov�n� adresy Master
    TWI0.MCTRLA = 0; // Resetov�n� ?�d�c�ho registru
    TWI0.MSTATUS = TWI_RIF_bm | TWI_WIF_bm; // Vy?i?t?n� p?�znak?
    
    // V�po?et hodnoty registru MBAUD pro po?adovanou frekvenci
    // BAUD = (F_CPU / (2 * freq)) - 5
    uint8_t baud = (F_CPU / (2 * freq)) - 5;
    
    // Nastaven� rychlosti I2C
    TWI0.MBAUD = baud;
    
    // Povolen� TWI rozhran� jako Master
    TWI0.MCTRLA = TWI_ENABLE_bm;
    
    // Nastaven� stavu Smart mode
    TWI0.MCTRLB = TWI_MCMD_RECVTRANS_gc;
    
    return I2C_OK;
}

/**
 * ?ek�n� na dokon?en� I2C operace s timeoutem
 * 
 * @return N�vratov� k�d operace
 */
static i2c_status_t i2c_wait_for_completion(void) {
    uint16_t timeout = 0;
    
    // ?ek�n� na dokon?en� operace (RIF nebo WIF)
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
        // RXACK = 0 znamen�, ?e slave za?�zen� poslalo ACK
        return I2C_OK;
    } else {
        // RXACK = 1 znamen�, ?e slave za?�zen� poslalo NACK
        return I2C_ERROR_NACK;
    }
}

/**
 * Za?�tek I2C p?enosu
 * 
 * @param address 7-bitov� adresa za?�zen�
 * @param read P?�znak ?ten� (true) nebo z�pisu (false)
 * @return N�vratov� k�d operace
 */
i2c_status_t i2c_start(uint8_t address, bool read) {
    // Kontrola, zda nen� sb?rnice zanepr�zdn?na
    if (TWI0.MSTATUS & TWI_BUSSTATE_BUSY_gc) {
        return I2C_ERROR_BUSY;
    }
    
    // Nastaven� adresy Master - adresa za?�zen� a typ operace (R/W)
    TWI0.MADDR = (address << 1) | (read ? 1 : 0);
    
    // ?ek�n� na dokon?en� operace
    return i2c_wait_for_completion();
}

/**
 * Ukon?en� I2C p?enosu
 */
void i2c_stop(void) {
    // Odesl�n� STOP podm�nky
    TWI0.MCTRLB = TWI_MCMD_STOP_gc;
}

/**
 * Odesl�n� bajtu p?es I2C
 * 
 * @param data Bajt k odesl�n�
 * @return N�vratov� k�d operace
 */
i2c_status_t i2c_write(uint8_t data) {
    // Odesl�n� dat
    TWI0.MDATA = data;
    
    // ?ek�n� na dokon?en� operace
    return i2c_wait_for_completion();
}

/**
 * ?ten� bajtu p?es I2C s mo?nost� ukon?en� p?enosu
 * 
 * @param data Ukazatel na m�sto pro ulo?en� p?ijat�ho bajtu
 * @param ack P?�znak, zda poslat ACK (true) nebo NACK (false) po p?ijet�
 * @return N�vratov� k�d operace
 */
i2c_status_t i2c_read(uint8_t *data, bool ack) {
    i2c_status_t status;
    
    // ?ek�n� na dokon?en� p?edchoz� operace
    status = i2c_wait_for_completion();
    if (status != I2C_OK) {
        return status;
    }
    
    // P?e?ten� dat
    *data = TWI0.MDATA;
    
    // Nastaven� ACK/NACK
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
 * Z�pis v�ce bajt? do I2C za?�zen�
 * 
 * @param address Adresa za?�zen�
 * @param reg Registr, do kter�ho zapisujeme
 * @param data Ukazatel na data k odesl�n�
 * @param len Po?et bajt? k odesl�n�
 * @return N�vratov� k�d operace
 */
i2c_status_t i2c_write_bytes(uint8_t address, uint8_t reg, const uint8_t *data, uint8_t len) {
    i2c_status_t status;
    
    // Zah�jen� p?enosu (z�pis)
    status = i2c_start(address, false);
    if (status != I2C_OK) {
        i2c_stop();
        return status;
    }
    
    // Odesl�n� adresy registru
    status = i2c_write(reg);
    if (status != I2C_OK) {
        i2c_stop();
        return status;
    }
    
    // Odesl�n� v?ech bajt?
    for (uint8_t i = 0; i < len; i++) {
        status = i2c_write(data[i]);
        if (status != I2C_OK) {
            i2c_stop();
            return status;
        }
    }
    
    // Ukon?en� p?enosu
    i2c_stop();
    
    return I2C_OK;
}

/**
 * ?ten� v�ce bajt? z I2C za?�zen�
 * 
 * @param address Adresa za?�zen�
 * @param reg Registr, ze kter�ho ?teme
 * @param data Ukazatel na m�sto pro ulo?en� p?ijat�ch dat
 * @param len Po?et bajt? k p?ijet�
 * @return N�vratov� k�d operace
 */
i2c_status_t i2c_read_bytes(uint8_t address, uint8_t reg, uint8_t *data, uint8_t len) {
    i2c_status_t status;
    
    // Zah�jen� p?enosu (z�pis)
    status = i2c_start(address, false);
    if (status != I2C_OK) {
        i2c_stop();
        return status;
    }
    
    // Odesl�n� adresy registru
    status = i2c_write(reg);
    if (status != I2C_OK) {
        i2c_stop();
        return status;
    }
    
    // Zah�jen� p?enosu (?ten�)
    status = i2c_start(address, true);
    if (status != I2C_OK) {
        i2c_stop();
        return status;
    }
    
    // ?ten� bajt?
    for (uint8_t i = 0; i < len; i++) {
        // Posledn� bajt obdr?� NACK, ostatn� ACK
        status = i2c_read(&data[i], (i < len - 1));
        if (status != I2C_OK) {
            i2c_stop();
            return status;
        }
    }
    
    // Ukon?en� p?enosu
    i2c_stop();
    
    return I2C_OK;
}

/**
 * Z�pis jednoho bajtu do I2C za?�zen�
 * 
 * @param address Adresa za?�zen�
 * @param reg Registr, do kter�ho zapisujeme
 * @param data Hodnota k z�pisu
 * @return N�vratov� k�d operace
 */
i2c_status_t i2c_write_byte(uint8_t address, uint8_t reg, uint8_t data) {
    return i2c_write_bytes(address, reg, &data, 1);
}

/**
 * ?ten� jednoho bajtu z I2C za?�zen�
 * 
 * @param address Adresa za?�zen�
 * @param reg Registr, ze kter�ho ?teme
 * @param data Ukazatel na m�sto pro ulo?en� p?ijat�ho bajtu
 * @return N�vratov� k�d operace
 */
i2c_status_t i2c_read_byte(uint8_t address, uint8_t reg, uint8_t *data) {
    return i2c_read_bytes(address, reg, data, 1);
}

/**
 * Zji?t?n�, zda za?�zen� odpov�d� na dan� adrese
 * 
 * @param address Adresa za?�zen�
 * @return true pokud za?�zen� odpov�d�, jinak false
 */
bool i2c_device_available(uint8_t address) {
    i2c_status_t status = i2c_start(address, false);
    i2c_stop();
    
    return (status == I2C_OK);
}

/**
 * Skenov�n� I2C sb?rnice pro nalezen� p?ipojen�ch za?�zen�
 * 
 * @param devices Pole pro ulo?en� nalezen�ch adres
 * @param max_devices Maxim�ln� po?et za?�zen� k nalezen�
 * @return Po?et nalezen�ch za?�zen�
 */
uint8_t i2c_scan(uint8_t *devices, uint8_t max_devices) {
    uint8_t count = 0;
    
    // Skenov�n� cel�ho adresn�ho prostoru (7-bit adresy: 0x08-0x77)
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
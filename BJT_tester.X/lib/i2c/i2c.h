/**
 * AVR64DA28 I2C knihovna - Hlavi?kov� soubor
 * 
 * Jednoduch� knihovna pro komunikaci p?es I2C rozhran� na mikrokontrol�ru AVR64DA28
 * I2C je p?ipojeno na piny PA1 (SDA) a PA2 (SCL)
 */

#ifndef I2C_H
#define I2C_H

#include <avr/io.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * Definice standardn�ch I2C frekvenc�
 */
typedef enum {
    I2C_FREQ_100KHZ = 100000,  // Standard mode
    I2C_FREQ_400KHZ = 400000,  // Fast mode
    I2C_FREQ_1MHZ   = 1000000  // Fast mode plus
} i2c_freq_t;

/**
 * N�vratov� k�dy funkc� I2C
 */
typedef enum {
    I2C_OK = 0,           // Operace byla �sp??n�
    I2C_ERROR_NACK,       // Za?�zen� neodpov?d?lo (NACK)
    I2C_ERROR_TIMEOUT,    // Vypr?el ?asov� limit
    I2C_ERROR_BUS,        // Chyba na I2C sb?rnici
    I2C_ERROR_BUSY        // Sb?rnice je zanepr�zdn?na
} i2c_status_t;

/**
 * Inicializace I2C rozhran�
 * 
 * @param freq Frekvence I2C sb?rnice
 * @return I2C_OK pokud byla inicializace �sp??n�
 */
i2c_status_t i2c_init(i2c_freq_t freq);

/**
 * Za?�tek I2C p?enosu
 * 
 * @param address 7-bitov� adresa za?�zen�
 * @param read P?�znak ?ten� (true) nebo z�pisu (false)
 * @return N�vratov� k�d operace
 */
i2c_status_t i2c_start(uint8_t address, bool read);

/**
 * Ukon?en� I2C p?enosu
 */
void i2c_stop(void);

/**
 * Odesl�n� bajtu p?es I2C
 * 
 * @param data Bajt k odesl�n�
 * @return N�vratov� k�d operace
 */
i2c_status_t i2c_write(uint8_t data);

/**
 * ?ten� bajtu p?es I2C s mo?nost� ukon?en� p?enosu
 * 
 * @param data Ukazatel na m�sto pro ulo?en� p?ijat�ho bajtu
 * @param ack P?�znak, zda poslat ACK (true) nebo NACK (false) po p?ijet�
 * @return N�vratov� k�d operace
 */
i2c_status_t i2c_read(uint8_t *data, bool ack);

/**
 * Z�pis v�ce bajt? do I2C za?�zen�
 * 
 * @param address Adresa za?�zen�
 * @param reg Registr, do kter�ho zapisujeme
 * @param data Ukazatel na data k odesl�n�
 * @param len Po?et bajt? k odesl�n�
 * @return N�vratov� k�d operace
 */
i2c_status_t i2c_write_bytes(uint8_t address, uint8_t reg, const uint8_t *data, uint8_t len);

/**
 * ?ten� v�ce bajt? z I2C za?�zen�
 * 
 * @param address Adresa za?�zen�
 * @param reg Registr, ze kter�ho ?teme
 * @param data Ukazatel na m�sto pro ulo?en� p?ijat�ch dat
 * @param len Po?et bajt? k p?ijet�
 * @return N�vratov� k�d operace
 */
i2c_status_t i2c_read_bytes(uint8_t address, uint8_t reg, uint8_t *data, uint8_t len);

/**
 * Z�pis jednoho bajtu do I2C za?�zen�
 * 
 * @param address Adresa za?�zen�
 * @param reg Registr, do kter�ho zapisujeme
 * @param data Hodnota k z�pisu
 * @return N�vratov� k�d operace
 */
i2c_status_t i2c_write_byte(uint8_t address, uint8_t reg, uint8_t data);

/**
 * ?ten� jednoho bajtu z I2C za?�zen�
 * 
 * @param address Adresa za?�zen�
 * @param reg Registr, ze kter�ho ?teme
 * @param data Ukazatel na m�sto pro ulo?en� p?ijat�ho bajtu
 * @return N�vratov� k�d operace
 */
i2c_status_t i2c_read_byte(uint8_t address, uint8_t reg, uint8_t *data);

/**
 * Zji?t?n�, zda za?�zen� odpov�d� na dan� adrese
 * 
 * @param address Adresa za?�zen�
 * @return true pokud za?�zen� odpov�d�, jinak false
 */
bool i2c_device_available(uint8_t address);

/**
 * Skenov�n� I2C sb?rnice pro nalezen� p?ipojen�ch za?�zen�
 * 
 * @param devices Pole pro ulo?en� nalezen�ch adres
 * @param max_devices Maxim�ln� po?et za?�zen� k nalezen�
 * @return Po?et nalezen�ch za?�zen�
 */
uint8_t i2c_scan(uint8_t *devices, uint8_t max_devices);

#endif // I2C_H
/**
 * AVR64DA28 I2C knihovna - Hlavi?kový soubor
 * 
 * Jednoduchá knihovna pro komunikaci p?es I2C rozhraní na mikrokontroléru AVR64DA28
 * I2C je p?ipojeno na piny PA1 (SDA) a PA2 (SCL)
 */

#ifndef I2C_H
#define I2C_H

#include <avr/io.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * Definice standardních I2C frekvencí
 */
typedef enum {
    I2C_FREQ_100KHZ = 100000,  // Standard mode
    I2C_FREQ_400KHZ = 400000,  // Fast mode
    I2C_FREQ_1MHZ   = 1000000  // Fast mode plus
} i2c_freq_t;

/**
 * Návratové kódy funkcí I2C
 */
typedef enum {
    I2C_OK = 0,           // Operace byla úsp??ná
    I2C_ERROR_NACK,       // Za?ízení neodpov?d?lo (NACK)
    I2C_ERROR_TIMEOUT,    // Vypr?el ?asový limit
    I2C_ERROR_BUS,        // Chyba na I2C sb?rnici
    I2C_ERROR_BUSY        // Sb?rnice je zaneprázdn?na
} i2c_status_t;

/**
 * Inicializace I2C rozhraní
 * 
 * @param freq Frekvence I2C sb?rnice
 * @return I2C_OK pokud byla inicializace úsp??ná
 */
i2c_status_t i2c_init(i2c_freq_t freq);

/**
 * Za?átek I2C p?enosu
 * 
 * @param address 7-bitová adresa za?ízení
 * @param read P?íznak ?tení (true) nebo zápisu (false)
 * @return Návratový kód operace
 */
i2c_status_t i2c_start(uint8_t address, bool read);

/**
 * Ukon?ení I2C p?enosu
 */
void i2c_stop(void);

/**
 * Odeslání bajtu p?es I2C
 * 
 * @param data Bajt k odeslání
 * @return Návratový kód operace
 */
i2c_status_t i2c_write(uint8_t data);

/**
 * ?tení bajtu p?es I2C s mo?ností ukon?ení p?enosu
 * 
 * @param data Ukazatel na místo pro ulo?ení p?ijatého bajtu
 * @param ack P?íznak, zda poslat ACK (true) nebo NACK (false) po p?ijetí
 * @return Návratový kód operace
 */
i2c_status_t i2c_read(uint8_t *data, bool ack);

/**
 * Zápis více bajt? do I2C za?ízení
 * 
 * @param address Adresa za?ízení
 * @param reg Registr, do kterého zapisujeme
 * @param data Ukazatel na data k odeslání
 * @param len Po?et bajt? k odeslání
 * @return Návratový kód operace
 */
i2c_status_t i2c_write_bytes(uint8_t address, uint8_t reg, const uint8_t *data, uint8_t len);

/**
 * ?tení více bajt? z I2C za?ízení
 * 
 * @param address Adresa za?ízení
 * @param reg Registr, ze kterého ?teme
 * @param data Ukazatel na místo pro ulo?ení p?ijatých dat
 * @param len Po?et bajt? k p?ijetí
 * @return Návratový kód operace
 */
i2c_status_t i2c_read_bytes(uint8_t address, uint8_t reg, uint8_t *data, uint8_t len);

/**
 * Zápis jednoho bajtu do I2C za?ízení
 * 
 * @param address Adresa za?ízení
 * @param reg Registr, do kterého zapisujeme
 * @param data Hodnota k zápisu
 * @return Návratový kód operace
 */
i2c_status_t i2c_write_byte(uint8_t address, uint8_t reg, uint8_t data);

/**
 * ?tení jednoho bajtu z I2C za?ízení
 * 
 * @param address Adresa za?ízení
 * @param reg Registr, ze kterého ?teme
 * @param data Ukazatel na místo pro ulo?ení p?ijatého bajtu
 * @return Návratový kód operace
 */
i2c_status_t i2c_read_byte(uint8_t address, uint8_t reg, uint8_t *data);

/**
 * Zji?t?ní, zda za?ízení odpovídá na dané adrese
 * 
 * @param address Adresa za?ízení
 * @return true pokud za?ízení odpovídá, jinak false
 */
bool i2c_device_available(uint8_t address);

/**
 * Skenování I2C sb?rnice pro nalezení p?ipojených za?ízení
 * 
 * @param devices Pole pro ulo?ení nalezených adres
 * @param max_devices Maximální po?et za?ízení k nalezení
 * @return Po?et nalezených za?ízení
 */
uint8_t i2c_scan(uint8_t *devices, uint8_t max_devices);

#endif // I2C_H
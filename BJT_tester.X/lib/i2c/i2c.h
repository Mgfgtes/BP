/**
 * AVR64DA28 I2C knihovna
 * 
 * Jednoducha knihovna pro komunikaci pres I2C rozhrani na mikrokontroleru AVR64DA28
 * I2C je pripojeno na piny PA2 (SDA) a PA3 (SCL)
 */
#ifndef I2C_H
#define I2C_H
#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>
#include <util/delay.h>

/**
 * Definice standardních I2C frekvencí
 */
typedef enum {
    I2C_NORMAL_MODE_100KHZ = 100000,  // Standard mode
    I2C_FAST_MODE_400KHZ = 400000,  // Fast mode
    I2C_FAST_MODE_PLUS_1MHZ   = 1000000  // Fast mode plus
} i2c_freq_t;
/**
 * Navratove kody funkci I2C
 */
typedef enum {
    I2C_OK = 0,           // Operace byla uspesna
    I2C_ERROR_NACK,       // Zarizeni neodpovedelo (NACK)
    I2C_ERROR_TIMEOUT,    // Vyprsel casovy limit
    I2C_ERROR_BUS,        // Chyba na I2C sbernici
    I2C_ERROR_BUSY        // Sbernice je zaneprazdnena
} i2c_status_t;
/**
 * Inicializace I2C rozhrani
 * 
 * @param freq Frekvence I2C sbernice
 * @return I2C_OK pokud byla inicializace uspesna
 */
i2c_status_t i2c_init(i2c_freq_t freq);
/**
 * Zapis dat na I2C sbernici
 * @param slave_addr adresa zarizeni
 * @param data ukazatel na data k odeslani
 * @param len pocet bajtu k odeslani
 * @return navratovy kod (viz i2c_status_t)
 */
i2c_status_t i2c_write(uint8_t slave_addr, const uint8_t *data, uint8_t len);
/**
 * Cteni dat z I2C sbernice
 * @param slave_addr adresa zarizeni (7-bit)
 * @param data ukazatel na buffer pro prijata data
 * @param len pocet bajtu k precteni
 * @return navratovy kod (viz i2c_status_t)
 */
i2c_status_t i2c_read(uint8_t slave_addr, uint8_t *data, uint8_t len);
/**
 * Zjisteni, zda zarizeni odpovida na dane adrese
 * 
 * @param address Adresa zarizeni
 * @return true pokud zarizeni odpovida, jinak false
 */
bool i2c_device_available(uint8_t address);
/**
 * Skenovani I2C sbernice pro nalezeni pripojenych zarizeni
 * 
 * @param devices Pole pro ulozeni nalezenych adres
 * @param max_devices Maximalni pocet zarizeni k nalezeni
 * @return Pocet nalezenych zarizeni
 */
uint8_t i2c_scan(uint8_t *devices, uint8_t max_devices);
#endif // I2C_H
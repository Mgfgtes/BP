/**
 * MCP4728A1 knihovna pro AVR64DA28
 * 
 * Ovladac pro 12-bitovy, 4-kanalovy DA prevodnik MCP4728A1
 * Vyuziva I2C knihovnu pro AVR64DA28
 */
#ifndef MCP4728_H
#define MCP4728_H

#include "../i2c/i2c.h"
#include <stdint.h>
#include <stdbool.h>

/**
 * Vychozi I2C adresa MCP4728A1
 * MCP4728A1 ma zakladni adresu 0x60 (96 desitkove), 
 * ale muze byt zmenena pomoci adresnich bitu A0, A1, A2
 */
#define MCP4728_DEFAULT_ADDRESS 0x60

/**
 * Kanaly MCP4728A1
 */
typedef enum {
    MCP4728_CHANNEL_A = 0,
    MCP4728_CHANNEL_B = 1,
    MCP4728_CHANNEL_C = 2,
    MCP4728_CHANNEL_D = 3
} mcp4728_channel_t;

/**
 * Napetove reference pro MCP4728A1
 */
typedef enum {
    MCP4728_VREF_VDD = 0,    // Pouzit VDD jako referenci
    MCP4728_VREF_INTERNAL = 1 // Pouzit interni referenci (2.048V)
} mcp4728_vref_t;

/**
 * Zes�len� v�stupu
 */
typedef enum {
    MCP4728_GAIN_1X = 0,     // Zes�len� 1x
    MCP4728_GAIN_2X = 1      // Zes�len� 2x
} mcp4728_gain_t;

/**
 * Power-down m�dy
 */
typedef enum {
    MCP4728_PD_NORMAL = 0,       // Norm�ln� operace
    MCP4728_PD_1K = 1,           // Power-down s 1 kOhm rezistorem na GND
    MCP4728_PD_100K = 2,         // Power-down se 100 kOhm rezistorem na GND
    MCP4728_PD_500K = 3          // Power-down s 500 kOhm rezistorem na GND
} mcp4728_powerdown_t;

/**
 * Inicializace MCP4728A1
 * 
 * @param address I2C adresa za?�zen� (0x60 + addrBits)
 * @return I2C_OK pokud byla inicializace �sp??n�
 */
i2c_status_t mcp4728_init(uint8_t address);

/**
 * Nastaven� hodnoty na jednom kan�lu
 * 
 * @param channel Kan�l (A, B, C nebo D)
 * @param value Hodnota (0-4095)
 * @param vref Volba nap??ov� reference (VDD nebo intern�)
 * @param gain Volba zes�len� (1x nebo 2x)
 * @param powerDown Volba power-down m�du
 * @return I2C_OK pokud byla operace �sp??n�
 */
i2c_status_t mcp4728_set_channel(mcp4728_channel_t channel, uint16_t value, 
                                mcp4728_vref_t vref, mcp4728_gain_t gain,
                                mcp4728_powerdown_t powerDown);

/**
 * Rychl� nastaven� hodnoty na jednom kan�lu (pou?ije posledn� nastaven� pro vref, gain a power-down)
 * 
 * @param channel Kan�l (A, B, C nebo D)
 * @param value Hodnota (0-4095)
 * @return I2C_OK pokud byla operace �sp??n�
 */
i2c_status_t mcp4728_fast_write(mcp4728_channel_t channel, uint16_t value);

/**
 * Nastaven� v?ech kan�l? najednou
 * 
 * @param values Pole hodnot pro kan�ly A, B, C, D (0-4095)
 * @return I2C_OK pokud byla operace �sp??n�
 */
i2c_status_t mcp4728_set_all_channels(uint16_t values[4]);

/**
 * Obecn� reset p?evodn�ku
 * 
 * @return I2C_OK pokud byla operace �sp??n�
 */
i2c_status_t mcp4728_general_reset(void);

/**
 * Proveden� p?�kazu wakeup (probuzen� z power-down re?imu)
 * 
 * @return I2C_OK pokud byla operace �sp??n�
 */
i2c_status_t mcp4728_wakeup(void);

#endif // MCP4728_H
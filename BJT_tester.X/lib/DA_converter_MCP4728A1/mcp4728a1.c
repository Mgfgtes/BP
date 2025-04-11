/**
 * MCP4728A1 knihovna pro AVR64DA28 - Implementace
 * 
 * Ovladac pro 12-bitovy, 4-kanalovy DA prevodnik MCP4728A1
 * Vyuziva I2C knihovnu pro AVR64DA28
 */

#include "mcp4728a1.h"

// P?�kazy pro MCP4728A1
#define MCP4728_CMD_FAST_WRITE       0x00 // Rychl� nastaven� hodnot
#define MCP4728_CMD_MULTI_WRITE      0x40 // V�cen�sobn� z�pis
#define MCP4728_CMD_SEQ_WRITE        0x50 // Sekven?n� z�pis
#define MCP4728_CMD_SINGLE_WRITE     0x58 // Z�pis jednoho kan�lu
#define MCP4728_CMD_VREF_WRITE       0x80 // Nastaven� reference
#define MCP4728_CMD_GAIN_WRITE       0xC0 // Nastaven� zes�len�
#define MCP4728_CMD_PD_WRITE         0xA0 // Nastaven� power-down
#define MCP4728_CMD_GEN_CALL_RESET   0x06 // Obecn� reset
#define MCP4728_CMD_GEN_CALL_WAKEUP  0x09 // Obecn� probuzen�

// Statick� prom?nn� pro ulo?en� adresy za?�zen�
static uint8_t _mcp4728_address = MCP4728_DEFAULT_ADDRESS;

i2c_status_t mcp4728_init(uint8_t address) {
    _mcp4728_address = address;
    
    // Zkontrolujeme, zda je za?�zen� dostupn�
    if (!i2c_device_available(_mcp4728_address)) {
        return I2C_ERROR_NACK;
    }
    
    return I2C_OK;
}

i2c_status_t mcp4728_set_channel(mcp4728_channel_t channel, uint16_t value, 
                                mcp4728_vref_t vref, mcp4728_gain_t gain,
                                mcp4728_powerdown_t powerDown) {
    
    // Omezen� hodnoty na 12 bit? (0-4095)
    if (value > 4095) {
        value = 4095;
    }
    
    // Slo?en� p?�kazu pro single write
    uint8_t data[3];
    
    // Prvn� byte: p?�kaz a kan�l
    data[0] = MCP4728_CMD_SINGLE_WRITE | (channel << 1);
    
    // Druh� byte: konfigurace a horn� 4 bity hodnoty
    data[1] = (vref << 7) | (powerDown << 5) | (gain << 4) | ((value >> 8) & 0x0F);
    
    // T?et� byte: doln�ch 8 bit? hodnoty
    data[2] = value & 0xFF;
    
    // Odesl�n� p?es I2C
    return i2c_write(_mcp4728_address, data, 3);
}

i2c_status_t mcp4728_fast_write(mcp4728_channel_t channel, uint16_t value) {
    // Omezen� hodnoty na 12 bit? (0-4095)
    if (value > 4095) {
        value = 4095;
    }
    
    // Slo?en� p?�kazu pro fast write
    uint8_t data[2];
    
    // Fast write m� specifick� form�t:
    // Prvn� byte: horn� 8 bit? hodnoty s DAC adresou v nejvy??�ch 2 bitech
    data[0] = (channel << 6) | ((value >> 4) & 0x3F);
    
    // Druh� byte: doln�ch 4 bity hodnoty v horn�ch 4 bitech
    data[1] = (value & 0x0F) << 4;
    
    // Odesl�n� p?es I2C
    return i2c_write(_mcp4728_address, data, 2);
}

i2c_status_t mcp4728_set_all_channels(uint16_t values[4]) {
    // Slo?en� p?�kazu pro multi write
    uint8_t data[9];
    data[0] = MCP4728_CMD_MULTI_WRITE;
    
    // Pro ka?d� kan�l p?id�me 2 byty
    for (uint8_t i = 0; i < 4; i++) {
        // Omezen� hodnoty na 12 bit?
        if (values[i] > 4095) {
            values[i] = 4095;
        }
        
        // P?id�n� horn�ch 8 bit?
        data[i*2 + 1] = (values[i] >> 4) & 0xFF;
        
        // P?id�n� doln�ch 4 bit?
        data[i*2 + 2] = (values[i] & 0x0F) << 4;
    }
    
    // Odesl�n� p?es I2C
    return i2c_write(_mcp4728_address, data, 9);
}

i2c_status_t mcp4728_general_reset(void) {
    // General Call adresa je 0x00
    uint8_t data[1] = {MCP4728_CMD_GEN_CALL_RESET};
    return i2c_write(0x00, data, 1);
}

i2c_status_t mcp4728_wakeup(void) {
    // General Call adresa je 0x00
    uint8_t data[1] = {MCP4728_CMD_GEN_CALL_WAKEUP};
    return i2c_write(0x00, data, 1);
}
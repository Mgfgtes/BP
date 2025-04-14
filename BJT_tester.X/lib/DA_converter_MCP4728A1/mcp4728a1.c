/**
 * MCP4728A1 knihovna pro AVR64DA28 - Implementace
 * 
 * Ovladac pro 12-bitovy, 4-kanalovy DA prevodnik MCP4728A1
 * Vyuziva I2C knihovnu pro AVR64DA28
 */

#include "mcp4728a1.h"

// P?íkazy pro MCP4728A1
#define MCP4728_CMD_FAST_WRITE       0x00 // Rychlé nastavení hodnot
#define MCP4728_CMD_MULTI_WRITE      0x40 // Vícenásobný zápis
#define MCP4728_CMD_SEQ_WRITE        0x50 // Sekven?ní zápis
#define MCP4728_CMD_SINGLE_WRITE     0x58 // Zápis jednoho kanálu
#define MCP4728_CMD_VREF_WRITE       0x80 // Nastavení reference
#define MCP4728_CMD_GAIN_WRITE       0xC0 // Nastavení zesílení
#define MCP4728_CMD_PD_WRITE         0xA0 // Nastavení power-down
#define MCP4728_CMD_GEN_CALL_RESET   0x06 // Obecný reset
#define MCP4728_CMD_GEN_CALL_WAKEUP  0x09 // Obecné probuzení

// Staticka promenna pro ulozeni adresy zarizeni
static uint8_t _mcp4728_address = MCP4728_DEFAULT_ADDRESS;

i2c_status_t mcp4728_init(uint8_t address) {
    _mcp4728_address = address;
    
    // Zkontrolujeme, zda je zarizeni dostupne
    if (!i2c_device_available(_mcp4728_address)) {
        return I2C_ERROR_NACK;
    }
    
    return I2C_OK;
}

i2c_status_t mcp4728_set_channel(mcp4728_channel_t channel, uint16_t value, 
                                mcp4728_vref_t vref, mcp4728_gain_t gain,
                                mcp4728_powerdown_t powerDown) {
    
    // Omezení hodnoty na 12 bitu (0-4095)
    if (value > 4095) {
        value = 4095;
    }
    
    // Slozeni prikazu pro single write
    uint8_t data[3];
    
    // Prvni byte: prikaz a kanal
    data[0] = MCP4728_CMD_SINGLE_WRITE | (channel << 1);
    
    // Druhy byte: konfigurace a horni 4 bity hodnoty
    data[1] = (vref << 7) | (powerDown << 5) | (gain << 4) | ((value >> 8) & 0x0F);
    
    // Treti byte: dolnich 8 bitu hodnoty
    data[2] = value & 0xFF;
    
    // Odeslani pres I2C
    return i2c_write(_mcp4728_address, data, 3);
}

i2c_status_t mcp4728_fast_write(mcp4728_channel_t channel, uint16_t value) {
    // Omezeni hodnoty na 12 bitu (0-4095)
    if (value > 4095) {
        value = 4095;
    }
    
    // Slozeni prikazu pro fast write
    uint8_t data[2];
    
    // Fast write ma specificky format:
    // Prvni byte: hornich 8 bitu hodnoty s DAC adresou v nejvyssich 2 bitech
    data[0] = (channel << 6) | ((value >> 4) & 0x3F);
    
    // Druhy byte: dolni 4 bity hodnoty v horních 4 bitech
    data[1] = (value & 0x0F) << 4;
    
    // Odeslani pres I2C
    return i2c_write(_mcp4728_address, data, 2);
}

i2c_status_t mcp4728_set_all_channels(uint16_t values[4]) {
    // Slozeni prikazu pro multi write
    uint8_t data[9];
    data[0] = MCP4728_CMD_MULTI_WRITE;
    
    // Pro kazdy kanal pridame 2 byty
    for (uint8_t i = 0; i < 4; i++) {
        // Omezení hodnoty na 12 bitu
        if (values[i] > 4095) {
            values[i] = 4095;
        }
        
        // Pridani hornich 8 bitu
        data[i*2 + 1] = (values[i] >> 4) & 0xFF;
        
        // Pridani dolnich 4 bitu
        data[i*2 + 2] = (values[i] & 0x0F) << 4;
    }
    
    // Odeslani pres I2C
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
#include <EEPROM.h>
#include <FastLED.h>
#include "config.hpp"

/**
 * Initializes the config in EEPROM and memory
 * All headers start off with 1 LED and a constant white colored
 * 
 * @param config Array of header configs to write to
 * @param address Starting address in EEPROM to write configs to
 * @param numHeaders Number of headers this controller has
 */
void initControllerConfig(RGBHeaderConfig config[], int address, uint8_t numHeaders) {
    EEPROM.write(address, CONFIG_INITIALIZED);
    address += 1;

    for (uint8_t i = 0; i < numHeaders; i++) {
        config[i] = {1, STATIC, CRGB(255, 255, 255)};
        writeHeaderConfig(&config[i], address, i);
    }
}

/**
 * Reads the config stored in EEPROM for the controller
 * Format: [ConfigSyncByte: 1 byte][RGBHeaderConfig: 5 bytes][RGBHeaderConfig: 5 bytes][...]
 * 
 * @param config Array of header configs to write to
 * @param address Starting address in EEPROM to read configs from
 * @param numHeaders Number of headers this controller has
 */
void loadControllerConfig(RGBHeaderConfig config[], int address, uint8_t numHeaders) {
    ConfigSyncByte sync = EEPROM.read(address);

    if (sync != CONFIG_INITIALIZED) {
        // Initialize the config
        initControllerConfig(config, address, numHeaders);
    } else {
        // Skip sync byte
        address += 1;

        // Load configs into memory struct by struct
        for (uint8_t i = 0; i < numHeaders; i++) {
            readHeaderConfig(&config[i], address, i);
        }
    }
}

/**
 * Writes a single instance of RGB Header config to EEPROM from memory
 * @param srcConfig Pointer to a RGBHeaderConfig to read from
 * @param address Starting address in configs in EEPROM
 * @param header Which header to read
 */
void writeHeaderConfig(RGBHeaderConfig *srcConfig, int address, uint8_t header) {
    EEPROM.put(address + (header * sizeof(RGBHeaderConfig)), *srcConfig);
}

/**
 * Reads a single instance of RGB Header config from EEPROM into memory
 * @param destConfig Pointer to a RGBHeaderConfig to write to
 * @param address Starting address in configs in EEPROM
 * @param header Which header to read
 */
void readHeaderConfig(RGBHeaderConfig *destConfig, int address, uint8_t header) {
    EEPROM.get(address + (header * sizeof(RGBHeaderConfig)), *destConfig);
}

#include <EEPROM.h>
#include <FastLED.h>
#include "config.hpp"

/**
 * Reads the config stored in EEPROM for the controller
 * Format: [ConfigSyncByte: 1 byte][RGBHeaderConfig: 5 bytes][RGBHeaderConfig: 5 bytes][...]
 * @param config Array of header configs to write to
 * @param address Starting address in EEPROM to read configs from
 * @param numHeaders Number of headers this controller has
 */
void HeaderConfig::load(RGBHeaderConfig config[], int address, uint8_t numHeaders)
{
    ConfigSyncByte sync = EEPROM.read(address);

    if (sync != CONFIG_INITIALIZED)
    {
        // Initialize the config
        init(config, address, numHeaders);
    }
    else
    {
        // Skip sync byte
        address += 1;

        // Load configs into memory struct by struct
        for (uint8_t i = 0; i < numHeaders; i++)
        {
            readFromRom(&config[i], address, i);
        }
    }
}

/**
 * Initializes the config in EEPROM and memory
 * All headers start with 1 LED and a constant white colored
 * @param config Array of header configs to write to
 * @param address Starting address in EEPROM to write configs to
 * @param numHeaders Number of headers this controller has
 */
void HeaderConfig::init(RGBHeaderConfig config[], int address, uint8_t numHeaders)
{
    EEPROM.write(address, CONFIG_INITIALIZED);
    address += 1;

    for (uint8_t i = 0; i < numHeaders; i++)
    {
        config[i] = {1, CONSTANT, {CRGB(255, 255, 255), CRGB(255, 255, 255), CRGB(255, 255, 255)}};
        writeToRom(&config[i], address, i);
    }
}

/**
 * Clears the config from EEPROM
 */
void HeaderConfig::wipe(int address, uint8_t numHeaders)
{
    // Replace numHeaders number of RGBHeaderConfig's with 0xFF, plus sync byte
    for (unsigned int i = 0; i < (numHeaders * sizeof(RGBHeaderConfig)) + 1; i++)
    {
        EEPROM.write(address + i, 0xFF);
    }
}

/**
 * Writes a single instance of RGB Header config to EEPROM from memory
 * @param srcConfig Pointer to a RGBHeaderConfig to read from
 * @param address Starting address in configs in EEPROM
 * @param header Which header to read
 */
void HeaderConfig::writeToRom(RGBHeaderConfig *srcConfig, int address, uint8_t header)
{
    EEPROM.put(address + (header * sizeof(RGBHeaderConfig)), *srcConfig);
}

/**
 * Reads a single instance of RGB Header config from EEPROM into memory
 * @param destConfig Pointer to a RGBHeaderConfig to write to
 * @param address Starting address in configs in EEPROM
 * @param header Which header to read
 */
void HeaderConfig::readFromRom(RGBHeaderConfig *destConfig, int address, uint8_t header)
{
    EEPROM.get(address + (header * sizeof(RGBHeaderConfig)), *destConfig);
}

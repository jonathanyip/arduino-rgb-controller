#ifndef HEADERCONFIG_HPP
#define HEADERCONFIG_HPP

/**
 * LED Modes
 */
typedef uint8_t LedMode;
const PROGMEM LedMode OFF = 0,
                      STATIC = 1;

/**
 * RGBHeaderConfig represents the state of a single RGB header (data pin out)
 * Layout: [numLeds: 1 byte][mode: 1 byte][color: 3 bytes]
 * 
 * @param numLeds   Number of LEDs in this header
 * @param mode      Mode that LEDs are in
 * @param color     LED colors (may be used depending on the mode)
 */
struct RGBHeaderConfig {
    uint8_t numLeds;
    LedMode mode;
    CRGB color;
};

/**
 * ConfigSyncByte is a 1-byte flag that determines
 * whether the config has been initialized yet.
 */
typedef uint8_t ConfigSyncByte;
const PROGMEM ConfigSyncByte CONFIG_INITIALIZED     = 0x01,
                             CONFIG_NOT_INITIALIZED = 0xFF;

void loadControllerConfig(RGBHeaderConfig config[], int address, uint8_t numHeaders);
void writeHeaderConfig(RGBHeaderConfig *srcConfig, int address, uint8_t header);
void readHeaderConfig(RGBHeaderConfig *destConfig, int address, uint8_t header);

#endif

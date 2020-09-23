#ifndef HEADERCONFIG_HPP
#define HEADERCONFIG_HPP

/**
 * LED Modes
 */
typedef uint8_t LedMode;
const PROGMEM LedMode OFF       = 0,
                      CONSTANT  = 1;

/**
 * LED Modes Data Structs
 */
struct ConstantData {
    CRGB color;
};

/**
 * RGBHeaderConfig represents the state of a single RGB header (data pin out)
 * Layout (12 bytes): [numLeds: 1 byte][mode: 1 byte][data: 10 bytes]
 * @param numLeds   Number of LEDs in this header
 * @param mode      Mode that LEDs are in
 * @param data      LED Modes data structs. May contain initial RGB colors, etc. whatever the mode requires
 */
struct RGBHeaderConfig
{
    uint8_t numLeds;
    LedMode mode;
    uint8_t data[10];
};

/**
 * ConfigSyncByte is a 1-byte flag that determines
 * whether the config has been initialized yet.
 */
typedef uint8_t ConfigSyncByte;
const PROGMEM ConfigSyncByte CONFIG_INITIALIZED     = 0x01,
                             CONFIG_NOT_INITIALIZED = 0xFF;

/**
 * HeaderConfig reads/writes configs to EEPROM for each controller RGB header
 */
class HeaderConfig
{
public:
    static void load(RGBHeaderConfig config[], int address, uint8_t numHeaders);
    static void wipe(int address, uint8_t numHeaders);
    static void init(RGBHeaderConfig config[], int address, uint8_t numHeaders);
    static void writeToRom(RGBHeaderConfig *srcConfig, int address, uint8_t header);
    static void readFromRom(RGBHeaderConfig *destConfig, int address, uint8_t header);
};

#endif

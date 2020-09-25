#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <FastLED.h>
#include "constants.hpp"
#include "config.hpp"

extern HardwareSerial Serial;

#define SERIAL_SYNC_BYTE    '?'
#define SERIAL_ACK_BYTE     'K'
#define SERIAL_TIMEOUT_MS   100

/**
 * Defines an action
 */
typedef uint8_t Action;
const PROGMEM Action SET_HEADER_CONFIG  = 1,
                     WIPE_CONFIG        = 2;

struct ActionPacket
{
    Action action;
};

class Controller
{
public:
    static void setup();
    static void loop();
private:
    static CRGB leds[NUM_HEADERS][MAX_LEDS_PER_HEADER];
    static RGBHeaderConfig config[NUM_HEADERS];
    static uint8_t dataCache[NUM_HEADERS][HEADER_DATA_CACHE_SIZE];
    static bool needsInit[NUM_HEADERS];
    static long timeout;

    static void colorLoop();
    static void serialLoop();
    template <unsigned H> static void setupLeds();

    static bool readBytes(uint8_t *buffer, size_t bytes);
};

#endif

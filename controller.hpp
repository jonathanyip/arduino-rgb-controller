#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <FastLED.h>
#include "constants.hpp"
#include "config.hpp"

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

    static void colorLoop();
    template <unsigned H> static void setupLeds();
};

#endif

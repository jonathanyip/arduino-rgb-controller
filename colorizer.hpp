#ifndef COLORIZER_HPP
#define COLORIZER_HPP

#include <FastLED.h>
#include "config.hpp"

/**
 * Colorizer applies colors to RGBs
 */
class Colorizer
{
public:
    static bool applyColor(RGBHeaderConfig *config, CRGB *leds, uint8_t *cache, bool needsInit);
    static bool off(RGBHeaderConfig *config, CRGB *leds, uint8_t *cache, bool needsInit);
    static bool constant(RGBHeaderConfig *config, CRGB *leds, uint8_t *cache, bool needsInit);
};

#endif

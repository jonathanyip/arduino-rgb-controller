#include <FastLED.h>
#include "colorizer.hpp"
#include "macros.hpp"

/**
 * Applies a color to LEDs. Switches depending on the led mode
 * @param config Pointer to header config (contains led count, mode, mode data)
 * @param leds Pointer to this header's leds
 * @param data Pointer to a cache persistent between loops. Of size HEADER_DATA_CACHE_SIZE
 * @param needsInit Whether this is a new config for this header / this header needs initialization
 * @return Whether we should update LEDs
 */
bool Colorizer::applyColor(RGBHeaderConfig *config, CRGB *leds, uint8_t *cache, bool needsInit)
{
    switch(config->mode)
    {
    case OFF:       return off(config, leds, cache, needsInit);
    case CONSTANT:  return constant(config, leds, cache, needsInit);
    }

    return false;
}

/**
 * Turns LEDs off
 */
bool Colorizer::off(RGBHeaderConfig *config, CRGB *leds, uint8_t *cache, bool needsInit)
{
    UNUSED_PARAM(cache);

    // Turn off all LEDs on this header
    for (uint8_t i = 0; i < config->numLeds; i++)
    {
        leds[i] = CRGB::Black;
    }

    return needsInit;
}

/**
 * Turns LEDs a solid color
 */
bool Colorizer::constant(RGBHeaderConfig *config, CRGB *leds, uint8_t *cache, bool needsInit)
{
    UNUSED_PARAM(cache);

    // Extract saved color from data
    ConstantData *a = (ConstantData*) config->data;

    // Switch LED color to the constant
    for (uint8_t i = 0; i < config->numLeds; i++)
    {
        leds[i] = a->color;
    }

    return needsInit;
}

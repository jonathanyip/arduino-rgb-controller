#include <FastLED.h>
#include "constants.hpp"
#include "config.hpp"

CRGB leds[MAX_LEDS];
RGBHeaderConfig config[NUM_HEADERS];

/**
 * Sets up the LEDs in FastLED based on the constant config values
 * @tparam H Number of headers to initialize
 */
template <unsigned H> void addLeds()
{
    CRGB *ledSlice = &leds[(H-1) * MAX_LEDS_PER_HEADER];
    FastLED.addLeds<WS2812B, HEADER_PINS[H-1]>(ledSlice, config[H-1].numLeds);
    addLeds<H-1>();
}

template <> void addLeds<0u>() {}

void setup() {
    loadControllerConfig(config, CONFIG_START_ADDR, NUM_HEADERS);
    addLeds<NUM_HEADERS>();
}

void loop() {
}

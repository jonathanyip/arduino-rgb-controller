#include "controller.hpp"

CRGB Controller::leds[MAX_LEDS];
RGBHeaderConfig Controller::config[NUM_HEADERS];

/**
 * Runs any setup for the controller. This should be run before loop() is called.
 */
void Controller::setup()
{
    setupConfig();
    setupLeds<NUM_HEADERS>();
}

/**
 * Primary loop for the controller
 */
void Controller::loop()
{
}

/**
 * Sets up the config variable in memory
 */
void Controller::setupConfig()
{
    HeaderConfig::load(config, CONFIG_START_ADDR, NUM_HEADERS);
}

/**
 * Sets up the LEDs in FastLED based on the constant config values
 * @tparam H Number of headers to initialize
 */
template <unsigned H> void Controller::setupLeds()
{
    CRGB *ledSlice = &leds[(H-1) * MAX_LEDS_PER_HEADER];
    FastLED.addLeds<WS2812B, HEADER_PINS[H-1]>(ledSlice, config[H-1].numLeds);
    setupLeds<H-1>();
}
template <> void Controller::setupLeds<0u>() {}

#include "controller.hpp"
#include "colorizer.hpp"

// Stores individual LED color data for FastLED
CRGB Controller::leds[NUM_HEADERS][MAX_LEDS_PER_HEADER];

// Stores saved configs for each header
RGBHeaderConfig Controller::config[NUM_HEADERS];

// Temporary space for headers to store state between loops
uint8_t Controller::dataCache[NUM_HEADERS][HEADER_DATA_CACHE_SIZE];

// Set to true when the header has not been set yet
// Or has just got a new config value and needs initialization
bool Controller::needsInit[NUM_HEADERS];

/**
 * Runs any setup for the controller. This should be run before loop() is called.
 */
void Controller::setup()
{
    HeaderConfig::load(config, CONFIG_START_ADDR, NUM_HEADERS);
    setupLeds<NUM_HEADERS>();

    // All headers start off as needing initialization
    for(uint8_t i = 0; i < NUM_HEADERS; i++)
    {
        needsInit[i] = true;
    }
}

/**
 * Primary loop for the controller
 */
void Controller::loop()
{
    colorLoop();
}

/**
 * Loop that handles colors
 */
void Controller::colorLoop()
{
    uint8_t changed = 0;

    // Run color changes for each header
    for (uint8_t i = 0; i < NUM_HEADERS; i++)
    {
        Colorizer::applyColor(&config[i], leds[i], dataCache[i], needsInit[i]);

        if(needsInit[i])
        {
            needsInit[i] = false;
        }
    }

    // If something changed, tell FastLED to refresh the leds
    if (changed != 0)
    {
        FastLED.show();
    }
}

/**
 * Sets up the LEDs in FastLED based on the constant config values
 * @tparam H Number of headers to initialize
 */
template <unsigned H> void Controller::setupLeds()
{
    FastLED.addLeds<WS2812B, HEADER_PINS[H-1]>(leds[H-1], config[H-1].numLeds);
    setupLeds<H-1>();
}
template <> void Controller::setupLeds<0u>() {}

#include "controller.hpp"
#include "colormode.hpp"

CRGB Controller::leds[MAX_LEDS];
RGBHeaderConfig Controller::config[NUM_HEADERS];
uint8_t Controller::dataCache[NUM_HEADERS * HEADER_DATA_CACHE_SIZE];

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
    colorLoop();
}

void Controller::colorLoop()
{
    uint8_t changed = 0;

    // Run color changes for each header
    for (uint8_t i = 0; i < NUM_HEADERS; i++) {
        RGBHeaderConfig &headerConfig = config[i];

        switch(headerConfig.mode)
        {
        case OFF:
            changed = ColorMode::off(headerConfig, getHeaderDataCache(i));
            break;
        case CONSTANT:
            changed = ColorMode::constant(headerConfig, getHeaderDataCache(i));
            break;
        }
    }

    // If something changed, tell FastLED to refresh the line
    if (changed != 0)
    {
        FastLED.show();
    }
}

/**
 * Gets the data cache for a header
 * The data cache is used by ColorMode to save state between loops for a header
 * @param header Header to get cache for
 * @return Pointer to the data cache location
 */
uint8_t* Controller::getHeaderDataCache(uint8_t header)
{
    return &dataCache[header * HEADER_DATA_CACHE_SIZE];
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

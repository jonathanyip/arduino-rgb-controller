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
    // Set up serial
    Serial.begin(SERIAL_BAUD_RATE);
    Serial.println();

    // Load header config into memory
    HeaderConfig::load(config, CONFIG_START_ADDR, NUM_HEADERS);

    // Set up LEDs
    setupLeds<NUM_HEADERS>();

    // All headers need to be reset at the beginning
    for(uint8_t i = 0; i < NUM_HEADERS; i++)
    {
        needsInit[i] = true;
    }

    char debugLine[64];
    sprintf(debugLine, "DEBUG %u %u %u %u\n", NUM_HEADERS, MAX_LEDS_PER_HEADER, MAX_LEDS, HEADER_DATA_CACHE_SIZE);
    Serial.println(debugLine);

    Serial.println("DEBUG Arduino is set up!\n");
}

/**
 * Primary loop for the controller
 */
void Controller::loop()
{
    serialLoop();
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
 * Loop that handles serial inputs
 */
void Controller::serialLoop()
{
    // Wait for sync byte
    if (Serial.available() > 0)
    {
        char syncByte = Serial.read();

        // If the sync byte does not match, clear the buffer and continue
        if (syncByte != SERIAL_SYNC_BYTE)
        {
            while(Serial.available() > 0) { Serial.read(); }
            return;
        }

        // Tell computer we are ready for input
        Serial.write(SERIAL_ACK_BYTE);

        // Read action bytes
        ActionPacket actionPacket;
        if (!readBytes((uint8_t*) &actionPacket, sizeof(ActionPacket))) return;

        // Do something based on action
        switch (actionPacket.action)
        {
        case SET_HEADER_CONFIG: break;
        case WIPE_CONFIG: break;
        }
    }
}

/**
 * Reads bytes from serial
 * @param buffer Buffer to store data in
 * @param bytes Number of bytes to read
 * @return true if it manages to read. False if it times out
 */
bool Controller::readBytes(uint8_t *buffer, size_t bytes)
{
    // Collect serial data into a buffer
    unsigned long timeout = millis();
    for (uint8_t i = 0; i < bytes; i++)
    {
        while(Serial.available() == 0)
        {
            // Timed out, break out of the loop
            if (millis() - timeout > SERIAL_TIMEOUT_MS)
            {
                return false;
            }
        }

        // Reset timeout
        timeout = millis();
        *buffer = Serial.read();

        // Advance pointer
        buffer++;
    }

    return true;
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

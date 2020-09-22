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
    static CRGB leds[MAX_LEDS];
    static RGBHeaderConfig config[NUM_HEADERS];

    template <unsigned H> static void setupLeds();
    static void setupConfig();
};

#endif

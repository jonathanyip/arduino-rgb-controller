#ifndef COLORMODE_HPP
#define COLORMODE_HPP

#include "constants.hpp"
#include "config.hpp"

class ColorMode
{
public:
    static bool off(RGBHeaderConfig& config, uint8_t *data);
    static bool constant(RGBHeaderConfig& config, uint8_t *data);
};

#endif

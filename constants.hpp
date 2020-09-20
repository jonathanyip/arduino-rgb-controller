#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <FastLED.h>
#include <avr/pgmspace.h>
#include "macros.hpp"

/**
 * Controller Configs
 */
#define NUM_HEADERS         6
#define MAX_LEDS_PER_HEADER 50
#define MAX_LEDS            NUM_HEADERS * MAX_LEDS_PER_HEADER
#define HEADER_CHIPSET      WS2812B

constexpr PROGMEM uint8_t HEADER_PINS[] = {3, 5, 6, 9, 10, 11};

// Starting address to write config data in EEPROM
#define CONFIG_START_ADDR 0x400

#endif

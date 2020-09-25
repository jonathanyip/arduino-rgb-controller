#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <FastLED.h>
#include <avr/pgmspace.h>
#include "macros.hpp"

/**
 * Controller Configs
 */
// Number of headers
#define NUM_HEADERS             6

// Maximum LEDs allowed per header
#define MAX_LEDS_PER_HEADER     50

// Number of LEDs in total
// Evalutated, should not be too large to avoid running out of memory
#define MAX_LEDS                NUM_HEADERS * MAX_LEDS_PER_HEADER

// Number of bytes allocated per header to store temporary data
#define HEADER_DATA_CACHE_SIZE  20

// Pins assigned to each header
constexpr PROGMEM uint8_t HEADER_PINS[] = {3, 5, 6, 9, 10, 11};

// Starting address to write config data in EEPROM
#define CONFIG_START_ADDR       0x400

// Serial rate
#define SERIAL_BAUD_RATE        9600

#endif

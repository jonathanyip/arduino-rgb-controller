# Arduino RGB Controller

**Work in Progress. This is a personal project, it's not really for general distribution.**

This Arduino project is to create an ARGB (3-pin) controller for PC RGB fans/peripherals.

## Context
With only 1 ARGB motherboard header (3-pin), I was looking for an ARGB controller with multiple ARGB headers.

Sadly, most options are just a splitter or it's proprietary (*cough Corsair*). If one wanted to control each RGB fan individually, it would not be possible.

Luckily, I found this [controller kit](https://www.amazon.com/gp/product/B07V56ZBQC/) that connects to Arduino Uno digital pins. It surfaces 6 ARGB pins (and PWM fans!).

* The [FastLED](https://github.com/FastLED/FastLED) seems promising in pushing out the colors. But I would like to control the colors from my computer.
* It'd also be nice if I could set it up with [OpenRGB](https://gitlab.com/CalcProgrammer1/OpenRGB) to get their color customization UI built in.
* The Arduino should remember my settings ideally. So it needs to store my RGB state in EEPROM.

In short, I'd like to have: PC -> OpenRGB -> (Serial) -> Arduino -> (ARGB Data In) -> RGB Fans

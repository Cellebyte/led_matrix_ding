#pragma once

#include "../../util.h"

#include "Arduino.h"

#include "FastLED.h"


#define LED_ROWS 10
#define LED_COLUMNS 10
#define NUM_LEDS LED_ROWS * LED_COLUMNS

#define LED_DATA_PIN 3

namespace hw {

    class LEDMatrix {
    public:
        LEDMatrix(){}

        NO_COPY_INSTANCE(LEDMatrix)

        struct Rect {
            uint8_t width;
            uint8_t height;
            CRGB color;
        };

        uint8_t setup();
        uint8_t loop();
        uint8_t set_pixel(const uint8_t x, const uint8_t y, const CRGB color);
        uint8_t show_rect(const uint8_t x, const uint8_t y, const Rect& rect);

    private:

    };

}
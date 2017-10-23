#include "FastLED.h"

#define LED_ROWS 10
#define LED_COLUMNS 10
#define NUM_LEDS LED_ROWS * LED_COLUMNS

namespace screen {

    struct area {
        uint8_t x;
        uint8_t y;
        uint8_t x_width;
        uint8_t y_width;
        CRGB color;
    };

    void setup();

}
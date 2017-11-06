#include "./led_matrix.h"

CRGB leds[NUM_LEDS];

uint8_t hw::LEDMatrix::setup() {
    //TODO: unimplemented
    //FastLED.addLeds<WS2812B, LED_DATA_PIN, RGB>(leds, NUM_LEDS);
    return 0;
}

uint8_t hw::LEDMatrix::loop() {
    //TODO: unimplemented
    return 0;
}
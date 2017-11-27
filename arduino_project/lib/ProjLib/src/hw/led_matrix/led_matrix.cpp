#include "./led_matrix.h"

CRGB leds[NUM_LEDS];

uint8_t hw::LEDMatrix::setup()
{
    FastLED.addLeds<WS2812B, LED_DATA_PIN, RGB>(leds, NUM_LEDS, 0); // 0 offset
    return 0;
}

uint8_t hw::LEDMatrix::set_pixel(
    const uint8_t x,
    const uint8_t y,
    const CRGB color)
{

    if (LED_COLUMNS <= x || LED_ROWS <= y)
    {
        return 1;
    }

    leds[y * LED_COLUMNS + x] = color;

    return 0;
}

uint8_t hw::LEDMatrix::show_rect(
    const uint8_t x,
    const uint8_t y,
    const hw::LEDMatrix::Rect &rect)
{
    if (LED_COLUMNS <= x
        || LED_COLUMNS < x + rect.width
        || LED_ROWS <= y
        || LED_ROWS < y + rect.height)
    {
        return 1;
    }

    for(uint8_t x_i = x; x_i < x + rect.width; x_i++) {
        for(uint8_t y_i = x; y_i < y + rect.height; y_i++) {
            set_pixel(x_i, y_i, rect.color);
            //leds[y_i * LED_COLUMNS + x_i] = rect.color;
        }
    }

    return 0;
}

uint8_t hw::LEDMatrix::loop()
{
    FastLED.show();
    return 0;
}
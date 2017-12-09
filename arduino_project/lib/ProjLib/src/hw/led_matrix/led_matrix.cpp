#include "./led_matrix.h"

CRGB leds[NUM_LEDS];

uint8_t hw::LEDMatrix::setup()
{
    FastLED.addLeds<WS2812B, LED_DATA_PIN, GRB>(leds, NUM_LEDS, 0); // 0 offset
    return 0;
}

uint8_t hw::LEDMatrix::set_pixel(
    const int8_t x,
    const int8_t y,
    const CRGB color)
{

    if (LED_COLUMNS <= x || LED_ROWS <= y || 0 > x || 0 > y)
    {
        return 1;
    }

    uint8_t index;

    if (y & 0x01)
    { // odd row
        uint8_t reverseX = (LED_COLUMNS - 1) - x;
        index = (y * LED_COLUMNS) + reverseX;
    }
    else
    {
        index = (y * LED_COLUMNS) + x;
    }

    leds[index] = color;
    return 0;
}

uint8_t hw::LEDMatrix::show_rect(
    const int8_t x,
    const int8_t y,
    const hw::LEDMatrix::Rect &rect)
{

    for (int8_t x_i = x; x_i < x + rect.width; x_i++)
    {
        for (int8_t y_i = y; y_i < y + rect.height; y_i++)
        {
            set_pixel(x_i, y_i, rect.color);
        }
    }

    return 0;
}

uint8_t hw::LEDMatrix::set_all(const CRGB color)
{
    for (uint8_t i = 0; i < NUM_LEDS; i++)
    {
        leds[i] = color;
    }
    return 0;
}

uint8_t hw::LEDMatrix::loop()
{
    FastLED.show();
    return 0;
}
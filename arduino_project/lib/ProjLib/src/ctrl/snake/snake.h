#pragma once
#include <Arduino.h>
#include "FastLED.h"
#include "../../util.h"
#include <stdint.h>
#include "../../hw/led_matrix/led_matrix.h"
#include "../../hw/buttons/buttons.h"
#define FOOD_COLOR CRGB::Purple

namespace ctrl
{

class SnakeCtrl
{
  public:
     SnakeCtrl(
        hw::LEDMatrix &led_matrix,
        hw::Buttons &buttons) : 
        led_matrix(led_matrix),
        buttons(buttons)
        {}

    NO_COPY_INSTANCE(SnakeCtrl)

    uint8_t setup();
    uint8_t loop();

  private:
    // Snake Information
    struct snake
    {
        uint8_t xpos;
        uint8_t ypos;
        uint8_t direction;
        uint8_t length;
        const CRGB headcolor;
        const CRGB bodycolor;
    } SNAKE;
    uint8_t timer;
    hw::Buttons &buttons;
    hw::LEDMatrix &led_matrix;

    // prints the snake map
    uint8_t printMap();
    //updates the snake map
    uint8_t updateView();
    // clears the screen after one iteration
    void clearScreen();

    CRGB getColor(uint8_t);
    uint8_t move(uint8_t, uint8_t);
    void generateFood();
    void changeDirection();
    // Map Dimension
    static const uint8_t mapwidth = 12;
    static const uint8_t mapheight = 12;
    uint8_t map [mapwidth][mapheight] = {};
};
}
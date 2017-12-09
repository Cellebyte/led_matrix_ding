#pragma once
#include <Arduino.h>
#include "FastLED.h"
#include "../../util.h"
#include <stdint.h>
#include "../../hw/led_matrix/led_matrix.h"
#include "../../hw/buttons/buttons.h"
#define FOOD_COLOR CRGB::Purple
#define MAP_WIDTH 10
#define MAP_HEIGHT 10

namespace ctrl
{

class SnakeCtrl
{
  public:
     SnakeCtrl(
        hw::LEDMatrix &led_matrix,
        hw::Buttons &buttons) :
        timer(0),
        led_matrix(led_matrix),
        buttons(buttons)
        {}

    NO_COPY_INSTANCE(SnakeCtrl);

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
        CRGB bodycolor;
    } SNAKE;
    uint8_t timer;
    hw::LEDMatrix &led_matrix;
    hw::Buttons &buttons;

    // prints the snake map
    uint8_t printMap();
    //updates the snake map
    uint8_t updateView();
    // clears the screen after one iteration
    void clearScreen();

    CRGB getColor(int8_t);
    uint8_t move(uint8_t, uint8_t);
    void generateFood();
    void changeDirection();
    int8_t map [MAP_WIDTH][MAP_HEIGHT] = {};
};
}
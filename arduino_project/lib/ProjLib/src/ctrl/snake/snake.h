#pragma once
#include "../../util.h"

namespace snake
{

class SnakeCtrl
{
  public:
    SnakeCtrl() {}

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
        uint8_t headcolor;
        uint8_t bodycolor;
    } SNAKE;
    struct food
    {
        uint8_t xpos;
        uint8_t ypos;
        uint8_t color;
    };

    // prints the snake map
    uint8_t printMap();
    //updates the snake map
    uint8_t updateView();
    // clears the screen after one iteration
    uint8_t clearView();
    uint8_t move(uint8_t, uint8_t);
    void generateFood();
    void changeDirection(uint8_t);
    // Map Dimension
    static const uint8_t mapwidth = 12;
    static const uint8_t mapheight = 12;
    uint8_t map [mapwidth][mapheight] = {};
};
}
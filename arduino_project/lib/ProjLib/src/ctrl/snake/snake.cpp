#include "snake.h"

uint8_t ctrl::SnakeCtrl::setup()
{
    SNAKE.headcolor = CRGB::Red;
    SNAKE.bodycolor = CRGB::Green;
    SNAKE.xpos = mapwidth / 2;
    SNAKE.ypos = mapheight / 2;
    SNAKE.length = 3;
    SNAKE.direction = 0;
    timer=0;

    // Set Snake head onto the printMap
    map[SNAKE.xpos][SNAKE.ypos] = 1;
    // Places top and bottom walls
    for (int x = 0; x < mapwidth; ++x)
    {
        map[x][0] = 255;
        map[x][mapheight - 1] = 255;
    }
    // Places left and right walls
    for (int y = 0; y < mapheight; y++)
    {
        map[0][y] = 255;
        map[mapwidth - 1][y] = 255;
    }
    // 0 is a wall and 11 is a wall (1-10)
    // So 10 x 10 is the playable area

    generateFood();
    return 0;
}

uint8_t ctrl::SnakeCtrl::loop()
{
    // return 1 == isExit
    // return 2 == loseGame
    changeDirection();
    if (timer > 9)
    {
        timer=0;
        if (updateView()) return 2;
        clearScreen();
        printMap();
    }
    timer++;
    if (isExit(buttons.get_state())) return 1;
    return 0;
}

uint8_t ctrl::SnakeCtrl::printMap()
{
    for (uint8_t y = 1; y < mapheight-1; y++)
    {
        for(uint8_t x = 1; x < mapwidth-1; x++)
        {
                led_matrix.set_pixel(x,y,getColor(map[x][y]));
        }
    }
    return 0;
}

void ctrl::SnakeCtrl::changeDirection() {
    /*
      W
    A + D
      S

        BTN_A1
    BTN_A0 + BTN_A2
        BTN_A3
    */
    uint8_t pressed_buttons = buttons.get_state();
    if (pressed_buttons & hw::Buttons::State::BTN_A1) SNAKE.direction = 3;
    else if (pressed_buttons & hw::Buttons::State::BTN_A0) SNAKE.direction = 0;
    else if (pressed_buttons & hw::Buttons::State::BTN_A3) SNAKE.direction = 1;
    else if (pressed_buttons & hw::Buttons::State::BTN_A2) SNAKE.direction = 2;

}

uint8_t ctrl::SnakeCtrl::updateView()
{
    /*
        OBEN
   LINKS  +   RECHTS
        UNTEN
          3
        0 + 2
          1
    */
    // Move in direction indicated
    switch (SNAKE.direction)
    {
    case 0:
        if (move(-1, 0)) return 1;
        break;
    case 1:
        if (move(0, 1)) return 1;
        break;
    case 2:
         if (move(1, 0)) return 1;
        break;
    case 3:
        if (move(0, -1)) return 1;
        break;
    }
    return 0;
}
// Moves snake head to new location
void ctrl::SnakeCtrl::generateFood()
{
    uint8_t x = 0;
    uint8_t y = 0;
    do
    {
        // Generate random x and y values within the map
        randomSeed(analogRead(0));
        x = random(1, mapwidth - 1);
        randomSeed(analogRead(0));
        y = random(1, mapheight);

        // If location is not free try again
    } while (map[x][y] != 0);

    // Place new food
    map[x][y] = 254;
}
uint8_t ctrl::SnakeCtrl::move(uint8_t dx, uint8_t dy)
{
    // determine new head position
    uint8_t newx = SNAKE.xpos + dx;
    uint8_t newy = SNAKE.ypos + dy;
    uint8_t food = 0;

    // Check if snake runs into a wall (indicated by 255 in map)
    if (map[newx][newy] == 255)
    {
        return 1;
    }
    // Check if snake runs into food (indicated by 254 in map)
    else if (map[newx][newy] == 254)
    {
        food = 1;
    }

    // Check for food in that location
    map[newx][newy] = 0;
    // Move head to new location and add the food to the length
    SNAKE.xpos = newx;
    SNAKE.ypos = newy;
    SNAKE.length = SNAKE.length + food;
    return 0;
}

void ctrl::SnakeCtrl::clearScreen(){
    led_matrix.set_all(CRGB::Black);
}

CRGB ctrl::SnakeCtrl::getColor(uint8_t value)
{
    // Returns a part of snake body
    if (value > 1 && value < 254)
        return SNAKE.bodycolor;
    else if (value == 1)
        return SNAKE.headcolor;
    else if (value == 254)
        return FOOD_COLOR;
    return 0;
}
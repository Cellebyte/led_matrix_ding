#include "snake.h"

uint8_t ctrl::SnakeCtrl::setup()
{
    SNAKE.xpos = 4;
    SNAKE.ypos = 2;
    SNAKE.length = 3;
    SNAKE.direction = 4;
    timer = 0;
    for (int x = 0; x < MAP_WIDTH; x++)
    {
        for (int y = 0; y < MAP_HEIGHT; y++)
        {
            map[x][y] = 0;
        }
    }
    // Set Snake head onto the printMap
    map[SNAKE.xpos][SNAKE.ypos] = 1;
    // Places top and bottom walls
    for (int x = 0; x < MAP_WIDTH; ++x)
    {
        map[x][0] = -1;
        map[x][MAP_HEIGHT - 1] = -1;
    }
    // Places left and right walls
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        map[0][y] = -1;
        map[MAP_WIDTH - 1][y] = -1;
    }
    // So 10 x 10 is the playable area

    generateFood();
    return 0;
}

uint8_t ctrl::SnakeCtrl::loop()
{
    // return 1 == isExit
    // return 2 == loseGame
    changeDirection();
    if (timer > 20)
    {

        timer = 0;
        if (updateView())
            return 2;
        clearScreen();
        printMap();
    }
    timer++;
    if (isExit(buttons.get_state()))
        return 1;
    return 0;
}

uint8_t ctrl::SnakeCtrl::printMap()
{
    for (uint8_t y = 0; y < MAP_HEIGHT; y++)
    {
        for (uint8_t x = 0; x < MAP_WIDTH; x++)
        {
            led_matrix.set_pixel(x, y, getColor(map[x][y]));
        }
    }
    return 0;
}

void ctrl::SnakeCtrl::changeDirection()
{
    /*
      W
    A + D
      S

        BTN_A1
    BTN_A0 + BTN_A2
        BTN_A3
    */
    uint8_t pressed_buttons = buttons.get_state();
    if (pressed_buttons & hw::Buttons::State::BTN_A1)
        SNAKE.direction = 3;
    else if (pressed_buttons & hw::Buttons::State::BTN_A0)
        SNAKE.direction = 0;
    else if (pressed_buttons & hw::Buttons::State::BTN_A3)
        SNAKE.direction = 1;
    else if (pressed_buttons & hw::Buttons::State::BTN_A2)
        SNAKE.direction = 2;
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
        if (move(-1, 0))
            return 1;
        break;
    case 1:
        if (move(0, 1))
            return 1;
        break;
    case 2:
        if (move(1, 0))
            return 1;
        break;
    case 3:
        if (move(0, -1))
            return 1;
        break;
    default:
        return 0;
        break;
    }

    // Reduce snake values on map by 1
    for (int i = 0; i < MAP_HEIGHT * MAP_WIDTH; i++)
    {
        if (map[i % MAP_WIDTH][i / MAP_HEIGHT] > 0)
            map[i % MAP_WIDTH][i / MAP_HEIGHT]--;
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
        x = random(0, MAP_WIDTH - 1);
        randomSeed(analogRead(0));
        y = random(0, MAP_HEIGHT - 1);

        // If location is not free try again
    } while (map[x][y] != 0);

    // Place new food
    map[x][y] = -2;
}
uint8_t ctrl::SnakeCtrl::move(uint8_t dx, uint8_t dy)
{
    // determine new head position
    uint8_t newx = SNAKE.xpos + dx;
    uint8_t newy = SNAKE.ypos + dy;
    int8_t food = 0;

    // Check if snake runs into a wall (indicated by -1 in map)
    if (map[newx][newy] == -1 || map[newx][newy] > 0)
    {
        return 1;
    }
    // Check if snake runs into food (indicated by -2 in map)
    else if (map[newx][newy] == -2)
    {
        food = 1;
        generateFood();
    }

    map[newx][newy] = 0;
    // Move head to new location and add the food to the length
    SNAKE.xpos = newx;
    SNAKE.ypos = newy;
    SNAKE.length = SNAKE.length + food;
    map[SNAKE.xpos][SNAKE.ypos] = SNAKE.length + 1;
    return 0;
}

void ctrl::SnakeCtrl::clearScreen()
{
    led_matrix.set_all(CRGB::Black);
}

CRGB ctrl::SnakeCtrl::getColor(int8_t value)
{
    if (SNAKE.length == value)
    {
        return SNAKE_HEAD_COLOR;
    }
    switch (value)
    {   
    case 0:
        return CRGB::Black;
    case -1:
        return SNAKE_BORDER_COLOR;
    case -2:
        return FOOD_COLOR;
    default:
        return SNAKE_BODY_COLOR;
    }
}
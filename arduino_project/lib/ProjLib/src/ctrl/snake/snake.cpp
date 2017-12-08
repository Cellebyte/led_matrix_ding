#include "snake.h"

uint8_t ctrl::SnakeCtrl::setup()
{
    SNAKE.headcolor = CRGB::Red;
    SNAKE.bodycolor = CRGB::Green;
    SNAKE.xpos = mapwidth / 2;
    SNAKE.ypos = mapheight / 2;
    SNAKE.length = 3;
    SNAKE.direction = 0;

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
    /*while(true) {
        if buttons.loop() {

        }
    }*/
    //TODO: implement
    isExit(buttons.get_state());
    return 0;
}

uint8_t ctrl::SnakeCtrl::printMap()
{
    return 0;
}

void ctrl::SnakeCtrl::changeDirection(uint8_t button) {
    /*
      W
    A + D
      S

      1
    4 + 2
      3
    */
    pressed_buttons = buttons.get_state();
    if (buttons)
    
    //     SNAKE.direction = 0;
    //     break;
    // case 'a':
    //     SNAKE.direction = 1;
    //     break;
    // case 's':
    //     SNAKE.direction = 2;
    //     break;
    // case 'd':
    //     SNAKE.direction = 3;
    //     break;
    
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
        move(-1, 0);
        break;
    case 1:
        move(0, 1);
        break;
    case 2:
        move(1, 0);
        break;
    case 3:
        move(0, -1);
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
        return -1;
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

uint8_t getColor(uint8_t value)
{
    // Returns a part of snake body
    if (value > 0 && value < 254)
        return 'g';
    else if (value == 254)
        return 'b';
    return 0;
}
#include "./pong.h"
#define BALL_COLOR CRGB::Red
#define POS_MAX 8
#define POS_MIN -1
#define START_POS_X 5
#define START_POS_Y 4

hw::LEDMatrix::Rect ab_bars[] = {
    hw::LEDMatrix::Rect{
        1, 3, CRGB::Yellow},
    hw::LEDMatrix::Rect{
        1, 3, CRGB::Cyan}};

hw::LEDMatrix::Rect fence[] = {
    hw::LEDMatrix::Rect{
        8, 1, CRGB::Grey}};

uint8_t ctrl::PongCtrl::setup()
{
    CURSORA.pos = 3;
    CURSORB.pos = 3;
    BALL.x = START_POS_X;
    BALL.y = START_POS_Y;
    BALL.x_vel = 1;
    BALL.y_vel = 0;
    return 0;
}

uint8_t ctrl::PongCtrl::move_cursors()
{

    hw::Buttons::State b_state = buttons.get_state();
    if (b_state & hw::Buttons::State::BTN_A3)
    {
        CURSORA.pos += 1;
        if (CURSORA.pos > POS_MAX)
        {
            CURSORA.pos = POS_MAX;
        }
    }
    else if (b_state & hw::Buttons::State::BTN_A1)
    {
        CURSORA.pos -= 1;
        if (CURSORA.pos < POS_MIN)
        {
            CURSORA.pos = POS_MIN;
        }
    }

    if (b_state & hw::Buttons::State::BTN_B3)
    {
        CURSORB.pos += 1;
        if (CURSORB.pos > POS_MAX)
        {
            CURSORB.pos = POS_MAX;
        }
    }
    else if (b_state & hw::Buttons::State::BTN_B1)
    {
        CURSORB.pos -= 1;
        if (CURSORB.pos < POS_MIN)
        {
            CURSORB.pos = POS_MIN;
        }
    }
    show_cursors();
    return 0;
}

void ctrl::PongCtrl::show_cursors()
{
    led_matrix.show_rect(0, CURSORA.pos, ab_bars[0]);
    led_matrix.show_rect(9, CURSORB.pos, ab_bars[1]);
}

void ctrl::PongCtrl::show_ball()
{
    led_matrix.set_pixel(BALL.x, BALL.y, BALL_COLOR);
}

uint8_t ctrl::PongCtrl::move_ball()
{
    int8_t new_vel_ball_x = BALL.x_vel;
    int8_t new_vel_ball_y = BALL.y_vel;

    BALL.x = BALL.x + BALL.x_vel;
    BALL.y = BALL.y + BALL.y_vel;

    //collisions
    if (1 == BALL.y || 8 == BALL.y)
    {
        new_vel_ball_y = (-1) * BALL.y_vel;
    }
    else if (1 == BALL.x)
    {
        if (CURSORA.pos == BALL.y)
        {
            new_vel_ball_x = (-1) * BALL.x_vel;
            new_vel_ball_y = -1;
        }
        else if (CURSORA.pos + 1 == BALL.y)
        {
            new_vel_ball_x = (-1) * BALL.x_vel;
            new_vel_ball_y = 0;
        }
        else if (CURSORA.pos + 2 == BALL.y)
        {
            new_vel_ball_x = (-1) * BALL.x_vel;
            new_vel_ball_y = 1;
        }

    }
    else if (8 == BALL.x)
    {
        if (CURSORB.pos == BALL.y)
        {
            new_vel_ball_x = (-1) * BALL.x_vel;
            new_vel_ball_y = -1;
        }
        else if (CURSORB.pos + 1 == BALL.y)
        {
            new_vel_ball_x = (-1) * BALL.x_vel;
            new_vel_ball_y = 0;
        }
        else if (CURSORB.pos + 2 == BALL.y)
        {
            new_vel_ball_x = (-1) * BALL.x_vel;
            new_vel_ball_y = 1;
        }
        else
        {
            new_vel_ball_x = BALL.x_vel;
            new_vel_ball_y = BALL.y_vel;
        }
    }
    else if (9 < BALL.x)
    {
        BALL.x = START_POS_X;
        BALL.y = START_POS_Y;
        BALL.x_vel = 1;
        BALL.y_vel = 0;
        return 3;
    }
    else if (0 > BALL.x)
    {
        BALL.x = START_POS_X;
        BALL.y = START_POS_Y;
        BALL.x_vel = -1;
        BALL.y_vel = 0;
        return 2;
    }
    else
    {
        new_vel_ball_x = BALL.x_vel;
        new_vel_ball_y = BALL.y_vel;
    }
    BALL.x_vel = new_vel_ball_x;
    BALL.y_vel = new_vel_ball_y;

    show_ball();
    return 0;
}

void ctrl::PongCtrl::clear_screen()
{
    led_matrix.set_all(CRGB::Black);
}

void ctrl::PongCtrl::show_playfield()
{
    led_matrix.show_rect(1, 0, fence[0]);
    led_matrix.show_rect(1, 9, fence[0]);
}
uint8_t ctrl::PongCtrl::loop()
{

    counter = (counter + 1) % 100;

    if (counter % 10 == 0)
    {
        clear_screen();
        show_playfield();
        move_cursors();
        uint8_t r = move_ball();
        if (r)
        {
            Serial.println(r);
        }
    }

    if (isExit(buttons.get_state()))
    {
        return 1;
    }
    return 0;
}
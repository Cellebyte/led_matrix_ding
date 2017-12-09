#include "./pong.h"

hw::LEDMatrix::Rect ab_bars[] = {
    hw::LEDMatrix::Rect{
        1, 3, CRGB::Yellow},
    hw::LEDMatrix::Rect{
        1, 3, CRGB::Cyan}};

hw::LEDMatrix::Rect fence[] = {
    hw::LEDMatrix::Rect{
        10, 1, CRGB::White}};

CRGB ball_color = CRGB::Red;

uint8_t ctrl::PongCtrl::setup()
{
    pos_a = 3;
    pos_b = 3;
    pos_ball_x = 5;
    pos_ball_y = 4;
    vel_ball_x = 1;
    vel_ball_y = 0;
    return 0;
}

uint8_t ctrl::PongCtrl::input()
{

    int8_t pos_max = 6;
    int8_t pos_min = 1;

    hw::Buttons::State b_state = buttons.get_state();
    if (b_state & hw::Buttons::State::BTN_A3)
    {
        pos_a += 1;
        if (pos_a > pos_max)
        {
            pos_a = pos_max;
        }
    }
    else if (b_state & hw::Buttons::State::BTN_A1)
    {
        pos_a -= 1;
        if (pos_a < pos_min)
        {
            pos_a = pos_min;
        }
    }

    if (b_state & hw::Buttons::State::BTN_B3)
    {
        pos_b += 1;
        if (pos_b > pos_max)
        {
            pos_b = pos_max;
        }
    }
    else if (b_state & hw::Buttons::State::BTN_B1)
    {
        pos_b -= 1;
        if (pos_b < pos_min)
        {
            pos_b = pos_min;
        }
    }
    return 0;
}

uint8_t ctrl::PongCtrl::loop()
{

    counter = (counter + 1) % 100;

    if (counter % 10 == 0)
    {
        input();
        int8_t new_pos_ball_x, new_pos_ball_y;
        int8_t new_vel_ball_x = vel_ball_x;
        int8_t new_vel_ball_y = vel_ball_y;

        //TODO: verify

        //collisions
        if (1 == pos_ball_y || 8 == pos_ball_y)
        {
            new_vel_ball_y = (-1) * vel_ball_y;
        }
        if (1 == pos_ball_x)
        {
            if (pos_a == pos_ball_x)
            {
                new_vel_ball_x = (-1) * vel_ball_x;
                new_vel_ball_y = -1;
            }
            else if (pos_a + 1 == pos_ball_x)
            {
                new_vel_ball_x = (-1) * vel_ball_x;
                new_vel_ball_y = 0;
            }
            else if (pos_a + 2 == pos_ball_x)
            {
                new_vel_ball_x = (-1) * vel_ball_x;
                new_vel_ball_y = 1;
            }
            else
            {
                //TODO:
                new_vel_ball_x = 0;
                new_vel_ball_y = 0;
            }
        }

        if (8 == pos_ball_x)
        {
            if (pos_b == pos_ball_x)
            {
                new_vel_ball_x = (-1) * vel_ball_x;
                new_vel_ball_y = -1;
            }
            else if (pos_b + 1 == pos_ball_x)
            {
                new_vel_ball_x = (-1) * vel_ball_x;
                new_vel_ball_y = 0;
            }
            else if (pos_b + 2 == pos_ball_x)
            {
                new_vel_ball_x = (-1) * vel_ball_x;
                new_vel_ball_y = 1;
            }
            else
            {
                //TODO:
                new_vel_ball_x = 0;
                new_vel_ball_y = 0;
            }
        }

        new_pos_ball_x = pos_ball_x + new_vel_ball_x;
        new_pos_ball_y = pos_ball_y + new_vel_ball_y;

        pos_ball_x = new_pos_ball_x;
        pos_ball_y = new_pos_ball_y;
        vel_ball_x = new_vel_ball_x;
        vel_ball_y = new_vel_ball_y;
    }

    led_matrix.set_all(CRGB::Black);
    led_matrix.set_pixel(9, 9, CRGB::Green);

    led_matrix.show_rect(0, 0, fence[0]);
    led_matrix.show_rect(0, 9, fence[0]);
    led_matrix.show_rect(0, pos_a, ab_bars[0]);
    led_matrix.show_rect(9, pos_b, ab_bars[1]);
    led_matrix.set_pixel(pos_ball_x, pos_ball_y, ball_color);

    if (isExit(buttons.get_state()))
    {
        return 1;
    }
    return 0;
}
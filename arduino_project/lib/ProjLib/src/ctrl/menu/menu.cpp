
#include "./menu.h"

hw::LEDMatrix::Rect snake_pic[] = {
    hw::LEDMatrix::Rect{1, 5, CRGB::White},
    hw::LEDMatrix::Rect{1, 4, CRGB::Green},
    hw::LEDMatrix::Rect{3, 1, CRGB::Green}};

uint8_t ctrl::MenuCtrl::show_1(int8_t offset)
{
    led_matrix.show_rect((int8_t)3 + offset, 3, snake_pic[0]);
    led_matrix.show_rect((int8_t)8 + offset, 4, snake_pic[1]);
    led_matrix.show_rect((int8_t)5 + offset, 7, snake_pic[2]);
    led_matrix.set_pixel((int8_t)8 + offset, 4, CRGB::GreenYellow);
    led_matrix.set_pixel((int8_t)8 + offset, 2, CRGB::Purple);
    return 0;
}

hw::LEDMatrix::Rect clock_pic[] = {
    hw::LEDMatrix::Rect{3, 5, CRGB::White},
    hw::LEDMatrix::Rect{2, 1, CRGB::Black},
    hw::LEDMatrix::Rect{5, 3, CRGB::Blue},
    hw::LEDMatrix::Rect{3, 5, CRGB::Blue},
    hw::LEDMatrix::Rect{3, 3, CRGB::Black},
    hw::LEDMatrix::Rect{1, 2, CRGB::Red}};

uint8_t ctrl::MenuCtrl::show_2(int8_t offset)
{
    led_matrix.show_rect((int8_t)1 + offset, 3, clock_pic[0]);
    led_matrix.show_rect((int8_t)1 + offset, 4, clock_pic[1]);
    led_matrix.show_rect((int8_t)2 + offset, 6, clock_pic[1]);
    led_matrix.show_rect((int8_t)5 + offset, 4, clock_pic[2]);
    led_matrix.show_rect((int8_t)6 + offset, 3, clock_pic[3]);
    led_matrix.show_rect((int8_t)6 + offset, 4, clock_pic[4]);
    led_matrix.show_rect((int8_t)7 + offset, 3, clock_pic[5]);
    led_matrix.set_pixel((int8_t)6 + offset, 5, CRGB::Red);
    led_matrix.set_pixel((int8_t)7 + offset, 5, CRGB::Blue);

    return 0;
}

hw::LEDMatrix::Rect pong_pic[] = {
    hw::LEDMatrix::Rect{1, 3, CRGB::Yellow},
    hw::LEDMatrix::Rect{1, 3, CRGB::Cyan}};

uint8_t ctrl::MenuCtrl::show_3(int8_t offset)
{
    led_matrix.show_rect((int8_t)1 + offset, 3, clock_pic[0]);
    led_matrix.show_rect((int8_t)1 + offset, 4, clock_pic[1]);
    led_matrix.show_rect((int8_t)1 + offset, 6, clock_pic[1]);
    led_matrix.show_rect((int8_t)5 + offset, 5, pong_pic[0]);
    led_matrix.show_rect((int8_t)8 + offset, 3, pong_pic[1]);
    led_matrix.set_pixel((int8_t)7 + offset, 4, CRGB::Red);

    return 0;
}

hw::LEDMatrix::Rect random_pic[] = {
    hw::LEDMatrix::Rect{
        1, 2, CRGB::Black},
    hw::LEDMatrix::Rect{
        2, 2, CRGB::Black}};

CRGB random_color[] = {
    CRGB::Purple,
    CRGB::Blue,
    CRGB::Green,
    CRGB::Yellow,
    CRGB::Orange,
    CRGB::Red};

uint8_t ctrl::MenuCtrl::show_4(int8_t offset)
{
    led_matrix.show_rect((int8_t)1 + offset, 3, clock_pic[0]);
    led_matrix.show_rect((int8_t)2 + offset, 3, random_pic[0]);
    led_matrix.show_rect((int8_t)1 + offset, 6, random_pic[1]);
    for (uint8_t c = 0; c < 6; c++)
    {
        for (uint8_t i = 0; i < 4; i++)
        {
            uint8_t x = (int8_t)5 + i + offset;
            uint8_t y = 3 + c - i;
            led_matrix.set_pixel(x, y, random_color[c]);
        }
    }

    return 0;
}

uint8_t ctrl::MenuCtrl::setup()
{
    screen = 0;
    transition_offset = 0;
    return 0;
}

uint8_t ctrl::MenuCtrl::show_screen()
{

    // show current screen or state of transition animation
    led_matrix.set_all(CRGB::Black);
    switch (screen)
    {
    case 0:
        show_1(0);
        break;
    case 1:
        show_2(0);
        break;
    case 2:
        show_3(0);
        break;
    case 3:
        show_4(0);
        break;

    // transition to next
    case 101:
        show_1((-1) * transition_offset);
        show_2(((-1) * transition_offset) + 9);
        break; // transition 1-2
    case 112:
        show_2(((-1) * transition_offset));
        show_3(((-1) * transition_offset) + 9);
        break; // transition 2-3
    case 123:
        show_3(((-1) * transition_offset));
        show_4(((-1) * transition_offset) + 9);
        break; // transition 3-4
    case 130:
        show_4(((-1) * transition_offset));
        show_1(((-1) * transition_offset) + 9);
        break; // transition 4-1

    // transition to prev
    case 210:
        show_2(transition_offset);
        show_1(transition_offset - 9);
        break; // transition 2-1
    case 221:
        show_3(transition_offset);
        show_2(transition_offset - 9);
        break; // transition 3-2
    case 232:
        show_4(transition_offset);
        show_3(transition_offset - 9);
        break; // transition 4-3
    case 203:
        show_1(transition_offset);
        show_4(transition_offset - 9);
        break; // transition 1-4
    default:
        led_matrix.set_all(CRGB::Red);
    }
    return 0;
}

// state machine transitions for screens and transition animations

uint8_t calc_next_screen(const uint8_t current_screen)
{
    switch(current_screen) {
        case 0: return 101;
        case 1: return 112;
        case 2: return 123;
        case 3: return 130;
        case 101: return 1;
        case 112: return 2;
        case 123: return 3;
        case 130: return 0;
        case 210: return 0;
        case 221: return 1;
        case 232: return 2;
        case 203: return 3;
        default: return 0;
    }
}

// reverse state machine transitions for screens and transition animations

uint8_t calc_prev_screen(const uint8_t current_screen)
{
    switch(current_screen) {
        case 0: return 203;
        case 1: return 210;
        case 2: return 221;
        case 3: return 232;
        case 101: return 0;
        case 112: return 1;
        case 123: return 2;
        case 130: return 3;
        //these have diferent behavior
        case 210: return 0;
        case 221: return 1;
        case 232: return 2;
        case 203: return 3;
        default: return 0;
    }
}



uint8_t ctrl::MenuCtrl::loop()
{
    show_screen();

    counter = (counter + 1) % 100;
    //TODo: fix this
    bool in_transition = (screen >= 100);

    hw::Buttons::State b_state = buttons.get_state();

    // switch to next screen if butten pressed
    if (wait_for_release_next && !(b_state & hw::Buttons::State::BTN_B2))
    {
        wait_for_release_next = false;
        //set to next screen or transition
        screen = calc_next_screen(screen);
        transition_offset = 0;
    }
    if (b_state & hw::Buttons::State::BTN_B2)
    {
        wait_for_release_next = true;
    }

    // switch to prev screen if butten pressed
    if (wait_for_release_prev && !(b_state & hw::Buttons::State::BTN_B0))
    {
        wait_for_release_prev = false;
        // set to prev screen or transition
        screen = calc_prev_screen(screen);
        transition_offset = 0;
    }
    if (b_state & hw::Buttons::State::BTN_B0)
    {
        wait_for_release_prev = true;
    }

    //launch app if button pressed
    if (!in_transition &&
        wait_for_release_select && !(b_state & hw::Buttons::State::BTN_B3))
    {
        wait_for_release_select = false;
        uint8_t selected_screen = screen;
        screen = 0; // reset to first screen
        transition_offset = 0;
        return selected_screen;
    }
    if (!in_transition && (b_state & hw::Buttons::State::BTN_B3))
    {
        wait_for_release_select = true;
    }

    //do transition animation
    if (in_transition && counter % 10 == 0)
    {
        transition_offset = (transition_offset + 1) % 10;
        if (transition_offset == 0)
        {
            in_transition = false;
            //set next or prev screen here
            //_next_ will work in both ways for transitions
            screen = calc_next_screen(screen);
            transition_offset = 0;
            return 255;
        }
    }

    return 255;
}

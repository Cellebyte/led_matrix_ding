
#include "./menu.h"

hw::LEDMatrix::Rect snake_pic[] = {
    hw::LEDMatrix::Rect {
        1,5, CRGB::White
    },
    hw::LEDMatrix::Rect {
        1,4, CRGB::Green
    },
    hw::LEDMatrix::Rect {
        3,1, CRGB::Green
    }
};



uint8_t ctrl::MenuCtrl::show_1(int8_t offset) {
    led_matrix.show_rect((int8_t)3+offset,3, snake_pic[0]);
    led_matrix.show_rect((int8_t)8+offset,4, snake_pic[1]);
    led_matrix.show_rect((int8_t)5+offset,7, snake_pic[2]);
    led_matrix.set_pixel((int8_t)8+offset,2, CRGB::Red);
    return 0;
}

hw::LEDMatrix::Rect clock_pic[] = {
    hw::LEDMatrix::Rect {
        3,5, CRGB::White
    },
    hw::LEDMatrix::Rect {
        2,1, CRGB::Black
    },
    hw::LEDMatrix::Rect {
        5,3, CRGB::Blue
    },
    hw::LEDMatrix::Rect {
        3,5, CRGB::Blue
    },
    hw::LEDMatrix::Rect {
        3,3, CRGB::Black
    },
    hw::LEDMatrix::Rect {
        1,2, CRGB::Red
    }
};

uint8_t ctrl::MenuCtrl::show_2(int8_t offset) {
    led_matrix.show_rect((int8_t)1+offset,3, clock_pic[0]);
    led_matrix.show_rect((int8_t)1+offset,4, clock_pic[1]);
    led_matrix.show_rect((int8_t)2+offset,6, clock_pic[1]);
    led_matrix.show_rect((int8_t)5+offset,4, clock_pic[2]);
    led_matrix.show_rect((int8_t)6+offset,3, clock_pic[3]);
    led_matrix.show_rect((int8_t)6+offset,4, clock_pic[4]);
    led_matrix.show_rect((int8_t)7+offset,3, clock_pic[5]);
    led_matrix.set_pixel((int8_t)6+offset,5, CRGB::Red);
    led_matrix.set_pixel((int8_t)7+offset,5, CRGB::Blue);

    return 0;
}

hw::LEDMatrix::Rect pong_pic[] = {
    hw::LEDMatrix::Rect {
        1,3, CRGB::Yellow
    },
    hw::LEDMatrix::Rect {
        1,3, CRGB::Cyan
    }
};

uint8_t ctrl::MenuCtrl::show_3(int8_t offset) {
    led_matrix.show_rect((int8_t)1+offset,3, clock_pic[0]);
    led_matrix.show_rect((int8_t)1+offset,4, clock_pic[1]);
    led_matrix.show_rect((int8_t)1+offset,6, clock_pic[1]);
    led_matrix.show_rect((int8_t)5+offset,5, pong_pic[0]);
    led_matrix.show_rect((int8_t)8+offset,3, pong_pic[1]);
    led_matrix.set_pixel((int8_t)7+offset,4, CRGB::Red);

    return 0;
}

hw::LEDMatrix::Rect random_pic[] = {
    hw::LEDMatrix::Rect {
        1,2, CRGB::Black
    },
    hw::LEDMatrix::Rect {
        2,2, CRGB::Black
    }
};

CRGB random_color[] = {
    CRGB::Purple,
    CRGB::Blue,
    CRGB::Green,
    CRGB::Yellow,
    CRGB::Orange,
    CRGB::Red
};

uint8_t ctrl::MenuCtrl::show_4(int8_t offset) {
    led_matrix.show_rect((int8_t)1+offset,3, clock_pic[0]);
    led_matrix.show_rect((int8_t)2+offset,3, random_pic[0]);
    led_matrix.show_rect((int8_t)1+offset,6, random_pic[1]);
    for(uint8_t c=0; c<6; c++) {
        for(uint8_t i=0; i<4; i++) {
            uint8_t x = (int8_t)5 + i +offset;
            uint8_t y = 3 + c - i;
            led_matrix.set_pixel(x, y, random_color[c]);
        }
    }

    return 0;
}

uint8_t ctrl::MenuCtrl::setup() {
    return 0;
}

uint8_t ctrl::MenuCtrl::loop() {
    led_matrix.set_all(CRGB::Black);
    switch(screen) {
        case 0:
            show_1(0); break;
        case 1:
            show_1((-1) * transition_offset);
            show_2(((-1) * transition_offset) + 9);
            break; // transition
        case 2: show_2(0); break;
        case 3:
            show_2(((-1) * transition_offset));
            show_3(((-1) * transition_offset) + 9);
            break; // transition
        case 4: show_3(0); break;
        case 5:
            show_3(((-1) * transition_offset));
            show_4(((-1) * transition_offset) + 9);
            break; // transition
        case 6: show_4(0); break;
        case 7:
            show_4(((-1) * transition_offset));
            show_1(((-1) * transition_offset) + 9);
            break; // transition
        default: led_matrix.set_all(CRGB::Red);
    }


    counter = (counter + 1) % 100;
    bool in_transition =
        (1==screen
        || 3==screen
        || 5==screen
        || 7==screen);

    hw::Buttons::State b_state = buttons.get_state();

    // switch screen if butten pressed
    if(wait_for_release_next
            && !(b_state & hw::Buttons::State::BTN_B2)) {
        wait_for_release_next = false;
        screen = (screen + 1) % 8;
        transition_offset = 0;
    }
    if(b_state & hw::Buttons::State::BTN_B2) {
        wait_for_release_next = true;
    }

    //launch app if button pressed
    if(!in_transition &&
            wait_for_release_select
            && !(b_state & hw::Buttons::State::BTN_B3)) {
        wait_for_release_select = false;
        uint8_t selected_screen = screen;
        screen = 0; // reset to first screen
        transition_offset = 0;
        return selected_screen;
    }
    if(!in_transition
        && (b_state & hw::Buttons::State::BTN_B3)) {
        wait_for_release_select = true;
    }

    //do transition animation
    if(in_transition && counter%10==0) {
        transition_offset = (transition_offset + 1) % 10;
        if(transition_offset == 0) {
            in_transition = false;
            screen = (screen + 1) % 8;
            transition_offset = 0;
            return 255;
        }

    }

    return 255;
}


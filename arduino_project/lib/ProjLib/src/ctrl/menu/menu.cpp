
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



uint8_t ctrl::MenuCtrl::show_1() {
    led_matrix.set_all(CRGB::Black);
    led_matrix.show_rect(3,3, snake_pic[0]);
    led_matrix.show_rect(8,4, snake_pic[1]);
    led_matrix.show_rect(5,7, snake_pic[2]);
    led_matrix.set_pixel(8,2, CRGB::Red);
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

uint8_t ctrl::MenuCtrl::show_2() {
    led_matrix.set_all(CRGB::Black);
    led_matrix.show_rect(1,3, clock_pic[0]);
    led_matrix.show_rect(1,4, clock_pic[1]);
    led_matrix.show_rect(2,6, clock_pic[1]);
    led_matrix.show_rect(5,4, clock_pic[2]);
    led_matrix.show_rect(6,3, clock_pic[3]);
    led_matrix.show_rect(6,4, clock_pic[4]);
    led_matrix.show_rect(7,3, clock_pic[5]);
    led_matrix.set_pixel(6,5, CRGB::Red);
    led_matrix.set_pixel(7,5, CRGB::Blue);

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

uint8_t ctrl::MenuCtrl::show_3() {
    led_matrix.set_all(CRGB::Black);
    led_matrix.show_rect(1,3, clock_pic[0]);
    led_matrix.show_rect(1,4, clock_pic[1]);
    led_matrix.show_rect(1,6, clock_pic[1]);
    led_matrix.show_rect(5,5, pong_pic[0]);
    led_matrix.show_rect(8,3, pong_pic[1]);
    led_matrix.set_pixel(7,4, CRGB::Red);

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

uint8_t ctrl::MenuCtrl::show_4() {
    led_matrix.set_all(CRGB::Black);
    led_matrix.show_rect(1,3, clock_pic[0]);
    led_matrix.show_rect(2,3, random_pic[0]);
    led_matrix.show_rect(1,6, random_pic[1]);
    for(uint8_t c=0; c<6; c++) {
        for(uint8_t i=0; i<4; i++) {
            uint8_t x = 5 + i;
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
    switch(screen) {
        case 0: show_1(); break;
        case 1: show_2(); break;
        case 2: show_3(); break;
        case 3: show_4(); break;
        default: show_1();
    }
    counter = (counter + 1) % 100;
    if(counter==0) {
        screen = (screen + 1) % 4;
    }
    return 0;
}


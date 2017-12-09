#pragma once

#include "Arduino.h"
#include "FastLED.h"
#include "../../util.h"
#include "../../hw/led_matrix/led_matrix.h"
#include "../../hw/buttons/buttons.h"

namespace ctrl {

    class PongCtrl {
    public:
        PongCtrl(
            hw::LEDMatrix &led_matrix,
            hw::Buttons &buttons
        ) :
            led_matrix(led_matrix),
            buttons(buttons),
            counter(0),
            pos_a(0),
            pos_b(0)
        {}

        NO_COPY_INSTANCE(PongCtrl);

        uint8_t setup();
        uint8_t loop();

    private:
        hw::LEDMatrix &led_matrix;
        hw::Buttons &buttons;
        uint8_t counter;
        int8_t pos_a, pos_b;
        int8_t pos_ball_x, pos_ball_y, vel_ball_x, vel_ball_y;
        uint8_t input();
    };

}
#pragma once

#include "Arduino.h"
#include "FastLED.h"
#include "../../util.h"
#include "../../hw/led_matrix/led_matrix.h"
#include "../../hw/buttons/buttons.h"

namespace ctrl {

    class MenuCtrl {
    public:
        MenuCtrl(
            hw::LEDMatrix &led_matrix,
            hw::Buttons &buttons
        ) :
            led_matrix(led_matrix),
            buttons(buttons)
        {}

        NO_COPY_INSTANCE(MenuCtrl)

        uint8_t setup();
        uint8_t loop();
    private:
        hw::LEDMatrix &led_matrix;
        hw::Buttons &buttons;

        uint8_t show_1();
        uint8_t show_2();
        uint8_t show_3();
        uint8_t show_4();

    };

}
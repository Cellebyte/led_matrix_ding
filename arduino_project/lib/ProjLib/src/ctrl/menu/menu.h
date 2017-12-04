#pragma once
#include "../../hw/led_matrix/led_matrix.h"
#include "../../hw/buttons/buttons.h"
#include "../../util.h"


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

        uint8_t setup()
        {
            //TODO: unimplemented
            return 0;
        }
        uint8_t loop() {
            //TODO: unimplemented
            hw::LEDMatrix::Rect r = hw::LEDMatrix::Rect {
                1, 1, CRGB::Red
            };
            led_matrix.show_rect(0,0, r);
            return 0;
        }
    private:
        hw::LEDMatrix &led_matrix;
        hw::Buttons &buttons;
    };

}
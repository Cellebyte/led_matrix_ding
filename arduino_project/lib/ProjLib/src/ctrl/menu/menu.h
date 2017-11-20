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
        }
        uint8_t loop() {
            //TODO: unimplemented
            hw::LEDMatrix::Rect r = hw::LEDMatrix::Rect {
                1, 1, CRGB::Red
            };
            led_matrix.show_rect(0,0, r);
        }
    private:
        hw::LEDMatrix &led_matrix;
        hw::Buttons &buttons;
    };

}
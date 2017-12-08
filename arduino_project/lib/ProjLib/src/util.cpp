#include "util.h"


uint8_t isExit(uint8_t buttons) {
    hw::Buttons::State pressed_buttons = static_cast<hw::Buttons::State>(buttons);
    if ((pressed_buttons == (
            hw::Buttons::State::BTN_A0 |
            hw::Buttons::State::BTN_A1 |
            hw::Buttons::State::BTN_A2 |
            hw::Buttons::State::BTN_A3)
        ) {
            return 1;
        }
    return 0;
}
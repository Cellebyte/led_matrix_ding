#pragma once

#include "Arduino.h"
#include "FastLED.h"
#include "../../util.h"
#include "../../hw/led_matrix/led_matrix.h"
#include "../../hw/buttons/buttons.h"

namespace ctrl
{

class MenuCtrl
{
  public:
    MenuCtrl(
        hw::LEDMatrix &led_matrix,
        hw::Buttons &buttons) : led_matrix(led_matrix),
                                buttons(buttons),
                                screen(0),
                                counter(0),
                                transition_offset(0),
                                wait_for_release_next(false),
                                wait_for_release_select(false)
    {
    }

    NO_COPY_INSTANCE(MenuCtrl);

    uint8_t setup();
    uint8_t loop();

  private:
    hw::LEDMatrix &led_matrix;
    hw::Buttons &buttons;
    uint8_t screen;
    uint8_t counter;
    uint8_t transition_offset;
    bool wait_for_release_next;
    bool wait_for_release_select;

    uint8_t show_1(int8_t offset);
    uint8_t show_2(int8_t offset);
    uint8_t show_3(int8_t offset);
    uint8_t show_4(int8_t offset);
};
}
#pragma once

#include "Arduino.h"
#include "../../util.h"

#define NUM_BTNS 8

namespace hw {

    class Buttons {
    public:
        Buttons(
            uint8_t pin_a0,
            uint8_t pin_a1,
            uint8_t pin_a2,
            uint8_t pin_a3,
            uint8_t pin_b0,
            uint8_t pin_b1,
            uint8_t pin_b2,
            uint8_t pin_b3
        ) :
            state(State::None),
            pins { pin_a0, pin_a1, pin_a2, pin_a3,
                pin_b0, pin_b1, pin_b2, pin_b3 }
        {}

        NO_COPY_INSTANCE(Buttons)

        enum State: uint8_t {
            None = 0,
            BTN_A0 = (1<<0),
            BTN_A1 = (1<<1),
            BTN_A2 = (1<<2),
            BTN_A3 = (1<<3),
            BTN_B0 = (1<<4),
            BTN_B1 = (1<<5),
            BTN_B2 = (1<<6),
            BTN_B3 = (1<<7),
        };

        uint8_t setup();
        uint8_t loop();

        State get_state() {
            return state;
        }

    private:
        State state;
        uint8_t pins[NUM_BTNS];
    };

}
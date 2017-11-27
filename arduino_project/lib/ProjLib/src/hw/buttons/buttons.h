#pragma once

#include "../../util.h"
#include "Arduino.h"

namespace hw {

    class Buttons {
    public:
        Buttons() :
            state(State::None)
        {}

        NO_COPY_INSTANCE(Buttons)

        enum class State: uint16_t {
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
    };

}
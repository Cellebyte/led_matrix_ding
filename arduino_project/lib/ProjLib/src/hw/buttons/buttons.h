#pragma once

#include "../../util.h"
#include "Arduino.h"

namespace hw {

    class Buttons {
    public:
        Buttons(){}

        NO_COPY_INSTANCE(Buttons)

        uint8_t setup();
        uint8_t loop();

    private:

    };

}
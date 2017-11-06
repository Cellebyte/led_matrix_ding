#pragma once

#include "../../util.h"

#include "FastLED.h"


#define LED_ROWS 10
#define LED_COLUMNS 10
#define NUM_LEDS LED_ROWS * LED_COLUMNS

namespace hw {

    class LEDMatrix {
    public:
        LEDMatrix(){}

        NO_COPY_INSTANCE(LEDMatrix)

        uint8_t setup();
        uint8_t loop();
    private:

    };

}
#include "../../util.h"

#include "FastLED.h"


#define LED_ROWS 10
#define LED_COLUMNS 10
#define NUM_LEDS LED_ROWS * LED_COLUMNS

namespace hw {

    class LEDMatrix {
    public:
        LEDMatrix(uint8_t pin): pin(pin) {}

        NO_COPY_INSTANCE(LEDMatrix)

        uint8_t setup() {
            //TODO: unimplemented
        }
        uint8_t loop() {
            //TODO: unimplemented
        }
    private:
        const uint8_t pin;
    };

}
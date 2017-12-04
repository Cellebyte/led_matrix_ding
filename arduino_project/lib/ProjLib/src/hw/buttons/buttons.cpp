#include "./buttons.h"


/* Example to check if BTN_A0 and BTN_A1 are currently pressed:

    if (get_state() & (hw::Buttons::State::BTN_A0 | hw::Buttons::State::BTN_A1)) {

    }

*/

uint8_t hw::Buttons::setup() {
    for(uint8_t i = 0; i < NUM_BTNS; i++) {
        pinMode(i, INPUT_PULLUP);
    }
    return 0;
}

uint8_t hw::Buttons::loop() {
    hw::Buttons::State new_state = 0;
    for(uint8_t i = 0; i < NUM_BTNS; i++) {
         new_state |= ((digitalRead(pins[i]) == HIGH ? 1 : 0) << i);
    }
    state = new_state;
    return 0;
}
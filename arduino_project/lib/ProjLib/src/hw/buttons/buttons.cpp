#include "./buttons.h"


/* Example to check if BTN_A0 and BTN_A1 are currently pressed:

    if (get_state() & (hw::Buttons::State::BTN_A0 | hw::Buttons::State::BTN_A1)) {

    }

*/

uint8_t hw::Buttons::setup() {
    for(uint8_t i = 0; i < NUM_BTNS; i++) {
        pinMode(pins[i], INPUT_PULLUP);
    }
    return 0;
}

uint8_t hw::Buttons::loop() {

    counter = (counter+1) % 100;

    hw::Buttons::State new_state = 0;
    for(uint8_t i = 0; i < NUM_BTNS; i++) { // I dont even know why this order is working
         new_state |= ((digitalRead(pins[i]) == HIGH ? 1 : 0) << i);
    }

    hw::Buttons::State smoothed_state = state;

    for(uint8_t i = 0; i < NUM_BTNS; i++) {
        if(new_state & (1<<i)) {
            counter_low[i] = 0;
            counter_high[i] += 1;
        } else {
            counter_high[i] = 0;
            counter_low[i] += 1;
        }
        if(counter_high[i] >= DEBOUNCE) {
            smoothed_state |= (1<<i);
        } else if(counter_low[i] >= DEBOUNCE) {
            smoothed_state &= ~(1<<i);
        }
    }



    state = smoothed_state;
    return 0;
}
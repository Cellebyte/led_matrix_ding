#include "hw/led_matrix/led_matrix.h"

enum class Ctrl: uint8_t {
    menu = 0,
    clock,
    pong,
    rainbow,
    snake,
}
volatile Ctrl active_ctrl = Ctrl::menu;


hw::LEDMatrix led_matrix = hw::LEDMatrix(3);


void setup() {
    led_matrix.setup();
}

void loop() {
    led_matrix.loop();
}

#include "ProjLib.h"

enum class Ctrl: uint8_t {
    menu = 0,
    clock,
    pong,
    rainbow,
    snake
};
volatile Ctrl active_ctrl = Ctrl::menu;

hw::LEDMatrix led_matrix = hw::LEDMatrix();
hw::Buttons buttons = hw::Buttons();
ctrl::MenuCtrl menu_ctrl = ctrl::MenuCtrl(led_matrix, buttons);

void setup() {
    led_matrix.setup();
    buttons.setup();
    menu_ctrl.setup();
}

void loop() {
    // update HW
    led_matrix.loop();
    buttons.loop();

    // update controllers
    switch(active_ctrl) {
        case Ctrl::menu : menu_ctrl.loop(); break;
        default: break;
    }

}
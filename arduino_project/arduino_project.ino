
#include "ProjLib.h"

enum class Ctrl: uint8_t {
    menu = 0,
    clock,
    pong,
    rainbow,
    snake
};
volatile Ctrl active_ctrl = Ctrl::menu;

// uses pin 3
hw::LEDMatrix led_matrix = hw::LEDMatrix();
// button pins
hw::Buttons buttons = hw::Buttons(4,5,6,7,8,9,10,11);
ctrl::MenuCtrl menu_ctrl = ctrl::MenuCtrl(led_matrix, buttons);

void setup() {
    Serial.begin(9600);
    while (!Serial) { ; }
    led_matrix.setup();
    buttons.setup();
    menu_ctrl.setup();
    pinMode(13, OUTPUT);
}

void loop() {
    // update HW
    led_matrix.loop();
    buttons.loop();

    digitalWrite(13, HIGH);
    delay(100);

    uint8_t btns = buttons.get_state();

    char s[16];
    sprintf(s, "S: %02X", btns);
    Serial.println(s);

    digitalWrite(13, LOW);
    delay(100);

    // update controllers
    switch(active_ctrl) {
        case Ctrl::menu : menu_ctrl.loop(); break;
        default: break;
    }

}
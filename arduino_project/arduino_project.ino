#include "ProjLib.h"

hw::LEDMatrix led_matrix;
hw::Buttons buttons(4,5,6,7,8,9,10,11);
ctrl::MenuCtrl menu(led_matrix, buttons);

int v = 0;

void setup() {
    buttons.setup();
    led_matrix.setup();

    menu.setup();

    Serial.begin(9600);

}

uint8_t a = 0;
uint8_t b = 0;

void loop() {
    buttons.loop();
    led_matrix.loop();

    menu.loop();

    delay(10);
    Serial.println(buttons.get_state());

}

#include "ProjLib.h"

hw::LEDMatrix led_matrix;
hw::Buttons buttons(4,5,6,7,8,9,10,11);
ctrl::MenuCtrl menu(led_matrix, buttons);
ctrl::SnakeCtrl snake(led_matrix,buttons);
ctrl::RainbowCtrl rainbow(led_matrix,buttons);
ctrl::PongCtrl pong(led_matrix, buttons);

void setup() {
    buttons.setup();
    led_matrix.setup();
    snake.setup();
    menu.setup();
    pong.setup();
    Serial.begin(9600);
}

uint8_t app = 255;

void loop() {
    buttons.loop();

    switch(app) {

        case 0:
        {
            uint8_t r = snake.loop();
            if(r==1) {
                app = 255;
            }
        }
            break;
        case 1:
        {
            app = 255;
        }
            break;
        case 2:
        {
            uint8_t r = pong.loop();
            if(r==1) {
                app = 255;
            }
        }
            break;
        case 3:
        {
            app = 255;
        }
            break;
        case 255:
        {
            uint8_t next = menu.loop();
            if(255==next){
                app = 255;
            } else {
                snake.setup(); //reset controllers
                pong.setup();
                app = next / 2;
                led_matrix.set_pixel(0,0, CRGB::Blue);
            }
        }
            break;
        default:
            led_matrix.set_all(CRGB::Blue);

    }

    led_matrix.loop();
    delay(10);
    //Serial.println((buttons.get_state()&hw::Buttons::State::BTN_B3));
}

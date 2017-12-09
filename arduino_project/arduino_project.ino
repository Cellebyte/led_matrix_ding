#include "ProjLib.h"

hw::LEDMatrix led_matrix;
hw::Buttons buttons(4, 5, 6, 7, 8, 9, 10, 11);
ctrl::MenuCtrl menu(led_matrix, buttons);
ctrl::SnakeCtrl snake(led_matrix, buttons);
ctrl::RainbowCtrl rainbow(led_matrix, buttons);
ctrl::PongCtrl pong(led_matrix, buttons);

void setup()
{
    buttons.setup();
    led_matrix.setup();
    snake.setup();
    menu.setup();
    pong.setup();
    Serial.begin(9600);
}

uint8_t app = 255;
uint8_t set_delay = 0;

void exit_and_to_menu(CRGB color)
{
    for (int x = 0; x < MAP_WIDTH; ++x)
    {
        led_matrix.set_pixel(x, 0, color);
        led_matrix.set_pixel(x, MAP_HEIGHT - 1, color);
    }
    // Places left and right walls
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        led_matrix.set_pixel(0, y, color);
        led_matrix.set_pixel(MAP_WIDTH - 1, y, color);
    }
}

void loop()
{
    buttons.loop();

    switch (app)
    {

    case 0:
    {
        uint8_t r = snake.loop();
        if (r == 1)
        {
            exit_and_to_menu(CRGB::Purple);
            set_delay = 1;
            app = 255;
        }
        else if (r == 2)
        {
            exit_and_to_menu(CRGB::Red);
            set_delay = 1;
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
        if (r == 1)
        {
            app = 255;
            exit_and_to_menu(CRGB::Purple);
            set_delay = 1;
        }
        else if (r==2)
        {
            app = 255;
            exit_and_to_menu(CURSERA_COLOR);
            set_delay = 1;
        }
        else if (r==3)
        {
            app = 255;
            exit_and_to_menu(CURSERB_COLOR);
            set_delay = 1;
        }
    }
    break;
    case 3:
    {
        if (rainbow.loop())
        {
            exit_and_to_menu(CRGB::Purple);
            set_delay = 1;
            app = 255;
        }
    }
    break;
    case 255:
    {
        uint8_t next = menu.loop();
        if (255 == next)
        {
            app = 255;
        }
        else
        {
            snake.setup(); //reset controllers
            pong.setup();
            rainbow.setup();
            app = next;
            //led_matrix.set_pixel(0,0, CRGB::Blue);
        }
    }
    break;
    default:
        led_matrix.set_all(CRGB::Blue);
    }

    led_matrix.loop();

    if (set_delay)
    {
        delay(2500);
        set_delay = 0;
    }

    delay(10);

    //Serial.println((buttons.get_state()&hw::Buttons::State::BTN_B3));
}
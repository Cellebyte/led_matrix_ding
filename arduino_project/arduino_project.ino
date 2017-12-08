#include "ProjLib.h"

hw::LEDMatrix led_matrix;
hw::Buttons buttons(4,5,6,7,8,9,10,11);

int v = 0;

void setup() {
    buttons.setup();
    led_matrix.setup();
    //  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);

}

uint8_t a = 0;
uint8_t b = 0;

void loop() {
    buttons.loop();
    led_matrix.loop();
    for(a=0; a<10; a++) {
        for(b=0; b<10; b++) {
            led_matrix.set_all(CRGB::Black);
            led_matrix.set_pixel((a+b) % 10, (a*b) % 10, CRGB::Red);
            led_matrix.loop();
            delay(20);
        }
    }




/*
  // Turn the LED on, then pause
  leds[0] = CRGB::Red;
  FastLED.show();
  delay(500);
  // Now turn the LED off, then pause
  leds[0] = CRGB::Black;
  FastLED.show();
  delay(500);
  */
}

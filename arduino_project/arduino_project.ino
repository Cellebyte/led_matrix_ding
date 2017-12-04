#include "ProjLib.h"

hw::LEDMatrix led_matrix;
hw::Buttons buttons(4,5,6,7,8,9,10,11);

int v = 0;

void setup() { 
    buttons.setup();
    led_matrix.setup();
    //  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);

}

void loop() { 
    buttons.loop();
    led_matrix.loop();
    //led_matrix.set_pixel(0,0,v ? CRGB::Blue : CRGB::Red);
    hw::Buttons::State state = buttons.get_state();
    if(state & hw::Buttons::State::BTN_A0) {
        led_matrix.set_pixel(1,0, CRGB::Yellow);    
    } else {
        led_matrix.set_pixel(1,0, CRGB::Green);
    }
    if(state & hw::Buttons::State::BTN_A1) {
        led_matrix.set_pixel(2,0, CRGB::Purple);    
    } else {
        led_matrix.set_pixel(2,0, CRGB::Red);
    }
    //led_matrix.show_rect(0,1, hw::LEDMatrix::Rect{ 3, 1, CRGB::Yellow});
    v^=1;
    //delay(500);
    
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

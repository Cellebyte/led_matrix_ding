#pragma once
#include <Arduino.h>
#include <FastLED.h>
#include "../../hw/buttons/buttons.h"
#include "../../hw/led_matrix/led_matrix.h"
#include "../../util.h"
#include <stdint.h>

#define NUM_LEDS 100

extern CRGBPalette16 myRedWhiteBluePalette;
const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM =
{
    CRGB::Red,
    CRGB::Gray, // 'white' is too bright compared to red and blue
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Red,
    CRGB::Gray,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Blue,
    CRGB::Black,
    CRGB::Black
};

namespace ctrl
{

class RainbowCtrl
{
  public:
    RainbowCtrl(hw::LEDMatrix &led_matrix, hw::Buttons &buttons): led_matrix(led_matrix), buttons(buttons) {}

    NO_COPY_INSTANCE(RainbowCtrl);

    uint8_t setup();
    uint8_t loop();

  private:
    CRGBPalette16 currentPalette;
    TBlendType    currentBlending;
    hw::Buttons &buttons;
    hw::LEDMatrix &led_matrix;
    uint8_t i;
    void FillLEDsFromPaletteColors(uint8_t colorIndex);
    void ChangePalettePeriodically();
    void SetupTotallyRandomPalette();
    void SetupBlackAndWhiteStripedPalette();
    void SetupPurpleAndGreenPalette();
    
    
};
}
#pragma once

#include "Arduino.h"
#include "FastLED.h"
#include "../../util.h"
#include "../../hw/led_matrix/led_matrix.h"
#include "../../hw/buttons/buttons.h"

namespace ctrl
{

class PongCtrl
{
public:
  PongCtrl(
      hw::LEDMatrix &led_matrix,
      hw::Buttons &buttons) : led_matrix(led_matrix),
                              buttons(buttons),
                              counter(0)
  {
  }

  NO_COPY_INSTANCE(PongCtrl);

  uint8_t setup();
  uint8_t loop();

private:
  hw::LEDMatrix &led_matrix;
  hw::Buttons &buttons;
  struct ball
  {
    int8_t x;
    int8_t y;
    int8_t x_vel;
    int8_t y_vel;
  } BALL;
  struct cursor
  {
    int8_t pos;
  } CURSORA,CURSORB;
  uint8_t counter;
  uint8_t move_cursors();
  uint8_t move_ball();
  void show_cursors();
  void show_ball();
  void show_playfield();
  void clear_screen();
};
}
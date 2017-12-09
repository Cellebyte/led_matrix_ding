#pragma once
#include "hw/buttons/buttons.h"

#define NO_COPY_INSTANCE(cls) \
    cls(const cls &);         \
    cls &operator=(const cls &);

#define CEIL_DIV(x, y) (x / y + (x % y != 0))

uint8_t isExit(uint8_t pressed_buttons);
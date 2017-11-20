#pragma once
#include <stdint.h>

#define NO_COPY_INSTANCE(cls) \
cls(const cls&);\
cls& operator =(const cls&);

#define CEIL_DIV(x, y) (x/y + (x % y != 0))


#include "Lcd1602Display.hpp"
#include <cstring>

Lcd1602Display::Lcd1602Display()
{
    memset(_line1, ' ', sizeof(_line1));
    memset(_line2, ' ', sizeof(_line2));
}


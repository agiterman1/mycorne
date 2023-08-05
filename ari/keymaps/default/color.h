#pragma once

#define COLOR_ON     RGB_ORANGE
#define COLOR_QWERTY RGB_BLACK
#define COLOR_NAV    RGB_GREEN
#define COLOR_SYM    RGB_WHITE
#define COLOR_FUNC   RGB_RED
#define COLOR_LEADER RGB_BLUE

#define RGB(val) ((val >> 16) & 0xFF, (val >> 8) & 0xFF, val & 0xFF)

long color(int r, int g, int b);
void light_led( int r, int g, int b);
void register_led_msg(void);


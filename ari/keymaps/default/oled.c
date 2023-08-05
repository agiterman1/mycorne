#include <stdint.h>
#include QMK_KEYBOARD_H

#include "quantum.h"
#include "raw_hid.h"
#include "transactions.h"

#include "print.h"

#include "oled.h"
#include "keymap.h"

#define MODLENGTH 10


const uint8_t maxY = 18;

// const uint8_t MODLENGTH = 10;
int8_t modIndex = -1;
char arr[MODLENGTH];
char last_arr[MODLENGTH];

extern bool is_in_leader;

static void render_letter(const char c, uint8_t y) {
    for (size_t i = 0; i < 3; i++) {
        oled_set_cursor(y+i, 1);
        oled_write_char((const char) c+i, false);

        oled_set_cursor(y+i, 2);
        oled_write_char((const char) c+i+32, false);
    }
}

void draw_mods(void) {
    // compare arrays
    if (modIndex == -1) return;

    if (modIndex == 0) {
        oled_clear();
        modIndex--;
        return;
    }

    uint8_t i;
    for (i = 0; i < modIndex; i++) {
        if (arr[i] != last_arr[i]) {
            break;
        }
    }
    printf("%d, %d\n", i, modIndex);
    if (i == modIndex) return;

    oled_clear();
    for (uint8_t i = 0; i < modIndex; i++) {
        render_letter((const char) arr[i], maxY - i * 3);
    }

    // copy arr to last_arr
    for (uint8_t i = 0; i < modIndex; i++) {
        last_arr[i] = arr[i];
    }
}

// static void render_logo(void) {
//     // static const char PROGMEM qmk_logo[] = {
//     //     0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
//     //     0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
//     //     0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
//     // };

//     // render_letter(128);
//     // oled_set_cursor(8, 1);
//     // oled_write_char((const char) 128, false);
//     // oled_set_cursor(9, 1);
//     // oled_write_char((const char) 129, false);
//     // oled_set_cursor(10, 1);
//     // oled_write_char((const char) 130, false);

//     // oled_set_cursor(8, 2);
//     // oled_write_char((const char) 160, false);
//     // oled_set_cursor(9, 2);
//     // oled_write_char((const char) 161, false);
//     // oled_set_cursor(10, 2);
//     // oled_write_char((const char) 162, false);

// }

bool oled_task_user(void) {
    if (!is_keyboard_master()) {
        return false;
    }

    if ( is_in_leader ) return false;

    // render_letter(137);

    // oled_write_P(font, false);
    // return false;

    // oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            // oled_write_P(PSTR("Def\n"), false);
            light_led( COLOR_QWERTY );
            break;
        case _NAV:
            // oled_write_P(PSTR("NAV\n"), false);
            light_led( COLOR_NAV );
            break;
        case _SYM:
            // oled_write_P(PSTR("SYM\n"), false);
            light_led( COLOR_SYM );
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            // oled_write_P(PSTR("FUNC\n"), false);
            light_led( COLOR_FUNC );
    }
    // ~MOD_MASK_SHIFT & get_oneshot_locked_mods()

    return false;
}

// void oneshot_mods_changed_kb(uint8_t mods) {
//     println("HELLO")
// }
// void oneshot_mods_changed_user(uint8_t mods) {
//   if (mods & MOD_MASK_SHIFT) {
//     println("Oneshot locked mods SHIFT");
//     // handle_locked_mod((char) 137);
//   } else {
//         println("Oneshot locked mods SHIFT OFF");
//         // handle_unlocked_mod((char) 137);
//     }
//   if (mods & MOD_MASK_CTRL) {
//     println("Oneshot locked mods CTRL");
//     // handle_locked_mod((char) 134);
//   } else {
//     println("Oneshot locked mods CTRL OFF");
//     // handle_unlocked_mod((char) 134);
//   }
//   if (mods & MOD_MASK_ALT) {
//     println("Oneshot locked mods ALT");
//     // handle_locked_mod((char) 128);
//   } else {
//     println("Oneshot locked mods ALT OFF");
//     // handle_unlocked_mod((char) 128);
//   }
//   if (mods & MOD_MASK_GUI) {
//     println("Oneshot locked mods GUI");
//     // handle_locked_mod((char) 140);
//   } else {
//     println("Oneshot locked mods GUI OFF");
//     // handle_unlocked_mod((char) 140);
//   }
//   if (!mods) {
//     println("Oneshot locked mods off");
//   }

//   // draw_mods();
// }



// add c to buffer (only if not there)
void handle_locked_mod(char c) {
    if (modIndex == -1) modIndex = 0;

    if ( modIndex + 1 == MODLENGTH ) return;

    for (uint8_t i = 0; i < modIndex; i++) {
        if (arr[i] == c) return;
    }

    arr[modIndex] = c;
    modIndex++;
}

// remove c from buffer (only if it is there)
void handle_unlocked_mod(char c) {
        for (uint8_t i = 0; i < modIndex; i++) {
            if (arr[i] == c) {
                // shift elements to the left
                for(uint8_t j=i;j<modIndex;j++)
                    arr[j]=arr[j+1];

                modIndex--; // the number of mods is down by 1
                return;
            }
        }
}

bool is_shift_locked = false;
bool is_alt_locked = false;
void oneshot_locked_mods_changed_user(uint8_t mods) {
  if (mods & MOD_MASK_SHIFT) {
    is_shift_locked = true;
    println("Oneshot locked mods SHIFT");
    handle_locked_mod(LETTER_S);
  } else {
        if (is_shift_locked) {
            is_shift_locked = false;
            println("Oneshot locked mods SHIFT OFF");
            handle_unlocked_mod(LETTER_S);
        }

    }
  if (mods & MOD_MASK_CTRL) {
    println("Oneshot locked mods CTRL");
    handle_locked_mod((char) 134);
  } else {
    println("Oneshot locked mods CTRL OFF");
    handle_unlocked_mod((char) 134);
  }
  if (mods & MOD_MASK_ALT) {
    is_alt_locked = true;
    println("Oneshot locked mods ALT");
    handle_locked_mod(LETTER_A);
  } else {
        if (is_alt_locked) {
            is_alt_locked = false;
            println("Oneshot locked mods ALT OFF");
            handle_unlocked_mod(LETTER_A);
        }

    }
  if (mods & MOD_MASK_GUI) {
    println("Oneshot locked mods GUI");
    handle_locked_mod((char) 140);
  } else {
    println("Oneshot locked mods GUI OFF");
    handle_unlocked_mod((char) 140);
  }
  if (!mods) {
    println("Oneshot locked mods off");
  }

  draw_mods();
}
/*
void draw_static(uint8_t x, uint8_t y, uint8_t width, uint8_t heigth, int color, uint8_t density) {
    unsigned long rx        = fastrand_long();
    unsigned long ry        = fastrand_long();
    unsigned long maskx     = 1;
    unsigned long masky     = 1;
    unsigned long mask_base = 1;

    // more 1 in the octet
    for (int r = 0; r < density; r++) {
        rx &= fastrand_long();
        ry &= fastrand_long();
    }

    color = ((rx >> 1) % 2) == 0;

    for (uint8_t i = 0; i < width; i++) {
        for (uint8_t j = 0; j < heigth; j++) {
            // new mask based on ij loop
            maskx = (mask_base << i);
            masky = (mask_base << j);

            // logic AND with the masks
            if (((rx & maskx) == maskx) && ((ry & masky) == masky)) {
                oled_write_pixel(x + i, y + j, color);
            }
        }
    }
}

*/


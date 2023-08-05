#include <stdint.h>
#include QMK_KEYBOARD_H

#include "quantum.h"
#include "raw_hid.h"
#include "transactions.h"

#include "print.h"


#include "keymap.h"
#define modLength 10

const uint8_t maxY = 18;

// const uint8_t modLength = 10;
uint8_t modIndex = 0;
char arr[modLength];

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
    oled_clear();

    for (uint8_t i = 0; i < modIndex; i++) {
        render_letter((const char) arr[i], maxY - i * 3);
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
        case _RAISE:
            // oled_write_P(PSTR("RAISE\n"), false);
            light_led( COLOR_RAISE );
            break;
        case _LOWER:
            // oled_write_P(PSTR("LOWER\n"), false);
            light_led( COLOR_LOWER );
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



void handle_locked_mod(char c) {
    bool inArr = false;
    for (uint8_t i = 0; i < modIndex; i++) {
        if (arr[i] == c) inArr = true;
    }

    if (!inArr) {
        arr[modIndex] = c;
        modIndex++;
    }
}

void handle_unlocked_mod(char c) {
        for (uint8_t i = 0; i < modIndex; i++) {
            if (arr[i] == c) {
                char temp=arr[i];
                {
                    for(uint8_t j=i;j<modIndex-1;j++)
                    arr[j]=arr[j+1];
                }

                arr[modIndex-1]=temp;
                i--;
                modIndex--;
            }
        }
}

bool is_shift_locked = false;
void oneshot_locked_mods_changed_user(uint8_t mods) {
  if (mods & MOD_MASK_SHIFT) {
    is_shift_locked = true;
    println("Oneshot locked mods SHIFT");
    handle_locked_mod((char) 137);
  } else {
        if (is_shift_locked) {
            is_shift_locked = false;
            println("Oneshot locked mods SHIFT OFF");
            handle_unlocked_mod((char) 137);
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
    println("Oneshot locked mods ALT");
    handle_locked_mod((char) 128);
  } else {
    println("Oneshot locked mods ALT OFF");
    handle_unlocked_mod((char) 128);
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

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
char arr[MODLENGTH] = {0};
char last_arr[MODLENGTH] = {1};

extern bool is_in_leader;

static void render_letter(const char c, uint8_t y) {
    for (size_t i = 0; i < 3; i++) {
        oled_set_cursor(y+i, 2);
        oled_write_char((const char) c+i, false);

        oled_set_cursor(y+i, 3);
        oled_write_char((const char) c+i+32, false);
    }
}

// draw mods (vertical)
void draw_mods(void) {
    printf("draw_mods, modIndex: %d\n", modIndex);
    if (modIndex == -1) return; // nothing on screen

    if (modIndex == 0) {        // last mod released
        oled_clear();
        arr[0] = 0; last_arr[0] = 1;
        modIndex--;
        return;
    }
    printf("draw_mods, test buffers\n");

    // compare arrays (avoid drawing twice the same image)
    uint8_t i;
    for (i = 0; i < MODLENGTH; i++) {
        if (arr[i] != last_arr[i]) {
            break;
        }
    }
    printf("draw_mods, %d, %d\n", i, modIndex);
    if (i == MODLENGTH) return; // frame not changed. nothing to draw
    printf("draw_mods,  DRAW!\n");

    // draw vertical
    oled_clear();
    for (uint8_t i = 0; i < modIndex; i++) {
        render_letter((const char) arr[i], maxY - i * 3);
    }

    // copy arr to last_arr
    for (uint8_t i = 0; i < MODLENGTH; i++) {
        last_arr[i] = arr[i];
    }
}

bool oled_task_user(void) {
    if (!is_keyboard_master()) {
        return false;
    }

    // println("OLED_TASK_USER");

    uint8_t mod_state = get_mods();
    (mod_state & MOD_MASK_SHIFT) ? handle_locked_mod(LETTER_S) : handle_unlocked_mod(LETTER_S);
    (mod_state & MOD_MASK_ALT) ? handle_locked_mod(LETTER_A) : handle_unlocked_mod(LETTER_A);
    (mod_state & MOD_MASK_CTRL) ? handle_locked_mod(LETTER_C) : handle_unlocked_mod(LETTER_C);
    (mod_state & MOD_MASK_GUI) ? handle_locked_mod(LETTER_G) : handle_unlocked_mod(LETTER_G);
    if (modIndex >= 0 ) draw_mods();

    oled_set_cursor(0,0);

    if ( is_in_leader ) {
        oled_write_P(PSTR("Leader\n"), false);
        light_led( COLOR_LEADER );
        return false;
    }

    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            switch (biton32(eeconfig_read_default_layer())) {
              case _QWERTY:
                oled_write_ln(PSTR("ARI"), false);
                light_led( COLOR_QWERTY );
                break;
              case _RANI:
                oled_write_ln(PSTR("RANI"), false);
                light_led( COLOR_RANI );
                break;
            };
            break;
        case _NAV:
            oled_write_ln(PSTR("NAV"), false);
            light_led( COLOR_NAV );
            break;
        case _SYM:
            oled_write_ln(PSTR("SYM"), false);
            light_led( COLOR_SYM );
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln(PSTR("FUNC"), false);
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
    printf("handle_locked_mod, modIndex: %d\n", modIndex);
    if (modIndex == -1) modIndex = 0;

    if ( modIndex + 1 == MODLENGTH ) return;

    for (uint8_t i = 0; i < modIndex; i++) {
        if (arr[i] == c) return;
    }

    printf("handle_locked_mod, Add: %d\n", c);
    arr[modIndex++] = c;
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

// bool is_shift_locked = false;
// bool is_alt_locked = false;
// void oneshot_locked_mods_changed_user(uint8_t mods) {
//     return;

//   if (mods & MOD_MASK_SHIFT) {
//     is_shift_locked = true;
//     println("Oneshot locked mods SHIFT");
//     handle_locked_mod(LETTER_S);
//   } else {
//         if (is_shift_locked) {
//             is_shift_locked = false;
//             println("Oneshot locked mods SHIFT OFF");
//             handle_unlocked_mod(LETTER_S);
//         }

//     }
//   if (mods & MOD_MASK_CTRL) {
//     println("Oneshot locked mods CTRL");
//     handle_locked_mod((char) 134);
//   } else {
//     println("Oneshot locked mods CTRL OFF");
//     handle_unlocked_mod((char) 134);
//   }
//   if (mods & MOD_MASK_ALT) {
//     is_alt_locked = true;
//     println("Oneshot locked mods ALT");
//     handle_locked_mod(LETTER_A);
//   } else {
//         if (is_alt_locked) {
//             is_alt_locked = false;
//             println("Oneshot locked mods ALT OFF");
//             handle_unlocked_mod(LETTER_A);
//         }

//     }
//   if (mods & MOD_MASK_GUI) {
//     println("Oneshot locked mods GUI");
//     handle_locked_mod((char) 140);
//   } else {
//     println("Oneshot locked mods GUI OFF");
//     handle_unlocked_mod((char) 140);
//   }
//   if (!mods) {
//     println("Oneshot locked mods off");
//   }

//   draw_mods();
// }

// void release_shift(void) {
//     if (!is_shift_locked) {
//         println("release_shift");
//         handle_unlocked_mod(LETTER_S);
//     }
// }

// void release_alt(void) {
//     if (!is_alt_locked) {
//         println("release_alt");
//         handle_unlocked_mod(LETTER_A);
//     }
// }
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


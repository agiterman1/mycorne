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

typedef union {
    uint8_t raw;
    struct {
        bool inverse : 1;
        int c : 7;
    } mod;
} mod_t;
int8_t modIndex = -1;
mod_t arr[MODLENGTH] = { {0} };
mod_t last_arr[MODLENGTH] = { {1} };

extern bool is_in_leader;

static void render_letter(const char c, uint8_t y, bool inverse) {
    for (size_t i = 0; i < 3; i++) {
        oled_set_cursor(y+i, 2);
        oled_write_char(c+i + 100, inverse);

        oled_set_cursor(y+i, 3);
        oled_write_char(c+i+32 + 100, inverse);
    }
}

static void render_letter_name(const char c, uint8_t y, bool inverse) {
    for (size_t i = 0; i < 2; i++) {
        oled_set_cursor(y+i, 2);
        oled_write_char(c+i + 100, inverse);

        oled_set_cursor(y+i, 3);
        oled_write_char(c+i+32 + 100, inverse);
    }
}

// clear line 2 and line 3
void oled_clear_mods(void) {
    oled_set_cursor(0, 2);
    oled_write_ln(PSTR(""), false);
    oled_write_ln(PSTR(""), false);

}
// draw mods (vertical)
void draw_mods(void) {
    // printf("draw_mods, modIndex: %d\n", modIndex);
    if (modIndex == -1) return; // nothing on screen

    if (modIndex == 0) {        // last mod released
        oled_clear_mods();
        arr[0].raw = 0; last_arr[0].raw = 1;
        modIndex--;
        return;
    }
    // printf("draw_mods, test buffers\n");

    // compare arrays (avoid drawing twice the same image)
    uint8_t i;
    for (i = 0; i < MODLENGTH; i++) {
        if (arr[i].raw != last_arr[i].raw ) {
            break;
        }
    }
    // printf("draw_mods, %d, %d\n", i, modIndex);
    if (i == MODLENGTH) return; // frame not changed. nothing to draw
    // printf("draw_mods,  DRAW!\n");

    // draw vertical
    oled_clear_mods();
    for (uint8_t i = 0; i < modIndex; i++) {
        render_letter( arr[i].mod.c, maxY - i * 3, arr[i].mod.inverse );
    }

    // copy arr to last_arr
    for (uint8_t i = 0; i < MODLENGTH; i++) {
        last_arr[i].raw= arr[i].raw;
    }
}

bool is_osm_shft=false;
bool is_osm_shft_lock=false;
void oneshot_mods_changed_user(uint8_t mods) {
    // println("oneshot_mods_changed_user, start");

    is_osm_shft = false;
    if (mods & MOD_MASK_SHIFT) {
        println("Oneshot mods SHIFT");
        is_osm_shft = true;
    }
    if (mods & MOD_MASK_CTRL) {
        println("Oneshot mods CTRL");
    }
    if (mods & MOD_MASK_ALT) {
        println("Oneshot mods ALT");
    }
    if (mods & MOD_MASK_GUI) {
        println("Oneshot mods GUI");
    }
    if (!mods) {
        println("Oneshot mods off");
    }
}

void oneshot_locked_mods_changed_user(uint8_t mods) {
    is_osm_shft_lock = false;
    if (mods & MOD_MASK_SHIFT) {
        println("Oneshot SHIFT locked");
        is_osm_shft_lock = true;
    }
}

bool oled_task_user(void) {

    if (!is_keyboard_master()) {
        return false;
    }

    // println("oled_task_user, start");

    // println("OLED_TASK_USER");

    uint8_t mod_state = get_mods();

// uprintf("oled_task_user, mods: 0x%04X\n", mod_state);
    (( mod_state & MOD_MASK_SHIFT ) || is_osm_shft || is_osm_shft_lock) ? mod_add(LETTER_S) : mod_remove(LETTER_S);
    (mod_state & MOD_MASK_ALT)   ? mod_add(LETTER_A) : mod_remove(LETTER_A);
    (mod_state & MOD_MASK_CTRL)  ? mod_add(LETTER_C) : mod_remove(LETTER_C);
    (mod_state & MOD_MASK_GUI)   ? mod_add(LETTER_G) : mod_remove(LETTER_G);
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
                oled_write_ln(PSTR(""), false);
                light_led( COLOR_RANI );
                render_letter_name(LETTER_R_NAME, 0, false);
                render_letter_name(LETTER_A_NAME, 3, false);
                render_letter_name(LETTER_N_NAME, 6, false);
                render_letter_name(LETTER_I_NAME, 9, false);
                break;
            };
            break;
        case _MOD:
            oled_write_ln(PSTR("MOD"), false);
            light_led( COLOR_MOD );
            break;
        case _NAV:
            oled_write_ln(PSTR("NAV"), false);
            light_led( COLOR_NAV );
            break;
        case _SYM:
            oled_write_ln(PSTR("SYM"), false);
            light_led( COLOR_SYM );
            break;
        case _NUM:
            oled_write_ln(PSTR("NUM"), false);
            light_led( COLOR_NUM );
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
void mod_add(char c) {
    // printf("mod_add, modIndex: %d, c: %d\n", modIndex, c);
    // println("mod_add, start");
    if (modIndex == -1) modIndex = 0;

    if ( modIndex + 1 == MODLENGTH ) return;

    for (uint8_t i = 0; i < modIndex; i++) {
        // if (arr[i].mod.c == c) return;
        if (arr[i].mod.c == c) mod_remove(c);
    }

    uint8_t locked_mods = get_oneshot_locked_mods();
 printf("mod_add, Add: %d, mods: %x\n", c, locked_mods);
    arr[modIndex].mod.c = c;
    if ( c == LETTER_S )
        arr[modIndex++].mod.inverse = MOD_MASK_SHIFT & locked_mods || is_osm_shft_lock;
    if ( c == LETTER_C )
        arr[modIndex++].mod.inverse = MOD_MASK_CTRL & locked_mods;
    if ( c == LETTER_A )
        arr[modIndex++].mod.inverse = MOD_MASK_ALT & locked_mods;
    if ( c == LETTER_G )
        arr[modIndex++].mod.inverse = MOD_MASK_GUI & locked_mods;
    // printf("mod_add, modIndex: %d, added: %d,%d\n", modIndex-1, arr[modIndex-1].mod.c, arr[modIndex-1].mod.inverse);

}

// remove c from buffer (only if it is there)
void mod_remove(char c) {
    if ( modIndex == -1 ) return;

    // printf("mod_remove, modIndex: %d, c: %d\n", modIndex, c);
    for (uint8_t i = 0; i < modIndex; i++) {
        if (arr[i].mod.c == c) {
            // shift elements to the left
            for(uint8_t j=i;j<modIndex;j++)
                arr[j].raw=arr[j+1].raw;

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


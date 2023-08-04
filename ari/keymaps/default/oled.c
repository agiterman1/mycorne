#include QMK_KEYBOARD_H

#include "transactions.h"

#include "print.h"


#include "keymap.h"

extern bool is_in_leader;

bool oled_task_user(void) {
    if (!is_keyboard_master()) {
        return false;
    }


    oled_set_cursor( 0, 0);
    oled_write_char((const char)0, false);
    oled_set_cursor( 1, 0);
    oled_write_char((const char)1, false);
    return false;


    if ( is_in_leader ) return false;

    // render_logo();
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("Def\n"), false);
            light_led( COLOR_QWERTY );
            break;
        case _RAISE:
            oled_write_P(PSTR("RAISE\n"), false);
            light_led( COLOR_RAISE );
            break;
        case _LOWER:
            oled_write_P(PSTR("LOWER\n"), false);
            light_led( COLOR_LOWER );
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_P(PSTR("FUNC\n"), false);
            light_led( COLOR_FUNC );
    }
    // ~MOD_MASK_SHIFT & get_oneshot_locked_mods()

    return false;
}

/*
void oneshot_mods_changed_user(uint8_t mods) {
  if (mods & MOD_MASK_SHIFT) {
    println("Oneshot mods SHIFT");
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
*/



void oneshot_locked_mods_changed_user(uint8_t mods) {
  if (mods & MOD_MASK_SHIFT) {
    println("Oneshot locked mods SHIFT");
  }
  if (mods & MOD_MASK_CTRL) {
    println("Oneshot locked mods CTRL");
  }
  if (mods & MOD_MASK_ALT) {
    println("Oneshot locked mods ALT");
  }
  if (mods & MOD_MASK_GUI) {
    println("Oneshot locked mods GUI");
  }
  if (!mods) {
    println("Oneshot locked mods off");
  }
}

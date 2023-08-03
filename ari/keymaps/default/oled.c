#include QMK_KEYBOARD_H

#include "quantum.h"
#include "raw_hid.h"
#include "transactions.h"

#include "print.h"


#include "keymap.h"

extern bool is_in_leader;

bool oled_task_user(void) {
    if (!is_keyboard_master()) {
        return false;
    }

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
    return false;
}



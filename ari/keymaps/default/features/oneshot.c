/* Copyright 2021 @jcmkk3
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "oneshot.h"

/* uint16_t shift_count = 0;     // avoid double capital */
//
void update_oneshot(
    oneshot_state *state,
    uint16_t mod,
    uint16_t trigger,
    uint16_t keycode,
    keyrecord_t *record
) {
    if (keycode == trigger) {
        if (record->event.pressed) {
            /* shift_count = 0; */
            // Trigger keydown
            if (*state == os_up_unqueued) {
                register_code(mod);
            }
            else if (mod== KC_LGUI) {
// println("update_oneshot, double!");
                *state = os_down_used;
                return;
            }
/* println("update_oneshot, pressed"); */
            *state = os_down_unused;
        } else {
            // Trigger keyup
            switch (*state) {
            case os_down_unused:
                // If we didn't use the mod while trigger was held, queue it.
                *state = os_up_queued;
                break;
            case os_down_used:
                // If we did use the mod while trigger was held, unregister it.
                *state = os_up_unqueued;
                unregister_code(mod);
                break;
            default:
                break;
            }
        }
    } else {
/* println("update_oneshot, else start"); */
        if (record->event.pressed) {
/* println("update_oneshot, else pressed"); */
printf("update_oneshot, else in shift, state=%u, keycode=%u\n", *state,keycode);
            if (is_oneshot_cancel_key(keycode) && *state != os_up_unqueued) {
                // Cancel oneshot on designated cancel keydown.
                *state = os_up_unqueued;
                unregister_code(mod);
            }
//             else if (keycode ==  0x4328) { // enter
// println("update_oneshot, else in enter DONE");
//                 unregister_code(mod);
//                 // oled_task_user();
//
//                 // need to clear the lcd. (mod is cleared but not from lcd)
//             }
/*             else if ( mod == KC_LSFT ) { */
// printf("update_oneshot, else in shift, state=%u, shift_count=%u\n", *state,shift_count);
/*                 if (++shift_count==2 && *state == 1 ) { */
/* println("update_oneshot, else in shift DONE"); */
/**/
/*                     unregister_code(mod); */
/*                     shift_count = 0; */
/*                 } */
/*             } */
            } else {
                if (!is_oneshot_ignored_key(keycode)) {
                    // On non-ignored keyup, consider the oneshot used.
                    switch (*state) {
                    case os_down_unused:
                        *state = os_down_used;

                        break;
                    case os_up_queued:
                        *state = os_up_unqueued;
                        unregister_code(mod);
                        break;
                    default:
                        break;
                    }
                }
            }
    }
}

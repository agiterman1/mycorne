#include QMK_KEYBOARD_H
#include "leader.h"
#include "raw_hid.h"

#include "print.h"

extern bool is_in_leader;

void leader_start_user(void) {
    is_in_leader = true;
    // oled_set_cursor(0,0);
    // oled_write_P(PSTR("LEAD\n"), false);
}

void tmux_prefix(void) {
  tap_code16(LCTL(KC_A));
}

void leader_end_user(void) {
    is_in_leader = false;

    // copy
    if (leader_sequence_one_key(KC_C))
        SEND_STRING(SS_LCTL("c"));  // tap_code16(LCTL(KC_C));

    // paste
    if (leader_sequence_one_key(KC_V))
        SEND_STRING(SS_LCTL("v"));

    // vim write
    if (leader_sequence_one_key(KC_W))
        SEND_STRING(SS_TAP(X_ESC) ":w" SS_TAP(X_ENTER));

    // select to end of line
    if (leader_sequence_two_keys(KC_L, KC_E))
        SEND_STRING(SS_LSFT(SS_TAP(X_END)));

    // select to start of line
    if (leader_sequence_two_keys(KC_L, KC_H))
        SEND_STRING(SS_LSFT(SS_TAP(X_HOME)));

    // select ALL line
    if (leader_sequence_two_keys(KC_L, KC_L))
        SEND_STRING(SS_TAP(X_HOME) SS_LSFT(SS_TAP(X_END)));

    // select ALL line and copy to clipboard
    if (leader_sequence_two_keys(KC_L, KC_C))
        SEND_STRING(SS_TAP(X_HOME) SS_LSFT(SS_TAP(X_END)) SS_LCTL("c"));


    // TMUX - a
    if (leader_sequence_one_key(KC_A)) {
        tmux_prefix();
    }

    //
    // TMUX - goto to last pane
    if (leader_sequence_one_key(KC_SEMICOLON)) {
        tmux_prefix();
        SEND_STRING(";");
    }

}


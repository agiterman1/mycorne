#include QMK_KEYBOARD_H
#include "keycodes.h"
// #include "quantum.h"
#include "raw_hid.h"
#include "transactions.h"

#include "print.h"

#include "keymap.h"
#include "color.h"
#include "oled.h"

#include "features/oneshot.h"
#include "features/layermodes.h"


enum combos {
  cmb_DASH,
  JK_ESC,
  // HJ_LEADER,
  NM_LEADER,
  // MCOMMA_NUM_WORD,
  cmb_TAB
};

const uint16_t PROGMEM dash_combo[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};
// const uint16_t PROGMEM hj_combo[] = {KC_H, KC_J, COMBO_END};
const uint16_t PROGMEM nm_combo[] = {KC_N, KC_M, COMBO_END};
// const uint16_t PROGMEM mcomma_combo[] = {KC_M, KC_COMM, COMBO_END};
const uint16_t PROGMEM tab_combo[] = {KC_Q, KC_W, COMBO_END};

combo_t key_combos[] = {
  // Add commonly used dash to home row
  [cmb_DASH]    = COMBO(dash_combo, KC_MINS),
  // For Vim, put Escape on the home row
  [JK_ESC]    = COMBO(jk_combo, KC_ESC),
  // leader key
  // [HJ_LEADER] = COMBO(hj_combo, QK_LEAD),
  [NM_LEADER] = COMBO(nm_combo, QK_LEAD),
  // num_word
  // [MCOMMA_NUM_WORD] = COMBO(mcomma_combo, NUMWORD),
  [cmb_TAB] = COMBO(tab_combo, KC_TAB),
};

// enum {
//   TD_Q_TAB = 0
// };

// tap_dance_action_t tap_dance_actions[] = {
//   [TD_Q_TAB] = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_TAB)
// };

// #define TD_Q TD(TD_Q_TAB)


// LA_MOD
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       /* KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,ALT_TAB , */
      XXXXXXX,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,ALT_TAB ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      /* OS_CTRL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                     KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_SCLN ,KC_QUOT , */
      XXXXXXX,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                     KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_SCLN ,KC_QUOT ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      OSM_SFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                     KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,OSL_FUN ,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          SHF_TAB, KC_BSPC,  LA_SYM,    NAV_ENT, MOD_SPC,OS_GUI
                                           //OS_GUI, KC_BSPC, LA_SYM,   NAV_ENT ,KC_SPC  ,LA_MOD
                                         // OSM_LCTL, GUI_ENT, SYM_TAB,   NAV_BSP ,KC_SPC  ,OSM_SFT
                                      //`--------------------------'  `--------------------------'
  ),

  [_RANI] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,ALT_TAB ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      CTL_ESC,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                     KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_SCLN ,KC_QUOT ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      OSM_SFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                     KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,OSL_FUN ,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         OSM_ALT , KC_BSPC, LA_SYM,   NAV_ENT ,KC_SPC  ,KC_LGUI
                                         // OSM_ALT, GUI_BSP, SYM_LDR,     NAV_ENT,KC_SPC  ,OSM_SFT
  ),

  [_MOD] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, KC_1,    KC_2,   KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    XXXXXXX ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,  OS_GUI,  OS_ALT, OS_SHFT, OS_CTRL, XXXXXXX,                     NUMWORD ,OS_CTRL , OS_SHFT, OS_ALT ,OS_GUI  ,XXXXXXX ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, CW_TOGG, XXXXXXX, XXXXXXX,                     XXXXXXX ,KC_APP  ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______,_______ ,_______

  ),

  [_SYM] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, KC_EXLM, KC_AT,  KC_HASH, KC_DLR,  KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN ,XXXXXXX ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_1,    KC_2,   KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0    ,XXXXXXX ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, NUMWORD, KC_TILD,KC_GRV, KC_LBRC, KC_LCBR,                       KC_RCBR, KC_RBRC ,_______ ,_______ ,_______ ,XXXXXXX ,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_TRNS,  KC_TRNS, SYM   ,    KC_TRNS, KC_SPC, KC_COLON
                                      //`--------------------------'  `--------------------------'
    ),


  [_NAV] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, KC_DEL , XXXXXXX, KC_UNDS, KC_PLUS, KC_PGUP,                      QK_REP , K_BACK , K_FORW , KC_BSLS, KC_PIPE,XXXXXXX ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_HOME, KC_END , KC_MINS, KC_EQL , KC_PGDN,                      KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT,  K_TMUX,XXXXXXX ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_LT  , KC_GT  , K_CPY  , K_PST  , KC_SCLN,                      KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT,KC_MPLY ,XXXXXXX ,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_TRNS, KC_TRNS, XXXXXXX,    NAV  , KC_TRNS, KC_TRNS
                                      //`--------------------------'  `--------------------------'
  ),

  [_NUM] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, KC_EXLM, KC_AT,  KC_UNDS, KC_PLUS, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN ,XXXXXXX ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_1,    KC_2,   KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0    ,KC_QUOT ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_LSFT, XXXXXXX,XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX , XXXXXXX,_______ ,_______ ,_______ ,XXXXXXX ,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_MINS,  KC_TRNS,KC_TRNS,  KC_TRNS , KC_SPC, KC_COLON
                                      //`--------------------------'  `--------------------------'

    ),
  [_FUNC] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, KC_F1  , KC_F2  , KC_F3  , KC_F4  ,  KC_F5 ,                     KC_F6   , KC_F7  , KC_F8  , KC_F9  , KC_F10 ,QK_LOCK ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, OS_GUI , OS_ALT , OS_SHFT, OS_CTRL,  KC_F11,                     KC_MS_L , KC_MS_D, KC_MS_U, KC_MS_R,XXXXXXX ,TO(_QWERTY),
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_CAPS, K_CUT  , K_CPY  , K_PST  ,  KC_F12,                     KC_WH_L , KC_WH_U, KC_WH_D, KC_WH_R,QK_BOOT ,_______ ,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            ARI  , RANI   , XXXXXXX,    KC_BTN1, KC_BTN3, KC_BTN2
                                      //`--------------------------'  `--------------------------'
  ),

};


long last_color;
bool is_in_leader = false;

// void keyboard_pre_init_user() {
// }

void keyboard_post_init_user() {
    register_led_msg();

    last_color = 0;
    light_led(COLOR_ON);
}

/* SHF_TAB, KC_BSPC,  LA_SYM,    NAV_ENT, MOD_SPC,OS_GUI */
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
      case NAV_ENT:
      case SHF_TAB:
      case MOD_SPC:
            return TAPPING_TERM_THUMB;
      // case LT(_SYM, KC_TAB):
      //       return TAPPING_TERM_THUMB;
      default:
            return TAPPING_TERM;
    }
}

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case LA_MOD:
    // case LA_NAV:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case LA_MOD:
    // case LA_NAV:
    // case KC_LSFT:
    // case KC_BSPC:
    case CTL_ESC:
    case OSM_SFT:
    case LA_SYM:
    case NAV_ENT:
    case OSL_FUN:
    // case KC_SPC:
    case KC_LGUI:
    case OS_SHFT:
    case OS_CTRL:
    case OS_ALT:
    case OS_GUI:
// uprintf("is_oneshot_ignored_key: 0x%04X, return true\n", keycode);
    case MOD_SPC:
        return true;
    default:
// uprintf("is_oneshot_ignored_key: 0x%04X, return false\n", keycode);
        return false;
    }
}

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_gui_state = os_up_unqueued;


// uint8_t mod_state;
uint16_t key_timer; // declare key_timer for use in macro
bool is_alt_tab_active = false; // ADD this near the beginning of keymap.c
uint16_t alt_tab_timer = 0;     // we will be using them soon.


// return false; // Skip all further processing of this key
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    update_oneshot(
        &os_shft_state, KC_LSFT, OS_SHFT,
        keycode, record
    );
    update_oneshot(
        &os_ctrl_state, KC_LCTL, OS_CTRL,
        keycode, record
    );
    update_oneshot(
        &os_alt_state, KC_LALT, OS_ALT,
        keycode, record
    );
    update_oneshot(
        &os_gui_state, KC_LGUI, OS_GUI,
        keycode, record
    );

// if (!process_caps_word(keycode, record)) { return false; }
    if (!process_num_word(keycode, record)) { return false; }

    // Store the current modifier state in the variable for later reference
    // static bool delkey_registered;
    uint8_t mod_state = get_mods();
    // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u, mod: 0x%04X\n",
            keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count, mod_state);
#endif
    switch (keycode) {

        case NUMWORD:
            process_num_word_activation(record);
            return false;

        case ALT_TAB:
            if (record->event.pressed) {
              if (!is_alt_tab_active) {
                is_alt_tab_active = true;
                register_code(KC_LALT);
              }
              alt_tab_timer = timer_read();
              register_code(KC_TAB);
            } else {
              unregister_code(KC_TAB);
            }
            break;

        // case SYM_LDR:
        //     if (record->event.pressed) {
        //          key_timer = timer_read();
        //     } else {
        //         if (timer_elapsed(key_timer) < TAPPING_TERM ) {
        //             if ( !is_in_leader )
        //                 leader_start();
        //             else
        //                 leader_end();
        //             return true;
        //         }
        //     }
        //     break;

//         case GUI_BSP:
//                 // of the delete key status: registered or not?
//             if (record->event.pressed) {
//                 // Detect the activation of either shift keys
// // #ifdef CONSOLE_ENABLE
//      uprintf("mod_state: 0x%04X, MOD_MASK_SHIFT: 0x%04X\n", mod_state, MOD_MASK_SHIFT);
// // #endif
//                 if (mod_state & MOD_MASK_SHIFT) {
//                     // uprintf("shif hold\n");
//                     // light_led( COLOR_LEADER );
//                     // First temporarily canceling both shifts so that
//                     // shift isn't applied to the KC_DEL keycode
//                     del_mods(MOD_MASK_SHIFT);
//                     register_code(KC_DEL);
//                     // Update the boolean variable to reflect the status of KC_DEL
//                     delkey_registered = true;
//                     // Reapplying modifier state so that the held shift key(s)
//                     // still work even after having tapped the Backspace/Delete key.
//                     set_mods(mod_state);
//                     return false; // Skip all further processing of this keyz
//                 }
//             } else { // on release of KC_BSPC
//                 // In case KC_DEL is still being sent even after the release of KC_BSPC
//                 if (delkey_registered) {
//                     // uprintf("release delkey\n");
//                     unregister_code(KC_DEL);
//                     delkey_registered = false;
//                     return false; // Skip all further processing of this keyz
//                 }
//             }
//             // Let QMK process the KC_BSPC keycode as usual outside of shift
//             return true;

        case ARI:
            if (record->event.pressed) {
                // default_layer_set(_QWERTY);
                oled_clear(); // clear oled
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;

        case RANI:
            if (record->event.pressed) {
                // default_layer_set(_RANI);
                set_single_persistent_default_layer(_RANI);
                light_led(COLOR_CONFIRM);
            }

            return false;
    }

    return true;

}

void matrix_scan_user(void) { // The very important timer.
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1000) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
}




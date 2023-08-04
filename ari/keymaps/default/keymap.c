#include QMK_KEYBOARD_H
#include "quantum.h"
#include "raw_hid.h"
#include "transactions.h"

#include "print.h"

#include "keymap.h"
#include "color.h"
#include "swapper.h"


enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  SW_WIN,  // Switch to next window         (cmd-tab)
};

enum combos {
  DF_DASH,
  JK_ESC
};

const uint16_t PROGMEM df_combo[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};

combo_t key_combos[] = {
  // Add commonly used dash to home row
  [DF_DASH]    = COMBO(df_combo, KC_MINS),
  // For Vim, put Escape on the home row
  [JK_ESC]    = COMBO(jk_combo, KC_ESC),
};

// For _QWERTY layer
#define OSM_LCTL OSM(MOD_LCTL)
#define OSM_AGR  OSM(MOD_RALT)
#define OSL_FUN  OSL(_FUNC)
#define GUI_ENT  GUI_T(KC_ENT)
#define LOW_LDR  LT(_LOWER, KC_NO)
#define RSE_BSP  LT(_RAISE, KC_BSPC)
#define OSM_SFT  OSM(MOD_LSFT)

#define GUI_BSP  GUI_T(KC_BSPC)
#define RSE_ENT  LT(_RAISE, KC_ENT)

// For _RAISE layer
#define CTL_ESC  LCTL_T(KC_ESC)
#define OSM_ALT  OSM(MOD_LALT)
#define K_CPY    C(S(KC_C))
#define K_PST    C(S(KC_V))
#define K_CUT    C(S(KC_X))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,QK_LOCK,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       CTL_ESC,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                     KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_SCLN ,KC_QUOT ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       OSM_SFT,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                     KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,OSL_FUN ,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         OSM_ALT, GUI_BSP, LOW_LDR,   RSE_ENT ,KC_SPC  ,OSM_SFT
                                         // OSM_LCTL, GUI_ENT, LOW_TAB,   RSE_BSP ,KC_SPC  ,OSM_SFT
                                      //`--------------------------'  `--------------------------'
  ),

  [_LOWER] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, KC_EXLM, KC_AT,  KC_HASH, KC_DLR,  KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______ ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_1,    KC_2,   KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______ ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX , KC_TILD,KC_GRV, KC_LBRC, KC_LCBR,                       KC_RCBR, KC_RBRC, KC_COMM,KC_DOT,  KC_SLSH, _______ ,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_TRNS,  KC_TRNS, LOWER,    KC_TRNS, KC_TRNS, KC_COLON
                                      //`--------------------------'  `--------------------------'
    ),


  [_RAISE] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, KC_DEL , XXXXXXX, KC_UNDS, KC_PLUS, KC_PGUP,                      XXXXXXX, XXXXXXX, XXXXXXX, KC_BSLS, KC_PIPE,_______ ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_HOME, KC_END , KC_MINS, KC_EQL , KC_PGDN,                      KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_APP ,_______ ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_LT  , KC_GT  , K_CPY  , K_PST  , KC_SCLN,                      KC_MPLY, KC_MPRV, KC_MNXT, KC_VOLD, KC_VOLU,_______ ,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          CTL_ESC, KC_TRNS, XXXXXXX,    RAISE  , KC_TRNS, KC_TRNS
                                      //`--------------------------'  `--------------------------'
  ),

  [_FUNC] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, KC_F1  , KC_F2  , KC_F3   , KC_F4 ,  KC_F5 ,                     KC_F6   , KC_F7  , KC_F8  , KC_F9  , KC_F10 ,_______ ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_F11 , KC_F12 , XXXXXXX, XXXXXXX, XXXXXXX,                     KC_MS_L , KC_MS_D, KC_MS_U, KC_MS_R,XXXXXXX ,TO(_QWERTY),
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_CAPS, K_CUT  , K_CPY  , K_PST  , XXXXXXX,                     KC_WH_L , KC_WH_D, KC_WH_U, KC_WH_R,QK_BOOT ,_______ ,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, XXXXXXX, XXXXXXX,    KC_BTN1, KC_BTN3, KC_BTN2
                                      //`--------------------------'  `--------------------------'
  )
};


long last_color;
bool is_in_leader = false;
bool sw_win_active = false;

void keyboard_pre_init_user() {

    // light_led( RGB_RED );
    // key_timer = timer_read();
    // setPinOutput(PS2_RST_PIN);
    // writePinHigh(PS2_RST_PIN);
    //         wait_ms(10);
    // writePinLow(PS2_RST_PIN);

}
void keyboard_post_init_user() {
    register_led_msg();

    // light_led( RGB_GREEN );
  //     rgblight_enable();
  // rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
  // rgblight_setrgb(RGB_CLEAR);

    // rgblight_enable_noeeprom(); // enables Rgb, without saving settings
    // rgblight_sethsv(200, 255, 255); // sets the color to teal/cyan without saving
    // rgblight_mode(RGBLIGHT_MODE_BREATHING); // sets mode to Fast breathing without saving
    last_color = 0;
    light_led(COLOR_ON);
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
      case LT(_RAISE, KC_BSPC):
            return TAPPING_TERM_THUMB;
      case LT(_LOWER, KC_TAB):
            return TAPPING_TERM_THUMB;
      default:
            return TAPPING_TERM;
    }
}

// layer_state_t layer_state_set_user(layer_state_t state) {
  // switch (biton32(state)) {
  // case _QWERTY:
  //   uprintf("layer: DEF\n");
  //   break;
  // case _SYMB:
  //   uprintf("layer: SYM\n");
  //   break;
  // }
  // return state;
// }



uint8_t mod_state;
uint16_t key_timer; // declare key_timer for use in macro

// return false; // Skip all further processing of this key
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif

    update_swapper(
        &sw_win_active, KC_LGUI, KC_TAB, SW_WIN,
        keycode, record
    );
    //
    // Store the current modifier state in the variable for later reference
    // static bool delkey_registered;
    mod_state = get_mods();
    switch (keycode) {

        // https://docs.qmk.fm/#/feature_macros?id=advanced-macro-functions
        // case ALT_TAB:
        //   if (record->event.pressed) {
        //     if (!is_alt_tab_active) {
        //       is_alt_tab_active = true;
        //       register_code(KC_LALT);
        //     }
        //     alt_tab_timer = timer_read();
        //     register_code(KC_TAB);
        //   } else {
        //     unregister_code(KC_TAB);
        //   }
        //   break;


        // case KC_BSPC:
        case LOW_LDR:
            if (record->event.pressed) {
                 key_timer = timer_read();
            } else {
                if (timer_elapsed(key_timer) < TAPPING_TERM ) {
                    if ( !is_in_leader )
                        leader_start();
                    else
                        leader_end();
                    return true;
                }
            }
            // rgblight_setrgb(RGB_BLUE);
            break;
/*
        case GUI_BSP:
                // of the delete key status: registered or not?
            if (record->event.pressed) {
                // Detect the activation of either shift keys
// #ifdef CONSOLE_ENABLE
//     uprintf("mod_state: 0x%04X, MOD_MASK_SHIFT: 0x%04X\n", mod_state, MOD_MASK_SHIFT);
// #endif
                if (mod_state & MOD_MASK_SHIFT) {
                    light_led( COLOR_LEADER );
                    // First temporarily canceling both shifts so that
                    // shift isn't applied to the KC_DEL keycode
                    del_mods(MOD_MASK_SHIFT);
                    register_code(KC_DEL);
                    // Update the boolean variable to reflect the status of KC_DEL
                    delkey_registered = true;
                    // Reapplying modifier state so that the held shift key(s)
                    // still work even after having tapped the Backspace/Delete key.
                    set_mods(mod_state);
                    return false; // Skip all further processing of this keyz
                }
            } else { // on release of KC_BSPC
                // In case KC_DEL is still being sent even after the release of KC_BSPC
                if (delkey_registered) {
                    unregister_code(KC_DEL);
                    delkey_registered = false;
                    return false; // Skip all further processing of this keyz
                }
            }
            // Let QMK process the KC_BSPC keycode as usual outside of shift
            return true;
*/
    }

    return true;

}

void ps2_mouse_moved_user(report_mouse_t *mouse_report) {
#ifdef CONSOLE_ENABLE
    uprintf("MS: x: %d, y: %d\n", mouse_report->x, mouse_report->y);
#endif
}


const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
	&delete_key_override,
	NULL // Null terminate the array of overrides!
};


// const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);

// // This globally defines all key overrides to be used
//
// const key_override_t **key_overrides = (const key_override_t *[]){
//     &delete_key_override,
//     NULL // Null terminate the array of overrides!
// };






/*
 * void oneshot_locked_mods_changed_user(uint8_t mods) {
    if (mods & MOD_MASK_SHIFT) {
        del_mods(MOD_MASK_SHIFT);
        set_oneshot_locked_mods(~MOD_MASK_SHIFT & get_oneshot_locked_mods());   // this will remove the lock!
        caps_word_on();
    }
}*/


/*
* set_single_persistent_default_layer
*/

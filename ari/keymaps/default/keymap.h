#pragma once

#include "quantum.h"


enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  SYM,
  NAV,
  ALT_TAB,  // Switch to next window         (cmd-tab)
  RANI,
  ARI,
    OS_SHFT,
    OS_CTRL,
    OS_ALT,
    OS_GUI,
    NUMWORD,
    SEL_LINE,
};
// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum custom_layers {
  _QWERTY,
  _RANI,
  _SYM,
  _NAV,
  _NUM,
  _MOD,
  _FUNC,
};

// For _QWERTY layer
#define OSM_LCTL OSM(MOD_LCTL)
#define OSM_SFT  OSM(MOD_LSFT)
#define OSM_AGR  OSM(MOD_RALT)
#define OSM_GUI  OSM(MOD_LGUI)
#define OSL_FUN  OSL(_FUNC)
#define GUI_ENT  GUI_T(KC_ENT)
#define SYM_LDR  LT(_SYM, KC_NO)
#define NAV_BSP  LT(_NAV, KC_BSPC)

#define GUI_BSP  GUI_T(KC_BSPC)
#define NAV_ENT  LT(_NAV, KC_ENT)
#define MOD_SPC  LT(_MOD, KC_SPC)
#define SHF_TAB  MT(OSM_SFT, KC_TAB)

// For _NAV layer
#define CTL_ESC  LCTL_T(KC_ESC)
#define OSM_ALT  OSM(MOD_LALT)
#define K_TMUX   C(KC_A)
#define K_CPY    C(KC_C)
#define K_PST    C(S(KC_V))
#define K_CUT    C(KC_X)
/* #define K_BACK   A(KC_B) */
#define K_BACK   C(KC_LEFT)
#define K_FORW   C(KC_RIGHT)
#define K_LANG   G(KC_SPC)


#define LA_MOD MO(_MOD)
#define LA_SYM MO(_SYM)
#define SYM_ESC  LT(_SYM, KC_ESC)

#define K_TAB_R    C(KC_TAB)
#define K_TAB_L    C(S(KC_TAB))

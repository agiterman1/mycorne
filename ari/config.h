#pragma once

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET // Activates the double-tap behavior
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U // Timeout window in ms in which the double tap can occur.
// #define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP27 // Specify a optional status led by GPIO number which blinks when entering the bootloader

/* Top left key on left half */
#define BOOTMAGIC_LITE_ROW    0
#define BOOTMAGIC_LITE_COLUMN 0
/* Top right key on right half */
#define BOOTMAGIC_LITE_ROW_RIGHT    0
#define BOOTMAGIC_LITE_COLUMN_RIGHT 0


// Split Keyboard Stuff
#define MASTER_RIGHT
/* #define MASTER_LEFT */
/* #define EE_HANDS */
// #define SPLIT_HAND_PIN GP8

#define USB_POLLING_INTERVAL_MS 1

#define SERIAL_USART_FULL_DUPLEX // Use full duplex communication (TRRS)
#define SERIAL_USART_TX_PIN GP0  // USART TX pin
#define SERIAL_USART_RX_PIN GP1  // USART RX pin
// #define SELECT_SOFT_SERIAL_SPEED 5

#define HAL_USE_I2C TRUE
#define I2C_DRIVER I2CD1
#define I2C1_SDA_PIN GP14
#define I2C1_SCL_PIN GP15

#define OLED_DISPLAY_128X32
#define OLED_DISPLAY_WIDTH 128
#define OLED_DISPLAY_HEIGHT 32
#define OLED_FONT_H "font.c"

// #undef RGB_MATRIX_LED_COUNT
// #define RGB_MATRIX_LED_COUNT 2
// #undef RGB_MATRIX_SPLIT
// #define RGB_MATRIX_SPLIT { 1, 1 }
// #define WS2812_DRIVER = vendor
// #define WS2812_DI_PIN GP16
// #define WS2812_PIO_USE_PIO16 // Force the usage of PIO1 peripheral, by default the WS2813 implementation uses the PIO0 peripheral
// #define RGBLED_NUM 2
// #define NOP_FUDGE 0.4
// #define RGBLIGHT_DEFAULT_HUE 85





// #define SERIAL_DEBUG


/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

// TrackPoint
//#define PS2_CLOCK_PIN GP28
//#define PS2_DATA_PIN  GP29
//#define PS2_RST_PIN   GP26

// Serial uses PIO0, change PS2 to PIO1.
#define PS2_MOUSE_INVERT_X
#define PS2_MOUSE_INVERT_Y
#define PS2_CLOCK_PIN GP11
#define PS2_DATA_PIN  GP10
/* #define PS2_RST_PIN   GP9 */
#define PS2_PIO_USE_PIO1 // Force the usage of PIO1 peripheral, by default the PS2 implementation uses the PIO0 peripheral
#define PS2_MOUSE_X_MULTIPLIER 2
#define PS2_MOUSE_Y_MULTIPLIER 2
#define PS2_MOUSE_V_MULTIPLIER 5
/* #define PS2_MOUSE_ROTATE 90 */ //Compensate for West-facing device orientation.
/* To debug the mouse reports */
/* #define PS2_MOUSE_DEBUG_HID */
/* #define PS2_MOUSE_DEBUG_RAW */







// Customized by markstos
#define TAPPING_TERM 200
#define TAPPING_TERM_PER_KEY
// used for Tapping Term on thumb keys
#define TAPPING_TERM_THUMB 260

#define DEBOUNCE 15

// If you press a dual-role key, press another key, and then release the
// dual-role key, all within the tapping term, by default the dual-role key
// will perform its tap action. If the HOLD_ON_OTHER_KEY_PRESS option is
// enabled, the dual-role key will perform its hold action instead.
// #define HOLD_ON_OTHER_KEY_PRESS

// When enabled, typing a mod-tap plus second within term will register as the mod-combo
// Ref: https://beta.docs.qmk.fm/using-qmk/software-features/tap_hold#permissive-hold
//#define PERMISSIVE_HOLD
#define HOLD_ON_OTHER_KEY_PRESS

// Set the COMBO_TERM so low that I won't type the keys one after each other during normal typing.
// They would have be held together intentionally to trigger this.
#define COMBO_TERM 50
#define COMBO_STRICT_TIMER

// These mostly affect my one-shot Shift key, providing a CapsLock alternative.
// I want a relatively low timeout, so if I accidentally type "Shift", I can pause just briefly and move on.
#define ONESHOT_TAP_TOGGLE 2  /* Tapping this number of times holds the key until tapped once again. */
#define ONESHOT_TIMEOUT 5000  /* Time (in ms) before the one shot key is released */





#define LEADER_NO_TIMEOUT
#define LEADER_PER_KEY_TIMING
#define LEADER_TIMEOUT 500






#undef SPLIT_USB_DETECT
/* #define SPLIT_MODS_ENABLE */
#define SPLIT_TRANSPORT_MIRROR
#define SPLIT_LAYER_STATE_ENABLE
// #define SPLIT_USB_TIMEOUT 5000
// #define SPLIT_USB_TIMEOUT_POLL 10
// #define SPLIT_LED_STATE_ENABLE
// #define RGBLIGHT_SPLIT
// #define RGBLED_SPLIT { 1, 1 }

// #define DEBUG_MATRIX_SCAN_RATE
//




#define SPLIT_TRANSACTION_IDS_USER USER_SYNC_LED


#ifdef MOUSEKEY_ENABLE
  #undef MOUSEKEY_INTERVAL
  #define MOUSEKEY_INTERVAL 10

  #undef MOUSEKEY_TIME_TO_MAX
  #define MOUSEKEY_TIME_TO_MAX 70

  #undef MOUSEKEY_MAX_SPEED
  #define MOUSEKEY_MAX_SPEED 6

  #undef MOUSEKEY_MOVE_DELTA
  #define MOUSEKEY_MOVE_DELTA 4

  #undef MOUSEKEY_DELAY
  #define MOUSEKEY_DELAY 5
#endif


// had problem with it. (nav/enter key)
// #define RETRO_TAPPING

// #define MOUSEKEY_INTERVAL 12
// #define MOUSEKEY_MAX_SPEED 6
// #define MOUSEKEY_TIME_TO_MAX 50

// #define MOUSEKEY_DELAY 20
// // It makes sense to use the same delay for the mouseweel
// #define MOUSEKEY_WHEEL_DELAY 100
// // The default is 100
// #define MOUSEKEY_WHEEL_INTERVAL 50
// // The default is 40
// #define MOUSEKEY_WHEEL_TIME_TO_MAX 100



// #define CAPS_WORD_TOGGLE_KEY

// #define AUTO_SHIFT_TIMEOUT 250
// #define NO_AUTO_SHIFT_SPECIAL
// #define NO_AUTO_SHIFT_NUMERIC
// #define AUTO_SHIFT_NO_AUTO_REPEAT


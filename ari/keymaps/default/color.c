#include "quantum.h"
#include "raw_hid.h"
#include "transactions.h"

#include "print.h"


#include "color.h"


extern long last_color;

long color(int r, int g, int b) {
    return r << 16 | g << 8 | b;
}

typedef struct _master_to_slave_t {
    int r,g,b;
} master_to_slave_t;


void user_sync_led_slave_handler(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
    const master_to_slave_t *m2s = (const master_to_slave_t*)in_data;
    rgblight_setrgb(m2s->r, m2s->g, m2s->b );
}

void register_led_msg() {
    transaction_register_rpc(USER_SYNC_LED, user_sync_led_slave_handler);
}

void light_led( int r, int g, int b) {
    // uprintf("light_led, start: 0x%02X, 0x%02X, 0x%02X\n", r, g, b);
    if ( last_color == color(COLOR_ON) && color(r,g,b) == color(COLOR_QWERTY) ) return;   // on boot, leave color on until any layer is pressed
    if ( last_color == color(r,g,b)) return;    // multiple calls. ignore dup

    // print("light_led, 1\n");
  // dprint("DPRINT IS WORKING!, 1\n");
    // rgblight_enable_noeeprom(); // enables Rgb, without saving settings
    // rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT); // sets mode to Fast breathing without saving

    last_color = color(r,g,b);
    rgblight_setrgb(r, g, b);
    rgblight_set(); // Utility functions do not call rgblight_set() automatically, so they need to be called explicitly.
    // rgb_matrix_set_color(0,r,g,b);

    if (is_keyboard_master()) {
        master_to_slave_t c = {r, g, b};
        transaction_rpc_send(USER_SYNC_LED, sizeof(c), &c);
    }
}


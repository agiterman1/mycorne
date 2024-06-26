SRC += leader.c \
	   color.c \
	   oled.c \
	   features/oneshot.c \
	   features/layermodes.c \
	   features/layer_lock.c

# Disable QMK core's Caps Word implementation.
CAPS_WORD_ENABLE = yes


# OLED_ENABLE = yes
OLED_DRIVER_ENABLE = yes
# LTO_ENABLE = yes

#RGBLIGHT_ENABLE = yes


#
# Split Keyboard Stuff
SPLIT_KEYBOARD = yes
SERIAL_DRIVER = vendor



#WS2812_DRIVER = vendor


### TrackPoint
# error on compile, add to ~/qmk_firmware/platforms/chibios/drivers/ps2/ps2_io.c
### #define PAL_MODE_OUTPUT_OPENDRAIN       7U
PS2_MOUSE_ENABLE = yes
PS2_ENABLE = yes
PS2_DRIVER = vendor
POINTING_DEVICE_DRIVER = ps2


COMBO_ENABLE = yes

LEADER_ENABLE = yes

KEY_LOCK_ENABLE = yes
# KEY_OVERRIDE_ENABLE = yes

# AUTO_SHIFT_ENABLE = yes
# TAP_DANCE_ENABLE = yes

REPEAT_KEY_ENABLE = yes


SRC += leader.c \
	   color.c \
	   oled.c \
	   swapper.c




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
#PS2_MOUSE_ENABLE = yes
#PS2_ENABLE = yes
#PS2_DRIVER = interrupt



COMBO_ENABLE = yes


LEADER_ENABLE = yes

KEY_LOCK_ENABLE = yes

KEY_OVERRIDE_ENABLE = yes

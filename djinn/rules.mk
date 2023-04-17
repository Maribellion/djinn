CUSTOM_MATRIX = lite

SERIAL_DRIVER = usart

WS2812_DRIVER = pwm
CIE1931_CURVE = yes

RGB_MATRIX_DRIVER = WS2812

EEPROM_DRIVER = spi

AUDIO_DRIVER = pwm_software

DEFAULT_FOLDER = tzarc/djinn/rev2
QUANTUM_PAINTER_ENABLE = yes
QUANTUM_PAINTER_DRIVERS += ili9341_spi

VPATH += keyboards/tzarc/djinn/keymaps/default/graphics

SRC += \
	djinn_portscan_matrix.c \
	djinn_split_sync.c \
	djinn_usbpd.c\


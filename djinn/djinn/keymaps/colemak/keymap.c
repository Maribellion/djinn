// Copyright 2018-2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#include "theme_djinn_default.h"
#include "partyparrot.qgf.h"
#include <qp.h>

// Layer definitions
enum { _QWERTY, _LOWER, _RAISE, _ADJUST };

//----------------------------------------------------------
// Key map

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_all(
        KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,      KC_5,    KC_MINS,                             KC_EQL,  KC_6,     KC_7,      KC_8,    KC_9,    KC_0,    KC_BSPC,
        KC_TAB,   KC_Q,   KC_W,    KC_F,    KC_P,      KC_B,    KC_LBRC,                             KC_RBRC, KC_J,     KC_L,      KC_U,    KC_Y,    KC_SCLN,    KC_BSLS,
        KC_LCTL,  KC_A,   KC_R,    KC_S,    KC_T,      KC_G,    KC_HOME,                             KC_PGUP, KC_M,     KC_N,      KC_E,    KC_I,    KC_O, KC_QUOT,
        KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_D,      KC_V,    KC_END,                              KC_PGDN, KC_K,     KC_H,      KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
                                   KC_LGUI, MO(_LOWER),KC_BSPC, KC_GRV,                              KC_DEL,   KC_SPC,   MO(_RAISE),KC_LALT,
                                                                      RGB_RMOD,              RGB_MOD,
                                                       KC_UP,                                                 KC_UP,
                                            KC_LEFT,   _______, KC_RIGHT,                            KC_LEFT, _______, KC_RIGHT,
                                                       KC_DOWN,                                               KC_DOWN
    ),
    [_LOWER] = LAYOUT_all(
        KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,     KC_F5,   _______,                             _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        _______, _______, KC_UP,   _______, _______,   _______, _______,                             _______, _______, _______, _______, _______, _______, _______,
        _______, KC_LEFT, KC_DOWN, KC_RIGHT,_______,   _______, _______,                             _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,   _______, _______,                             _______, _______, _______, _______, _______, _______, _______,
                                   _______, _______,   _______, _______,                             _______, _______, _______, _______,
                                                                      BL_DOWN,               BL_UP, 
                                                     _______,                                               _______,
                                            _______,   _______, _______,                             _______, _______, _______,
                                                     _______,                                               _______
    ),
    [_RAISE] = LAYOUT_all(
        KC_F12, KC_F1,   KC_F2,    KC_F3,   KC_F4,     KC_F5,   _______,                             _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        _______,_______, KC_UP,    _______, _______,   _______, _______,                             _______, _______, _______, _______, _______, _______, _______,
        _______,KC_LEFT, KC_DOWN,  KC_RIGHT,_______,   KC_UNDS, KC_NO,                               KC_NO,   KC_EQL,  _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,   KC_MINS, KC_NO,                               KC_NO,   KC_PLUS, _______, _______, _______, _______, _______,
                                   _______, _______,   _______, _______,                             _______, _______, _______, _______,
                                                                      _______,               _______,
                                                     _______,                                               _______,
                                            _______,   _______, _______,                             _______, _______, _______,
                                                     _______,                                               _______
    ),
    [_ADJUST] = LAYOUT_all(
        _______, KC_CAPS, KC_NUM,  KC_SCRL, _______,   _______, _______,                             _______, _______, _______, _______, DB_TOGG, EE_CLR,  QK_BOOT,
        _______, _______, _______, _______, _______,   _______, _______,                             _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,   _______, _______,                             _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,   _______, _______,                             _______, _______, _______, _______, _______, _______, _______,
                                   _______, _______,   _______, _______,                             _______, _______, _______, _______,
                                                                      _______,               _______,
                                                     _______,                                               _______,
                                            _______,   _______, _______,                             _______, _______, _______,
                                                     _______,                                               _______
    )
};
// clang-format on

//----------------------------------------------------------
// Encoder map

// clang-format off
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_QWERTY] = { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [_LOWER]  = { ENCODER_CCW_CW(RGB_HUD, RGB_HUI),           ENCODER_CCW_CW(RGB_SAD, RGB_SAI)  },
    [_RAISE]  = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI),           ENCODER_CCW_CW(RGB_SPD, RGB_SPI)  },
    [_ADJUST] = { ENCODER_CCW_CW(RGB_RMOD, RGB_MOD),          ENCODER_CCW_CW(KC_LEFT, KC_RIGHT) },
};
// clang-format on


painter_device_t qp_ili9341_make_spi_device(uint16_t panel_width, uint16_t panel_height, pin_t chip_select_pin, pin_t dc_pin, pin_t reset_pin, uint16_t spi_divisor, int spi_mode);

//----------------------------------------------------------
// Overrides

static painter_image_handle_t partyparrot;
static deferred_token my_anim;
void keyboard_post_init_user(void) {
    partyparrot = qp_load_image_mem(gfx_partyparrot);
    if (partyparrot != NULL) {
        my_anim = qp_animate(display, (240 - partyparrot->width), (320 - partyparrot->height), partyparrot);
    }
}
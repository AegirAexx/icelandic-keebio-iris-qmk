#include QMK_KEYBOARD_H
#include "keymap_icelandic.h"

// --------------------------------------------------------------------------------
// 1. LAYERS & SETUP
// --------------------------------------------------------------------------------
enum layers {
    _QWERTY,
    _SYMB_L,
    _SYMB_R,
    _NAV
};

// Inner Thumbs: Only Enter is a Mod-Tap now
#define ALT_ENT MT(MOD_LALT, KC_ENT)

// Home Row Mods (Nav Layer Only)
#define NAV_CTL KC_LCTL
#define NAV_GUI KC_LGUI
#define NAV_ALT KC_LALT
#define NAV_SFT KC_LSFT

// --------------------------------------------------------------------------------
// 3. COMBOS
// --------------------------------------------------------------------------------
enum combos { CAPS_COMBO, CAD_COMBO };
const uint16_t PROGMEM caps_keys[] = {KC_LSFT, KC_RSFT, COMBO_END};
const uint16_t PROGMEM cad_keys[]  = {KC_F6, KC_F7, COMBO_END};

combo_t key_combos[] = {
    [CAPS_COMBO] = COMBO(caps_keys, KC_CAPS),
    [CAD_COMBO]  = COMBO(cad_keys,  LALT(LCTL(KC_DEL)))
};

bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    if (combo_index == CAD_COMBO) { return layer_state_is(_NAV); }
    return true;
}

// --------------------------------------------------------------------------------
// 4. KEYMAP
// --------------------------------------------------------------------------------
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = LAYOUT(
        KC_ESC,  IS_1,    IS_2,    IS_3,    IS_4,    IS_5,                       IS_6,    IS_7,    IS_8,    IS_9,    IS_0,    IS_ODIA,
        KC_TAB,  IS_Q,    IS_W,    IS_E,    IS_R,    IS_T,                       IS_Y,    IS_U,    IS_I,    IS_O,    IS_P,    IS_ETH,
        KC_BSPC, IS_A,    IS_S,    IS_D,    IS_F,    IS_G,                       IS_H,    IS_J,    IS_K,    IS_L,    IS_AE,   IS_ACUT,
        KC_LSFT, IS_Z,    IS_X,    IS_C,    IS_V,    IS_B,    KC_LGUI,  KC_F12,  IS_N,    IS_M,    IS_COMM, IS_DOT,  IS_THRN, KC_RSFT,
                                      KC_LCTL, MO(_SYMB_L), ALT_ENT,         KC_SPC,  MO(_SYMB_R), KC_LCTL
    ),

    [_SYMB_L] = LAYOUT(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                      KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
        KC_NO,   IS_EXLM, IS_AT,   IS_HASH, IS_DLR,  IS_LBRC,                    IS_RBRC, IS_CIRC, IS_SLSH, IS_BSLS, IS_PIPE, KC_NO,
        KC_DEL,  IS_PLUS, IS_MINS, IS_UNDS, IS_EQL,  IS_LCBR,                    IS_RCBR, IS_DQUO, IS_QUOT, IS_GRV,  IS_QUES, KC_NO,
        KC_LSFT, IS_PERC, IS_TILD, IS_AMPR, IS_ASTR, IS_LPRN, KC_LGUI,  KC_PSCR, IS_RPRN, IS_LABK, IS_SCLN, IS_COLN, IS_RABK, KC_RSFT,
                                         KC_LCTL, KC_TRNS, ALT_ENT,        KC_SPC,  MO(_SYMB_R), KC_LCTL
    ),

    [_SYMB_R] = LAYOUT(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                      KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
        KC_NO,   IS_EXLM, IS_AT,   IS_HASH, IS_DLR,  IS_LBRC,                    IS_RBRC, IS_CIRC, IS_SLSH, IS_BSLS, IS_PIPE, KC_NO,
        KC_DEL,  IS_PLUS, IS_MINS, IS_UNDS, IS_EQL,  IS_LCBR,                    IS_RCBR, IS_DQUO, IS_QUOT, IS_GRV,  IS_QUES, KC_NO,
        KC_LSFT, IS_PERC, IS_TILD, IS_AMPR, IS_ASTR, IS_LPRN, KC_LGUI,  KC_PSCR, IS_RPRN, IS_LABK, IS_SCLN, IS_COLN, IS_RABK, KC_RSFT,
                                   KC_LCTL, MO(_SYMB_L), ALT_ENT,          KC_SPC,  KC_TRNS, KC_LCTL
    ),

    [_NAV] = LAYOUT(
        QK_BOOT, KC_NO,   KC_BRID, KC_BRIU, KC_NO,   KC_F6,                      KC_F7,   KC_NO,   KC_VOLD, KC_VOLU,  KC_NO, QK_CLEAR_EEPROM,
        KC_NO,   KC_NO,   KC_HOME, KC_END,  KC_NO,   KC_NO,                      KC_NO,   KC_NO,   KC_TAB,  KC_ESC,  KC_NO,   KC_NO,
        KC_NO,   NAV_CTL, NAV_GUI, NAV_ALT, NAV_SFT, KC_NO,                      KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_NO,   KC_NO,
        KC_NO,   IS_1,    IS_2,    IS_3,    IS_4,    IS_5,    KC_NO,    KC_NO,   IS_6,    IS_7,    IS_8,    IS_9,    IS_0,    KC_NO,
                                        KC_NO,   KC_TRNS, KC_NO,            KC_NO,   KC_TRNS, KC_NO
    )
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _SYMB_L, _SYMB_R, _NAV);
}

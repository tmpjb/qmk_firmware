/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
 * Copyright 2020 Okke Formsma <okke@formsma.nl>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#ifdef CONSOLE_ENABLE
#    include "print.h"
#endif

uint16_t copy_paste_timer;

enum layers { COLEMAK = 0, NAV, NUM, NAV2, MOD, NPAD, FNS, FNS2, MOVE, MOUS };

enum custom_keycodes { KC_CCCV = SAFE_RANGE };

// [LYR] = LAYOUT(
//       _______,  _______,   _______,   _______,   _______,   _______,                        _______,    _______,    _______,  _______,   _______,  _______,
//       _______,  _______,   _______,   _______,   _______,   _______,                        _______,    _______,    _______,  _______,   _______,  _______,
//       _______,  _______,   _______,   _______,   _______,   _______,                        _______,    _______,    _______,  _______,   _______,  _______,
//                            _______,   _______,  _______, _______, _______,              _______, _______, _______,  _______,  _______
//     ),

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [COLEMAK] = LAYOUT(OSM(MOD_LGUI), KC_Q, KC_W, KC_F, KC_P, KC_B,                                         KC_J, KC_L, KC_U,    KC_Y,   KC_SCLN, OSM(MOD_RGUI),
                       OSM(MOD_LSFT), KC_A, KC_R, KC_S, KC_T, KC_G,                                         KC_M, KC_N, KC_E,    KC_I,   KC_O,    OSM(MOD_RSFT),
                       OSM(MOD_LCTL), KC_Z, KC_X, KC_C, KC_D, KC_V,                                         KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH, OSM(MOD_RCTL),
                        OSL(NPAD), OSM(MOD_LALT), OSL(MOVE), KC_SPC, OSL(NUM),                       OSL(NUM), OSL(NAV), OSL(FNS), OSM(MOD_RALT), OSL(MOVE)),
  
    [NAV] = LAYOUT( _______, _______, KC_QUOT, S(KC_QUOT), KC_GRV,  _______,                                  KC_PAUS, _______, KC_LPRN, KC_RPRN, KC_DEL, _______,
                    _______, KC_LEFT, KC_DOWN, KC_RGHT,    KC_UP,   KC_CAPS,                                  _______, KC_ENT,  KC_ESC,  KC_TAB,  KC_COLN, _______, 
                    _______, KC_HOME, KC_PGDN, KC_END,     KC_PGUP, KC_BSLS,                                  KC_INS,  _______, KC_LBRC, KC_RBRC, KC_BSPC, _______, 
                                           _______, _______, MO(MOUS), KC_UNDS, _______,               _______, _______, _______, _______, _______),

    [NUM] = LAYOUT(_______, KC_BSPC, KC_WBAK, KC_EQL,   KC_MINS,  KC_WFWD,                                  _______, KC_EQL, _______, _______, _______, _______, 
                   _______, KC_1,    KC_2,    KC_3,     KC_4,     KC_5,                                     KC_BSPC, KC_5,   KC_6,    KC_7,    KC_8,    _______,
                   _______, KC_6,    KC_7,    KC_8,     KC_9,     KC_0,                                     KC_DEL,  KC_0,   KC_COMM, KC_DOT,  _______, _______, 
                                        _______, _______, _______, _______,  OSL(MOD),               _______, OSL(NAV2), _______, _______, _______),

    [NAV2] = LAYOUT( _______, _______, KC_QUOT, S(KC_QUOT), KC_GRV,  _______,                                  KC_PAUS, _______, KC_LPRN, KC_RPRN, _______, _______,
                    _______, KC_LEFT, KC_DOWN, KC_RGHT,    KC_UP,   KC_CAPS,                                  KC_BSPC, KC_ENT,  KC_ESC,  KC_TAB,  KC_COLN, _______, 
                    _______, KC_HOME, KC_PGDN, KC_END,     KC_PGUP, KC_BSLS,                                  KC_INS,  _______, KC_LBRC, KC_RBRC, _______, _______, 
                                           _______, _______, MO(MOUS), KC_UNDS, _______,               _______, _______, _______, _______, _______),

                                    
    [MOD] = LAYOUT(        
      _______,  _______,   _______,   _______,   _______,   _______,                        _______,    _______,    _______,  _______,   _______,  _______,
      _______,  KC_BSPC,   KC_LALT,   KC_LSFT,   KC_LCTL,   _______,                        _______,    _______,    _______,  _______,   _______,  _______,
      _______,  _______,   _______,   _______,   KC_LGUI,   _______,                        _______,    _______,    _______,  _______,   _______,  _______,
                           _______,   _______,  _______, _______, _______,              _______, _______, _______,  _______,  _______),


    [NPAD] = LAYOUT(_______, _______, KC_LCBR, KC_LPRN, KC_LBRC, KC_PAUS,                                  KC_PEQL, KC_P7, KC_P8, KC_P9, KC_PMNS, _______,
                    _______, KC_COLN, KC_LGUI,  KC_LSFT,  KC_LCTL,  KC_CAPS,                                  KC_PSLS, KC_P4, KC_P5, KC_P6, KC_PPLS, KC_NLCK, 
                    _______, KC_LALT, KC_TAB, KC_ESC,   KC_ENT, _______,                                   KC_PAST, KC_P1, KC_P2, KC_P3, _______, _______,
                                _______, _______, _______, _______, _______,                 _______, KC_PENT, KC_NLCK, KC_P0, KC_PDOT),

    [FNS] = LAYOUT(_______, TO(COLEMAK), _______, KC_F12,  KC_F11, _______,                                 _______, KC_F12, _______, _______, _______, _______,
                   _______, KC_F1,   KC_F2,   KC_F3,    KC_F4,  KC_F5,                                  _______, KC_F5,  KC_F6,   KC_F7,   KC_F8,   _______,
                   _______, KC_F6,   KC_F7,   KC_F8,    KC_F9,  KC_F10,                                 _______, KC_F10, _______, _______, _______, _______,
                                _______, _______, _______, _______, _______,               _______, _______, OSL(FNS2), _______, _______),


    [FNS2] = LAYOUT(_______, _______, _______, KC_F23,  KC_F23,  _______,                           _______, KC_F24, _______, _______, _______, _______,
                    _______, KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,                            _______, KC_F17,  KC_F18,  KC_F19,  KC_F20,  _______,
                    _______, KC_F18,  KC_F19,  KC_F20,  KC_F21,  KC_F22,                            _______, KC_F22,  KC_F24,  _______, _______, _______,
                           _______, _______, _______, KC_BSPC, _______,               _______, _______, _______, _______, _______),

    [MOVE] = LAYOUT(_______, KC_SCLN, KC_Y,   KC_U,     KC_L, KC_J,                             _______, _______, _______, _______, _______, _______, 
                    _______, KC_O,    KC_I,   KC_E,     KC_N, KC_M,                             _______, KC_BSPC, C(KC_BSPC), _______,  _______, _______,
                    _______, KC_SLSH, KC_DOT, KC_COMMA, KC_H, KC_K,                             _______, _______, _______, _______, _______, _______,
                                     RESET, _______, OSL(NAV), OSL(FNS), OSL(FNS2),               _______, MO(MOUS), _______, RESET, _______),

    [MOUS] = LAYOUT(_______, KC_WH_L, KC_WH_D, KC_WH_R, KC_WH_U, _______,                             _______, _______, KC_BTN3, KC_ACL2, _______, _______, 
                    _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_MS_U, _______,                             _______, KC_BTN1, KC_BTN2, KC_ACL1, KC_ACL0, _______,
                    _______, _______, KC_LALT, KC_LSFT, KC_LCTL, _______,                             _______, KC_BTN3, KC_LSFT, KC_LALT, _______, _______,
                                       _______, _______, _______, _______, _______,               _______, _______, _______, _______, KC_LCTL)};

void keyboard_post_init_user(void) {}


// void oneshot_mods_changed_user(uint8_t mods) {
//   if (mods & MOD_MASK_SHIFT) {
//       add_mods(MOD_BIT(KC_LSFT));
//   }
//   if (mods & MOD_MASK_CTRL) {
//   }
//   if (mods & MOD_MASK_ALT) {
//   }
//   if (!mods) {
//       clear_mods();
//   }
// }

// uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
//     switch (keycode) {
//         case OSM(MOD_LALT):
//             return 70;
//         case OSM(MOD_LSFT):
//             return 70;
//         case OSM(MOD_LCTL):
//             return 70;
//         default:
//             return TAPPING_TERM;
//     }
// }

const key_override_t delete_key_override  = ko_make_basic(MOD_MASK_SHIFT, KC_BSPACE, KC_DELETE);
const key_override_t delete_word_override = ko_make_basic(MOD_MASK_SHIFT, C(KC_BSPACE), C(KC_DELETE));
// const key_override_t shift_override = {.trigger_mods =MOD_MASK_SHIFT,
//                                         .layers = (1<<COLEMAK),
//                                         .suppressed_mods=0,
//                                         .trigger = KC_SPC,
//                                         .replacement=KC_NO,
//                                         .enabled=NULL};
// const key_override_t control_override = {.trigger_mods =MOD_MASK_CTRL,
//                                         .layers = (1<<COLEMAK),
//                                         .suppressed_mods=0,
//                                         .trigger = KC_SPC,
//                                         .replacement=KC_NO,
//                                         .enabled=NULL};


const key_override_t **key_overrides = (const key_override_t *[]){
    &delete_key_override,
    &delete_word_override,
    // &shift_override,
    // &control_override,
    // &alt_override,
    NULL  // Null terminate the array of overrides!
};
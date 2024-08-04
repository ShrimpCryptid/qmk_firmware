/* Copyright 2022 MechMerlin
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

/**
 * const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_ortho_4x4(  Base 
    KC_P7,    KC_P8,    KC_P9,    KC_PMNS,
    KC_P4,    KC_P5,    KC_P6,    KC_PPLS,
    KC_P1,    KC_P2,    KC_P3,    KC_PSLS,
    MO(1),    KC_P0,    KC_PDOT,  KC_PENT
  ),

  [1] = LAYOUT_ortho_4x4(  Fn Layer 
    RGB_TOG,   RGB_HUI,    RGB_SAI,    RGB_VAI,
    RGB_MOD,   RGB_HUD,    RGB_SAD,    RGB_VAD,
    RGB_SPD,   RGB_SPI,    KC_TRNS,    KC_TRNS,
    KC_TRNS,   KC_TRNS,    KC_TRNS,    QK_BOOT
  ),
};
 */

enum custom_keycodes {
    // Inkscape macros
    MI_LAYER_UP = SAFE_RANGE,
    MI_LAYER_DOWN,
    MI_LAYER_VIS,
    MI_LAYER_LOCK,
    MI_CLONE,
    MI_UNCLONE,
    MI_DYN_OUTSET,
    MI_SIMPLIFY,
    MI_STITCH_PREV,
    MI_STITCH_SIM,
    MI_SAVE_PES

    // Krita macros
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_ortho_4x4( /* Base numpad */
    KC_NUM,   KC_P7,    KC_P8,    KC_P9,
    TO(2),    KC_P4,    KC_P5,    KC_P6,
    TO(1),    KC_P1,    KC_P2,    KC_P3,
    TO(0),    KC_DOT,   KC_P0,     KC_EQL
  ),

  [1] = LAYOUT_ortho_4x4( /* Inkscape */
    KC_NUM,    MI_LAYER_UP,    MI_LAYER_VIS,   MI_LAYER_DOWN,
    KC_TRNS,   MI_CLONE,       MI_LAYER_LOCK,  MI_UNCLONE,
    KC_TRNS,   MI_DYN_OUTSET,  MI_SIMPLIFY,    KC_TRNS,
    KC_TRNS,   MI_STITCH_PREV, MI_STITCH_SIM,  MI_SAVE_PES
  ),

  [2] = LAYOUT_ortho_4x4( 
    KC_NUM,    RGB_HUI,    RGB_SAI,    RGB_VAI,
    KC_TRNS,   RGB_HUD,    RGB_SAD,    RGB_VAD,
    KC_TRNS,   RGB_SPI,    KC_TRNS,    KC_TRNS,
    KC_TRNS,   KC_TRNS,    KC_TRNS,    QK_BOOT
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  // Inkscape layer up/down
  case MI_LAYER_UP:
    if (record->event.pressed) {
      // Use X for macro key identifiers
      SEND_STRING(SS_LCTL(SS_TAP(X_PGUP)));
    }
    break;
  case MI_LAYER_DOWN:
    if (record->event.pressed) {
      // Use X for macro key identifiers
      SEND_STRING(SS_LCTL(SS_TAP(X_PGDN)));
    }
    break;
  // Inkscape layer controls

  }
  return true;
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (!clockwise) {
            tap_code_delay(KC_WH_D, 10);
        } else {
            tap_code_delay(KC_WH_U, 10);
        }
    }
    return false;
}
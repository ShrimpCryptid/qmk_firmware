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
    MI_LAYER_UP = SAFE_RANGE, // ctrl + pgup
    MI_LAYER_DOWN,  // ctrl + pgdn
    MI_LAYER_VIS,   // ctrl + alt + pgup
    MI_LAYER_LOCK,  // ctrl + alt + pgdn
    MI_RESET_ZOOM,  // 
    MI_CLONE,       // alt + d
    MI_UNCLONE,     // shift + alt + d
    MI_DYN_OUTSET,  // ctrl + j
    MI_SIMPLIFY,    // ctrl + shift + j
    MI_STITCH_PROP, // ctrl + shift + p
    MI_STITCH_PREV, // ctrl + shift + l
    MI_STITCH_SIM,  // ctrl + alt + shift + l
    MI_SAVE_PES     // ctrl + alt + shift + s > tab > right x18 > enter

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
    KC_P1,     MI_LAYER_UP,    MI_LAYER_VIS,   MI_LAYER_DOWN,
    KC_TRNS,   MI_CLONE,       MI_LAYER_LOCK,  MI_UNCLONE,
    KC_TRNS,   MI_DYN_OUTSET,  MI_SIMPLIFY,    MI_STITCH_PROP,
    KC_TRNS,   MI_STITCH_PREV, MI_STITCH_SIM,  MI_SAVE_PES
  ),

  [2] = LAYOUT_ortho_4x4( 
    KC_NUM,    RGB_HUI,    RGB_SAI,    RGB_VAI,
    KC_TRNS,   RGB_HUD,    RGB_SAD,    RGB_VAD,
    KC_TRNS,   RGB_SPI,    KC_TRNS,    KC_TRNS,
    KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS
  ),
};

void keyboard_post_init_user(void) {
    rgb_matrix_enable_noeeprom();
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_REACTIVE_SIMPLE);
    // rgb_matrix_set_color_all(RGB_OFF);
}

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }

    // Index for indicator keys are:
    // 7
    // 11
    // 15

    uint8_t layer_colors [3][3] = {
      {0x11, 0xA0, 0x10}, // dark green
      {0x09, 0xC0, 0x00}, // light green
      {0xFF, 0x33, 0x03}  // orange
    };
    // Ordered by corresponding layer (0, 1, 2)
    uint8_t indicator_keys [3] = {15, 11, 7};

    const int layer = get_highest_layer(layer_state);

    for (uint8_t i = 0; i < 3; i++) {
        float strength = 0.4;
        if (layer != i) {
          strength = 0.1;
        }

        rgb_matrix_set_color(indicator_keys[i],
            (int) (layer_colors[layer][0] * strength),
            (int) (layer_colors[layer][1] * strength),
            (int) (layer_colors[layer][2] * strength)
        );
    }
    
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {

    // Inkscape layer controls
    case MI_LAYER_UP:
      if (record->event.pressed) {
        // Use X for macro key identifiers
        SEND_STRING(SS_LCTL(SS_TAP(X_PGUP)));
      }
      break;
    case MI_LAYER_DOWN:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL(SS_TAP(X_PGDN)));
      }
      break;
    case MI_LAYER_VIS:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_PGUP))));
      }
      break;
    case MI_LAYER_LOCK:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_PGDN))));
      }
      break;
    
    // Clone + unclone
    case MI_CLONE:
      if (record->event.pressed) {
        SEND_STRING(SS_LALT("d"));
      }
      break;
    case MI_UNCLONE:
      if (record->event.pressed) {
        SEND_STRING(SS_LALT(SS_LSFT("d")));
      }
      break;

    // Add'l commands
    case MI_DYN_OUTSET:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL("j"));
      }
      break;
    case MI_SIMPLIFY:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL(SS_LSFT("j")));
      }
      break;

    //Inkstitch commands
    case MI_STITCH_PREV:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL(SS_LSFT("l")));
      }
      break;
    case MI_STITCH_SIM:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL(SS_LSFT(SS_LALT("l"))));
      }
      break;
    case MI_STITCH_PROP:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL(SS_LSFT("p")));;
      }
      break;
    case MI_SAVE_PES:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL(SS_LSFT(SS_LALT("s"))));
        SEND_STRING(SS_DELAY(500) SS_TAP(X_TAB));
        for (int i = 0; i < 19; i++) {
          SEND_STRING(SS_DELAY(10) SS_TAP(X_RIGHT));
        }
        SEND_STRING(SS_TAP(X_ENTER));
      }
      break;
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
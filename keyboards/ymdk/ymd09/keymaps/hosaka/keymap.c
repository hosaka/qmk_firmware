/*
Copyright 2021 hosaka <hosaka@users.noreply.github.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include QMK_KEYBOARD_H

#include "action_layer.h"
#include "rgblight.h"
#include "rgblight_list.h"

#define LAYER_INDICATOR_RGB 4


enum layer_names {
  _IDE,
  _UNREAL_EDITOR,
  _RGB_EDIT
};

enum custom_keycodes {
  IDE_BUILD = SAFE_RANGE,
  IDE_CONTINUE,
  IDE_DEBUG,
  IDE_STEP_OVER,
  IDE_STEP_IN,
  IDE_STEP_OUT,

  UE_DEPLOY
};


const rgblight_segment_t PROGMEM ide_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {LAYER_INDICATOR_RGB, 1, HSV_RED}
);

const rgblight_segment_t PROGMEM unreal_editor_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {LAYER_INDICATOR_RGB, 1, HSV_GREEN}
);

const rgblight_segment_t PROGMEM rgb_edit_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {LAYER_INDICATOR_RGB, 1, HSV_BLUE}
);

const rgblight_segment_t* const PROGMEM rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    ide_layer,
    unreal_editor_layer,
    rgb_edit_layer
);

// bool led_update_user(led_t led_state) {
//     rgblight_set_layer_state(0, led_state.caps_lock);
//     return true;
// }

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(_IDE, layer_state_cmp(state, _IDE));
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(_UNREAL_EDITOR, layer_state_cmp(state, _UNREAL_EDITOR));
    rgblight_set_layer_state(_RGB_EDIT, layer_state_cmp(state, _RGB_EDIT));
    return state;
}

void keyboard_post_init_user(void) {
    rgblight_layers = rgb_layers;
    layer_state_set_user(layer_state);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case IDE_BUILD:
      if (record->event.pressed) {
        tap_code16(C(A(KC_B)));
      }
      break;
  }
  return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_IDE] = LAYOUT(
    KC_KP_7, KC_KP_8, RESET,
    KC_KP_4, TO(_UNREAL_EDITOR), KC_KP_6,
    IDE_BUILD, KC_KP_2, KC_KP_3),

  [_UNREAL_EDITOR] = LAYOUT(
    KC_KP_7, KC_KP_8, KC_KP_9,
    KC_KP_4, TO(_RGB_EDIT), KC_KP_6,
    KC_KP_1, KC_KP_2, KC_KP_3),

  [_RGB_EDIT] = LAYOUT(
    RGB_RMOD, RGB_VAI, RGB_MOD,
    RGB_HUI, TO(_IDE), RGB_SAI,
    RGB_HUD, RGB_VAD, RGB_SAD),
};

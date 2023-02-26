/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>

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

 /* Custom Layout Skelvir 230226
 * In Windwos, select US default Layout
 * Second Fn Key mapped to Capslock
 * Capslock mapped to Fn + LShift
 * Supporting german Umlaute without the need to use US-INTL keyboard layout:
 * Ä mapped to AltGr+Shift+A or AltGr+Shift+Q
 * ä mapped to AltGr+a or AltGr+q
 * Ö mapped to AltGr+Shift+O or AltGr+Shift+P
 * ö mapped to AltGr+o or AltGr+p
 * Ü mapped to AltGr+Shift+U or AltGr+Shift+Y
 * ü mapped to AltGr+u or AltGr+y
 * ß mapped to AltGr+s
 * Z and Y swapped -> QWERTZ
 * Shift+Backspace mapped to Delete, therefore Ctrl+Shift+Backspace deletes the next word (=Ctrl+Delete)
 *
 *
 * For bootmode hold ESC pressed while plugging in keyboard or Fn+Space, Default Space+B might not work anymore
 *
 *
 */


#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.

#define MODS_SHIFT_MASK (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))

enum custom_keycodes {
  DE_AE_OnA = SAFE_RANGE, // use the safe range, otherwise other keys may be overriden unintentionally
  DE_AE_OnQ,
  DE_OE_OnO,
  DE_OE_OnP,
  DE_UE_OnU,
  DE_UE_OnY,
  DE_SS_OnS,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// base layer
[0] = LAYOUT(
  KC_GESC,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_DEL,
  KC_TAB,   DE_AE_OnQ,     KC_W,     KC_E,     KC_R,     KC_T,     DE_UE_OnY,     DE_UE_OnU,     KC_I,     DE_OE_OnO,     DE_OE_OnP,     KC_LBRC,  KC_RBRC,  KC_BSLS,   KC_PGUP,
  MO(1),  DE_AE_OnA,     DE_SS_OnS,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,            KC_PGDN,
  KC_LSFT,  KC_Y,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_UP,    KC_END,
  KC_LCTL,  KC_LGUI,  KC_LALT,                                KC_SPC,                                 KC_RALT,  MO(1),    KC_LEFT,  KC_DOWN,  KC_RGHT),
// function layer
[1] = LAYOUT(
   KC_GRV,    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,   KC_F10,   KC_F11,   KC_F12,   _______,  KC_INS,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_PSCR,  KC_SCRL,  KC_PAUS,   _______,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,             _______,
  KC_CAPS,  _______,  RGB_HUI,  RGB_HUD,  RGB_SPD,  RGB_SPI,  KC_MUTE,  KC_VOLU,  KC_VOLD,  KC_MPRV,  KC_MPLY,  KC_MNXT,  _______,   RGB_VAI,  KC_HOME,
  _______,  _______,  _______,                                RESET,                                  _______,  _______,  RGB_RMOD,  RGB_VAD,  RGB_MOD),

/* empty template
[2] = LAYOUT(
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,             _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,
  _______,  _______,  _______,                                _______,                                _______,  _______,  _______,   _______,  _______)
  */
};


void tap_key(uint16_t keycode) {
  register_code(keycode);
  unregister_code(keycode);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) 
{
  switch(keycode) 
  {
    // Ä 142, ä 132
    case DE_AE_OnA:
      if (record->event.pressed) {
        uint8_t temp_mod = get_mods();

        if(temp_mod & MOD_BIT(KC_RALT))
        {
          clear_mods();
          register_code(KC_LALT);
          if (temp_mod & MODS_SHIFT_MASK) {
            tap_key(KC_P1); tap_key(KC_P4); tap_key(KC_P2); // Ä
          } else {
            tap_key(KC_P1); tap_key(KC_P3); tap_key(KC_P2); // ä
          }
          unregister_code(KC_LALT);
          set_mods(temp_mod);
        }
        else
        {
          tap_key(KC_A); // default processing A
        }
        return false; // Skip further key processing
        
        
      }
      break;

    case DE_AE_OnQ:
      if (record->event.pressed) {
        uint8_t temp_mod = get_mods();

        if(temp_mod & MOD_BIT(KC_RALT))
        {
          clear_mods();
          register_code(KC_LALT);
          if (temp_mod & MODS_SHIFT_MASK) {
            tap_key(KC_P1); tap_key(KC_P4); tap_key(KC_P2); // Ä
          } else {
            tap_key(KC_P1); tap_key(KC_P3); tap_key(KC_P2); // ä
          }
          unregister_code(KC_LALT);
          set_mods(temp_mod);
        }
        else
        {
          tap_key(KC_Q); // default processing Q
        }
        return false; // Skip further key processing
        
        
      }
      break;

    // Ö 153, ö 148
    case DE_OE_OnO:
      if (record->event.pressed) {
        uint8_t temp_mod = get_mods();

        if(temp_mod & MOD_BIT(KC_RALT))
        {
          clear_mods();
          register_code(KC_LALT);
          if (temp_mod & MODS_SHIFT_MASK) {
            tap_key(KC_P1); tap_key(KC_P5); tap_key(KC_P3); // Ö
          } else {
            tap_key(KC_P1); tap_key(KC_P4); tap_key(KC_P8); // ö
          }
          unregister_code(KC_LALT);
          set_mods(temp_mod);
        }
        else
        {
          tap_key(KC_O); // default processing O
        }

        return false; // Skip further key processing
        
        
      }
      break;

    case DE_OE_OnP:
      if (record->event.pressed) {
        uint8_t temp_mod = get_mods();

        if(temp_mod & MOD_BIT(KC_RALT))
        {
          clear_mods();
          register_code(KC_LALT);
          if (temp_mod & MODS_SHIFT_MASK) {
            tap_key(KC_P1); tap_key(KC_P5); tap_key(KC_P3); // Ö
          } else {
            tap_key(KC_P1); tap_key(KC_P4); tap_key(KC_P8); // ö
          }
          unregister_code(KC_LALT);
          set_mods(temp_mod);
        }
        else
        {
          tap_key(KC_P); // default processing P
        }

        return false; // Skip further key processing
        
        
      }
      break;


    // Ü 154, ü 129
    case DE_UE_OnU:
      if (record->event.pressed) {
        uint8_t temp_mod = get_mods();

        if(temp_mod & MOD_BIT(KC_RALT))
        {
          clear_mods();
          register_code(KC_LALT);
          if (temp_mod & MODS_SHIFT_MASK) {
            tap_key(KC_P1); tap_key(KC_P5); tap_key(KC_P4); // Ü
          } else {
            tap_key(KC_P1); tap_key(KC_P2); tap_key(KC_P9); // ü
          }
          unregister_code(KC_LALT);
          set_mods(temp_mod);
        }
        else
        {
          tap_key(KC_U); // default processing U
        }

        return false; // Skip further key processing
        
        
      }
      break;

    case DE_UE_OnY:
      if (record->event.pressed) {
        uint8_t temp_mod = get_mods();

        if(temp_mod & MOD_BIT(KC_RALT))
        {
          clear_mods();
          register_code(KC_LALT);
          if (temp_mod & MODS_SHIFT_MASK) {
            tap_key(KC_P1); tap_key(KC_P5); tap_key(KC_P4); // Ü
          } else {
            tap_key(KC_P1); tap_key(KC_P2); tap_key(KC_P9); // ü
          }
          unregister_code(KC_LALT);
          set_mods(temp_mod);
        }
        else
        {
          tap_key(KC_Z); // default processing Z -> swapped instead of Y
        }

        return false; // Skip further key processing
        
        
      }
      break;



    // ß 225
    case DE_SS_OnS:
      if (record->event.pressed) {
        uint8_t temp_mod = get_mods();

        if(temp_mod & MOD_BIT(KC_RALT))
        {
          clear_mods();
          register_code(KC_LALT);
          tap_key(KC_P2); tap_key(KC_P2); tap_key(KC_P5); // ß
          unregister_code(KC_LALT);
          set_mods(temp_mod);
        }
        else
        {
          tap_key(KC_S); // default processing S
        }

        return false; // Skip further key processing
        
        
      }
      break;

      // Shift + Backspace delete, see https://docs.qmk.fm/#/feature_advanced_keycodes?id=checking-modifier-state
      case KC_BSPC:
      {
      
        uint8_t temp_mod = get_mods();
        // Initialize a boolean variable that keeps track
        // of the delete key status: registered or not?
        static bool delkey_registered;
        if (record->event.pressed) {
            // Detect the activation of either shift keys
            if (temp_mod & MOD_MASK_SHIFT) {
                // First temporarily canceling both shifts so that
                // shift isn't applied to the KC_DEL keycode
                del_mods(MOD_MASK_SHIFT);
                register_code(KC_DEL);
                // Update the boolean variable to reflect the status of KC_DEL
                delkey_registered = true;
                // Reapplying modifier state so that the held shift key(s)
                // still work even after having tapped the Backspace/Delete key.
                set_mods(temp_mod);
                return false;
            }
        } 
        else 
        { 
            // on release of KC_BSPC
            // In case KC_DEL is still being sent even after the release of KC_BSPC
            if (delkey_registered) {
                unregister_code(KC_DEL);
                delkey_registered = false;
                return false;
            }
        }
        break;
      }

  }




  return true;
}
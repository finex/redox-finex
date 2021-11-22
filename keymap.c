#include QMK_KEYBOARD_H

// Layer names
enum{
  _COLEMAKDH, // Base Colemak Mod-DH
  _SYMB, // Symbols
  _NUMB, // Numbers
  _FUNC, // Functions keys
  _AWES, // AwesomeWM
  _MOUS, // Mouse
  _ADJUST // Adjust
};

// Custom keycodes
enum custom_keycodes {
  COLEMAKDH = SAFE_RANGE,
  ASC_SAR,
  ASC_DAR,
  ASC_SQT,
  ASC_DQT,
  ASC_CIRC,
  ASC_TILD,
  ASC_HAP,
  ASC_SAD,
  ASC_BKT,
  ASC_CBRL,
  ASC_CBRR,
  ASC_LAN,
  ASC_RAN
};

// Tap dance statuses
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

// Tap dance enums
enum {
  TD_DEL, // single: KC_DEL; hold: LGUI; double hold: _MOUSE
  TD_SCL, // single: `;`   ; double: `:`
  TD_LBR, // single: `[`   ; double: `{`
  TD_RBR  // single: `]`   ; double: `}`
};

td_state_t cur_dance(qk_tap_dance_state_t *state);

// For the tap dances. Put it here so it can be used in any keymap
void del_finished(qk_tap_dance_state_t *state, void *user_data);
void del_reset(qk_tap_dance_state_t *state, void *user_data);

void scl_finished(qk_tap_dance_state_t *state, void *user_data);
void scl_reset(qk_tap_dance_state_t *state, void *user_data);

void lbr_finished(qk_tap_dance_state_t *state, void *user_data);
void lbr_reset(qk_tap_dance_state_t *state, void *user_data);

void rbr_finished(qk_tap_dance_state_t *state, void *user_data);
void rbr_reset(qk_tap_dance_state_t *state, void *user_data);


// Shortcuts to make keymap more readable
// - Adjustment Layer:
#define KC_ADEN LT(_ADJUST, KC_END)   // End / _ADJUST layer
#define KC_ADPU LT(_ADJUST, KC_PGUP)  // Page Up / _ADJUST layer
// - Custom home row layers:
#define KC_N_SH RSFT_T(KC_N)       // N key or right SHIFT
#define KC_T_SH LSFT_T(KC_T)       // T key or left SHIFT
// - Other keys/modifiers:
#define KC_ATAB RALT_T(KC_TAB)        // Tab / Alt Gr
#define KC_CESC LCTL_T(KC_ESC)        // Esc / Left Ctrl
#define KC_GUSP RGUI_T(KC_SPC)        // Space / Right Gui
#define KC_AEQL LALT_T(KC_EQL)        // Equals / Left Alt
#define KC_CMIN RCTL_T(KC_MINUS)      // Minus / Right Ctrl
#define KC_NUES LT(_NUMB, KC_ESC)     // Esc / _numbers
#define KC_CBSP LCTL_T(KC_BSPC)       // Backspace / Left Ctrl
#define KC_GUDE LGUI_T(KC_DEL)        // Del / Left Gui
#define KC_SYSP LT(_SYMB, KC_SPC)     // Space / _symbols
#define KC_AWEN LT(_AWES, KC_ENT)     // Enter / AwesomeWM
#define KC_FUTA LT(_FUNC, KC_TAB)     // Tab / _functions
#define KC_MODE LT(_MOUS, KC_DEL)     // Del / _mouse
#define KC_GU_A LGUI_T(KC_A)          // A / Left Gui
#define KC_CT_S LCTL_T(KC_S)          // R / Left Ctrl
#define KC_AL_R LALT_T(KC_R)          // S / Left Alt
#define KC_GU_O RGUI_T(KC_O)          // O / Right Gui
#define KC_AL_I LALT_T(KC_I)          // E / Left Alt (left alt because used as Emacs M- )
#define KC_CT_E RCTL_T(KC_E)          // I / Right Ctrl
#define KC_RAEN RALT_T(KC_ENT)        // Enter / Right Alt
// Tap dance keys:
#define KC_TDSC TD(TD_SCLN)           // ;; -> :
#define KC_TDLB TD(TD_LBRC)           // [[ -> {
#define KC_TDRB TD(TD_RBRC)           // ]] -> }
/* #define KC_SLQM TD(TD_SLQM)           // // -> ? */
#define TG_NUM TG(_NUMB)

// Awesome WM macros
#define KC_AW1 LGUI(KC_1)
#define KC_AW2 LGUI(KC_2)
#define KC_AW3 LGUI(KC_3)
#define KC_AW4 LGUI(KC_4)
#define KC_AW5 LGUI(KC_5)
#define KC_AW6 LGUI(KC_6)
#define KC_AW7 LGUI(KC_7)
#define KC_AW8 LGUI(KC_8)
#define KC_AW9 LGUI(KC_9)


// Clipboard, Undo/Redo and "select all"
#define U_PST S(KC_INS)
#define U_CPY C(KC_INS)
#define U_CUT S(KC_DEL)
#define U_UND KC_UNDO
#define U_RDO KC_AGIN
#define U_ALL C(KC_A) // Emacs need to rebind mark-whole-buffer to: C-a

// Send custom strings or change default base layer
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch(keycode) {
      case ASC_SAR:
        SEND_STRING("->");
        return false;
      case ASC_DAR:
        SEND_STRING("=>");
        return false;
      case ASC_SQT:
        // SS_RALT(): Avoid sending dead key on software intl layouts
        SEND_STRING(SS_RALT("'"));
        return false;
      case ASC_DQT:
        // SS_RALT(SS_LSFT()): Avoid sending dead key on software intl layouts
        SEND_STRING(SS_RALT(SS_LSFT("\"")));
        return false;
      case ASC_CIRC:
        // SS_RALT(): Avoid sending dead key on software intl layouts
        SEND_STRING(SS_RALT("^"));
        return false;
      case ASC_TILD:
        // SS_RALT(SS_LSFT()): Avoid sending dead key on software intl layouts
        SEND_STRING(SS_RALT(SS_LSFT("~")));
        return false;
      case ASC_HAP:
        SEND_STRING(":-) ");
        return false;
      case ASC_SAD:
        SEND_STRING(":-( ");
        return false;
      case ASC_BKT:
        // SS_RALT(): Avoid sending dead key on software intl layouts
        SEND_STRING(SS_RALT("`"));
        return false;
      case ASC_CBRL:
        SEND_STRING("{");
        return false;
      case ASC_CBRR:
        SEND_STRING("}");
        return false;
      case ASC_LAN:
        SEND_STRING(SS_RALT("["));
        return false;
      case ASC_RAN:
        SEND_STRING(SS_RALT("]"));
        return false;
      case COLEMAKDH:
        if (record->event.pressed) {
          set_single_persistent_default_layer(_COLEMAKDH);
        }
        return false;
        break;
    }
  }
  return true;
};

// Fine tuning of TAPPING_TERM valuer on some home row modifiers to avoid errors during typing.
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  // Ring fingers
  case KC_AL_I:
  case KC_AL_R:
    return TAPPING_TERM + 200;
  // Pinkies
  case KC_GU_O:
  case KC_GU_A:
    return TAPPING_TERM + 50;
  // Middle fingers
  case KC_CT_S:
  case KC_CT_E:
    return TAPPING_TERM - 30;
  // Right thumb for "symbols" layer
  case KC_SYSP:
    return TAPPING_TERM - 50;
  default:
    return TAPPING_TERM;
  }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // Colemak Mod-DH
  [_COLEMAKDH] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
       KC_ESC  ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,                                            KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,KC_BSPC ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       KC_ATAB ,KC_Q    ,KC_W    ,KC_F    ,KC_P    ,KC_B    ,KC_PSCR ,                          KC_DEL  ,KC_J    ,KC_L    ,KC_U    ,KC_Y    ,TD_SCL  ,KC_AEQL ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       KC_CESC ,KC_GU_A ,KC_AL_R ,KC_CT_S ,KC_T_SH ,KC_G    ,TD_LBR  ,                          TD_RBR  ,KC_M    ,KC_N_SH ,KC_CT_E ,KC_AL_I ,KC_GU_O ,KC_CMIN ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       KC_LSPO ,KC_Z    ,KC_X    ,KC_C    ,KC_D    ,KC_V    ,KC_ADPU ,KC_PGDN ,        KC_HOME ,KC_ADEN ,KC_K    ,KC_H    ,KC_COMM ,KC_DOT  ,KC_SLSH ,KC_RSPC ,
    //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
       KC_GUSP ,KC_HYPR ,TG_NUM  ,KC_RAEN ,     KC_NUES ,    KC_CBSP ,TD_DEL  ,        KC_AWEN ,KC_SYSP ,    KC_FUTA ,     KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT
    //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  // Symbols, home row arrows, function keys and macros layer
  [_SYMB] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
       _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       _______ ,KC_EXLM ,KC_AT   ,KC_HASH ,KC_DLR  ,KC_PERC ,_______ ,                          _______ ,ASC_CIRC,KC_AMPR ,KC_ASTR ,KC_PLUS ,_______ ,_______ ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       _______ ,KC_PIPE ,KC_PMNS ,ASC_SQT ,ASC_DQT ,KC_GRV  ,ASC_SAR ,                          ASC_DAR ,KC_QUOT ,KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT ,_______ ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       _______ ,KC_BSLS ,KC_UNDS ,KC_COLN ,ASC_TILD,KC_EQL  ,ASC_SAD ,ASC_HAP ,        _______ ,_______ ,ASC_BKT ,KC_HOME ,KC_PGDN ,KC_PGUP ,KC_END  ,_______ ,
    //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
       _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,_______ ,        _______ ,_______ ,    _______ ,     _______ ,_______ ,_______ ,_______
    //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  // Numeric keypad layer
  [_NUMB] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
       _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       _______ ,_______ ,KC_UP   ,_______ ,KC_NLCK ,KC_CAPS ,_______ ,                          _______ ,KC_PENT ,KC_KP_7 ,KC_KP_8 ,KC_KP_9 ,KC_PPLS ,KC_PEQL ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       _______ ,KC_LEFT ,KC_DOWN ,KC_RIGHT,U_ALL   ,KC_INS  ,_______ ,                          _______ ,KC_COMM ,KC_KP_4 ,KC_KP_5 ,KC_KP_6 ,KC_PAST ,KC_PMNS ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       _______ ,U_UND   ,U_CUT   ,U_CPY   ,U_PST   ,U_RDO   ,_______ ,_______ ,        _______ ,_______ ,S(KC_9) ,KC_KP_1 ,KC_KP_2 ,KC_KP_3 ,KC_PSLS ,S(KC_0) ,
    //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
       _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,_______ ,        KC_PENT ,KC_KP_0 ,    KC_PDOT ,     KC_KP_0 ,KC_PDOT ,XXXXXXX ,XXXXXXX
    //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  // Function layer and some extra keys on right hand
  [_FUNC] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
       _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       _______ ,_______ ,KC_UP   ,_______ ,KC_NLCK ,KC_CAPS ,_______ ,                          _______ ,XXXXXXX ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F12  ,_______ ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       _______ ,KC_LEFT ,KC_DOWN ,KC_RIGHT,U_ALL   ,KC_INS  ,_______ ,                          _______ ,XXXXXXX ,KC_F4   ,KC_F5   ,KC_F6   ,KC_F11  ,_______ ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       _______ ,U_UND   ,U_CUT   ,U_CPY   ,U_PST   ,U_RDO   ,_______ ,_______ ,        _______ ,_______ ,XXXXXXX ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F10  ,_______ ,
    //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
       _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,_______ ,        _______ ,_______ ,    _______ ,     _______ ,_______ ,_______ ,_______
    //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  // AwesomeWM
  [_AWES] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
       _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       _______ ,_______ ,KC_UP   ,_______ ,KC_NLCK ,KC_CAPS ,_______ ,                          _______ ,_______ ,KC_AW7  ,KC_AW8  ,KC_AW9  ,_______ ,_______ ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       _______ ,KC_LEFT ,KC_DOWN ,KC_RIGHT,U_ALL   ,KC_INS  ,_______ ,                          _______ ,_______ ,KC_AW4  ,KC_AW5  ,KC_AW6  ,_______ ,_______ ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       _______ ,U_UND   ,U_CUT   ,U_CPY   ,U_PST   ,U_RDO   ,_______ ,_______ ,        _______ ,_______ ,_______ ,KC_AW1  ,KC_AW2  ,KC_AW3  ,_______ ,_______ ,
    //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
       _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,_______ ,        _______ ,_______ ,    _______ ,     _______ ,_______ ,_______ ,_______
    //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  // Mouse
  [_MOUS] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
       _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       _______ ,U_UND   ,U_CUT   ,U_CPY   ,U_PST   ,U_RDO   ,_______ ,                          _______ ,U_RDO   ,U_PST   ,U_CPY   ,U_CUT   ,U_UND   ,_______ ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                          _______ ,_______ ,KC_MS_L ,KC_MS_D ,KC_MS_U ,KC_MS_R ,_______ ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,        _______ ,_______ ,_______ ,KC_WH_L ,KC_WH_D ,KC_WH_U ,KC_WH_R ,_______ ,
    //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
       _______ ,_______ ,_______ ,XXXXXXX ,     _______ ,    _______ ,_______ ,        KC_BTN1 ,KC_BTN3 ,    KC_BTN2 ,     _______ ,_______ ,_______ ,_______
    //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  // Adjust layer (RGB, Reset and base layer switch)
  [_ADJUST] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
       XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                                            XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       XXXXXXX ,RESET   ,RGB_M_P ,RGB_TOG ,RGB_MOD ,RGB_HUD ,XXXXXXX ,                          XXXXXXX ,RGB_SAI ,RGB_VAD ,RGB_VAI ,RGB_SAD ,RGB_M_SW,XXXXXXX ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,RGB_M_SN,XXXXXXX ,                          XXXXXXX ,RGB_M_R ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       XXXXXXX ,RGB_M_B ,RGB_M_K ,RGB_M_X ,RGB_M_G ,RGB_HUI ,_______ ,XXXXXXX ,        XXXXXXX ,_______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
    //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
       XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,     XXXXXXX ,    XXXXXXX ,XXXXXXX ,        XXXXXXX ,XXXXXXX ,    XXXXXXX ,     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX
    //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  )

};



/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'TD_DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
        else return TD_TRIPLE_HOLD;
    } else return TD_UNKNOWN;
}


// Tap dance DEL/GUI/MOUSE
// Create an instance of 'td_tap_t' for the 'del' tap dance.
static td_tap_t deltap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
void del_finished(qk_tap_dance_state_t *state, void *user_data) {
    deltap_state.state = cur_dance(state);
    switch (deltap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_DEL); break;
        case TD_SINGLE_HOLD: register_code(KC_LGUI); break;
        case TD_DOUBLE_TAP: register_code(KC_DEL); break;
        case TD_DOUBLE_HOLD: layer_on(_MOUS); break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_DEL); register_code(KC_DEL);
    }
}
void del_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (deltap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_DEL); break;
        case TD_SINGLE_HOLD: unregister_code(KC_LGUI); break;
        case TD_DOUBLE_TAP: unregister_code(KC_DEL); break;
        case TD_DOUBLE_HOLD: layer_off(_MOUS);
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_DEL);
    }
    deltap_state.state = TD_NONE;
}



// Tap dance SEMICOLON/COLON
// Create an instance of 'td_tap_t' for the 'scl' tap dance.
static td_tap_t scltap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
void scl_finished(qk_tap_dance_state_t *state, void *user_data) {
    scltap_state.state = cur_dance(state);
    switch (scltap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_SCLN); break;
        case TD_SINGLE_HOLD: register_code(KC_SCLN); break;
        case TD_DOUBLE_TAP: register_code (KC_COLN); break;
        case TD_DOUBLE_HOLD: register_code(KC_SCLN); break;
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_SCLN); register_code(KC_SCLN);
    }
}

void scl_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (scltap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_SCL); break;
        case TD_SINGLE_HOLD: unregister_code(KC_LGUI); break;
        case TD_DOUBLE_TAP: unregister_code (KC_COLN); break;
        case TD_DOUBLE_HOLD: unregister_code (KC_COLN);
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_DEL);
    }
    scltap_state.state = TD_NONE;
}


// Tap dance LEFT BRACKET/LEFT CURLY BRACE
// Create an instance of 'td_tap_t' for the 'lbr' tap dance.
static td_tap_t lbrtap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
void lbr_finished(qk_tap_dance_state_t *state, void *user_data) {
    lbrtap_state.state = cur_dance(state);
    switch (lbrtap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_LBRC); break;
        case TD_SINGLE_HOLD: register_code(KC_LBRC); break;
        case TD_DOUBLE_TAP: register_code (KC_LCBR); break;
        case TD_DOUBLE_HOLD: register_code(KC_LBRC); break;
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_LBRC); register_code(KC_LBRC);
    }
}

void lbr_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (lbrtap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_LBRC); break;
        case TD_SINGLE_HOLD: unregister_code(KC_LBRC); break;
        case TD_DOUBLE_TAP: unregister_code (KC_LCBR); break;
        case TD_DOUBLE_HOLD: unregister_code (KC_LBRC);
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_LBRC);
    }
    lbrtap_state.state = TD_NONE;
}



// Tap dance RIGHT BRACKET/RIGHT CURLY BRACE
// Create an instance of 'td_tap_t' for the 'rbr' tap dance.
static td_tap_t rbrtap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
void rbr_finished(qk_tap_dance_state_t *state, void *user_data) {
    rbrtap_state.state = cur_dance(state);
    switch (rbrtap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_RBRC); break;
        case TD_SINGLE_HOLD: register_code(KC_RBRC); break;
        case TD_DOUBLE_TAP: register_code (KC_RCBR); break;
        case TD_DOUBLE_HOLD: register_code(KC_RBRC); break;
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_RBRC); register_code(KC_RBRC);
    }
}

void rbr_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (rbrtap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_RBRC); break;
        case TD_SINGLE_HOLD: unregister_code(KC_RBRC); break;
        case TD_DOUBLE_TAP: unregister_code (KC_RCBR); break;
        case TD_DOUBLE_HOLD: unregister_code (KC_RBRC);
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_RBRC);
    }
    rbrtap_state.state = TD_NONE;
}


qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_DEL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, del_finished, del_reset),
    [TD_SCL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, scl_finished, scl_reset),
    [TD_LBR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lbr_finished, lbr_reset),
    [TD_RBR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rbr_finished, rbr_reset)
};

#include QMK_KEYBOARD_H

// Layer names
enum{
  _COLEMAKDH, // Base Colemak Mod-DH
  _BUTT,
  _MEDI,
  _NAVI,
  _MOUS,
  _SYMB,
  _NUMB,
  _FUNC,
  _ADJUST
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

// Tap dance keycodes
enum tap_dance{
  TD_SCLN, // ;; -> :
  TD_LBRC, // [[ -> {
  TD_RBRC  // ]] -> }
};

// Semicolon to Colon
void dance_scln_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code (KC_SCLN);
  } else {
    register_code (KC_RSFT);
    register_code (KC_SCLN);
  }
}
void dance_scln_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_SCLN);
  } else {
    unregister_code (KC_RSFT);
    unregister_code (KC_SCLN);
  }
}

// Square braket to curly bracket (left)
void dance_lbrc_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code (KC_LBRC);
  } else {
    register_code (KC_RSFT);
    register_code (KC_LBRC);
  }
}
void dance_lbrc_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_LBRC);
  } else {
    unregister_code (KC_RSFT);
    unregister_code (KC_LBRC);
  }
}

// Square braket to curly bracket (right)
void dance_rbrc_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code (KC_RBRC);
  } else {
    register_code (KC_RSFT);
    register_code (KC_RBRC);
  }
}
void dance_rbrc_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_RBRC);
  } else {
    unregister_code (KC_RSFT);
    unregister_code (KC_RBRC);
  }
}


//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_SCLN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_scln_finished, dance_scln_reset),
  [TD_LBRC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_lbrc_finished, dance_lbrc_reset),
  [TD_RBRC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_rbrc_finished, dance_rbrc_reset),
};



// Layers
// - Toggle
#define TG_NUMB TG(_NUMB)
#define TG_BUTT TG(_BUTT)
// - Layer / Tap
#define LT_ADEN LT(_ADJUST, KC_END)
#define LT_ADPU LT(_ADJUST, KC_PGUP)
#define LT_MEES LT(_MEDI, KC_ESC)
#define LT_NASP LT(_NAVI, KC_SPACE)
#define LT_MOTA LT(_MOUS, KC_TAB)
#define LT_SYEN LT(_SYMB, KC_ENTER)
#define LT_NUBS LT(_NUMB, KC_BSPACE)
#define LT_FUDE LT(_FUNC, KC_DEL)

// Clipboard keys
#define U_RDO KC_AGIN
#define U_PST S(KC_INS)
#define U_CPY C(KC_INS)
#define U_CUT S(KC_DEL)
#define U_UND KC_UNDO

// Home row mod tap
// - Left
#define QHGA LGUI_T(KC_A)
#define QHAR LALT_T(KC_R)
#define QHCS LCTL_T(KC_S)
#define QHST LSFT_T(KC_T)
#define QHLX RALT_T(KC_X)
// - Right
#define QHGO LGUI_T(KC_O)
#define QHAI LALT_T(KC_I)
#define QHCE RCTL_T(KC_E)
#define QHSN LSFT_T(KC_N)
#define QHLD RALT_T(KC_DOT)

// Mod tap
#define HYP_PRS HYPR_T(KC_PSCR)


#define KC_AW1 LGUI(KC_1)
#define KC_AW2 LGUI(KC_2)
#define KC_AW3 LGUI(KC_3)
#define KC_AW4 LGUI(KC_4)
#define KC_AW5 LGUI(KC_5)
#define KC_AW6 LGUI(KC_6)
#define KC_AW7 LGUI(KC_7)
#define KC_AW8 LGUI(KC_8)
#define KC_AW9 LGUI(KC_9)

// Tap dance keys:
#define KC_TDSC TD(TD_SCLN)           // ;; -> :
#define KC_TDLB TD(TD_LBRC)           // [[ -> {
#define KC_TDRB TD(TD_RBRC)           // ]] -> }


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

/* // Fine tuning of TAPPING_TERM valuer on some home row modifiers to avoid errors during typing. */
/* uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) { */
/*   switch (keycode) { */
/*   // Ring fingers */
/*   case QHAI: */
/*   case QHAR: */
/*     return TAPPING_TERM + 200; */
/*   // Pinkies */
/*   case QHGO: */
/*   case QHGA: */
/*     return TAPPING_TERM + 50; */
/*   // Middle fingers */
/*   case QHCS: */
/*   case QHCE: */
/*     return TAPPING_TERM - 30; */
/*   // Right thumb for "symbols" layer */
/*   case LT_NUBS: */
/*     return TAPPING_TERM - 50; */
/*   default: */
/*     return TAPPING_TERM; */
/*   } */
/* } */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // Colemak Mod-DH
  [_COLEMAKDH] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
       KC_ESC  ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,                                            KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,KC_ESC  ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       TG_BUTT ,KC_Q    ,KC_W    ,KC_F    ,KC_P    ,KC_B    ,XXXXXXX ,                          XXXXXXX ,KC_J    ,KC_L    ,KC_U    ,KC_Y    ,KC_TDSC ,TG_NUMB ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       KC_GRV  ,QHGA    ,QHAR    ,QHCS    ,QHST    ,KC_G    ,KC_TDLB ,                          KC_TDRB ,KC_M    ,QHSN    ,QHCE    ,QHAI    ,QHGO    ,KC_QUOT ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       KC_LSPO ,KC_Z    ,QHLX    ,KC_C    ,KC_D    ,KC_V    ,LT_ADPU ,KC_PGDN ,        KC_HOME ,LT_ADEN ,KC_K    ,KC_H    ,KC_COMM ,QHLD    ,KC_SLSH ,KC_RSPC ,
    //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
       XXXXXXX ,XXXXXXX ,HYP_PRS ,KC_ENT  ,     LT_MEES ,    LT_NASP ,LT_MOTA ,        LT_SYEN , LT_NUBS,    LT_FUDE ,     KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT
    //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  // Symbols and macros layer
  [_SYMB] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
       _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                                            XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       _______ ,KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR ,XXXXXXX ,                          XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       XXXXXXX ,KC_COLN, KC_DLR  ,KC_PERC ,ASC_CIRC,KC_PLUS ,ASC_SAR ,                          ASC_DAR ,XXXXXXX ,KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI ,XXXXXXX ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       XXXXXXX ,ASC_TILD, KC_EXLM ,KC_AT  ,KC_HASH ,KC_PIPE ,ASC_SAD ,ASC_HAP ,        XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
    //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
       XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,     KC_LPRN ,    KC_RPRN ,KC_UNDS ,        XXXXXXX ,XXXXXXX ,    XXXXXXX ,     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX
    //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  // Numeric layer
  [_NUMB] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
       _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                                            XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       _______ ,KC_LBRC ,KC_7    ,KC_8    ,KC_9    ,KC_RBRC ,XXXXXXX ,                          XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       XXXXXXX ,KC_SCLN ,KC_4    ,KC_5    ,KC_6    ,KC_EQL  ,XXXXXXX ,                          XXXXXXX ,XXXXXXX ,KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI ,XXXXXXX ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       XXXXXXX ,ASC_DQT ,KC_1    ,KC_2    ,KC_3    ,KC_BSLS ,XXXXXXX ,XXXXXXX ,        XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
    //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
       XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,     KC_DOT  ,    KC_0    ,KC_MINS ,        XXXXXXX ,XXXXXXX ,    XXXXXXX ,     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX
    //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  // Function layer
  [_FUNC] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
       _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                                            XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       _______ ,KC_F12  ,KC_F7   ,KC_F8   ,KC_F9   ,XXXXXXX ,XXXXXXX ,                          XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       XXXXXXX ,KC_F11  ,KC_F4   ,KC_F5   ,KC_F6   ,KC_CAPS ,XXXXXXX ,                          XXXXXXX ,XXXXXXX ,KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI ,XXXXXXX ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       XXXXXXX ,KC_F10  ,KC_F1   ,KC_F2   ,KC_F3   ,KC_INS  ,XXXXXXX ,XXXXXXX ,        XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,KC_ALGR ,XXXXXXX ,XXXXXXX ,
    //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
       XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,     KC_APP  ,    KC_SPC  , KC_TAB ,        XXXXXXX ,XXXXXXX ,    XXXXXXX ,     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX
    //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),


  // Navigation layer
  [_NAVI] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
       _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                                            XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                          XXXXXXX ,U_RDO   ,U_PST   ,U_CPY   ,U_CUT   ,U_UND   ,_______ ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       XXXXXXX ,KC_LGUI, KC_LALT ,KC_LCTL ,KC_LSFT ,XXXXXXX ,XXXXXXX ,                          XXXXXXX ,XXXXXXX ,KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT ,XXXXXXX ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       XXXXXXX ,XXXXXXX ,KC_ALGR ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,        XXXXXXX ,XXXXXXX ,XXXXXXX ,KC_HOME ,KC_PGDN ,KC_PGUP ,KC_END  ,XXXXXXX ,
    //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
       XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,     XXXXXXX ,    XXXXXXX ,XXXXXXX ,        KC_ENT  ,KC_BSPC ,    KC_DEL  ,     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX
    //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),


  // Mouse layer
  [_MOUS] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
       _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                                            XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                          XXXXXXX ,U_RDO   ,U_PST   ,U_CPY   ,U_CUT   ,U_UND   ,_______ ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       XXXXXXX ,KC_LGUI, KC_LALT ,KC_LCTL ,KC_LSFT ,XXXXXXX ,XXXXXXX ,                          XXXXXXX ,XXXXXXX ,KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R ,XXXXXXX ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       XXXXXXX ,XXXXXXX ,KC_ALGR ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,        XXXXXXX ,XXXXXXX ,XXXXXXX ,KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R ,XXXXXXX ,
    //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
       XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,     XXXXXXX ,    XXXXXXX ,XXXXXXX ,        KC_BTN1 ,KC_BTN3 ,    KC_BTN2 ,     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX
    //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  // Media layer
  [_MEDI] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
       _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                                            XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       _______ ,XXXXXXX ,KC_AW7  ,KC_AW8  ,KC_AW9  ,XXXXXXX ,XXXXXXX ,                          XXXXXXX ,U_RDO   ,U_PST   ,U_CPY   ,U_CUT   ,U_UND   ,_______ ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       XXXXXXX ,XXXXXXX ,KC_AW4  ,KC_AW5  ,KC_AW6  ,XXXXXXX ,XXXXXXX ,                          XXXXXXX ,KC_MPRV ,KC_VOLD ,KC_VOLU ,KC_MNXT ,XXXXXXX ,XXXXXXX ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       XXXXXXX ,XXXXXXX ,KC_AW1  ,KC_AW2  ,KC_AW3  ,XXXXXXX ,XXXXXXX ,XXXXXXX ,        XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
    //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
       XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,     XXXXXXX ,    XXXXXXX ,XXXXXXX ,        KC_MSTP ,KC_MPLY,     KC_MUTE ,     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX
    //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),



  // Buttons layer
  [_BUTT] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
       _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                                            XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       _______ ,U_UND   ,U_CUT   ,U_CPY   ,U_PST   ,U_RDO   ,XXXXXXX ,                          XXXXXXX ,U_RDO   ,U_PST   ,U_CPY   ,U_CUT   ,U_UND   ,_______ ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       XXXXXXX ,KC_LGUI ,KC_LALT ,KC_LCTL ,KC_LSFT ,XXXXXXX ,XXXXXXX ,                          XXXXXXX ,XXXXXXX ,KC_RSFT ,KC_RCTL ,KC_LALT, KC_RGUI ,XXXXXXX ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       XXXXXXX ,U_UND   ,U_CUT   ,U_CPY   ,U_PST   ,U_RDO   ,XXXXXXX ,XXXXXXX ,        XXXXXXX ,XXXXXXX ,U_RDO   ,U_PST   ,U_CPY   ,U_CUT   ,U_UND   ,XXXXXXX ,
    //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
       XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,     KC_BTN2 ,    KC_BTN3 ,KC_BTN1 ,        KC_BTN1 ,KC_BTN3 ,    KC_BTN2  ,     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX
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

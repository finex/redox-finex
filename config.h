/*
Copyright 2018 Leonardo (FiNeX) Finetti <finex@finex.org>

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

#pragma once

/* Use I2C or Serial, not both */
#define USE_SERIAL

/* Select hand configuration */
#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

/* RGB Settings */
#undef RGBLED_NUM
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 14
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8

/* #define RETRO_TAPPING */
/* #define RETRO_SHIFT */
/* #define PERMISSIVE_HOLD */



/* Fine tuning */
// - Reduce errors on fast typing
#define IGNORE_MOD_TAP_INTERRUPT
// - Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
// #define TAPPING_FORCE_HOLD
// - enable TAPPING_FORCE_HOLD only on single keys (home row mods) in order to allow auto-repeat on all other keys (like backspace or space).
#define TAPPING_FORCE_HOLD_PER_KEY
// - Recommended for heavy chording
#define QMK_KEYS_PER_SCAN 4
// - Custom tapping term
#define TAPPING_TERM 200
#define TAPPING_TERM_PER_KEY


/* // - Mouse tuning */
/* #undef MOUSEKEY_DELAY */
/* #define MOUSEKEY_DELAY          0 */
/* #undef MOUSEKEY_SCROLL_DELAY */
/* #define MOUSEKEY_SCROLL_DELAY   100 */
/* #undef MOUSEKEY_INTERVAL */
/* #define MOUSEKEY_INTERVAL       16 */
/* #undef MOUSEKEY_WHEEL_DELAY */
/* #define MOUSEKEY_WHEEL_DELAY    0 */
/* #undef MOUSEKEY_MAX_SPEED */
/* #define MOUSEKEY_MAX_SPEED      6 */
/* #undef MOUSEKEY_TIME_TO_MAX */
/* #define MOUSEKEY_TIME_TO_MAX    64 */

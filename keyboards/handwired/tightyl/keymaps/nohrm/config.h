#pragma once
#define EE_HANDS
// #define MASTER_RIGHT
//#define MASTER_LEFT

// Configure the global tapping term (default: 200ms)
#define TAPPING_TERM 300 // was 220 (180 too low)
// #define TAPPING_TERM_PER_KEY

// #define COMBO_COUNT 3
// #define COMBO_TERM 120
// Prevent normal rollover on alphas from accidentally triggering mods.
// #define IGNORE_MOD_TAP_INTERRUPT
// #define RETRO_TAPPING_PER_KEY
// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
// #define TAPPING_FORCE_HOLD

// Apply the modifier on keys that are tapped during a short hold of a modtap
// #define PERMISSIVE_HOLD

// constant accelation
#define MK_3_SPEED
#define MK_MOMENTARY_ACCEL
#define MK_C_OFFSET_UNMOD 8
#define MK_C_INTERVAL_UNMOD 4
#define MK_C_OFFSET_1 2
#define MK_C_INTERVAL_1 8
#define MK_C_OFFSET_0 1
#define MK_C_INTERVAL_0 16
#define MK_C_OFFSET_2 10
#define MK_C_INTERVAL_2 6

// #define ONESHOT_TAP_TOGGLE 7 /* Tapping this number of times holds the key until tapped once again. */
#define ONESHOT_TIMEOUT 1000 /* Time (in ms) before the one shot key is released */

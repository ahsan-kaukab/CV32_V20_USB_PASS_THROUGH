#ifndef KITE_H

#define KITE_H

#include "stdint.h"

//#define SCROLL_LOCK_OVERRIDE 0x00
/*
 * If defined SCROLL_LOCK_OVERRIDE
 * Overrides scroll lock with specified keycode
 * Turns scroll lock into layout toggle
 * Turns scroll lock LED into keymap status indicator
 */

//#define KEYMAP_SUSPEND_MASK 0xDD
/*
 * 0x00 always remap HID keycodes
 * 0x9D remap unless modifiers other then Shift and AltGr are involved
 * 0xDD remap unless modifiers other then Shift are involved
 */

extern uint8_t disable_keymap;

void mask(uint8_t code);

uint8_t kite(uint8_t code);

#endif

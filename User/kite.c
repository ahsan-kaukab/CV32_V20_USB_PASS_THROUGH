#include "kite.h"
//#include "keymap.h"

#ifdef KEYMAP_SUSPEND_MASK
int suspend_keymap = 0;
int mods_mask_flag = 0;
int blank_kc_count = 0;
#endif

uint8_t disable_keymap = 0;

/*
 * Keymap iterator
 */

uint8_t kite( uint8_t code )
{

#ifdef SCROLL_LOCK_OVERRIDE

	if( code == 0x47)
	{
		disable_keymap = !disable_keymap;
		return SCROLL_LOCK_OVERRIDE;
	}

#endif

	if( disable_keymap )
	{
		return code;
	}

#ifdef KEYMAP_SUSPEND_MASK

	if( suspend_keymap )
	{
		if( code == 0 )
		{
			if( blank_kc_count == 6)
			{
				suspend_keymap = 0;
			}
			blank_kc_count++;
		}
		return code;
	}
	else if( mods_mask_flag && code )
	{
		suspend_keymap = 1;
		return code;
	}

#endif

//	if( code == 0)
//	{
//		return code;
//	}
//
//	int i;
//	int l = sizeof(KITE_KEYMAP)/sizeof(uint8_t);
//
//	for( i = 0; i < l/2; i++ ) {
//		if (KITE_KEYMAP[ 2*i ] == code) {
//			return KITE_KEYMAP[ 2*i + 1 ];
//		}
//	}

	return code;
}

#ifdef KEYMAP_SUSPEND_MASK
void mask( uint8_t code )
{
	mods_mask_flag = 0;

	if( code == 0 )
	{
		blank_kc_count = 1;
	}
	else
	{
		if( code & KEYMAP_SUSPEND_MASK )
		{
			mods_mask_flag = 1;
		}
		blank_kc_count = 0;
	}
}
#endif

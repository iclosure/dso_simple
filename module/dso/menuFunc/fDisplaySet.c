
#include "menuFunc.h"
#include "key.h"
#include "wave.h"
#include <string.h>


/*************************************************************
 *
 *                      static code 
 *
 *************************************************************
 */

/*************************************************************
 *
 *                      public code 
 *
 *************************************************************
 */

/************************************************************
 *
 *                        显示参数快照
 *                     [1/25/2012 robot]
 */
void* mf_SetGrid(PROJECT_INFO *info,I8 id) {
	WAVE_INFO *wave_info=info->wave_info;
	KEY_DECODE key=info->key_info->newkey.index;
	if(key == KEY_MENU_UP) {
		wave_setNetAndGrid(wave_info,++wave_info->gridrate);
	} else if(key == KEY_MENU_DOWN) {
		wave_setNetAndGrid(wave_info,--wave_info->gridrate);
	}

	return NULL;
}
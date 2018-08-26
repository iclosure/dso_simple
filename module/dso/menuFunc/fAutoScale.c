
#include "menu.h"
#include "menuFunc.h"
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
void* mfAutoScale_SelChannels(PROJECT_INFO *info,I8 id) {
	MENUUP_DATA *menu2=info->page_info->sk[2].menuup;

	statusbar_dispTriggerSource(info->statusbar,menu2->item[menu2->index].kword);

	return NULL;
}

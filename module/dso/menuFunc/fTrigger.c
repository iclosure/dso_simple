
#include "menu.h"
#include "menuFunc.h"
#include <string.h>


/*������ʽ�˵�������*/
void* mfTrigger_slop(PROJECT_INFO *info,I8 id) {
	MENUUP_DATA *menu2=info->page_info->sk[2].menuup;

	statusbar_dispTriggerType(info->statusbar,menu2->item[menu2->index].icon);

	return NULL;
}

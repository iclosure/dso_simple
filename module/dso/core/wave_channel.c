
#include "wave.h"
#include "dpo.h"
#include "thread.h"
#include "dso_confDefaults.h"
#include <stdlib.h>
#include <string.h>

/**************************************************************
 *
 *
 */
CHANNEL_INFO	chinfo		;  /*通道信息*/

/**************************************************************
 *
 *
 */
int channel_register(CHANNEL_INFO *info,U8 id) {
	info->ch[id].sort	= (t_ad*)malloc(WAVEWIN_XSIZE*sizeof(t_ad));
	info->ch[id].sample	= (t_ad*)malloc(WAVEWIN_XSIZE*sizeof(t_ad));
	info->ch[id].real	= (t_real*)malloc(WAVEWIN_XSIZE*sizeof(t_real));
	info->ch[id].status	= 1;
	if(!info->action)  /**/
		info->action	= &info->ch[id];
	if(info->ch[id].dpo.status==1 && !info->ch[id].dpo.buff) {
		info->ch[id].dpo.buff = (U8 *)malloc(info->ch[id].dpo.size);
		memset(info->ch[id].dpo.buff,0x00,info->ch[id].dpo.size);
	}
	info->validn ++;
	return 0;
}
/**************************************************************
 *
 *                  注销某通道
 */
int channel_undo(CHANNEL_INFO *info,U8 id) {
	MENUPAGE_INFO *page_info=info->parent->parent->page_info;
	free(info->ch[id].sort);
	free(info->ch[id].sample);
	free(info->ch[id].real);
	info->ch[id].sort	= NULL;
	info->ch[id].sample	= NULL;
	info->ch[id].real	= NULL;
	if(info->ch[id].dpo.buff) {
		free(info->ch[id].dpo.buff);
		info->ch[id].dpo.buff = NULL;
		wave_fresh();
		dpo_clearAll(info);
	}
	if(info->action && info->action->id == id) {
		info->action		= NULL;
		wave_fresh();
	}
	info->ch[id].status		= 0;
	info->validn --;
	if(page_info->task)
		page_info->task(page_info->parent,page_info->id);
	return 0;
}
/**************************************************************
 *
 *                       通道选择
 */
void channel_selectAction(CHANNEL_INFO *info,U8 id) {
	info->action = &info->ch[id];
}
/**************************************************************
 *
 *                       通道选择
 */
int channel_select(CHANNEL_INFO *info,U8 id) {
	thread_lock();
	if(info->ch[id].status == 0) {
		channel_register(info,id);
		info->validn++;
	} else {
		channel_undo(info,id);
		info->validn--;
	}
	thread_unlock();
	return 0;
}

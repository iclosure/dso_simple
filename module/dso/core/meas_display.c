
#include "dso.h"
#include "meas.h"
#include "thread.h"


/*****************************************************************
 *
 *                     meas task
 */
void meas_task(WAVE_INFO *info) {
	if(info->ch->validn > 0) {
		PROJECT_INFO *prj=info->parent;
		int i;
		for(i=0; i<info->ch->n; i++) {
			if(info->ch->ch[i].status == 1) {
				meas_preReady(&info->ch->ch[i].measure);
				meas_voltInfo(&info->ch->ch[i].measure);
				meas_timeInfo(&info->ch->ch[i].measure);
				thread_lock();
				param_dislpay(&info->ch->ch[i].measure);
				if(prj->page_info->task && prj->page_info->enExt==1)
					prj->page_info->task(prj,0);
				thread_unlock();
			}
		}
	}
}
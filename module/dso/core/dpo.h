
#ifndef DPO_H
#define DPO_H

#include "dso_type.h"


/***************************************************************
 *
 *                          
 */
/*DPO色温板数据*/
//COLOR dpo_color_quad[10];


/***************************************************************
 *
 *                        functions
 */
/****************************************************************
 *
 *                     灰度级式DPO
 */
void dpo_init(DPO_INFO *info);
void dpo_start(DPO_INFO *info);
void dpo_stop(DPO_INFO *info);
void dpo_add(DPO_INFO *info);
void dpo_display(DPO_INFO *info);
void dpo_clear(CHANNEL_INFO *info,U8 id);
void dpo_clearAll(CHANNEL_INFO *info);
/****************************************************************
 *
 *                     灰度级式DPO
 */




#endif /**/

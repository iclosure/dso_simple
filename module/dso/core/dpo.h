
#ifndef DPO_H
#define DPO_H

#include "dso_type.h"


/***************************************************************
 *
 *                          
 */
/*DPOɫ�°�����*/
//COLOR dpo_color_quad[10];


/***************************************************************
 *
 *                        functions
 */
/****************************************************************
 *
 *                     �Ҷȼ�ʽDPO
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
 *                     �Ҷȼ�ʽDPO
 */




#endif /**/

/****************************************************************
 *
 *                     色温式DPO
 *
 * 
 *                  [1/6/2012 lkh]
 */

#include "dpo.h"
#include "dso_confDefaults.h"
#include "GUI.h"
#include "GUI_Protected.h"
#include "LCD_Private.h"
#include <string.h>


#define DPO_NUM		(10)    /*DPO颜色等级数*/

/************************************************************
 *
 *                   DPO处理缓存
 */
/*DPO色温板数据*/
static COLOR dpo_color_quad[DPO_NUM] = {
	color_black,
	color_blue,
	color_lightblue,
	color_cyan,
	color_brown,
	color_green,
	color_yellow,
	color_orange,
	color_redorange,
	color_red,

};
#define DPO_GRAY
#if defined(DPO_GRAY)
/*DPO灰度级色谱数据*/
static COLOR dpo_color_gray[DPO_NUM] = {
	_24TO565(  0,  0,  0)	,
	_24TO565(255,255,102)	,
	_24TO565(255,255, 89)	,
	_24TO565(255,255, 76)	,
	_24TO565(255,255, 63)	,
	_24TO565(255,255, 51)	,
	_24TO565(255,255, 38)	,
	_24TO565(255,255, 25)	,
	_24TO565(255,255, 12)	,
	_24TO565(255,255,  0)	,

};
#endif
/**********************************************************
 *
 *                         functions
 */
/*初始化DPO*/
void dpo_init(DPO_INFO *info) {

}
/*启动DPO显示*/
void dpo_start(DPO_INFO *info) {

}
/*停止DPO显示*/
void dpo_stop(DPO_INFO *info) {

}
/*向DPO缓存添加式记录一组数据*/
void dpo_add(DPO_INFO *info) { 
	int x;
	for(x=0; x<WAVEWIN_XSIZE/*info->parent->sampleN*/; x++) {
		if(info->parent->sample[x] < 0 || info->parent->sample[x] >= WAVEWIN_YSIZE) continue;
		if(info->buff[info->parent->sample[x]*WAVEWIN_XSIZE+x] < DPO_NUM)
			info->buff[info->parent->sample[x]*WAVEWIN_XSIZE+x]++;  /*累计数据点出现次数*/
	}
}
/*显示*/
void dpo_display(DPO_INFO *info) {
	int x,y;
	COLOR c;
	for(y=0; y<WAVEWIN_YSIZE; y++)
		for(x=0; x<WAVEWIN_XSIZE; x++) {
			c = dpo_color_quad[info->buff[(WAVEWIN_YSIZE-y-1)*WAVEWIN_XSIZE+x]];
			if(c)  /**/
				LCD[WAVEWIN_SY+y][WAVEWIN_SX+x] = c;
		}
}
/*清缓存*/
void dpo_clear(CHANNEL_INFO *info,U8 id) {
	if(info->ch[id].dpo.buff)
		memset(info->ch[id].dpo.buff,0x00,info->ch[id].dpo.size);
}
/*清全部缓存*/
void dpo_clearAll(CHANNEL_INFO *info) {
	int i;
	for(i=0; i<info->n; i++) {
		if(info->ch[i].dpo.buff)
			memset(info->ch[i].dpo.buff,0x00,info->ch[i].dpo.size);
	}
}

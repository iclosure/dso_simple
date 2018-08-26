
#include "dso_confDefaults.h"
#include "wave.h"
#include "dpo.h"
#include "dsp.h"
#include "GUI_Protected.h"
#include "LCD_Private.h"
#include <string.h>


GUI_RECT   WaveWinArea= {WAVEWIN_SX,WAVEWIN_SY,WAVEWIN_EX,WAVEWIN_EY};  // 波形绘制窗口
static U16 WaveWinBuff[WAVEWIN_YSIZE][WAVEWIN_XSIZE];  // 波形区域缓冲存储区
				
/***********************************************
 *                static code
 ***********************************************/
static void _DrawHLine(WAVE_INFO *info,int y0, int x0, int x1) {
	for(;x0<=x1; x0++)
		WaveWinBuff[y0][x0]= info->gridcolor;
}
static void _DrawVLine(WAVE_INFO *info,int x0, int y0, int y1) {
	for(;y0<=y1; y0++)
		WaveWinBuff[y0][x0]= info->gridcolor;
}

static U16 _CalcBrightness(U8 rate) {
	U16 r,g,b;
	r= rate*31/100;
	g= rate*63/100;
	b= rate*31/100;
	return (r<<11)|(g<<5)|b;
}
static void _DrawNetAndGrid(WAVE_INFO *info) {
	int i,x,y;
	// 绘制X轴方向网格线
	for(i=1; i<WAVEWIN_XGRIDNUM; i++) {
		x = WAVEWIN_XGRIDSIZE*i-1;
		for(y=0; y<WAVEWIN_YSIZE; y++)
			WaveWinBuff[y][x]= info->gridcolor;
	}
	// 绘制Y轴方向网格线
	for(i=WAVEWIN_YGRIDNUM-1; i>=1; i--) {
		y = WAVEWIN_YGRIDSIZE*i;
		for(x=0; x<WAVEWIN_XSIZE; x++)
			WaveWinBuff[y][x]= info->gridcolor;
	}
	// 绘制X轴方向刻度线
	y= WAVEWIN_YGRIDSIZE*(WAVEWIN_YGRIDNUM/2);
	for(i=1; i<=WAVEWIN_XSCALE_TOTALNUM; i++)
		_DrawVLine(info,WAVEWIN_XSCALEINTERVAL*i-1, y-WAVEWIN_YSCALESIZE/2,y+WAVEWIN_YSCALESIZE/2);
	// 绘制Y轴方向刻度线
	x= WAVEWIN_XGRIDSIZE*(WAVEWIN_XGRIDNUM/2)-1;
	for(i=WAVEWIN_YSCALE_TOTALNUM; i>=0; i--)
		_DrawHLine(info,WAVEWIN_YSCALEINTERVAL*i, x-WAVEWIN_XSCALESIZE/2,x+WAVEWIN_XSCALESIZE/2);	
	{ // 绘制时基图[波形区域顶部中央]
		U16 color= info->gridcolor;
		info->gridcolor = 0xFC20;
		for(i=0; i<5; i++) {
			_DrawHLine(info,i, x-5+i,x-4+i);
			_DrawHLine(info,i, x+4-i,x+5-i);
		}
		WaveWinBuff[i][x]= info->gridcolor;
		info->gridcolor = color;
	}
}
/***********************************************
 *                public code
 ***********************************************/

/***************************************************************
 *                   初始化绘制波形窗口背景
 *
 */
void wave_initBk(WAVE_INFO *info) {
	int y;
	// 初始化波形区域缓冲存储区为黑色
	for(y=0; y<WAVEWIN_YSIZE; y++) {
		memset(WaveWinBuff[y], 0x00, WAVEWIN_XSIZE*size_U16);
	}
	// 绘制波形区域网格线和刻度线
	_DrawNetAndGrid(info);
	// 更新到虚拟屏对应位置
	wave_fresh();
}
/***************************************************************
 *               设置波形区窗口格亮度
 *
 */
int wave_setNetAndGrid(WAVE_INFO *info,U8 rate) { // rate-- 百分比
	if(rate >100) {
		return 2;
	} else {
		// 更新波形窗口网格颜色
		info->gridrate = rate;
		info->gridcolor = _CalcBrightness(rate);
		_DrawNetAndGrid(info);
		// 更新到虚拟屏对应位置
		wave_fresh();
		return 0;
	}
}
// 将网格设置为默认颜色
void wave_setColorToDefault(WAVE_INFO *info) {
	info->gridcolor = WAVEWIN_GRIDCOLOR;
	// 绘制波形区域网格线和刻度线
	_DrawNetAndGrid(info);
	// 更新到虚拟屏对应位置
	wave_fresh();
}
/**/
void wave_setReserveCnt(WAVE_INFO *info,I8 cnt) {
	info->wavecnt = cnt;
}
/**/
void wave_setDefaultCnt(WAVE_INFO *info) {
	info->wavecnt = 10;

	wave_initBk(info);
}
/***************************************************************
 *               在波形窗口绘制波形
 *   参数说明：pData--数据；NumPoints--数据点数
 *             xoff,yoff--坐标偏移量
 */
void wave_display(t_ad *data, int size,int xStep) {
	int i;
	GUI_RECT rect;
	GUI_GetClientRect(&rect);
	GUI_SetClipRect(&WaveWinArea);
	GUI_MoveTo(WaveWinArea.x0, WaveWinArea.y1 - data[0]);
	for(i=1; i<=WaveWinArea.x1; i++)
		GUI_DrawLineRel(xStep, data[i-1] - data[i]);
	GUI_SetClipRect(&rect);
}
// 刷新波形显示窗口
void wave_fresh(void) {
	int y;
	for(y=0; y<WAVEWIN_YSIZE; y++)
		memcpy(LCD[WAVEWIN_SY+y]+WAVEWIN_SX,WaveWinBuff[y],WAVEWIN_XSIZE*size_U16);
}
/***********************************************************
 *
 *                     wave task
 */
t_ad data1[WAVEWIN_XSIZE];
t_ad interp[WAVEWIN_XSIZE];

void wave_task_0(WAVE_INFO *info) {
	//wave_fresh();
	if(info->ch->validn > 0) {
		CHANNEL_DATA *list=info->ch->ch;
		if(++info->ch->dpocnt == 500) {
			wave_fresh();
			dpo_clearAll(info->ch);
			info->ch->dpocnt = 0;
		} else {
			U8 i;
			for(i=0; i<info->ch->n; i++) {
				if(list[i].dpo.buff) {
					wave_getCHxData(info->ch,i);
					if(list[i].sampleN < WAVEWIN_XSIZE) {  // 不足WAVEWIN_XSIZE则进行插值(暂时定为正弦插值)
						dsp_sincinterp(list[i].sample,list[i].sampleN,WAVEWIN_XSIZE);
					}
					dpo_add(&list[i].dpo);
					dpo_display(&list[i].dpo);
				}
			}
		}
	}
}

void wave_task(WAVE_INFO *info) {
	wave_fresh();
	if(info->ch->validn > 0) {
		CHANNEL_DATA *list=info->ch->ch;
		U8 i;
		for(i=0; i<info->ch->n; i++) {
			GUI_SetColor(list[i].color);
			if(list[i].sample) {
				wave_getCHxData(info->ch,i);
				GUI_SetColor(list[i].color-0xFF);
				wave_display(list[i].sample,WAVEWIN_XSIZE, WAVEWIN_XSIZE/(list[i].sampleN-1));
				if(list[i].sampleN < WAVEWIN_XSIZE) {  // 不足WAVEWIN_XSIZE则进行插值(暂时定为正弦插值)
					dsp_sincinterp(list[i].sample,list[i].sampleN,WAVEWIN_XSIZE);
				}

				GUI_SetColor(list[i].color);
				wave_display(list[i].sample,WAVEWIN_XSIZE, 1);
			}
		}
	}
}

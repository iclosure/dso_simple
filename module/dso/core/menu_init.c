
#include "menu.h"
#include "dso.h"
#include "dso_fileDir.h"
#include "myxml.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/************************************************************************/
/*                    global variables                                  */
/************************************************************************/
MENUPAGE_INFO pageinfo; /*(当前)菜单页信息*/

/********************************************************************
 * 
 *                    static code
 *
 ********************************************************************
 */
// 获取上拉菜单客户区高度
static int _CalcClientSizeY(MENUUP_DATA *menu) {
	int ySize=0;
	int cnt = menu->itemn;
	while(cnt--)
		ySize += menu_calcItemYSize(menu->item[cnt])+MENUUP_MENU_SPACE;
	return ySize+MENUUP_TOPTITLE_HEIGHT+MENUUP_FINGER_HEIGHT*2;
}
// 获取上拉菜单客户区最大宽度
static int _CalcClientSizeX(MENUUP_DATA *menu) {
	int xSize=0,sum;
	int cnt = menu->itemn;
	menu->MaxXSize = 0;
	while(cnt--) {
		MENUITEM_DATA *item=&menu->item[cnt];
		if(item->option == MENUUP_IF_MENU) {
			if(item->title) {
				sum = GUI_GetStringDistX(item->title);
				if(menu->MaxXSize < sum)
					menu->MaxXSize = sum;
				sum += 30;
			} else {
				sum = 0;
			}
			if(item->icon) {
				sum += 5;  // 5为图标与字体之间的水平间隔	
				if(item->icon->BitsPerPixel == 1) { // 二值Bitmap
					sum += item->icon->XSize;
				} else {  // 彩图有外框
					sum += MENUUP_ICONFRAME_XSIZE;
				}
			}
			if(xSize < sum)  
				xSize = sum;
		}
	}

	return xSize+30; // 30为空区
}

// 初始化指定软键的menuup.menun
static void _Initmenun(MENUUP_DATA *menu) {
	int i=menu->itemn;
	menu->menun= 0;
	while(i--) {
		if(menu->item[i].option == MENUUP_IF_MENU)
			menu->menun++;
	}
}
// 初始化指定软键的pMenuUp.Rect
static void _InitRect(SOFTKEY_DATA *sk) {
	int delta;
	GUI_RECT *rect=&sk->menuup->frame;
	if(!sk->menuup)
		return ;
	// 计算上拉菜单的x0,x1
	delta = _CalcClientSizeX(sk->menuup); 
	if(sk->id == 0 && delta > SOFTKEY_XSIZE*2/3) {
		rect->x0 = WAVEWIN_SX+5;
		rect->x1 = rect->x0 + delta-1;
	} else if(sk->id == 4) {
		rect->x1 = WAVEWIN_EX-5;
		rect->x0 = rect->x1 - delta+1;
	} else if(sk->id == 5 && delta > SOFTKEY_XSIZE*2/3) {
			rect->x1 = LCD_XSIZE-5;
			rect->x0 = rect->x1 - delta+1;
	} else {  // 按四六分[从软键中心, 左四右六]
		rect->x0= SOFTKEY_SX + (SOFTKEY_SPACE+bmsoftkeybk.XSize)*sk->id \
			+ bmsoftkeybk.XSize/2 -delta*2/5;
		rect->x1 = rect->x0 + delta-1;
	}
	// 初始化上拉菜单的y1
	rect->y1 =  MENUUP_EY;
	// 计算上拉菜单的y0
	delta= _CalcClientSizeY(sk->menuup);
	rect->y0 = rect->y1-delta+1;
	if(rect->y0 < WAVEWIN_SY)
		rect->y0 = WAVEWIN_SY;
	sk->menuup->width  = rect->x1-rect->x0+1;
	sk->menuup->height = rect->y1-rect->y0+1;
	sk->menuup->client.x0 = rect->x0 + 1;
	sk->menuup->client.y0 = rect->y0 + MENUUP_TOPTITLE_HEIGHT+MENUUP_FINGER_HEIGHT+1;
	sk->menuup->client.x1 = rect->x1 - 1;
	sk->menuup->client.y1 = rect->y1 - MENUUP_FINGER_HEIGHT-1;
}
/**********************************************************
 *
 *                 初始化菜单数据
 *  参数说明：IsContinue--表示是否紧接上次调用此函数读取文件后的位置[1:表示是,否则从头开始读取]
 */
static int _menu_init(MENUPAGE_DATA *page,FILE *fp) {
	int i,j;
	const char **list[3];
	// 初始化菜单页的 title & kword
	list[0] = &page->title;
	list[1] = &page->kword;
	myxml_readTxtString(*list,"2 title kword",fp);
	for(i=0; i<page->n; i++) {
		MENUUP_DATA *menu=page->sk[i].menuup;
		// 初始化软键的 title & ktype
		list[0] = &page->sk[i].title;
		list[1] = &page->sk[i].ktype;
		myxml_readTxtString(*list,"2 title ktype",fp);
		if(menu) {
			// 初始化上拉菜单 title
			myxml_readTxtString(&menu->title,"1 title",fp);
			// 初始化上拉菜单的 title & kword & help
			for(j=0; j<menu->itemn; j++) {
				if(menu->item[j].option==MENUUP_IF_TITLE || menu->item[j].option==MENUUP_IF_MENU) {
					myxml_readTxtString(&menu->item[j].title,"1 title",fp);
					if(menu->item[j].option == MENUUP_IF_MENU) {
						// 初始化上拉菜单选项的 title & kword & help
						list[0] = &menu->item[j].kword;
						list[1] = &menu->item[j].help;
						myxml_readTxtString(*list,"2 kword help",fp);
					}
				}
				if(menu->item[j].next) {  // 如果上拉菜单项中存在子软键
					_menu_init(menu->item[j].next, fp);
				}
			} 
			_Initmenun(menu);
			_InitRect(&page->sk[i]);
		} else if(page->sk[i].next) {
			// 初始化菜单页标题
			_menu_init(page->sk[i].next, fp);
		}
	}
	return 0;
}
/**/
static void _initOtherText(OTHERTEXT_DATA *info,FILE *fp) {
	myxml_readTxtString(&info->runstatus[0],"1 title",fp);
	myxml_readTxtString(&info->runstatus[1],"1 title",fp);
}
/********************************************************************
 * 
 *                    public code
 *
 ********************************************************************
 */
// 计算上拉菜单选项高度
int menu_calcItemYSize(MENUITEM_DATA item) {
	switch(item.option) {
	case MENUUP_IF_TITLE:
		return MENUUP_SUBTITLE_HEIGHT;
	case MENUUP_IF_MENU:
		if(item.icon) {
			if(item.icon->BitsPerPixel == 1) { // 二值Bitmap
				if(GUI_GetFontSizeY() > item.icon->YSize)
					return GUI_GetFontSizeY();
				else
					return item.icon->YSize;
			} else { // 彩图时会画外框
				return MENUUP_ICONFRAME_YSIZE;
			}
		} else {
			return GUI_GetFontSizeY();
		}
	case MENUUP_IF_SEPARATOR:
		return MENUUP_SEPARALINE_HEIGHT;
	default: return 0;
	}
}
void menu_init(MENUPAGE_INFO *info) {
	int i=0;
	FILE *fpdir,*fpfile;
	const char *language,*file;
	char dir[80];
	// 获得当前语言版本[保存在menudir.xml中]
	fpdir = myxml_ready("../resource/menu/menudir.xml");
	while(i++ <= info->langtype)
		myxml_readTxtString(&language,"1 language",fpdir);
	fclose(fpdir);
	/** ++++++++++++++++++++++++++++ **/
	fpdir = myxml_ready("../resource/menu/menufile.xml");
	for(i=0; i<GUI_COUNTOF(menu_all); i++) {
		myxml_gotoNextLine(fpdir);
		myxml_readTxtString(&file,"1 file",fpdir);
		sprintf(dir,"../resource/menu/%s/%s.xml",language,file);
		fpfile = myxml_ready(dir);
		_menu_init(menu_all[i], fpfile);
		fclose(fpfile);
	}
	// Read Others.inf
	myxml_readTxtString(&file,"1 file",fpdir);
	sprintf(dir,"../resource/menu/%s/%s.xml",language,file);
	fpfile= myxml_ready(dir);
	// 初始化其他字符串
	_initOtherText(&menuOtherText,fpfile);
	fclose(fpfile);

	fclose(fpdir);
}

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
MENUPAGE_INFO pageinfo; /*(��ǰ)�˵�ҳ��Ϣ*/

/********************************************************************
 * 
 *                    static code
 *
 ********************************************************************
 */
// ��ȡ�����˵��ͻ����߶�
static int _CalcClientSizeY(MENUUP_DATA *menu) {
	int ySize=0;
	int cnt = menu->itemn;
	while(cnt--)
		ySize += menu_calcItemYSize(menu->item[cnt])+MENUUP_MENU_SPACE;
	return ySize+MENUUP_TOPTITLE_HEIGHT+MENUUP_FINGER_HEIGHT*2;
}
// ��ȡ�����˵��ͻ��������
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
				sum += 5;  // 5Ϊͼ��������֮���ˮƽ���	
				if(item->icon->BitsPerPixel == 1) { // ��ֵBitmap
					sum += item->icon->XSize;
				} else {  // ��ͼ�����
					sum += MENUUP_ICONFRAME_XSIZE;
				}
			}
			if(xSize < sum)  
				xSize = sum;
		}
	}

	return xSize+30; // 30Ϊ����
}

// ��ʼ��ָ�������menuup.menun
static void _Initmenun(MENUUP_DATA *menu) {
	int i=menu->itemn;
	menu->menun= 0;
	while(i--) {
		if(menu->item[i].option == MENUUP_IF_MENU)
			menu->menun++;
	}
}
// ��ʼ��ָ�������pMenuUp.Rect
static void _InitRect(SOFTKEY_DATA *sk) {
	int delta;
	GUI_RECT *rect=&sk->menuup->frame;
	if(!sk->menuup)
		return ;
	// ���������˵���x0,x1
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
	} else {  // ��������[���������, ��������]
		rect->x0= SOFTKEY_SX + (SOFTKEY_SPACE+bmsoftkeybk.XSize)*sk->id \
			+ bmsoftkeybk.XSize/2 -delta*2/5;
		rect->x1 = rect->x0 + delta-1;
	}
	// ��ʼ�������˵���y1
	rect->y1 =  MENUUP_EY;
	// ���������˵���y0
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
 *                 ��ʼ���˵�����
 *  ����˵����IsContinue--��ʾ�Ƿ�����ϴε��ô˺�����ȡ�ļ����λ��[1:��ʾ��,�����ͷ��ʼ��ȡ]
 */
static int _menu_init(MENUPAGE_DATA *page,FILE *fp) {
	int i,j;
	const char **list[3];
	// ��ʼ���˵�ҳ�� title & kword
	list[0] = &page->title;
	list[1] = &page->kword;
	myxml_readTxtString(*list,"2 title kword",fp);
	for(i=0; i<page->n; i++) {
		MENUUP_DATA *menu=page->sk[i].menuup;
		// ��ʼ������� title & ktype
		list[0] = &page->sk[i].title;
		list[1] = &page->sk[i].ktype;
		myxml_readTxtString(*list,"2 title ktype",fp);
		if(menu) {
			// ��ʼ�������˵� title
			myxml_readTxtString(&menu->title,"1 title",fp);
			// ��ʼ�������˵��� title & kword & help
			for(j=0; j<menu->itemn; j++) {
				if(menu->item[j].option==MENUUP_IF_TITLE || menu->item[j].option==MENUUP_IF_MENU) {
					myxml_readTxtString(&menu->item[j].title,"1 title",fp);
					if(menu->item[j].option == MENUUP_IF_MENU) {
						// ��ʼ�������˵�ѡ��� title & kword & help
						list[0] = &menu->item[j].kword;
						list[1] = &menu->item[j].help;
						myxml_readTxtString(*list,"2 kword help",fp);
					}
				}
				if(menu->item[j].next) {  // ��������˵����д��������
					_menu_init(menu->item[j].next, fp);
				}
			} 
			_Initmenun(menu);
			_InitRect(&page->sk[i]);
		} else if(page->sk[i].next) {
			// ��ʼ���˵�ҳ����
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
// ���������˵�ѡ��߶�
int menu_calcItemYSize(MENUITEM_DATA item) {
	switch(item.option) {
	case MENUUP_IF_TITLE:
		return MENUUP_SUBTITLE_HEIGHT;
	case MENUUP_IF_MENU:
		if(item.icon) {
			if(item.icon->BitsPerPixel == 1) { // ��ֵBitmap
				if(GUI_GetFontSizeY() > item.icon->YSize)
					return GUI_GetFontSizeY();
				else
					return item.icon->YSize;
			} else { // ��ͼʱ�ử���
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
	// ��õ�ǰ���԰汾[������menudir.xml��]
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
	// ��ʼ�������ַ���
	_initOtherText(&menuOtherText,fpfile);
	fclose(fpfile);

	fclose(fpdir);
}
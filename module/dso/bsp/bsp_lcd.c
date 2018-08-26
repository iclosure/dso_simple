/*
 * ***************************************************
 *                  │╖  ╓ ╔══╗ ╥ ╔══╕│
 *                  │╚══╝ ╜  ╙ ╨ ╚══╛│
 *                          DSO
 *     Universal graphic software for embedded applications
 *
 *     (c) Copyright 2011, Unic Inc., China, Sc
 *     (c) Copyright 2011, SEGGER Microcontroller Systeme GmbH
 *  DSO is protected by international copyright laws. Knowledge of the
 *  source code may not be used to write a similar product. This file may
 *  only be used in accordance with a license and should not be redistributed
 *  in any way. We appreciate your understanding and fairness.
 * 
 *  Project : DSC--C-sources
 *  Aurthor : L.K.H.
 *  Version : V1.0 
 *  Data    : 09/20/2011
 * ---------------------------------------------------------------------
 File        : BSP_LCD.c
 Purpose     : Linux: LCD.
   ----------------------------------------------------------------------
*/

#include "LCD_Private.h"      /* private modul definitions & config */
#include "GUI_Private.h"
#include "GUIType.h"
#include <stdio.h>
#include <string.h>

#if (!WIN32)

/* for linux framebuffer */
#include <unistd.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/types.h>

//###########################################
//#include <asm/page.h>
/* PAGE_SHIFT determines the page size */
#define PAGE_SHIFT		12
#define PAGE_SIZE		(1UL << PAGE_SHIFT)
#define PAGE_MASK		(~(PAGE_SIZE-1))
//###########################################

typedef struct _FBDEV_DATA {
	int			   id;		            // 设备ID
	char	       fbname[10];   	    // LCD设备名
	U32			   offset;	            // framebuffer映射偏移量
	U16          (*pwfbmem)[LCD_XSIZE]; // framebuffer映射变量0，以双字节表示一个像素点
	U8           (*pbfbmem)[LCD_XSIZE*2]; // framebuffer映射变量0，以单字节表示一个像素点
	U16 		   ScreenWidth;	        // 屏宽
	U16 		   ScreenHeight;        // 屏高
	U32 		   screensize;		    // lCD屏幕物理尺寸(一个像素点用16位表示)
	struct fb_fix_screeninfo finfo;     // LCD 固定参数结构体*
	struct fb_var_screeninfo vinfo;     // LCD 可变s参数结构体 
} FBDEV_DATA;

// 全局液晶设备文件信息
FBDEV_DATA fbdev = {.fbname="/dev/fb0"};


/********************************************************
*          Name : fb_printinfo
*      Function : print LCD‘s basic info
*        Inputs : pfbdev -- 
*        Output : None
*   Description : None
*
*       Version : v1.0
*        Author : L.K.H.
*          date : 2011/04/08
********************************************************
#include <stdio.h>
static void fb_printinfo(void)
{
	// ###################
	// 打印fb_fix_screeninfo信息
	printf("id[16]=%s\n", fbdev.finfo.id);
	printf("smem_start=%d\n", fbdev.finfo.smem_start);
	printf("smem_len=%ld\n", fbdev.finfo.smem_len);
	printf("ktype=%d\n", fbdev.finfo.type);
	printf("type_aux=%d\n", fbdev.finfo.type_aux);
	printf("visual=%d\n", fbdev.finfo.visual);
	printf("xpanstep=%d, ypanstep=%d\n", fbdev.finfo.xpanstep, fbdev.finfo.ypanstep);
	printf("line_length=%d\n", fbdev.finfo.line_length);
	printf("mmio_start=%ld\n", fbdev.finfo.mmio_start);
	printf("mmio_len=%d\n", fbdev.finfo.mmio_len);
	printf("accel=%d\n", fbdev.finfo.accel);
	//printf("reserved=%s\n", fbdev.vinfo.reserved);
	// ###################

	// ###################
	// 打印fb_var_screeninfo信息
	printf("xres=%d, yres=%d\n", fbdev.vinfo.xres, fbdev.vinfo.yres);
	printf("xres_virtual=%d, yres_virtual=%d\n", fbdev.vinfo.xres_virtual, fbdev.vinfo.yres_virtual);
	printf("xoffset=%d, yoffset=%d\n", fbdev.vinfo.xoffset, fbdev.vinfo.yoffset);
	printf("bits_per_pixel=%d, grayscale=%d\n", fbdev.vinfo.bits_per_pixel, fbdev.vinfo.grayscale);
	printf(".red.offset=%d, .red.length=%d, .red.msb_right=%d\n", fbdev.vinfo.red.offset, fbdev.vinfo.red.length, fbdev.vinfo.red.msb_right);
	printf(".green.offset=%d, .green.length=%d, .green.msb_right=%d\n", fbdev.vinfo.green.offset, fbdev.vinfo.green.length, fbdev.vinfo.green.msb_right);
	printf(".blue.offset=%d, .blue.length=%d, .blue.msb_right=%d\n", fbdev.vinfo.blue.offset, fbdev.vinfo.blue.length, fbdev.vinfo.blue.msb_right);
	printf(".transp.offset=%d, .transp.length=%d, .transp.msb_right=%d\n", fbdev.vinfo.transp.offset, fbdev.vinfo.transp.length, fbdev.vinfo.transp.msb_right);
	printf("############################\n");
	printf("nonstd=%d\n", fbdev.vinfo.nonstd);
	printf("activate=%d\n", fbdev.vinfo.activate);
	printf("height=%d, width=%d\n", fbdev.vinfo.height,fbdev.vinfo.width);
	printf("accel_flags=%d\n", fbdev.vinfo.accel_flags);
	printf("pixclock=%d\n", fbdev.vinfo.pixclock);
	printf("left_margin=%d, right_margin=%d\n", fbdev.vinfo.left_margin,fbdev.vinfo.right_margin);
	printf("upper_margin=%d, lower_margin=%d\n", fbdev.vinfo.upper_margin,fbdev.vinfo.lower_margin);
	printf("hsync_len=%d, vsync_len=%d\n", fbdev.vinfo.hsync_len,fbdev.vinfo.vsync_len);
	printf("sync=%d\n", fbdev.vinfo.sync);
	printf("vmode=%d\n", fbdev.vinfo.vmode);
	printf("rotate=%d\n", fbdev.vinfo.rotate);
	//printf("reserved=%s\n", fbdev.vinfo.reserved);
	// ###################

	printf("screensize=%dx%d \n", fbdev.vinfo.xres,fbdev.vinfo.yres );
	printf("fbdev.offset=%ld\n", fbdev.offset);
}
*/
/*********************************************************************
*
*       LCDDEV_Init
*
* Purpose:
*   Initialises the LCD-controller.
*/
int  LCDDEV_Init(void) {
	fbdev.id = open(fbdev.fbname, O_RDWR);

    if(fbdev.id < 0) {
		printf("Error: opening %s: %d. Check kernel config\n", fbdev.fbname,fbdev.id);
		close(fbdev.id);
        return -1;
	}

    if (-1 == ioctl(fbdev.id,FBIOGET_VSCREENINFO,&(fbdev.vinfo))) {
		printf("ioctl FBIOGET_VSCREENINFO\n");
		close(fbdev.id);
		return -1;
	}

    if (-1 == ioctl(fbdev.id,FBIOGET_FSCREENINFO,&(fbdev.finfo))) {
		printf("ioctl FBIOGET_FSCREENINFO\n");
		close(fbdev.id);
	 	return -1;
	}

	/* set screensiez >: lCD屏幕物理尺寸(一个像素点用16位表示) */
	fbdev.screensize = fbdev.vinfo.xres*fbdev.vinfo.yres;  //*fbdev.vinfo.bits_per_pixel/8;
	fbdev.ScreenWidth  = fbdev.vinfo.xres;
	fbdev.ScreenHeight = fbdev.vinfo.yres;

	// map physics address to virtual address
	// fbdev.finfo.smem_start=f0000000
	fbdev.offset = (U32)(fbdev.finfo.smem_start) & (~PAGE_MASK);

	fbdev.pbfbmem= (U8 (*)[LCD_XSIZE*2])mmap(NULL, fbdev.finfo.smem_len + fbdev.offset, \
			PROT_READ | PROT_WRITE, MAP_SHARED, fbdev.id, 0);
	fbdev.pwfbmem= (U16 (*)[LCD_XSIZE])fbdev.pbfbmem; 
	
	//fb_printinfo();

	return 0;
}

/*********************************************************************
 *
 *                将虚拟屏LCD某个矩形区域映射到Framebuff显示
 */

void lcd_displayRect(LCD_RECT rect,int x0,int y0) {
	I16 y;
	for(y=y0; y<=y0+rect.y0; y++)
		memcpy(fbdev.pbfbmem[y]+x0, LCD[rect.y0+y]+rect.x0, (rect.x1-rect.x0+1) * size_U16);
}

/*********************************************************************
 *
 *                将当前指定的虚拟屏映射到Framebuff显示
 */

void lcd_display(void) {
	I16 y;
	for(y=0; y<LCD_YSIZE; y++)
		memcpy(fbdev.pbfbmem[y], LCD[y], SIZEPERLINE);
}

/*********************************************************************
 *
 *                LCD_SetOrg
 */

void LCD_SetOrg(int x, int y) { }

#else

// int  LCDDEV_Init(void) { return -1; }
// void LCD_DispRect(LCD_RECT rect,int x0,int y0) { }
// void LCD_DispLCD(void) { }
// void LCD_SetOrg(int x, int y) { }

#endif /*!WIN32*/


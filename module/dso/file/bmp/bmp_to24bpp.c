
#include "bmp.h"
#include "thread.h"
#include "LCDConf.h"
#include "LCD.h"
#include <stdlib.h>
#include <stdio.h>


// ��16λɫת��Ϊ24λɫ
RGBQUAD_INFO bpp16To24(U16 color16)
{
	RGBQUAD_INFO rgb;

	rgb.R = (color16 & 0xF800) >> 8; 
	rgb.G = (color16 & 0x07E0) >> 3;
	rgb.B = (color16 & 0x001F) << 3;
	rgb.Res= 0;

	return rgb;
}
/************************************************************
 *
 *                      publuc code
 *   ����˵����file�ɰ���·����...
 */
void bmp_to24bpp(PROJECT_INFO *info,const char *file) {
	BMPHEADER_INFO header;
	// ��ʼ��λͼͷ��Ϣ
	// ++++++++++++++++++++++++++++++++++++
	header.bfType			= 'B' | ('M'<<8);
    header.bfSize			= sizeof(BITMAPFILEHEADER_INFO) + sizeof(BITMAPINFOHEADER_INFO) + LCD_XSIZE*LCD_YSIZE*3;
    header.bfReserved1		= 0;
    header.bfReserved2		= 0;
    header.bfOffBits		= sizeof(BITMAPFILEHEADER_INFO) + sizeof(BITMAPINFOHEADER_INFO);
	// ++++++++++++++++++++++++++++++++++++
    header.biSize			= sizeof(BITMAPINFOHEADER_INFO);
    header.biWidth		    = LCD_XSIZE;
    header.biHeight		    = - LCD_YSIZE;
    header.biPlanes		    = 1;
    header.biBitCount		= 24;  // 24bpp  //@@
    header.biCompression	= BI_RGB;
    header.biSizeImage		= header.bfSize*2;
    header.biXPelsPerMeter	= 0;
    header.biYPelsPerMeter	= 0;
    header.biClrUsed		= 0;
    header.biClrImportant	= 0;
	// ++++++++++++++++++++++++++++++++++++
	// �ȴ�LOGO��ת����ʼλ��
	thread_unlock();
	while(info->infobar->cnt != 1000);
	thread_lock();
	{
		FILE *fp;
		U16 x, y;
		char str[80];

		sprintf(str,"%s%s",file,"dso_preview.bmp");
		// ����һ��BMPͼ
		fp= fopen(str, "wb");
		if(fp < 0) return;
		// ������Ϣ��BMPͼ
		fwrite(&header, sizeof(BMPHEADER_INFO), 1, fp);
		for(y=0; y<LCD_YSIZE; y++) {
			for(x=0; x<LCD_XSIZE; x++) {
				putc((LCD[y][x]&0x001F)<<3, fp); // B
				putc((LCD[y][x]&0x07E0)>>3, fp); // G
				putc((LCD[y][x]&0xF800)>>8, fp); // R
			}
		}
		fclose(fp);
	}
}

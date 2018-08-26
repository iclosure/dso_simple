#ifndef BITMAPTYPE_H_
#define BITMAPTYPE_H_

#include "integer.h"


typedef struct tagBITMAPFILEHEADERINFO	BITMAPFILEHEADER_INFO	;  /*位图的文件头结构*/
typedef struct tagBITMAPINFOHEADERINFO	BITMAPINFOHEADER_INFO	;  /*位图的文件头结构*/
typedef struct tagRGBQUADINFO			RGBQUAD_INFO			;  /*位图的调色板结构*/
typedef struct tagBMPHEADERINFO			BMPHEADER_INFO			;  /*位图头信息*/

/************************************************************
 *
 *                   bmp data type
 */
#pragma pack(1)	// 这一步至关重要，因为后面用到的读写都是块读写
// 位图的文件头结构
typedef struct tagBITMAPFILEHEADERINFO { // bmfh
	WORD	bfType;	            // 位图文件的类型, 必须为"BM"(0x4D42) 
	DWORD	bfSize;			    // 位图文件的大小，以字节为单位
	WORD	bfReserved1;		// 位图文件保留字，必须为0
	WORD	bfReserved2;		// 位图文件保留字，必须为0
	DWORD	bfOffBits;			// 位图数据的起始位置，以相对于位图文件头的偏移量表示，以字节为单位
} tBITMAPFILEHEADERINFO;

// 位图的信息头结构
typedef struct tagBITMAPINFOHEADERINFO { // bmih
	DWORD	biSize;				// 位图文件的大小，以字节为单位
	LONG	biWidth;			// 位图的宽度，以像素为单位
	LONG	biHeight;			// 位图的高度，以像素为单位
	WORD	biPlanes;			// 目标设备的级别，必须为1
	WORD	biBitCount;			// 每个像素所需的位数，必须是1(双色),4(16色)，8(256色)或24(真彩色)之一
	DWORD	biCompression;		// 位图压缩类型，必须是 0(不压缩),1(BI_RLE8压缩类型)或2(BI_RLE4压缩类型)之一
	DWORD	biSizeImage;		// 位图的大小，以字节为单位
	LONG	biXPelsPerMeter;	// 位图水平分辨率
	LONG	biYPelsPerMeter;	// 位图垂直分辨率
	DWORD	biClrUsed;			// 位图实际使用的颜色表中的颜色数
	DWORD	biClrImportant;		// 位图显示过程中重要的颜色数
} tBITMAPINFOHEADER_INFO;
// 位图的调色板结构
typedef struct tagRGBQUADINFO { // rgbq
    BYTE    R;
    BYTE    G;
    BYTE    B;
    BYTE    Res;
} tRGBQUAD_INFO;
// 位图头信息
/* windows style*/
typedef struct tagBMPHEADERINFO{
	/* BITMAPFILEHEADER*/
	WORD	bfType;
	DWORD	bfSize;
	WORD	bfReserved1;
	WORD	bfReserved2;
	DWORD	bfOffBits;
	/* BITMAPINFOHEADER*/
	DWORD	biSize;
	LONG	biWidth;
	LONG	biHeight;
	WORD	biPlanes;
	WORD	biBitCount;
	DWORD	biCompression;
	DWORD	biSizeImage;
	LONG	biXPelsPerMeter;
	LONG	biYPelsPerMeter;
	DWORD	biClrUsed;
	DWORD	biClrImportant;
} tBMPHEADER_INFO;
#pragma pack()



#endif /*BITMAPTYPE_H_*/
